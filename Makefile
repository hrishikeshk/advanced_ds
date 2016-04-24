include OptMake

.PHONY: bloom_filter clean current unit_tests

DIRS=current bloom_filter unit_tests

all: $(DIRS)

bloom_filter: 
	cd bloom_filter; $(MAKE) bloom_filter

current: Common_Funcs.cpp Common_Funcs.h Consts.h TypeDefs.h
	$(CC) $(OPTIONS) $(WARN) $(DEBUG) $(INCLUDES) $(FPIC_OBJ) -o cf.o -c Common_Funcs.cpp

unit_tests: bloom_filter
	cd unit_tests; $(MAKE) unit_tests

clean:
	rm -f *.o; \
	cd libs; \
        rm -f *.so; \
        cd $(SRC_DIR)/bloom_filter; \
        $(MAKE) clean; \
        cd $(SRC_DIR)/unit_tests; \
        $(MAKE) clean
