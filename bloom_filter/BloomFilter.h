#ifndef _BLOOM_FILTER_
#define _BLOOM_FILTER_

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

	Bool add(UInt8 data[]);
	Bool is_added(UInt8 data[]) const;

	private:
		BitMap	m_bm;
		UInt8 m_k;
};

#endif

