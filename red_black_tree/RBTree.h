#ifndef AUG_RBTREE
#define AUG_RBTREE

#include <tuple>

#include "TypeDefs.h"
#include "Consts.h"

#include "Key.h"
#include "Common_Funcs.h"

#include "RBNode.h"
#include "Augment.h"
#include "Dependent_Includes.h"

namespace Func_RBTree{

	template<size_t n, typename... Others>
	class ApplyFuncToTuple{
		public:
		void apply(Operation op, 
			   std::tuple<Others...>& tup, 
			   UInt32 pos,
			   UInt32 root,
			   std::function<RBNode(UInt32)> accessor_func){

			std::get<n>(tup).fix(op, pos, root, accessor_func);
			ApplyFuncToTuple<n - 1, Others...> af;
			af.apply(op, tup, pos, root, accessor_func);
		}
	};

	template<typename... Others>
	class ApplyFuncToTuple<0, Others...>{
		public:
		void apply(Operation op, 
			   std::tuple<Others...>& tup, 
			   UInt32 pos,
			   UInt32 root,
			   std::function<RBNode(UInt32)> accessor_func){

			std::get<0>(tup).fix(op, pos, root, accessor_func);
		}
	};
}

template<typename... Others>
class AugRBTree{

        UInt32 m_root;
        std::vector<RBNode> m_nodes;
        UInt32 m_first_free;
	std::tuple<Others...> m_tuple;

        public:

        AugRBTree();

        Bool insert(const Key& k, UInt32 offset); // Create Key that has your inserted value, and pass the offset at which you added it in your container...

        Bool find(const Key& k, UInt32& ref); // Find the offset 'ref' within your container, where the value within the Key is stored ... Fast ...

        Bool remove(const Key& k); // Remove the value within the Key from the Index ...

        void traverse_inorder(std::vector<UInt32>& o_contents); // Gets you a list of offsets into your container such that they are ordered ...

        AugRBTree(const AugRBTree&) = delete;
        AugRBTree& operator=(const AugRBTree&) = delete;

	template<UInt32 ta, typename Index>
	auto augment_accessor(Index i){
		return std::get<ta>(m_tuple).aug_val_at(i);
	}

        private:

        void rb_insert_fixup(const UInt32& new_node);

        void rb_remove_fixup(UInt32 child_succ);

        void left_rotate(const UInt32& node);

        void right_rotate(const UInt32& node);

        UInt32 tree_successor(const UInt32& node) const;

        void inorder(UInt32 root, std::vector<UInt32>& o_contents);

	Bool find_detailed(const Key& k, UInt32& ref, UInt32& pos, Operation op);
};


template<typename... Others>
AugRBTree<Others...>::AugRBTree():m_root(m_nil), m_first_free(maxUInt32){
	RBNode nil_node; // Sentinel
	nil_node.m_color = Color::BLACK;
	m_nodes.push_back(nil_node);
}

template<typename... Others>
void AugRBTree<Others...>::traverse_inorder(std::vector<UInt32>& o_contents){

	o_contents.clear();

	inorder(m_root, o_contents);
}

template<typename... Others>
void AugRBTree<Others...>::inorder(UInt32 root, std::vector<UInt32>& o_contents){

	if(root != m_nil){
		inorder(m_nodes[root].m_left, o_contents);

		o_contents.push_back(m_nodes[root].m_payload);

		inorder(m_nodes[root].m_right, o_contents);
	}
}

template<typename... Others>
Bool AugRBTree<Others...>::find(const Key& k, UInt32& ref){
	UInt32 pos;
	return find_detailed(k, ref, pos, FIND);
}

template<typename... Others>
Bool AugRBTree<Others...>::find_detailed(const Key& k, UInt32& ref, UInt32& pos, Operation op){

	ref = m_nil;
        if(m_root == m_nil)
                return false;

        pos = m_root;

        UInt32 exp = m_nodes[pos].m_payload;
        RBStatus rs = k.compare(exp);

        while(rs != RBStatus::EQUAL){

                if(rs == RBStatus::LESS){
                        pos = m_nodes[pos].m_left;
                }
                else{
                        pos = m_nodes[pos].m_right;
                }
                if(pos == m_nil)
                        return false;
                rs = k.compare(m_nodes[pos].m_payload);
        }

        ref = m_nodes[pos].m_payload;
        return true;
}

