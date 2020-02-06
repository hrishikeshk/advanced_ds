include $(SRC_DIR)/OptMake

.PHONY: unit_tests clean

TST_INCLUDES=$(BOOST_INCLUDES) -I $(SRC_DIR)/red_black_tree -I $(SRC_DIR)/bloom_filter -I $(SRC_DIR)/unit_tests -I $(SRC_DIR)/bi_tree

simple_tests.o: simple_tests.cpp Test_Key.h Test_Utils.h ../red_black_tree/RBTree.h ../red_black_tree/Augment.h ../Common_Funcs.cpp ../Common_Funcs.h
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(TST_INCLUDES) -o simple_tests.o -c simple_tests.cpp

aug_tree_tests.o: aug_tree_tests.cpp Test_Key.h Test_Utils.h ../red_black_tree/RBTree.h ../red_black_tree/Augment.h ../Common_Funcs.cpp ../Common_Funcs.h
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(TST_INCLUDES) -o aug_tree_tests.o -c aug_tree_tests.cpp

bmp_tests.o: bmp_tests.cpp ../Common_Funcs.cpp ../Common_Funcs.h ../bloom_filter/BitMap.h ../bloom_filter/BitMap.cpp
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(TST_INCLUDES) -o bmp_tests.o -c bmp_tests.cpp

bf_tests.o: bf_tests.cpp ../Common_Funcs.cpp ../Common_Funcs.h ../bloom_filter/BloomFilter.h ../bloom_filter/BloomFilter.cpp
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(TST_INCLUDES) -o bf_tests.o -c bf_tests.cpp

perf_tests.o: perf_tests.cpp Test_Key.h Test_Utils.h ../red_black_tree/RBTree.h ../red_black_tree/Augment.h ../Common_Funcs.cpp ../Common_Funcs.h
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(TST_INCLUDES) -o perf_tests.o -c perf_tests.cpp

bi_tree_tests.o: bi_tree_tests.cpp ../Common_Funcs.cpp ../Common_Funcs.h ../bi_tree/bi_tree.h bi_tree_tests.cpp
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(TST_INCLUDES) -o bi_tree_tests.o -c bi_tree_tests.cpp
	
unit_tests: simple_tests.o aug_tree_tests.o perf_tests.o bmp_tests.o bf_tests.o bi_tree_tests.o ../cf.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -o $(SRC_DIR)/libs/simple_tests simple_tests.o ../cf.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -o $(SRC_DIR)/libs/aug_tree_tests aug_tree_tests.o ../cf.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -o $(SRC_DIR)/libs/perf_tests perf_tests.o ../cf.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -o $(SRC_DIR)/libs/bf_tests bf_tests.o ../cf.o -lbf
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -o $(SRC_DIR)/libs/bmp_tests bmp_tests.o ../cf.o -lbf
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -o $(SRC_DIR)/libs/bi_tree_tests bi_tree_tests.o ../cf.o

clean:
	rm -rf *.o; rm -rf $(SRC_DIR)/libs/simple_tests; rm -rf $(SRC_DIR)/libs/perf_tests; \
	rm -rf $(SRC_DIR)/libs/bmp_tests; rm -rf $(SRC_DIR)/libs/aug_tree_tests; rm -rf $(SRC_DIR)/libs/bf_tests \
	rm -rf $(SRC_DIR)/libs/bi_tree_tests

