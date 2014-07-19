#ifndef _TEST_UTILS_
#define _TEST_UTILS_

#include <vector>

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

