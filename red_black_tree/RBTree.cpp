#include "TypeDefs.h"
#include "Consts.h"

#include "Key.h"
#include "Common_Funcs.h"

#include "RBTree.h"

RBTree::RBTree():m_root_ox(m_nil_ox), m_first_free_ox(maxUInt32){
	RBNode nil_node; // Sentinel
	nil_node.m_color = BLACK;
	m_nodes.push_back(nil_node);
}

Bool RBTree::find_element(const Key& k, UInt32& ref_ox) const{

	ref_ox = m_nil_ox;
	if(m_root_ox == m_nil_ox)
		return false;

	UInt32 exp_ox = m_root_ox;
	RBStatus rs = k.compare(exp_ox);

	while(rs != EQUAL){
		if(rs == LESS){
			exp_ox = m_nodes[exp_ox].m_left_ox;
		}
		else{
			exp_ox = m_nodes[exp_ox].m_right_ox;
		}
		if(exp_ox == m_nil_ox)
			return false;
		rs = k.compare(exp_ox);
	}
	ref_ox = m_nodes[exp_ox].m_payload;
	return true;
}

Bool RBTree::insert_element(const Key& k, const UInt32 ref_ox){

	RBNode new_node;
	UInt32 lead_ox = m_root_ox;
	RBStatus rs = EQUAL;
	while(lead_ox != m_nil_ox){
		new_node.m_parent_ox = lead_ox;
		rs = k.compare(lead_ox);
		if(rs == MORE){
			lead_ox = m_nodes[lead_ox].m_right_ox;
		}
		else if(rs == LESS){
			lead_ox = m_nodes[lead_ox].m_left_ox;
		}
		else{
			return false; // Already inserted, return failure to uniquely insert.
		}
	}
	new_node.m_payload = ref_ox;
	UInt32 new_node_ox;
	if(m_first_free_ox != maxUInt32){
		new_node_ox = m_first_free_ox;
		m_first_free_ox = m_nodes[m_first_free_ox].m_next_free_ox;
		m_nodes[new_node_ox] = new_node;
	}
	else{
		new_node_ox = m_nodes.size();
		m_nodes.push_back(new_node);
	}
	if(rs == MORE){
		v_assert(m_nodes[new_node.m_parent_ox].m_right_ox == maxUInt32, "Incorrect child links in the parent to which insertion is being done");
		if(new_node.m_parent_ox != m_nil_ox)
			m_nodes[new_node.m_parent_ox].m_right_ox = new_node_ox;
	}
	else if(rs == LESS){
		v_assert(m_nodes[new_node.m_parent_ox].m_left_ox == maxUInt32, "Incorrect child links in the parent to which insertion is being done");
		if(new_node.m_parent_ox != m_nil_ox)
			m_nodes[new_node.m_parent_ox].m_left_ox = new_node_ox;
	}
	if(m_root_ox == m_nil_ox){
		m_root_ox = new_node_ox;
	}
	rb_insert_fixup(new_node_ox);
	return true;
}

void RBTree::rb_insert_fixup(const UInt32& new_node_ox){

	UInt32 curr_node_ox = new_node_ox;
	UInt32 par_ox = m_nodes[curr_node_ox].m_parent_ox;
	UInt32 gpar_ox = m_nodes[par_ox].m_parent_ox;

	while(m_nodes[par_ox].m_color == RED){
		UInt32 uncle_ox;
		if(par_ox == m_nodes[gpar_ox].m_left_ox){
			uncle_ox = m_nodes[gpar_ox].m_right_ox;
			if(uncle_ox != maxUInt32 && m_nodes[uncle_ox].m_color == RED){
				m_nodes[par_ox].m_color = BLACK;
				m_nodes[uncle_ox].m_color = BLACK;
				m_nodes[gpar_ox].m_color = RED;
				curr_node_ox = gpar_ox;
			}
			else{
				if(curr_node_ox == m_nodes[par_ox].m_right_ox){
					curr_node_ox = par_ox;
					left_rotate(curr_node_ox);
				}
				m_nodes[par_ox].m_color = BLACK;
				m_nodes[gpar_ox].m_color = RED;
				right_rotate(gpar_ox);
			}
		}
		else{
			uncle_ox = m_nodes[gpar_ox].m_left_ox;
			if(uncle_ox != maxUInt32 && m_nodes[uncle_ox].m_color == RED){
				m_nodes[par_ox].m_color = BLACK;
				m_nodes[uncle_ox].m_color = BLACK;
				m_nodes[gpar_ox].m_color = RED;
				curr_node_ox = gpar_ox;
			}
			else{
				if(curr_node_ox == m_nodes[par_ox].m_left_ox){
					curr_node_ox = par_ox;
					right_rotate(curr_node_ox);
				}
				m_nodes[par_ox].m_color = BLACK;
				m_nodes[gpar_ox].m_color = RED;
				left_rotate(gpar_ox);
			}

		}
		if(curr_node_ox == maxUInt32)
			break;
		par_ox = m_nodes[curr_node_ox].m_parent_ox;
		if(par_ox == maxUInt32)
			break;
		gpar_ox = m_nodes[par_ox].m_parent_ox;
	}

	m_nodes[m_root_ox].m_color = BLACK;
}

