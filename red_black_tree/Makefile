.PHONY: clean

include $(SRC_DIR)/OptMake

RB_INCLUDES = -I $(SRC_DIR)/red_black_tree

red_black_tree: rbtree.o
	$(CC) $(WARN) $(DEBUG) $(SHAREDLIB_FLAGS) -o $(SRC_DIR)/libs/librbtree.so rbtree.o

rbtree.o: RBTree.cpp RBNode.h Key.h RBTree.h
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) $(INCLUDES) $(RB_INCLUDES) $(FPIC_OBJ) -o rbtree.o -c RBTree.cpp 

clean:
	rm -rf *.o *.so *.a
