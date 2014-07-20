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

	Bool insert(const Key& k, const UInt32 ref);

	Bool find(const Key& k, UInt32& ref) const;

	Bool remove(const Key& k);

	void traverse_inorder(std::vector<UInt32>& o_contents);

	private:

	void rb_insert_fixup(const UInt32& new_node);

	void rb_remove_fixup(UInt32 child_succ);

	void left_rotate(const UInt32& node);

	void right_rotate(const UInt32& node);

	UInt32 tree_successor(const UInt32& node) const;

	void inorder(UInt32 root, std::vector<UInt32>& o_contents);

	Bool find_detailed(const Key& k, UInt32& ref, UInt32& pos) const;
};

#endif

