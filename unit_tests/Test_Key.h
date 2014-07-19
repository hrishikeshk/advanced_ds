#ifndef TEST_KEY_RBTREE
#define TEST_KEY_RBTREE

#include <vector>
#include "Key.h"

class Test_Key : public Key{

	public:
	
	RBStatus compare(const UInt32 cmp_ox) const{
		return EQUAL;
	}
};

class Test_Sorted_Order_Key : public Key{
	const std::vector<UInt32>& 	m_array;
	UInt32			m_offset;
	public:
	Test_Sorted_Order_Key(const std::vector<UInt32>& arr, UInt32 offset):m_array(arr), m_offset(offset){
	}
	RBStatus compare(const UInt32 cmp_ox) const{
		if(m_array[m_offset] < m_array[cmp_ox]){
			return LESS;
		}
		else if(m_array[m_offset] > m_array[cmp_ox]){
			return MORE;
		}
		return EQUAL;
	}
};


#endif

