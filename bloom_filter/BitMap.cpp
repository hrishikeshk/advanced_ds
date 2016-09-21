#include <string.h>

#include "TypeDefs.h"
#include "Consts.h"
#include "Common_Funcs.h"

#include "BitMap.h"

BitMap::BitMap(): m_bytes(0), m_buffer(nullptr){

}

BitMap::BitMap(UInt32 size_in_bytes): m_bytes(size_in_bytes){
	try{
		m_buffer = new UInt8[size_in_bytes];
	}
	catch(std::bad_alloc& ba){
		v_assert(false, "Failed to allocate memory in BitMap()");
		throw ba;
	}
	memset(m_buffer, 0, m_bytes);
}

BitMap::~BitMap(){
	delete[] m_buffer;
}

Bool BitMap::resize(UInt32 size_in_bytes){
	UInt8* pTemp = nullptr;
	try{
		pTemp = new UInt8[size_in_bytes];
	}
	catch(std::bad_alloc& ba){
		return v_assert(false, "Failed to allocate memory in resize()");
	}
	if(m_buffer != nullptr){
		UInt32 limit = size_in_bytes;
		if(limit > m_bytes){
			memset(pTemp + m_bytes, 0, size_in_bytes - m_bytes);
			limit = m_bytes;
		}
		for(UInt32 i = 0; i < limit; ++i){
			pTemp[i] = m_buffer[i];
		}
		m_bytes = size_in_bytes;
		delete[] m_buffer;
	}
	else{
		m_bytes = size_in_bytes;
		memset(pTemp, 0, m_bytes);
	}
	m_buffer = pTemp;
	return true;
}

