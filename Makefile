include OptMake

.PHONY: red_black_tree clean

DIRS=red_black_tree unit_tests

all: $(DIRS)

red_black_tree: 
	cd red_black_tree; $(MAKE) red_black_tree

unit_tests: red_black_tree
	cd unit_tests; $(MAKE) unit_tests

clean:
	cd libs; rm -rf *.so; cd $(SRC_DIR)/red_black_tree; $(MAKE) clean; cd $(SRC_DIR)/unit_tests; $(MAKE) clean