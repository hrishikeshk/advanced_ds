#ifndef _BM_BLOOM_FILTER_
#define _BM_BLOOM_FILTER_

#include "TypeDefs.h"
#include "Consts.h"
#include "Common_Funcs.h"

#include "Dependent_Includes.h"

class BitMap{

	public:
	
	BitMap();
	BitMap(UInt32 size_in_bytes);
	~BitMap();

	Bool resize(UInt32 size_in_bytes);

	inline UInt32 get_size() const{
		return m_bytes;
	}

	inline Bool mark(UInt32 offset){
        	UInt32 byte_num = offset / byte_size;
        	if(byte_num >= m_bytes){
                	return v_assert(false, "mark() : input offset beyond map size");
        	}
        	UInt8 bit_num = offset % byte_size;
        	UInt8 mask = (1 << bit_num);
        	m_buffer[byte_num] |= mask;
        	return true;
	}

	inline Bool is_marked(UInt32 offset) const{
        	UInt32 byte_num = offset / byte_size;
        	if(byte_num >= m_bytes){
                	return v_assert(false, "is_marked() : input offset beyond map size");
        	}
        	UInt8 bit_num = offset % byte_size;
	        UInt8 mask = (1 << bit_num);
        	return (m_buffer[byte_num] & mask);
	}

	inline Bool unmark(UInt32 offset){
        	UInt32 byte_num = offset / byte_size;
	        v_assert(byte_num < m_bytes, "unmark() : input offset beyond map size");
        	if(byte_num >= m_bytes){
                	return false;
	        }
        	UInt8 bit_num = offset % byte_size;
	        UInt8 mask = (1 << bit_num);
        	m_buffer[byte_num] &= (~mask);
	        return true;
	}

	private:
		UInt32 m_bytes;
		UInt8*	m_buffer;

		const UInt8 byte_size = 8;
};

#endif

