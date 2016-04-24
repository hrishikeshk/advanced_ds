#include <string.h>

#include "TypeDefs.h"
#include "Consts.h"
#include "Common_Funcs.h"

#include "BitMap.h"

const UInt8 byte_size = 8;

BitMap::BitMap(UInt32 size_in_bytes): m_bytes(size_in_bytes), m_buffer(new UInt8[size_in_bytes]){
	memset(m_buffer, 0, m_bytes);
}

BitMap::~BitMap(){
	delete[] m_buffer;
}

Bool BitMap::mark(UInt32 offset){
	UInt32 byte_num = offset / byte_size;
	v_assert(byte_num < m_bytes, "mark() : input offset beyond map size");
	if(byte_num >= m_bytes){
		return false;
	}
	UInt8 bit_num = offset % byte_size;
	UInt8 mask = (1 << bit_num);
	m_buffer[byte_num] |= mask;
	return true;
}

Bool BitMap::is_marked(UInt32 offset) const{
	UInt32 byte_num = offset / byte_size;
	v_assert(byte_num < m_bytes, "is_marked() : input offset beyond map size");
	if(byte_num >= m_bytes){
		return false;
	}
	UInt8 bit_num = offset % byte_size;
	UInt8 mask = (1 << bit_num);
	return (m_buffer[byte_num] & mask);
}

Bool BitMap::unmark(UInt32 offset){
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

