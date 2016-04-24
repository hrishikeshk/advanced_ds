.PHONY: clean bloom_filter

include $(SRC_DIR)/OptMake

BF_INCLUDES = -I $(SRC_DIR)/bloom_filter

bloom_filter: bm.o bf.o
	$(CC) $(WARN) $(DEBUG) $(SHAREDLIB_FLAGS) -o $(SRC_DIR)/libs/libbf.so bm.o bf.o ../cf.o

bm.o: BitMap.h BitMap.cpp ../Common_Funcs.cpp ../Common_Funcs.h
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) $(INCLUDES) $(BF_INCLUDES) $(FPIC_OBJ) -o bm.o -c BitMap.cpp 

bf.o: BloomFilter.h BloomFilter.cpp bm.o ../Common_Funcs.cpp ../Common_Funcs.h
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) $(INCLUDES) $(BF_INCLUDES) $(FPIC_OBJ) -o bf.o -c BloomFilter.cpp 

clean:
	rm -rf *.o *.so *.a

