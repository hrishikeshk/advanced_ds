//#define BOOST_TEST_MODULE simple_tests
#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>

#include "RBNode.h"
#include "RBTree.h"
#include "Test_Key.h"

using namespace boost::unit_test;

void simple_ctor_RBNode(){
	RBNode rbn;
	BOOST_CHECK(rbn.m_color == BLACK);
}

void simple_ctor_RBTree(){
	RBTree rbt;
	Test_Key tk;
	UInt32 ox = 0;
	BOOST_CHECK(rbt.find_element(tk, ox) == false);
}

BOOST_AUTO_TEST_CASE( testA ){
	BOOST_CHECK(true);
}
/*
BOOST_AUTO_TEST_CASE( simple_ctor_RBNode ){
	BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE( simple_ctor_RBTree ){
	BOOST_CHECK(true);
}
*/
