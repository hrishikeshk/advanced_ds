#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>

#include "BitMap.h"

using namespace boost::unit_test;

void simple_ctor_bmp(){
	for(UInt32 i = 0; i <= 10; ++i){
		try{
			BitMap bmp(i);
		}
		catch(std::bad_alloc ba){
			BOOST_REQUIRE(false);
		}
	}
}

void simple_usage_bmp(){
	BitMap bmp(10);

	for(UInt32 x = 0; x < 10 * 8; ++x){
		BOOST_REQUIRE(bmp.is_marked(x) == false);
		BOOST_REQUIRE(bmp.mark(x) == true);
		BOOST_REQUIRE(bmp.is_marked(x) == true);
	}
	for(UInt32 x = 0; x < 10 * 8; ++x){
		BOOST_REQUIRE(bmp.is_marked(x) == true);
		BOOST_REQUIRE(bmp.unmark(x) == true);
		BOOST_REQUIRE(bmp.is_marked(x) == false);
	}
}

void np_check_bmp(){
	BitMap bmp(10);
	for(UInt32 i = 0; i < 10 * 8; ++i){
		BOOST_REQUIRE(bmp.is_marked(i) == false);
	}
}

void random_usage_bmp(){
	BitMap bmp(10);
	std::vector<bool> pos(8 * 10, false);
	for(UInt32 x = 0; x < 10 * 8; ++x){
		UInt32 r = rand() % 80;
		BOOST_REQUIRE(bmp.mark(r) == true);
		BOOST_REQUIRE(bmp.is_marked(r) == true);
		pos[r] = true;
	}

	for(UInt32 x = 0; x < 8 * 10; ++ x){
		if(pos[x]){
			BOOST_REQUIRE(bmp.is_marked(x) == true);
			BOOST_REQUIRE(bmp.unmark(x) == true);
		}
		else{
			BOOST_REQUIRE(bmp.is_marked(x) == false);
		}
	}
}

void perf1bmp(UInt32 size_to_use){

	double regression_limit_mark = 3.0;

	while(true){
		try{
			BitMap bmp(size_to_use);

			std::cout << "Running Performance Test for all operations - # " << "1\n";

			////
			std::cout << "Trying marking .... with " << size_to_use * 8 << " marks\n";
			time_t t_start = time(NULL);
			for(UInt32 x = 0; x < size_to_use * 8; ++x){
				bmp.mark(x);
			}
			time_t t_mark = time(NULL);
			std::cout << " Time for marking " << size_to_use * 8 << " data spots = " << difftime(t_mark, t_start) << " seconds\n";
			BOOST_REQUIRE(regression_limit_mark >= difftime(t_mark, t_start) );

			////
			std::cout << "Trying checking marks .... with " << size_to_use * 8 << " marks\n";
			t_start = time(NULL);
			for(UInt32 x = 0; x < size_to_use * 8; ++x){
				bmp.is_marked(x);
			}
			t_mark = time(NULL);
			std::cout << " Time for checking " << size_to_use * 8 << " data spots = " << difftime(t_mark, t_start) << " seconds\n";
			BOOST_REQUIRE(regression_limit_mark >= difftime(t_mark, t_start) );

			////
			std::cout << "Trying un-marking .... with " << size_to_use * 8 << " marks\n";
			t_start = time(NULL);
			for(UInt32 x = 0; x < size_to_use * 8; ++x){
				bmp.unmark(x);
			}
			t_mark = time(NULL);
			std::cout << " Time for un-marking " << size_to_use * 8 << " data spots = " << difftime(t_mark, t_start) << " seconds\n";
			BOOST_REQUIRE(regression_limit_mark >= difftime(t_mark, t_start) );

			break;	
		}
		catch(std::bad_alloc ba){
			size_to_use /= 2;
		}
		catch(...){
			BOOST_REQUIRE(false);
			break;
		}
		break;
	}

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_SUITE ( test_suite1 )

BOOST_AUTO_TEST_CASE( ctor_BMP ){
	std::cout << "Running Test # " << "1\n";
	simple_ctor_bmp();
	std::cout << " ... done\n";
}
BOOST_AUTO_TEST_CASE( insert_10_BMP ){
	std::cout << "Running Test # " << "2\n";
	simple_usage_bmp();
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( use_rand10_BMP ){
	std::cout << "Running Test # " << "3\n";
	random_usage_bmp();
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( insert_rand10_failure_RBTree ){
	std::cout << "Running Test # " << "4\n";
	np_check_bmp();
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( perf_1_bmp ){
	perf1bmp(0x1fffff);
}

BOOST_AUTO_TEST_SUITE_END()