Bool RBTree::delete_element(const Key& k){

	UInt32 del_node_ox;
	Bool ret = find_element(k, del_node_ox);
	if(ret == false || del_node_ox == maxUInt32)
		return false;

	UInt32 node_succ_ox, child_succ_ox;
	if(m_nodes[del_node_ox].m_left_ox == maxUInt32 || 
		m_nodes[del_node_ox].m_right_ox == maxUInt32){

		node_succ_ox = del_node_ox;
	}
	else{
		node_succ_ox = tree_successor(del_node_ox);
	}
	v_assert(node_succ_ox != maxUInt32, "Unexpected : node_succ offset is NIL");
	
	if(m_nodes[node_succ_ox].m_left_ox != maxUInt32){
		child_succ_ox = m_nodes[node_succ_ox].m_left_ox;
	}
	else{
		child_succ_ox = m_nodes[node_succ_ox].m_right_ox;
	}
	if(child_succ_ox != maxUInt32){
		m_nodes[child_succ_ox].m_parent_ox = m_nodes[node_succ_ox].m_parent_ox;
	}
	if(m_nodes[node_succ_ox].m_parent_ox == maxUInt32){
		m_root_ox = child_succ_ox;
	}
	else{
		if(node_succ_ox == m_nodes[m_nodes[node_succ_ox].m_parent_ox].m_left_ox){
			m_nodes[m_nodes[node_succ_ox].m_parent_ox].m_left_ox = child_succ_ox;
		}
		else{
			m_nodes[m_nodes[node_succ_ox].m_parent_ox].m_right_ox = child_succ_ox;
		}
	}
	if(node_succ_ox != del_node_ox){
		m_nodes[del_node_ox].m_payload = m_nodes[node_succ_ox].m_payload;
		m_nodes[node_succ_ox].m_next_free_ox = m_first_free_ox;
		m_first_free_ox = node_succ_ox;
	}
	if(m_nodes[node_succ_ox].m_color == BLACK){
		rb_delete_fixup(child_succ_ox);
	}
	return true;
}

void RBTree::rb_delete_fixup(UInt32 child_succ_ox){
	while(child_succ_ox != maxUInt32 && child_succ_ox != m_root_ox && m_nodes[child_succ_ox].m_color == BLACK){
		UInt32 par_ox = m_nodes[child_succ_ox].m_parent_ox;
		if(child_succ_ox == m_nodes[par_ox].m_left_ox){
			UInt32 sibling_ox = m_nodes[par_ox].m_right_ox;
			if(m_nodes[sibling_ox].m_color == RED){
				m_nodes[sibling_ox].m_color = BLACK;
				m_nodes[par_ox].m_color = RED;
				left_rotate(par_ox);
				sibling_ox = m_nodes[m_nodes[child_succ_ox].m_parent_ox].m_right_ox;
			}
			UInt32 sibling_left_ox = m_nodes[sibling_ox].m_left_ox;
			UInt32 sibling_right_ox = m_nodes[sibling_ox].m_right_ox;
			if(m_nodes[sibling_left_ox].m_color == BLACK && m_nodes[sibling_right_ox].m_color == BLACK){
				m_nodes[sibling_ox].m_color = RED;
				child_succ_ox = m_nodes[child_succ_ox].m_parent_ox;
			}
			else if(m_nodes[sibling_right_ox].m_color == BLACK){
				m_nodes[sibling_left_ox].m_color = BLACK;
				m_nodes[sibling_ox].m_color = RED;
				right_rotate(sibling_ox);
				par_ox = m_nodes[child_succ_ox].m_parent_ox;
				sibling_ox = m_nodes[par_ox].m_right_ox;
				m_nodes[sibling_ox].m_color = m_nodes[par_ox].m_color;
				m_nodes[par_ox].m_color = BLACK;
				m_nodes[m_nodes[sibling_ox].m_right_ox].m_color = BLACK;
				left_rotate(par_ox);
				child_succ_ox = m_root_ox;
			}
		}
		else{
			UInt32 sibling_ox = m_nodes[par_ox].m_left_ox;
			if(m_nodes[sibling_ox].m_color == RED){
				m_nodes[sibling_ox].m_color = BLACK;
				m_nodes[par_ox].m_color = RED;
				right_rotate(par_ox);
				sibling_ox = m_nodes[m_nodes[child_succ_ox].m_parent_ox].m_left_ox;
			}
			UInt32 sibling_left_ox = m_nodes[sibling_ox].m_left_ox;
			UInt32 sibling_right_ox = m_nodes[sibling_ox].m_right_ox;
			if(m_nodes[sibling_left_ox].m_color == BLACK && m_nodes[sibling_right_ox].m_color == BLACK){
				m_nodes[sibling_ox].m_color = RED;
				child_succ_ox = m_nodes[child_succ_ox].m_parent_ox;
			}
			else if(m_nodes[sibling_left_ox].m_color == BLACK){
				m_nodes[sibling_right_ox].m_color = BLACK;
				m_nodes[sibling_ox].m_color = RED;
				left_rotate(sibling_ox);
				par_ox = m_nodes[child_succ_ox].m_parent_ox;
				sibling_ox = m_nodes[par_ox].m_left_ox;
				m_nodes[sibling_ox].m_color = m_nodes[par_ox].m_color;
				m_nodes[par_ox].m_color = BLACK;
				m_nodes[m_nodes[sibling_ox].m_left_ox].m_color = BLACK;
				right_rotate(par_ox);
				child_succ_ox = m_root_ox;
			}
		}
	}
	m_nodes[child_succ_ox].m_color = BLACK;
}

