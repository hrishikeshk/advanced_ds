.PHONY: clean

include $(SRC_DIR)/OptMake

BF_INCLUDES = -I $(SRC_DIR)/bloom_filter

bloom_filter: bf.o
	$(CC) $(WARN) $(DEBUG) $(SHAREDLIB_FLAGS) -o $(SRC_DIR)/libs/libbf.so bf.o

bf.o: BitMap.h BitMap.cpp
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) $(INCLUDES) $(RB_INCLUDES) $(FPIC_OBJ) -o bf.o -c BitMap.cpp 

clean:
	rm -rf *.o *.so *.a
