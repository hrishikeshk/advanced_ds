#include "TypeDefs.h"
#include "Consts.h"

#include "Key.h"
#include "Common_Funcs.h"

#include "RBTree.h"

RBTree::RBTree():m_root(m_nil), m_first_free(maxUInt32){
	RBNode nil_node; // Sentinel
	nil_node.m_color = BLACK;
	m_nodes.push_back(nil_node);
}

void RBTree::traverse_inorder(std::vector<UInt32>& o_contents){

	o_contents.clear();

	inorder(m_root, o_contents);
}

void RBTree::inorder(UInt32 root, std::vector<UInt32>& o_contents){

	if(root != m_nil){
		inorder(m_nodes[root].m_left, o_contents);

		o_contents.push_back(m_nodes[root].m_payload);

		inorder(m_nodes[root].m_right, o_contents);
	}
}

Bool RBTree::find(const Key& k, UInt32& ref) const{
	UInt32 pos;
	return find_detailed(k, ref, pos);
}

Bool RBTree::find_detailed(const Key& k, UInt32& ref, UInt32& pos) const{

	ref = m_nil;
        if(m_root == m_nil)
                return false;

        UInt32 exp = m_nodes[m_root].m_payload;
        RBStatus rs = k.compare(exp);

        pos = m_root;

        while(rs != EQUAL){
                if(rs == LESS){
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

Bool RBTree::insert(const Key& k, const UInt32 ref){

	RBNode new_node;
	UInt32 lead = m_root;
	RBStatus rs = EQUAL;
	while(lead != m_nil){
		new_node.m_parent = lead;
		rs = k.compare(m_nodes[lead].m_payload);
		if(rs == LESS){
			lead = m_nodes[lead].m_left;
		}
		else if(rs == MORE){
			lead = m_nodes[lead].m_right;
		}
		else{
			return false; // Already inserted, return failure to uniquely insert.
		}
	}
	new_node.m_payload = ref;
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
	if(rs == MORE){
		v_assert(m_nodes[new_node.m_parent].m_right == m_nil, "Incorrect child links in the parent to which insertion is being done");
		if(new_node.m_parent != m_nil)
			m_nodes[new_node.m_parent].m_right = new_node_offset;
	}
	else if(rs == LESS){
		v_assert(m_nodes[new_node.m_parent].m_left == m_nil, "Incorrect child links in the parent to which insertion is being done");
		if(new_node.m_parent != m_nil)
			m_nodes[new_node.m_parent].m_left = new_node_offset;
	}
	if(m_root == m_nil){
		m_root = new_node_offset;
	}
	rb_insert_fixup(new_node_offset);
	return true;
}

void RBTree::rb_insert_fixup(const UInt32& new_node){

	UInt32 curr_node = new_node;
	UInt32 par = m_nodes[curr_node].m_parent;

	while(m_nodes[par].m_color == RED){
		UInt32 gpar = m_nodes[par].m_parent;
		UInt32 uncle;
		if(par == m_nodes[gpar].m_left){
			uncle = m_nodes[gpar].m_right;
			if(m_nodes[uncle].m_color == RED){
				m_nodes[par].m_color = BLACK;
				m_nodes[uncle].m_color = BLACK;
				m_nodes[gpar].m_color = RED;
				curr_node = gpar;
			}
			else{
				if(curr_node == m_nodes[par].m_right){
					curr_node = par;
					left_rotate(curr_node);
					par = m_nodes[curr_node].m_parent;
					gpar = m_nodes[par].m_parent;
				}
				m_nodes[par].m_color = BLACK;
				m_nodes[gpar].m_color = RED;
				right_rotate(gpar);
			}
		}
		else{
			uncle = m_nodes[gpar].m_left;
			if(m_nodes[uncle].m_color == RED){
				m_nodes[par].m_color = BLACK;
				m_nodes[uncle].m_color = BLACK;
				m_nodes[gpar].m_color = RED;
				curr_node = gpar;
			}
			else{
				if(curr_node == m_nodes[par].m_left){
					curr_node = par;
					right_rotate(curr_node);
					par = m_nodes[curr_node].m_parent;
					gpar = m_nodes[par].m_parent;
				}
				m_nodes[par].m_color = BLACK;
				m_nodes[gpar].m_color = RED;
				left_rotate(gpar);
			}

		}
		par = m_nodes[curr_node].m_parent;
	}

	m_nodes[m_root].m_color = BLACK;
}

Bool RBTree::remove(const Key& k){

	UInt32 del_node, ref;
	Bool ret = find_detailed(k, ref, del_node);
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

	if(m_nodes[node_succ].m_color == BLACK){
		rb_remove_fixup(child_succ);
	}
	return true;
}

void RBTree::rb_remove_fixup(UInt32 child_successor){
	UInt32 child_succ = child_successor;
	while(child_succ != m_nil && child_succ != m_root && m_nodes[child_succ].m_color == BLACK){
		UInt32 par = m_nodes[child_succ].m_parent;
		if(child_succ == m_nodes[par].m_left){
			UInt32 sibling = m_nodes[par].m_right;
			if(m_nodes[sibling].m_color == RED){
				m_nodes[sibling].m_color = BLACK;
				m_nodes[par].m_color = RED;
				left_rotate(par);
				sibling = m_nodes[m_nodes[child_succ].m_parent].m_right;
			}
			UInt32 sibling_left = m_nodes[sibling].m_left;
			UInt32 sibling_right = m_nodes[sibling].m_right;
			if(m_nodes[sibling_left].m_color == BLACK && m_nodes[sibling_right].m_color == BLACK){
				m_nodes[sibling].m_color = RED;
				child_succ = m_nodes[child_succ].m_parent;
			}
			else if(m_nodes[sibling_right].m_color == BLACK){
				m_nodes[sibling_left].m_color = BLACK;
				m_nodes[sibling].m_color = RED;
				right_rotate(sibling);
				par = m_nodes[child_succ].m_parent;
				sibling = m_nodes[par].m_right;
			}
			m_nodes[sibling].m_color = m_nodes[par].m_color;
			m_nodes[par].m_color = BLACK;
			m_nodes[m_nodes[sibling].m_right].m_color = BLACK;
			left_rotate(par);
			child_succ = m_root;
		}
		else{
			UInt32 sibling = m_nodes[par].m_left;
			if(m_nodes[sibling].m_color == RED){
				m_nodes[sibling].m_color = BLACK;
				m_nodes[par].m_color = RED;
				right_rotate(par);
				sibling = m_nodes[m_nodes[child_succ].m_parent].m_left;
			}
			UInt32 sibling_left = m_nodes[sibling].m_left;
			UInt32 sibling_right = m_nodes[sibling].m_right;
			if(m_nodes[sibling_left].m_color == BLACK && m_nodes[sibling_right].m_color == BLACK){
				m_nodes[sibling].m_color = RED;
				child_succ = m_nodes[child_succ].m_parent;
			}
			else if(m_nodes[sibling_left].m_color == BLACK){
				m_nodes[sibling_right].m_color = BLACK;
				m_nodes[sibling].m_color = RED;
				left_rotate(sibling);
				par = m_nodes[child_succ].m_parent;
				sibling = m_nodes[par].m_left;
			}
			m_nodes[sibling].m_color = m_nodes[par].m_color;
			m_nodes[par].m_color = BLACK;
			m_nodes[m_nodes[sibling].m_left].m_color = BLACK;
			right_rotate(par);
			child_succ = m_root;
		}
	}
	m_nodes[child_succ].m_color = BLACK;
}

void RBTree::left_rotate(const UInt32& node){

	if(node == m_nil)
		return;
	UInt32 right_curr = m_nodes[node].m_right;
	if(right_curr == m_nil)
		return;
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

void RBTree::right_rotate(const UInt32& node){

	if(node == m_nil)
		return;
	UInt32 left_curr = m_nodes[node].m_left;
	if(left_curr == m_nil)
		return;
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

UInt32 RBTree::tree_successor(const UInt32& node) const{

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
	else{
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

