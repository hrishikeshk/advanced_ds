#ifndef _RBTREE_
#define _RBTREE_

#include "TypeDefs.h"
#include "Consts.h"
#include "RBNode.h"
#include "Key.h"

#include "Dependent_Includes.h"

class RBTree{

	UInt32 m_root;
	std::vector<RBNode> m_nodes;
	UInt32 m_first_free;
	
	public:
	
	RBTree();

	Bool insert_element(const Key& k, const UInt32 ref);

	Bool find_element(const Key& k, UInt32& ref) const;

	Bool delete_element(const Key& k);

	void traverse_inorder(std::vector<UInt32>& o_contents);

	private:

	void rb_insert_fixup(const UInt32& new_node);

	void rb_delete_fixup(UInt32 child_succ);

	void left_rotate(const UInt32& node);

	void right_rotate(const UInt32& node);

	UInt32 tree_successor(const UInt32& node) const;

	void inorder(UInt32 root, std::vector<UInt32>& o_contents);
};

#endif

