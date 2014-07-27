#ifndef _TEST_UTILS_
#define _TEST_UTILS_

#include <string>
#include <vector>
#include <string.h>

class Compound_Test{
	public:
		std::string	m_name;
		UInt32		m_age;

	bool operator<(const Compound_Test& co){
		int str_cmp = strcmp(m_name.c_str(), co.m_name.c_str());
		if(str_cmp == 0 && m_age == co.m_age)
			return false;
		if(str_cmp < 0)
			return false;
		else if(str_cmp > 0)
			return true;
		else if(m_age < co.m_age)
			return true;
		return false;
	}

	bool operator>(const Compound_Test& co){
		if( m_name == co.m_name && m_age == co.m_age)
			return false;
		return !(operator<(co));
	}
};

void permute_and_call(  const std::vector<UInt32>& original, 
			std::vector<UInt32>& target, 
			UInt32 num_filled, 
			void (*fp)(const std::vector<UInt32>&)
		    ){

	if(num_filled == original.size()){
		fp(target);
	}
	else{
		for(UInt32 i = 0; i < original.size(); ++i){
			bool to_add = true;
			for(UInt32 j = 0; j < num_filled; ++j){
				if(target[j] == original[i]){
					to_add = false;
					break;
				}
			}
			if(to_add == true){
				target[num_filled] = original[i];
				permute_and_call(original, target, num_filled + 1, fp);
			}
		}
	}
}

#endif

