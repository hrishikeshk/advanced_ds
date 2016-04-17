#ifndef _RBNODE_
#define _RBNODE_

#include "TypeDefs.h"
#include "Consts.h"

enum Operation {FIND = 0, INSERT, REMOVE, LEFT_ROTATE, RIGHT_ROTATE};

enum class Color : char { BLACK, RED };

const UInt32 m_nil = 0;

struct RBNode{

	UInt32 m_parent;
	UInt32 m_left;
	UInt32 m_right;
	UInt32 m_next_free;
	UInt32 m_payload;
	Color m_color;

	RBNode():m_parent(m_nil), m_left(m_nil), m_right(m_nil), m_next_free(maxUInt32), m_payload(maxUInt32), m_color(Color::RED){
	}
};

#endif

