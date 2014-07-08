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

BOOST_AUTO_TEST_SUITE_END()

