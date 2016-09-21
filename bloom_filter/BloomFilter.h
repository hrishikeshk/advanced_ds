#ifndef _BLOOM_FILTER_
#define _BLOOM_FILTER_

#include <vector>

#include "TypeDefs.h"
#include "Consts.h"
#include "Dependent_Includes.h"

#include "BitMap.h"

class BloomFilter{

	public:
	
	BloomFilter(UInt32 size_in_bytes, UInt8 num_hash);
	~BloomFilter();
	BloomFilter(BloomFilter&) = delete;
	BloomFilter& operator=(const BloomFilter&) = delete;

	Bool add(const std::vector<UInt8>& data);
	Bool is_added(const std::vector<UInt8>& data);

	private:
	BitMap	m_bm;
	UInt8 m_k;
	const UInt64 fnv_offset_basis = 14695981039346656037;
	const UInt64 fnv_prime = 1099511628211;

	UInt32 indices[max_hash_functions];

	UInt32* compute_hash(const std::vector<UInt8>&);
};

#endif

