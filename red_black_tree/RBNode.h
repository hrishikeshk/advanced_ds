#ifndef _RBNODE_
#define _RBNODE_

#include "TypeDefs.h"
#include "Consts.h"

enum Color { BLACK, RED };

struct RBNode{

	UInt32 m_parent_ox;
	UInt32 m_left_ox;
	UInt32 m_right_ox;
	UInt32 m_next_free_ox;
	UInt32 m_payload;
	Color m_color;

	RBNode():m_parent_ox(maxUInt32), m_left_ox(maxUInt32), m_right_ox(maxUInt32), m_next_free_ox(maxUInt32), m_payload(maxUInt32), m_color(BLACK){
	}
};

#endif

