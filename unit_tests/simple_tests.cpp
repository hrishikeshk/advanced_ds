#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include "RBNode.h"
#include "RBTree.h"
#include "Test_Key.h"
#include <iostream>
#include <vector>

using namespace boost::unit_test;

void simple_ctor_RBNode(){
	RBNode rbn;
	BOOST_REQUIRE(rbn.m_color == RED);
}

void simple_ctor_RBTree(){
	RBTree rbt;
	Test_Key tk;
	UInt32 ox = 0;
	BOOST_REQUIRE(rbt.find_element(tk, ox) == false);
}

void simple_insert_RBTree(){
	RBTree rbt;
	std::vector<UInt32> array(10);
	array[0] = 2;
	Test_Sorted_Order_Key tk(array, 0);
	UInt32 ref_ox = 0;

	BOOST_REQUIRE(rbt.insert_element(tk, ref_ox) == true);

	UInt32 searched_ox;
	BOOST_REQUIRE(rbt.find_element(tk, searched_ox) == true);

	BOOST_REQUIRE(searched_ox == ref_ox);
}

void multi_insert_RBTree(){
	RBTree rbt;
	std::vector<UInt32> array(10);
	for(UInt32 i = 0; i < 10; ++i){
		array[i] = i;
		Test_Sorted_Order_Key tk(array, i);
	
		BOOST_REQUIRE(rbt.insert_element(tk, i) == true);

		UInt32 searched_ox;
		BOOST_REQUIRE(rbt.find_element(tk, searched_ox) == true);

		BOOST_REQUIRE(searched_ox == i);
	}

	for(UInt32 i = 0; i < 10; ++i){
		Test_Sorted_Order_Key tk(array, i);
		
		UInt32 searched_ox;
		BOOST_REQUIRE(rbt.find_element(tk, searched_ox) == true);

		BOOST_REQUIRE(searched_ox == i);
	}
}

void multi_random_insert_RBTree(){
	RBTree rbt;
	std::vector<UInt32> array(10);
	array[0] = 4;
	array[1] = 43;
	array[2] = 23;
	array[3] = 6;
	array[4] = 57;
	array[5] = 5;
	array[6] = 8;
	array[7] = 1018;
	array[8] = 54;
	array[9] = 67;

	for(UInt32 i = 0; i < 10; ++i){

		Test_Sorted_Order_Key tk(array, i);
	
		BOOST_REQUIRE(rbt.insert_element(tk, i) == true);

		UInt32 searched_ox;
		BOOST_REQUIRE(rbt.find_element(tk, searched_ox) == true);

		BOOST_REQUIRE(searched_ox == i);
	}

	for(UInt32 i = 0; i < 10; ++i){
		Test_Sorted_Order_Key tk(array, i);
		
		UInt32 searched_ox;
		BOOST_REQUIRE(rbt.find_element(tk, searched_ox) == true);

		BOOST_REQUIRE(searched_ox == i);
	}
}

void multi_random_insert_failure_RBTree(){
	RBTree rbt;
	std::vector<UInt32> array(10);
	array[0] = 4;
	array[1] = 43;
	array[2] = 23;
	array[3] = 6;
	array[4] = 57;
	array[5] = 5;
	array[6] = 8;
	array[7] = 1018;
	array[8] = 54;
	array[9] = 67;

	for(UInt32 i = 0; i < 10; ++i){

		Test_Sorted_Order_Key tk(array, i);
	
		BOOST_REQUIRE(rbt.insert_element(tk, i) == true);

		UInt32 searched_ox;
		BOOST_REQUIRE(rbt.find_element(tk, searched_ox) == true);

		BOOST_REQUIRE(searched_ox == i);
	}

	for(UInt32 i = 0; i < 10; ++i){
		Test_Sorted_Order_Key tk(array, i);
		
		UInt32 searched_ox;
		BOOST_REQUIRE(rbt.find_element(tk, searched_ox) == true);

		BOOST_REQUIRE(searched_ox == i);
	}

	for(UInt32 i = 0; i < 10; ++i){
		Test_Sorted_Order_Key tk(array, i);
		BOOST_REQUIRE(rbt.insert_element(tk, i) == false);
	}
}

void multi_random_insert_RBTree_Order_Check(){
	RBTree rbt;
	std::vector<UInt32> array(10);
	array[0] = 4;
	array[1] = 43;
	array[2] = 23;
	array[3] = 6;
	array[4] = 57;
	array[5] = 5;
	array[6] = 8;
	array[7] = 1018;
	array[8] = 54;
	array[9] = 67;

	for(UInt32 i = 0; i < 10; ++i){

		Test_Sorted_Order_Key tk(array, i);
	
		BOOST_REQUIRE(rbt.insert_element(tk, i) == true);
	}

	std::vector<UInt32> o_contents;

	rbt.traverse_inorder(o_contents);

	UInt32 sz = o_contents.size();

	BOOST_REQUIRE(sz == 10);

	for(UInt32 i = 0; i < sz; ++i){
		std::cout << array[o_contents[i]] << " ";
	}
	std::cout << "\n";

	for(UInt32 i = 1; i < sz; ++i){
		BOOST_REQUIRE(array[o_contents[i]] > array[o_contents[i - 1]]);
	}
}


BOOST_AUTO_TEST_SUITE ( test_suite1 )

BOOST_AUTO_TEST_CASE( ctor_RBNode ){
	simple_ctor_RBNode();
}

BOOST_AUTO_TEST_CASE( ctor_RBTree ){
	simple_ctor_RBTree();
}

BOOST_AUTO_TEST_CASE( insert_1_RBTree ){
	simple_insert_RBTree();
}

BOOST_AUTO_TEST_CASE( insert_10_RBTree ){
	multi_insert_RBTree();
}

BOOST_AUTO_TEST_CASE( insert_rand10_RBTree ){
	multi_random_insert_RBTree();
}

BOOST_AUTO_TEST_CASE( insert_rand10_failure_RBTree ){
	multi_random_insert_failure_RBTree();
}

BOOST_AUTO_TEST_CASE( insert_rand10_order_check_RBTree ){
	multi_random_insert_RBTree_Order_Check();
}

BOOST_AUTO_TEST_SUITE_END()

