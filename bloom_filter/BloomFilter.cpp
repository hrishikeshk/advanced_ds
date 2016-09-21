#include "TypeDefs.h"
#include "Consts.h"

#include "Common_Funcs.h"

#include "BloomFilter.h"

BloomFilter::BloomFilter(UInt32 size_in_bytes, UInt8 num_hashes): m_k(num_hashes){
	v_assert(m_k < max_hash_functions, "Too many hash functions specified");
	m_bm.resize(size_in_bytes);
}

BloomFilter::~BloomFilter(){
}

UInt32* BloomFilter::compute_hash(const std::vector<UInt8>& data){
	auto len = data.size();
	UInt64 hash = fnv_offset_basis;
	for(UInt32 i = 0; i < len; ++i){
		hash ^= data[i];
		hash *= fnv_prime;
	}
        UInt32 upper = (hash >> 32);
	UInt32 lower = (hash & 0xffffffff);
	UInt32 size = m_bm.get_size();
	for(UInt8 i = 0; i < m_k; ++i){
		indices[i] = (upper + i * lower) % size;
	}
	return indices;
}

Bool BloomFilter::add(const std::vector<UInt8>& data){
	UInt32* indxs = compute_hash(data);
	Bool result = true;
	for(UInt32 i = 0; i < m_k; ++i){
		result &= m_bm.mark(indxs[i]);
	}
	return result;
}

Bool BloomFilter::is_added(const std::vector<UInt8>& data){
	UInt32* indxs = compute_hash(data);
	for(UInt32 i = 0; i < m_k; ++i){
		if(! (m_bm.is_marked(indxs[i])) )
			return false;
	}
	return true;
}

