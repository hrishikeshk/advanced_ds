#ifndef AUGMENT_RBTREE
#define AUGMENT_RBTREE

#include <functional>
#include <vector>

#include "Common_Funcs.h"
#include "RBNode.h"

class NullAugType{
	public:
		void fix(Operation op, 
			 UInt32 pos, 
			 UInt32 root, 
			 std::function<RBNode(UInt32)>& accessor_func){

		}
};

class AugmentCount{
	std::vector<UInt32> m_child_counts;
	    // Ordering as per Operations for avoiding a conditional dispatch of each functions...
            std::function<void(UInt32, UInt32, std::function<RBNode(UInt32)>)> func_array[5] = {
		[this](UInt32 pos, UInt32 root, std::function<RBNode(UInt32)> accessor_func){ // FIND
			
		},
		[this](UInt32 pos, UInt32 root, std::function<RBNode(UInt32)> accessor_func){ // INSERT
			if(m_child_counts.size() <= pos){
				m_child_counts.push_back(1);
				v_assert(m_child_counts.size() == (pos + 1), "Out of sync child count vector with main vector");
			}
			else{
				m_child_counts[pos] = 0; 
			}
			while(pos != root){
				const RBNode& node = accessor_func(pos);
				v_assert(m_child_counts.size() > pos, "Out of bounds access into child counts vector");
				m_child_counts[pos]++;
				pos = node.m_parent;
			}
			m_child_counts[pos]++;
		},
		[this](UInt32 pos, UInt32 root, std::function<RBNode(UInt32)> accessor_func){ // REMOVE
			while(pos != root){
				const RBNode& node = accessor_func(pos);
				v_assert(m_child_counts.size() > pos, "Out of bounds access into child counts vector");
				m_child_counts[pos]--;
				pos = node.m_parent;
			}
			m_child_counts[pos]--;
		},
		[this](UInt32 pos, UInt32 root, std::function<RBNode(UInt32)> accessor_func){ // LEFT_ROTATE
			const RBNode& curr_node = accessor_func(pos);
			UInt32 right_of_pos = curr_node.m_right;
			v_assert(right_of_pos != m_nil, "Unexpected, to have right child NIL in case of left-rotate");

			UInt32 left_right_of_pos = m_nil;

			const RBNode& right_curr_node = accessor_func(right_of_pos);
			left_right_of_pos = right_curr_node.m_left;
			
			UInt32 new_pos_count = m_child_counts[pos] - m_child_counts[right_of_pos];
			if(left_right_of_pos != m_nil){
				new_pos_count += m_child_counts[left_right_of_pos];
			}
			m_child_counts[pos] += (new_pos_count);

			m_child_counts[right_of_pos] = new_pos_count;
			UInt32 right_right_of_pos = right_curr_node.m_right;
			if(right_right_of_pos != m_nil){
				m_child_counts[right_of_pos] += m_child_counts[right_right_of_pos];
			}
		},
		[this](UInt32 pos, UInt32 root, std::function<RBNode(UInt32)> accessor_func){ // RIGHT_ROTATE
			const RBNode& curr_node = accessor_func(pos);
			UInt32 left_of_pos = curr_node.m_left;
			v_assert(left_of_pos != m_nil, "Unexpected, to have left child NIL in case of right-rotate");

			UInt32 right_left_of_pos = m_nil;

			const RBNode& left_curr_node = accessor_func(left_of_pos);
			right_left_of_pos = left_curr_node.m_right;
			
			UInt32 new_pos_count = m_child_counts[pos] - m_child_counts[left_of_pos];
			if(right_left_of_pos != m_nil){
				new_pos_count += m_child_counts[right_left_of_pos];
			}
			m_child_counts[pos] += (new_pos_count);

			m_child_counts[left_of_pos] = new_pos_count;
			UInt32 left_left_of_pos = left_curr_node.m_left;
			if(left_left_of_pos != m_nil){
				m_child_counts[left_of_pos] += m_child_counts[left_left_of_pos];
			}
		}
	     };

	public:
	    AugmentCount(){
		m_child_counts.push_back(m_nil);
	    }
	    
	   // AugmentCount(AugmentCount&) = delete;
	   // AugmentCount& operator=(const AugmentCount&) = delete;

	    void fix(Operation op, 
		 UInt32 pos, 
		 UInt32 root, 
		 std::function<RBNode(UInt32)>& accessor_func){

		 func_array[op](pos, root, accessor_func); // Avoided any conditions...
	    }

	    UInt32 aug_val_at(UInt32 offset){
		v_assert(offset < m_child_counts.size(), "Out-of-bounds access for fetching subtree size at some position");
		return m_child_counts[offset];
	    }
};

#endif