template<typename... Others>
Bool AugRBTree<Others...>::insert(const Key& k, UInt32 offset){

	RBNode new_node;
	UInt32 lead = m_root;
	RBStatus rs = RBStatus::EQUAL;
	while(lead != m_nil){
		new_node.m_parent = lead;
		rs = k.compare(m_nodes[lead].m_payload);
		if(rs == RBStatus::LESS){
			lead = m_nodes[lead].m_left;
		}
		else if(rs == RBStatus::MORE){
			lead = m_nodes[lead].m_right;
		}
		else{
			return false; // Already inserted, return failure to uniquely insert.
		}
	}

	new_node.m_payload = offset; // This is the offset into the external container where the element is already stored...

	UInt32 new_node_offset;
	if(m_first_free != maxUInt32){
		new_node_offset = m_first_free;
		m_first_free = m_nodes[m_first_free].m_next_free;
		m_nodes[new_node_offset] = new_node;
	}
	else{
		new_node_offset = m_nodes.size();
		m_nodes.push_back(new_node);
	}
	if(rs == RBStatus::MORE){
		v_assert(m_nodes[new_node.m_parent].m_right == m_nil, "Incorrect child links in the parent to which insertion is being done");
		if(new_node.m_parent != m_nil)
			m_nodes[new_node.m_parent].m_right = new_node_offset;
	}
	else if(rs == RBStatus::LESS){
		v_assert(m_nodes[new_node.m_parent].m_left == m_nil, "Incorrect child links in the parent to which insertion is being done");
		if(new_node.m_parent != m_nil)
			m_nodes[new_node.m_parent].m_left = new_node_offset;
	}
	if(m_root == m_nil){
		m_root = new_node_offset;
	}

	Func_RBTree::ApplyFuncToTuple<sizeof...(Others) - 1, Others...> af;
	std::vector<RBNode>* p_nodes = &m_nodes;

	af.apply(INSERT,
		 m_tuple,
		 new_node_offset,
		 m_root,
		 [p_nodes](UInt32 offset){ return (*p_nodes)[offset]; }
	);
	// Severe perf regression found after this addition. TODO fix...

	rb_insert_fixup(new_node_offset);
	return true;
}

template<typename... Others>
void AugRBTree<Others...>::rb_insert_fixup(const UInt32& new_node){

	UInt32 curr_node = new_node;
	UInt32 par = m_nodes[curr_node].m_parent;

	while(m_nodes[par].m_color == Color::RED){
		UInt32 gpar = m_nodes[par].m_parent;
		UInt32 uncle;
		if(par == m_nodes[gpar].m_left){
			uncle = m_nodes[gpar].m_right;
			if(m_nodes[uncle].m_color == Color::RED){
				m_nodes[par].m_color = Color::BLACK;
				m_nodes[uncle].m_color = Color::BLACK;
				m_nodes[gpar].m_color = Color::RED;
				curr_node = gpar;
			}
			else{
				if(curr_node == m_nodes[par].m_right){
					curr_node = par;
					left_rotate(curr_node);
					par = m_nodes[curr_node].m_parent;
					gpar = m_nodes[par].m_parent;
				}
				m_nodes[par].m_color = Color::BLACK;
				m_nodes[gpar].m_color = Color::RED;
				right_rotate(gpar);
			}
		}
		else{
			uncle = m_nodes[gpar].m_left;
			if(m_nodes[uncle].m_color == Color::RED){
				m_nodes[par].m_color = Color::BLACK;
				m_nodes[uncle].m_color = Color::BLACK;
				m_nodes[gpar].m_color = Color::RED;
				curr_node = gpar;
			}
			else{
				if(curr_node == m_nodes[par].m_left){
					curr_node = par;
					right_rotate(curr_node);
					par = m_nodes[curr_node].m_parent;
					gpar = m_nodes[par].m_parent;
				}
				m_nodes[par].m_color = Color::BLACK;
				m_nodes[gpar].m_color = Color::RED;
				left_rotate(gpar);
			}

		}
		par = m_nodes[curr_node].m_parent;
	}

	m_nodes[m_root].m_color = Color::BLACK;
}

