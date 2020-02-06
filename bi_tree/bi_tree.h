#ifndef BI_TREE
#define BI_TREE

#include <vector>

#include "TypeDefs.h"

class BI_Tree{
public:
  BI_Tree(UInt32 size):freqs(size){
  }
  private:
  std::vector<Int32> freqs;
  
};

#endif

