#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>

#include "RBNode.h"
#include "RBTree.h"
#include "Test_Key.h"
#include "Test_Utils.h"

using namespace boost::unit_test;

void simple_ctor_RBNode(){
	RBNode rbn;
	BOOST_REQUIRE(rbn.m_color == RED);
}

void simple_ctor_RBTree(){
	RBTree rbt;
	Test_Key tk;
	UInt32 ox = 0;
	BOOST_REQUIRE(rbt.find(tk, ox) == false);
}

void simple_insert_RBTree(){
	RBTree rbt;
	std::vector<UInt32> array(10);
	array[0] = 2;
	Test_Sorted_Order_Key tk(array, 0);
	UInt32 ref = 0;

	BOOST_REQUIRE(rbt.insert(tk, ref) == true);

	UInt32 searched;
	BOOST_REQUIRE(rbt.find(tk, searched) == true);

	BOOST_REQUIRE(searched == ref);
}

void multi_insert_RBTree(){
	RBTree rbt;
	std::vector<UInt32> array(10);
	for(UInt32 i = 0; i < 10; ++i){
		array[i] = i;
		Test_Sorted_Order_Key tk(array, i);
	
		BOOST_REQUIRE(rbt.insert(tk, i) == true);

		UInt32 searched;
		BOOST_REQUIRE(rbt.find(tk, searched) == true);

		BOOST_REQUIRE(searched == i);
	}

	for(UInt32 i = 0; i < 10; ++i){
		Test_Sorted_Order_Key tk(array, i);
		
		UInt32 searched;
		BOOST_REQUIRE(rbt.find(tk, searched) == true);

		BOOST_REQUIRE(searched == i);
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
	
		BOOST_REQUIRE(rbt.insert(tk, i) == true);

		UInt32 searched;
		BOOST_REQUIRE(rbt.find(tk, searched) == true);

		BOOST_REQUIRE(searched == i);
	}

	for(UInt32 i = 0; i < 10; ++i){
		Test_Sorted_Order_Key tk(array, i);
		
		UInt32 searched;
		BOOST_REQUIRE(rbt.find(tk, searched) == true);

		BOOST_REQUIRE(searched == i);
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
	
		BOOST_REQUIRE(rbt.insert(tk, i) == true);

		UInt32 searched;
		BOOST_REQUIRE(rbt.find(tk, searched) == true);

		BOOST_REQUIRE(searched == i);
	}

	for(UInt32 i = 0; i < 10; ++i){
		Test_Sorted_Order_Key tk(array, i);
		
		UInt32 searched;
		BOOST_REQUIRE(rbt.find(tk, searched) == true);

		BOOST_REQUIRE(searched == i);
	}

	for(UInt32 i = 0; i < 10; ++i){
		Test_Sorted_Order_Key tk(array, i);
		BOOST_REQUIRE(rbt.insert(tk, i) == false);
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
	
		BOOST_REQUIRE(rbt.insert(tk, i) == true);
	}

	std::vector<UInt32> o_contents;

	rbt.traverse_inorder(o_contents);

	UInt32 sz = o_contents.size();

	BOOST_REQUIRE(sz == 10);

	for(UInt32 i = 1; i < sz; ++i){
		BOOST_REQUIRE(array[o_contents[i]] > array[o_contents[i - 1]]);
	}
}

void inorder_check_helper(const std::vector<UInt32>& o_contents, const std::vector<UInt32>& array){
	UInt32 sz = o_contents.size();
	for(UInt32 i = 1; i < sz; ++i){
		BOOST_REQUIRE(array[o_contents[i]] > array[o_contents[i - 1]] );
	}
}

void multi_random_insert_Stepwise_Order_Check(){
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

	std::vector<UInt32> o_contents;
	for(UInt32 i = 0; i < 10; ++i){

		Test_Sorted_Order_Key tk(array, i);
	
		BOOST_REQUIRE(rbt.insert(tk, i) == true);
		
		rbt.traverse_inorder(o_contents);
		UInt32 sz = o_contents.size();

		BOOST_REQUIRE(sz == ( i + 1 ) );

		inorder_check_helper(o_contents, array);
	}
}

