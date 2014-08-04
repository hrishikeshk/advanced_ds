#include "TypeDefs.h"
#include "Consts.h"

#include "Common_Funcs.h"

#include "BitMap.h"

BitMap::BitMap(UInt32 size_in_bytes): m_bytes(size_in_bytes), m_buffer(new UInt8[size_in_bytes]){

}

BitMap::~BitMap(){
	delete[] m_buffer;
}

Bool BitMap::mark(UInt32 offset){

	return false;
}

Bool BitMap::is_marked(UInt32 offset) const{

	return false;
}

Bool BitMap::unmark(UInt32 offset){

	return false;
}

