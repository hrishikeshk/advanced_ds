#include "TypeDefs.h"
#include "Consts.h"

#include "Common_Funcs.h"

#include "BloomFilter.h"

BloomFilter::BloomFilter(UInt32 size_in_bytes, UInt8 num_hashes): m_bm(size_in_bytes), m_k(num_hashes){
}

BloomFilter::~BloomFilter(){
}

Bool BloomFilter::add(UInt8 data[]){
	return true;
}

Bool BloomFilter::is_added(UInt8 data[]) const{
	return true;
}

