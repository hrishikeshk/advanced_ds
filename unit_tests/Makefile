include $(SRC_DIR)/OptMake

.PHONY: unit_tests clean

TST_INCLUDES=-I $(SRC_DIR)/red_black_tree -I $(SRC_DIR)/bloom_filter -I $(SRC_DIR)/unit_tests

TST_LIBS=-L $(SRC_DIR)/red_black_tree -L $(SRC_DIR)/bloom_filter

simple_tests.o: simple_tests.cpp Test_Key.h Test_Utils.h
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(RB_INCLUDES) $(TST_INCLUDES) -o simple_tests.o -c simple_tests.cpp

bmp_tests.o: bmp_tests.cpp
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(RB_INCLUDES) $(TST_INCLUDES) -o bmp_tests.o -c bmp_tests.cpp

perf_tests.o: perf_tests.cpp Test_Key.h Test_Utils.h
	$(CC) $(OPTIONS)  $(WARN) $(DEBUG) $(FPIC_OBJ) $(INCLUDES) $(RB_INCLUDES) $(TST_INCLUDES) -o perf_tests.o -c perf_tests.cpp

unit_tests: simple_tests.o perf_tests.o bmp_tests.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -lrbtree -o $(SRC_DIR)/libs/simple_tests simple_tests.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -lrbtree -o $(SRC_DIR)/libs/perf_tests perf_tests.o
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) -L $(SRC_DIR)/libs -lbf -o $(SRC_DIR)/libs/bmp_tests bmp_tests.o

clean:
	rm -rf *.o; rm -rf $(SRC_DIR)/libs/simple_tests; rm -rf $(SRC_DIR)/libs/perf_tests; \
	rm -rf $(SRC_DIR)/libs/bmp_tests

