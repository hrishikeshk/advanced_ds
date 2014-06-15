#ifndef _RBNODE_
#define _RBNODE_

#include "TypeDefs.h"
#include "Consts.h"

enum Color { BLACK, RED };

const UInt32 m_nil_ox = 0;

struct RBNode{

	UInt32 m_parent_ox;
	UInt32 m_left_ox;
	UInt32 m_right_ox;
	UInt32 m_next_free_ox;
	UInt32 m_payload;
	Color m_color;

	RBNode():m_parent_ox(m_nil_ox), m_left_ox(m_nil_ox), m_right_ox(m_nil_ox), m_next_free_ox(maxUInt32), m_payload(maxUInt32), m_color(RED){
	}
};

#endif

