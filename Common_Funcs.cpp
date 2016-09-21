#ifndef _COMMON_FUNCS_
#define _COMMON_FUNCS_

#include <assert.h>
#include <iostream>
#include <string>

#include "TypeDefs.h"
#include "Consts.h"
#include "Common_Funcs.h"

UInt32 maxUInt32 = 0x7fffffff;

Bool v_assert(Bool val, const std::string& mesg){
#ifdef _DEBUG_BUILD_
	assert(val);
#else
	if(val == false){
		std::cerr << "*********** \n FATAL problem detected\n ***********\n";
		std::cerr << mesg << "\n";
		//throw mesg;
	}
#endif
	return val;
}

#endif

