include $(SRC_DIR)/OptMake

.PHONY: unit_tests clean

TST_INCLUDES=-I $(SRC_DIR)/red_black_tree -I $(SRC_DIR)/unit_tests

TST_LIBS=-L $(SRC_DIR)/red_black_tree

simple_tests.o: simple_tests.cpp
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(RB_INCLUDES) $(TST_INCLUDES) -o simple_tests.o -c simple_tests.cpp

unit_tests: simple_tests.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -lrbtree -o $(SRC_DIR)/libs/simple_tests simple_tests.o

clean:
	rm -rf *.o; rm -rf $(SRC_DIR)/libs/simple_tests

