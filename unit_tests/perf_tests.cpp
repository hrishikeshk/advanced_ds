#define BOOST_TEST_MODULE test_suite2
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>
#include <time.h>


#include "RBNode.h"
#include "RBTree.h"
#include "Test_Key.h"
#include "Test_Utils.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE ( test_suite2)

BOOST_AUTO_TEST_CASE( insert_1M_RBTree ){
	std::cout << "Running Test # " << "1\n";

	double regression_limit_insert = 5.0;
	double regression_limit_find = 3.0;

	RBTree rbt;

	time_t t_start = time(NULL);

	UInt32 size = 1000000;
	std::vector<UInt32> array(size);
	for(UInt32 i = 0; i < size; ++i){
		array[i] = i;
		Test_Sorted_Order_Key tk(array, i);

                BOOST_REQUIRE(rbt.insert(tk, i) == true);
	}

	time_t t_insert = time(NULL);
	for(UInt32 i = 0; i < size; ++i){
		Test_Sorted_Order_Key tk(array, i);
		UInt32 searched;

		BOOST_REQUIRE(rbt.find(tk, searched) == true);
	}

	double insert_time = difftime(t_insert, t_start); 
	std::cout << " Time for Insertion 1 M data = " << insert_time << " seconds\n";

	BOOST_REQUIRE(insert_time <= regression_limit_insert);

	time_t t_search = time(NULL);
	double find_time = difftime(t_search, t_insert);
	std::cout << " Time for Finding 1 M data = " << find_time << " seconds\n";

	BOOST_REQUIRE(find_time <= regression_limit_find);

}

BOOST_AUTO_TEST_CASE( delete_1M_RBTree ){
	std::cout << "Running Test # " << "2\n";

	double regression_limit_remove = 5.0;

	time_t t_start = time(NULL);

	RBTree rbt;
	UInt32 size = 1000000;
	std::vector<UInt32> array(size);
	for(UInt32 i = 0; i < size; ++i){
		array[i] = i;
		Test_Sorted_Order_Key tk(array, i);

                BOOST_REQUIRE(rbt.insert(tk, i) == true);
	}
	time_t t_insert = time(NULL);

	for(UInt32 i = 0; i < size; ++i){
		Test_Sorted_Order_Key tk(array, i);

		BOOST_REQUIRE(rbt.remove(tk) == true);
	}

	std::cout << " Time for Insertion 1 M data = " << difftime(t_insert, t_start) << " seconds\n";

	time_t t_remove = time(NULL);
	double remove_time = difftime(t_remove, t_insert);
	std::cout << " Time for Removing 1 M data = " << remove_time << " seconds\n";

	BOOST_REQUIRE(remove_time <= regression_limit_remove);

}

BOOST_AUTO_TEST_SUITE_END()