template<typename... Others>
Bool AugRBTree<Others...>::remove(const Key& k){

	UInt32 del_node, ref;
	Bool ret = find_detailed(k, ref, del_node, REMOVE);
	if(ret == false || del_node == m_nil)
		return false;

	UInt32 node_succ, child_succ;
	if(m_nodes[del_node].m_left == m_nil || 
		m_nodes[del_node].m_right == m_nil){

		node_succ = del_node;
	}
	else{
		node_succ = tree_successor(del_node);
	}
	v_assert(node_succ != m_nil, "Delete : Unexpected : node_succ offset is NIL");

	Func_RBTree::ApplyFuncToTuple<sizeof...(Others) - 1, Others...> af;
	std::vector<RBNode>* p_nodes = &m_nodes;

	af.apply(REMOVE,
		 m_tuple,
		 node_succ,
		 m_root,
		 [p_nodes](UInt32 offset){ return (*p_nodes)[offset]; }
	);
	// Severe perf regression found after this addition. TODO fix...

	if(m_nodes[node_succ].m_left != m_nil){
		child_succ = m_nodes[node_succ].m_left;
	}
	else{
		child_succ = m_nodes[node_succ].m_right;
	}
	if(child_succ != m_nil){
		m_nodes[child_succ].m_parent = m_nodes[node_succ].m_parent;
	}
	if(m_nodes[node_succ].m_parent == m_nil){
		m_root = child_succ;
	}
	else{
		if(node_succ == m_nodes[m_nodes[node_succ].m_parent].m_left){
			m_nodes[m_nodes[node_succ].m_parent].m_left = child_succ;
		}
		else{
			m_nodes[m_nodes[node_succ].m_parent].m_right = child_succ;
		}
	}
	if(node_succ != del_node){
		m_nodes[del_node].m_payload = m_nodes[node_succ].m_payload;
	}
	m_nodes[node_succ].m_next_free = m_first_free;
	m_first_free = node_succ;

	if(m_nodes[node_succ].m_color == Color::BLACK){
		rb_remove_fixup(child_succ);
	}
	return true;
}

template<typename... Others>
void AugRBTree<Others...>::rb_remove_fixup(UInt32 child_successor){
	UInt32 child_succ = child_successor;
	while(child_succ != m_nil && child_succ != m_root && m_nodes[child_succ].m_color == Color::BLACK){
		UInt32 par = m_nodes[child_succ].m_parent;
		if(child_succ == m_nodes[par].m_left){
			UInt32 sibling = m_nodes[par].m_right;
			if(m_nodes[sibling].m_color == Color::RED){
				m_nodes[sibling].m_color = Color::BLACK;
				m_nodes[par].m_color = Color::RED;
				left_rotate(par);
				sibling = m_nodes[m_nodes[child_succ].m_parent].m_right;
			}
			UInt32 sibling_left = m_nodes[sibling].m_left;
			UInt32 sibling_right = m_nodes[sibling].m_right;
			if(m_nodes[sibling_left].m_color == Color::BLACK && m_nodes[sibling_right].m_color == Color::BLACK){
				m_nodes[sibling].m_color = Color::RED;
				child_succ = m_nodes[child_succ].m_parent;
			}
			else if(m_nodes[sibling_right].m_color == Color::BLACK){
				m_nodes[sibling_left].m_color = Color::BLACK;
				m_nodes[sibling].m_color = Color::RED;
				right_rotate(sibling);
				par = m_nodes[child_succ].m_parent;
				sibling = m_nodes[par].m_right;
			}
			m_nodes[sibling].m_color = m_nodes[par].m_color;
			m_nodes[par].m_color = Color::BLACK;
			m_nodes[m_nodes[sibling].m_right].m_color = Color::BLACK;
			left_rotate(par);
			child_succ = m_root;
		}
		else{
			UInt32 sibling = m_nodes[par].m_left;
			if(m_nodes[sibling].m_color == Color::RED){
				m_nodes[sibling].m_color = Color::BLACK;
				m_nodes[par].m_color = Color::RED;
				right_rotate(par);
				sibling = m_nodes[m_nodes[child_succ].m_parent].m_left;
			}
			UInt32 sibling_left = m_nodes[sibling].m_left;
			UInt32 sibling_right = m_nodes[sibling].m_right;
			if(m_nodes[sibling_left].m_color == Color::BLACK && m_nodes[sibling_right].m_color == Color::BLACK){
				m_nodes[sibling].m_color = Color::RED;
				child_succ = m_nodes[child_succ].m_parent;
			}
			else if(m_nodes[sibling_left].m_color == Color::BLACK){
				m_nodes[sibling_right].m_color = Color::BLACK;
				m_nodes[sibling].m_color = Color::RED;
				left_rotate(sibling);
				par = m_nodes[child_succ].m_parent;
				sibling = m_nodes[par].m_left;
			}
			m_nodes[sibling].m_color = m_nodes[par].m_color;
			m_nodes[par].m_color = Color::BLACK;
			m_nodes[m_nodes[sibling].m_left].m_color = Color::BLACK;
			right_rotate(par);
			child_succ = m_root;
		}
	}
	m_nodes[child_succ].m_color = Color::BLACK;
}

