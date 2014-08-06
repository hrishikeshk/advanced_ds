#ifndef _BLOOM_FILTER_
#define _BLOOM_FILTER_

#include "TypeDefs.h"
#include "Consts.h"

#include "Dependent_Includes.h"

class BitMap{

	public:
	
	BitMap(UInt32 size_in_bytes);

	~BitMap();

	Bool mark(UInt32 offset); // This offset will be marked, it should be within range of the map size

	Bool is_marked(UInt32 offset) const; // Simple read-only check 

	Bool unmark(UInt32 offset); // No issues if the offset is already unmarked

	private:
		UInt32 m_bytes;

		UInt8*	m_buffer;
};

#endif

