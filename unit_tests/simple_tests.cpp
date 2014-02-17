#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include "RBNode.h"
#include "RBTree.h"
#include "Test_Key.h"
#include <iostream>

using namespace boost::unit_test;

void simple_ctor_RBNode(){
	RBNode rbn;
	BOOST_REQUIRE(rbn.m_color == BLACK);
}

void simple_ctor_RBTree(){
	RBTree rbt;
	Test_Key tk;
	UInt32 ox = 0;
	BOOST_REQUIRE(rbt.find_element(tk, ox) == false);
}

BOOST_AUTO_TEST_SUITE ( test_suite1 )

BOOST_AUTO_TEST_CASE( ctor_RBNode ){
	simple_ctor_RBNode();

}

BOOST_AUTO_TEST_CASE( ctor_RBTree ){
	simple_ctor_RBTree();
}

BOOST_AUTO_TEST_SUITE_END()