template<typename... Others>
void AugRBTree<Others...>::left_rotate(const UInt32& node){

	if(node == m_nil)
		return;
	UInt32 right_curr = m_nodes[node].m_right;
	if(right_curr == m_nil)
		return;

	Func_RBTree::ApplyFuncToTuple<sizeof...(Others) - 1, Others...> af;
	std::vector<RBNode>* p_nodes = &m_nodes;

	af.apply(LEFT_ROTATE,
		 m_tuple,
		 node,
		 m_root,
		 [p_nodes](UInt32 offset){ return (*p_nodes)[offset]; }
	);
	// Severe perf regression found after this addition. TODO fix...

	m_nodes[node].m_right = m_nodes[right_curr].m_left;

	UInt32 left_right_curr = m_nodes[right_curr].m_left;
	if(left_right_curr != m_nil){
		m_nodes[left_right_curr].m_parent = node;
	}
	m_nodes[right_curr].m_parent = m_nodes[node].m_parent;

	if(m_nodes[node].m_parent == m_nil){
		m_root = right_curr;
	}
	else{
		if(node == m_nodes[m_nodes[node].m_parent].m_left){
			m_nodes[m_nodes[node].m_parent].m_left = right_curr;
		}
		else{
			m_nodes[m_nodes[node].m_parent].m_right = right_curr;
		}
	}
	m_nodes[right_curr].m_left = node;
	m_nodes[node].m_parent = right_curr;
}

template<typename... Others>
void AugRBTree<Others...>::right_rotate(const UInt32& node){

	if(node == m_nil)
		return;
	UInt32 left_curr = m_nodes[node].m_left;
	if(left_curr == m_nil)
		return;

	Func_RBTree::ApplyFuncToTuple<sizeof...(Others) - 1, Others...> af;
	std::vector<RBNode>* p_nodes = &m_nodes;

	af.apply(RIGHT_ROTATE,
		 m_tuple,
		 node,
		 m_root,
		 [p_nodes](UInt32 offset){ return (*p_nodes)[offset]; }
	);
	// Severe perf regression found after this addition. TODO fix...

	m_nodes[node].m_left = m_nodes[left_curr].m_right;

	UInt32 right_left_curr = m_nodes[left_curr].m_right;
	if(right_left_curr != m_nil){
		m_nodes[right_left_curr].m_parent = node;
	}
	m_nodes[left_curr].m_parent = m_nodes[node].m_parent;

	if(m_nodes[node].m_parent == m_nil){
		m_root = left_curr;
	}
	else{
		if(node == m_nodes[m_nodes[node].m_parent].m_left){
			m_nodes[m_nodes[node].m_parent].m_left = left_curr;
		}
		else{
			m_nodes[m_nodes[node].m_parent].m_right = left_curr;
		}
	}
	m_nodes[left_curr].m_right = node;
	m_nodes[node].m_parent = left_curr;
}

template<typename... Others>
UInt32 AugRBTree<Others...>::tree_successor(const UInt32& node) const{

	if(node == m_nil)
		return node;
	UInt32 candidate = m_nodes[node].m_right;
	if(candidate != m_nil){
		UInt32 next = m_nodes[candidate].m_left;
		while(next != m_nil){
			candidate = next;
			next = m_nodes[candidate].m_left;
		}
	}
	else{ // Should never hit this in case of this limited RBTree usage ....
		v_assert(false, "Unexpected usage or context for tree_successor() ... ");
		UInt32 curr_node = node;
		candidate = m_nodes[curr_node].m_parent;
		while(candidate != m_nil){
			if(m_nodes[candidate].m_left == curr_node){
				return candidate;
			}
			curr_node = candidate;
			candidate = m_nodes[candidate].m_parent;
		}
	}
	return candidate;
}

using RBTree = AugRBTree<NullAugType>;
//using RBTree = AugRBTree<AugmentCount>;

#endif

