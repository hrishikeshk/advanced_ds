#ifndef TEST_KEY_RBTREE
#define TEST_KEY_RBTREE

#include "Key.h"

class Test_Key : public Key{

	public:
	
	RBStatus compare(const UInt32 cmp_ox) const{
		return EQUAL;
	}
};

#endif

