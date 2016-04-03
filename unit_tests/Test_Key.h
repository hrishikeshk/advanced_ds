#ifndef TEST_KEY_RBTREE
#define TEST_KEY_RBTREE

#include <vector>
#include "Key.h"

class Test_Key : public Key{
	public:
	RBStatus compare(const UInt32 cmp_ox) const{
		return RBStatus::EQUAL;
	}
};

class Test_Sorted_Order_Key : public Key{
	const std::vector<UInt32>& 	m_array;
	UInt32				m_value; // Has a defined ordering and is a unique identifier of the objects within the container
	public:
	Test_Sorted_Order_Key(const std::vector<UInt32>& arr, UInt32 value): m_array(arr), m_value(value){
	}
	RBStatus compare(const UInt32 cmp_ox) const{
		if(m_value < m_array[cmp_ox]){
			return RBStatus::LESS;
		}
		else if(m_value > m_array[cmp_ox]){
			return RBStatus::MORE;
		}
		return RBStatus::EQUAL;
	}
};

template <typename Compound_Object>
class Test_Compound_Object_Key : public Key {
        const std::vector<Compound_Object>&     m_array;
        Compound_Object&                        m_value; // Has a defined ordering and is a unique identifier of the objects within the container
        public:
        Test_Compound_Object_Key(const std::vector<Compound_Object>& arr, Compound_Object& value): m_array(arr), m_value(value){
        }
        RBStatus compare(const UInt32 cmp_ox) const{
                if(m_value < m_array[cmp_ox]){
                        return RBStatus::LESS;
                }
                else if(m_value > m_array[cmp_ox]){
                        return RBStatus::MORE;
                }
                return RBStatus::EQUAL;
        }
};

#endif

