#define BOOST_TEST_MODULE test_suite1
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <bitset>

#include "Test_Utils.h"

#include "BloomFilter.h"

using namespace boost::unit_test;

void simple_ctor_bmp(){
	try{
		BloomFilter bf((1 << 20), 5);
	}
	catch(std::bad_alloc ba){
		BOOST_REQUIRE(false);
	}
}

void simple_usage_bmp(){
	BloomFilter bf(1024, 10);
	BOOST_REQUIRE(bf.is_added(str_to_vec("Hrishikesh")) == false);
	BOOST_REQUIRE(bf.add(str_to_vec("Hrishikesh")) == true);
	BOOST_REQUIRE(bf.is_added(str_to_vec("Hrishikesh")) == true);

	BloomFilter bf_single(1024, 1);
	BOOST_REQUIRE(bf_single.is_added(str_to_vec("Hrishikesh")) == false);
	BOOST_REQUIRE(bf_single.add(str_to_vec("Hrishikesh")) == true);
	BOOST_REQUIRE(bf_single.is_added(str_to_vec("Hrishikesh")) == true);

}

void perf1bmp(UInt32 size_to_use){

	double regression_limit_mark = 1.0;

	while(true){
		try{
			UInt32 num_hashes = size_to_use / (3 * 50);
			if(num_hashes < 1)
				num_hashes = 1;
			BloomFilter bf(size_to_use, num_hashes);

			std::cout << "Running Performance Test for all operations - # " << "1\n";

			////
			std::cout << "Trying adding .... with " << 50 << " sets\n";
			time_t t_start = time(NULL);
			for(UInt32 x = 1; x <= 50; ++x){
				BOOST_REQUIRE(bf.add(rand_vec(x)) == true);
			}
			time_t t_mark = time(NULL);
			std::cout << " Time for adding " << 50 << " data spots = " << difftime(t_mark, t_start) << " seconds\n";
			BOOST_REQUIRE(regression_limit_mark >= difftime(t_mark, t_start) );

			////
			std::cout << "Trying checking additions .... with " << 50 << " sets\n";
			t_start = time(NULL);
			for(UInt32 x = 1; x <= 50; ++x){
				BOOST_REQUIRE(bf.add(rand_vec(x)) == true);
			}
			t_mark = time(NULL);
			std::cout << " Time for checking " << 50 << " data spots = " << difftime(t_mark, t_start) << " seconds\n";
			BOOST_REQUIRE(regression_limit_mark >= difftime(t_mark, t_start) );

			break;	
		}
		catch(std::bad_alloc ba){
			std::cout << "WARN: Had to reduce size, memory allocation failed ... \n";
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

BOOST_AUTO_TEST_CASE( perf_1_bmp ){
	perf1bmp(0x1fffff);
}

BOOST_AUTO_TEST_SUITE_END()

