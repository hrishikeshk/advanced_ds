#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <bitset>

#include "bi_tree.h"

using namespace boost::unit_test;

void simple_ctor_bi_tree(){
	for(UInt32 i = 0; i <= 10; ++i){
		try{
		  BI_Tree bit(i);
		}
		catch(std::bad_alloc ba){
			BOOST_REQUIRE(false);
		}
	}
}

BOOST_AUTO_TEST_SUITE ( test_suite1 )

BOOST_AUTO_TEST_CASE( ctor_BMP ){
	std::cout << "Running Test # " << "1\n";
	simple_ctor_bi_tree();
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_SUITE_END()