void multi_permute_insert_Stepwise_Order_Check(const std::vector<UInt32>& array){
	RBTree rbt;
	std::vector<UInt32> o_contents;
	for(UInt32 i = 0; i < 10; ++i){

		Test_Sorted_Order_Key tk(array, i);
	
		BOOST_REQUIRE(rbt.insert(tk, i) == true);
		
		rbt.traverse_inorder(o_contents);
		UInt32 sz = o_contents.size();

		BOOST_REQUIRE(sz == ( i + 1 ) );

		inorder_check_helper(o_contents, array);
	}
}

void simple_delete_RBTree(){
	RBTree rbt;
	std::vector<UInt32> array(10);
	array[0] = 2;
	Test_Sorted_Order_Key tk(array, 0);
	UInt32 ref = 0;

	BOOST_REQUIRE(rbt.insert(tk, ref) == true);

	UInt32 searched;
	BOOST_REQUIRE(rbt.find(tk, searched) == true);

	BOOST_REQUIRE(searched == ref);

	BOOST_REQUIRE(rbt.remove(tk) == true);

	BOOST_REQUIRE(rbt.find(tk, searched) == false);
}

void multi_delete_RBTree(const std::vector<UInt32>& order_of_removal){
        RBTree rbt;
        std::vector<UInt32> array(order_of_removal.size());
        for(UInt32 i = 0; i < order_of_removal.size(); ++i){
                array[i] = i;
                Test_Sorted_Order_Key tk(array, i);

                BOOST_REQUIRE(rbt.insert(tk, i) == true);

                UInt32 searched;
                BOOST_REQUIRE(rbt.find(tk, searched) == true);

                BOOST_REQUIRE(searched == i);
        }

        for(UInt32 i = 0; i < order_of_removal.size(); ++i){
                Test_Sorted_Order_Key tk(array, order_of_removal[i]);

                UInt32 searched;
                BOOST_REQUIRE(rbt.find(tk, searched) == true);

		BOOST_REQUIRE(rbt.remove(tk) == true);

                //UInt32 searched;
                BOOST_REQUIRE(rbt.find(tk, searched) == false);
        }
}

void delete_2_RBTree(){
        RBTree rbt;
        std::vector<UInt32> array(3);
        array[0] = 2;
        array[1] = 1;
        array[2] = 3;
        Test_Sorted_Order_Key tk0(array, 0);
        BOOST_REQUIRE(rbt.insert(tk0, 0) == true);
        Test_Sorted_Order_Key tk1(array, 1);
        BOOST_REQUIRE(rbt.insert(tk1, 1) == true);
        Test_Sorted_Order_Key tk2(array, 2);
        BOOST_REQUIRE(rbt.insert(tk1, 2) == true);

        UInt32 searched;

	BOOST_REQUIRE(rbt.remove(tk0) == true);
        BOOST_REQUIRE(rbt.find(tk0, searched) == false);

	BOOST_REQUIRE(rbt.remove(tk1) == true);
        BOOST_REQUIRE(rbt.find(tk1, searched) == false);

	BOOST_REQUIRE(rbt.remove(tk2) == true);
        BOOST_REQUIRE(rbt.find(tk2, searched) == false);
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

BOOST_AUTO_TEST_CASE( insert_rand10_sw_order_check_RBTree ){
	multi_random_insert_Stepwise_Order_Check();
}

BOOST_AUTO_TEST_CASE( insert_permute_sw_order_check_RBTree ){
	std::vector<UInt32> array(8);
	array[0] = 4;
	array[1] = 43;
	array[2] = 23;
	array[3] = 6;
	array[4] = 57;
	array[5] = 5;
	array[6] = 8;
	array[7] = 1018;
	std::vector<UInt32> target(8);
	
	permute_and_call(array, target, 0, multi_permute_insert_Stepwise_Order_Check);
}

BOOST_AUTO_TEST_CASE( delete_1_RBTree ){
	simple_delete_RBTree();
}


BOOST_AUTO_TEST_CASE( delete_2_RBTree ){
	delete_2_RBTree();
}


BOOST_AUTO_TEST_CASE( delete_10_RBTree ){
	std::vector<UInt32> array(8);
	array[0] = 4;
	array[1] = 3;
	array[2] = 5;
	array[3] = 2;
	array[4] = 7;
	array[5] = 0;
	array[6] = 6;
	array[7] = 1;

	std::vector<UInt32> target(8);

	permute_and_call(array, target, 0, multi_delete_RBTree);
}


BOOST_AUTO_TEST_SUITE_END()

