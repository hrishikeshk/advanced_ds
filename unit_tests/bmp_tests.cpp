#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <bitset>

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

void resize_ctor_bmp(){
	for(UInt32 i = 0; i <= 10; ++i){
		try{
			BitMap bmp;
			bmp.resize(i);
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

void resize_usage_bmp(){
	BitMap bmp(10);

	for(UInt32 x = 0; x < 10 * 8; ++x){
		BOOST_REQUIRE(bmp.is_marked(x) == false);
		BOOST_REQUIRE(bmp.mark(x) == true);
		BOOST_REQUIRE(bmp.is_marked(x) == true);
	}

	bmp.resize(15);
	
	for(UInt32 x = 0; x < 10 * 8; ++x){
		BOOST_REQUIRE(bmp.is_marked(x) == true);
	}
	for(UInt32 x = 10 * 8; x < 15 * 8; ++x){
		BOOST_REQUIRE(bmp.is_marked(x) == false);
	}

	bmp.resize(5);
	for(UInt32 x = 0; x < 5 * 8; ++x){
		BOOST_REQUIRE(bmp.is_marked(x) == true);
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

BOOST_AUTO_TEST_CASE( unset_10_BMP ){
	std::cout << "Running Test # " << "4\n";
	np_check_bmp();
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( rs_ctor_BMP ){
	std::cout << "Running Test # " << "5\n";
	resize_ctor_bmp();
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( rs_insert_10_BMP ){
	std::cout << "Running Test # " << "6\n";
	resize_usage_bmp();
	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( perf_1_bmp ){
	perf1bmp(0x1fffff);
}


void perf_compare_bs_bmp(){

	double regression_limit_mark = 3.0;

	constexpr unsigned int size_to_use = 0x1fffff;
		try{
			std::bitset<size_to_use * 8> bs(0);

			std::cout << "Compare with std::bitset ! \n\nRunning Performance Test for all operations - # " << "1\n";

			////
			std::cout << "Trying marking .... with " << size_to_use * 8 << " marks\n";
			time_t t_start = time(NULL);
			for(UInt32 x = 0; x < size_to_use * 8; ++x){
				bs[x] = true;
			}
			time_t t_mark = time(NULL);
			std::cout << " Time for marking " << size_to_use * 8 << " data spots = " << difftime(t_mark, t_start) << " seconds\n";
			BOOST_REQUIRE(regression_limit_mark >= difftime(t_mark, t_start) );

			////
			bool tmp;
			std::cout << "Trying checking marks .... with " << size_to_use * 8 << " marks\n";
			t_start = time(NULL);
			for(UInt32 x = 0; x < size_to_use * 8; ++x){
				tmp = bs[x];
			}
			t_mark = time(NULL);
			std::cout << "Value set as " << tmp << "\n";
			std::cout << " Time for checking " << size_to_use * 8 << " data spots = " << difftime(t_mark, t_start) << " seconds...\n";
			BOOST_REQUIRE(regression_limit_mark >= difftime(t_mark, t_start) );

			////
			std::cout << "Trying un-marking .... with " << size_to_use * 8 << " marks\n";
			t_start = time(NULL);
			for(UInt32 x = 0; x < size_to_use * 8; ++x){
				bs[x] = false;
			}
			t_mark = time(NULL);
			std::cout << " Time for un-marking " << size_to_use * 8 << " data spots = " << difftime(t_mark, t_start) << " seconds\n";
			BOOST_REQUIRE(regression_limit_mark >= difftime(t_mark, t_start) );
		}
		catch(std::bad_alloc ba){
			throw ba;
		}
		catch(...){
			BOOST_REQUIRE(false);
		}

	std::cout << " ... done\n";
}

BOOST_AUTO_TEST_CASE( perf_2_bmp ){
	perf_compare_bs_bmp();
}


BOOST_AUTO_TEST_SUITE_END()

