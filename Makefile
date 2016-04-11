include OptMake

.PHONY: bloom_filter clean

DIRS=bloom_filter unit_tests

all: $(DIRS)

bloom_filter: 
	cd bloom_filter; $(MAKE) bloom_filter

unit_tests: bloom_filter
	cd unit_tests; $(MAKE) unit_tests

clean:
	cd libs; \
        rm -rf *.so; \
        cd $(SRC_DIR)/bloom_filter; \
        $(MAKE) clean; \
        cd $(SRC_DIR)/unit_tests; \
        $(MAKE) clean