void RBTree::left_rotate(const UInt32& node_ox){

	if(node_ox == maxUInt32)
		return;
	UInt32 right_curr_ox = m_nodes[node_ox].m_right_ox;
	if(right_curr_ox == maxUInt32)
		return;
	m_nodes[node_ox].m_right_ox = m_nodes[right_curr_ox].m_left_ox;

	UInt32 left_right_curr_ox = m_nodes[right_curr_ox].m_left_ox;
	if(left_right_curr_ox != maxUInt32){
		m_nodes[left_right_curr_ox].m_parent_ox = node_ox;
	}
	m_nodes[right_curr_ox].m_parent_ox = m_nodes[node_ox].m_parent_ox;

	if(m_nodes[node_ox].m_parent_ox == maxUInt32){
		m_root_ox = right_curr_ox;
	}
	else{
		if(node_ox == m_nodes[m_nodes[node_ox].m_parent_ox].m_left_ox){
			m_nodes[m_nodes[node_ox].m_parent_ox].m_left_ox = right_curr_ox;
		}
		else{
			m_nodes[m_nodes[node_ox].m_parent_ox].m_right_ox = right_curr_ox;
		}
	}
	m_nodes[right_curr_ox].m_left_ox = node_ox;
	m_nodes[node_ox].m_parent_ox = right_curr_ox;
}

void RBTree::right_rotate(const UInt32& node_ox){

	if(node_ox == maxUInt32)
		return;
	UInt32 left_curr_ox = m_nodes[node_ox].m_left_ox;
	if(left_curr_ox == maxUInt32)
		return;
	m_nodes[node_ox].m_left_ox = m_nodes[left_curr_ox].m_right_ox;

	UInt32 right_left_curr_ox = m_nodes[left_curr_ox].m_right_ox;
	if(right_left_curr_ox != maxUInt32){
		m_nodes[right_left_curr_ox].m_parent_ox = node_ox;
	}
	m_nodes[left_curr_ox].m_parent_ox = m_nodes[node_ox].m_parent_ox;

	if(m_nodes[node_ox].m_parent_ox == maxUInt32){
		m_root_ox = left_curr_ox;
	}
	else{
		if(node_ox == m_nodes[m_nodes[node_ox].m_parent_ox].m_left_ox){
			m_nodes[m_nodes[node_ox].m_parent_ox].m_left_ox = left_curr_ox;
		}
		else{
			m_nodes[m_nodes[node_ox].m_parent_ox].m_right_ox = left_curr_ox;
		}
	}
	m_nodes[left_curr_ox].m_right_ox = node_ox;
	m_nodes[node_ox].m_parent_ox = left_curr_ox;
}

UInt32 RBTree::tree_successor(const UInt32& node_ox) const{

	if(node_ox == maxUInt32)
		return node_ox;
	UInt32 candidate_ox = m_nodes[node_ox].m_right_ox;
	if(candidate_ox != maxUInt32){
		UInt32 next_ox = m_nodes[candidate_ox].m_left_ox;
		while(next_ox != maxUInt32){
			candidate_ox = next_ox;
			next_ox = m_nodes[candidate_ox].m_left_ox;
		}
	}
	else{
		UInt32 curr_node_ox = node_ox;
		candidate_ox = m_nodes[curr_node_ox].m_parent_ox;
		while(candidate_ox != maxUInt32){
			if(m_nodes[candidate_ox].m_left_ox == curr_node_ox){
				return candidate_ox;
			}
			curr_node_ox = candidate_ox;
			candidate_ox = m_nodes[candidate_ox].m_parent_ox;
		}
	}
	return candidate_ox;
}

