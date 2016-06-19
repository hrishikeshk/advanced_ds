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
                UInt32 aug_val_at(UInt32 offset){
                    return 0;
                }
                Bool validate(UInt32 pos, UInt32 root, std::function<RBNode(UInt32)>& accessor_func){
                    return true;
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
				v_assert(m_child_counts.size() == pos, "Out of sync child count vector with main vector");
				m_child_counts.push_back(0);
			}
			else{
				m_child_counts[pos] = 0; 
			}
                        if(pos == root)
                            return;
			const RBNode& node = accessor_func(pos);
			pos = node.m_parent;
			while(pos != root){
				v_assert(m_child_counts.size() > pos, "Insertion: Out of bounds access into child counts vector");
				m_child_counts[pos]++;
				const RBNode& node2 = accessor_func(pos);
				pos = node2.m_parent;
			}
			m_child_counts[pos]++;
		},
		[this](UInt32 pos, UInt32 root, std::function<RBNode(UInt32)> accessor_func){ // REMOVE
			while(pos != root){
				v_assert(m_child_counts.size() > pos, "Deletion: Out of bounds access into child counts vector");
				m_child_counts[pos]--;
				const RBNode& node = accessor_func(pos);
				pos = node.m_parent;
			}
			m_child_counts[pos]--;
		},
		[this](UInt32 pos, UInt32 root, std::function<RBNode(UInt32)> accessor_func){ // LEFT_ROTATE

                        const RBNode& c = accessor_func(pos);
                        UInt32 orc = c.m_right;
                        v_assert(orc != m_nil, "Unexpected, to have right child NIL in case of left-rotate");
                        const RBNode& rc = accessor_func(orc);

                        UInt32 olrc = rc.m_left;
                        UInt32 curr_ct = 0;
                        if(olrc != m_nil){
                            curr_ct = 1 + m_child_counts[olrc];
                        }
                        UInt32 lc = c.m_left;
                        if(lc != m_nil){
                            curr_ct += (1 + m_child_counts[lc]);
                        }
                        m_child_counts[pos] = curr_ct;

                        UInt32 right_ct = 0;
                        UInt32 orrc = rc.m_right;
                        if(orrc != m_nil){
                            right_ct = 1 + m_child_counts[orrc];
                        }
                        right_ct += curr_ct + 1;
                        m_child_counts[orc] = right_ct;
		},
		[this](UInt32 pos, UInt32 root, std::function<RBNode(UInt32)> accessor_func){ // RIGHT_ROTATE

                        const RBNode& c = accessor_func(pos);
                        UInt32 olc = c.m_left;
                        v_assert(olc != m_nil, "Unexpected, to have left child NIL in case of right-rotate");
                        const RBNode& lc = accessor_func(olc);

                        UInt32 orlc = lc.m_right;
                        UInt32 curr_ct = 0;
                        if(orlc != m_nil){
                            curr_ct = 1 + m_child_counts[orlc];
                        }
                        UInt32 rc = c.m_right;
                        if(rc != m_nil){
                            curr_ct += (1 + m_child_counts[rc]);
                        }
                        m_child_counts[pos] = curr_ct;

                        UInt32 left_ct = 0;
                        UInt32 ollc = lc.m_left;
                        if(ollc != m_nil){
                            left_ct = 1 + m_child_counts[ollc];
                        }
                        left_ct += curr_ct + 1;
                        m_child_counts[olc] = left_ct;
		}
	     };

	public:
	    AugmentCount(){
		m_child_counts.push_back(m_nil);
	    }
	    
	    //AugmentCount(AugmentCount&) = delete;
	    // TODO - This Copying needs to be prevented. PERF Problem here...
	    

	    AugmentCount& operator=(const AugmentCount&) = delete;

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

            Bool validate(UInt32 pos, UInt32 root, std::function<RBNode(UInt32)>& accessor_func){
                v_assert(m_child_counts.size() > pos, "Out-of-bounds access in child count vector: Validation failed");
                const RBNode& curr = accessor_func(pos);
                UInt32 left = curr.m_left;
                UInt32 right = curr.m_right;
                UInt32 child_count = 0;
                if(left != m_nil){
                    child_count += m_child_counts[left] + 1;
                }

                if(right != m_nil){
                    child_count += m_child_counts[right] + 1;
                }
                v_assert(child_count == m_child_counts[pos], "Mismatch in child counts: Augmented child counter test failed");
                return (child_count == m_child_counts[pos]);
            }
};

#endif

