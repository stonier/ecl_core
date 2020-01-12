/**
 * @file /ecl_type_traits/src/test/numeric_limits.cpp
 *
 * @brief Unit test for the expanded numeric limits.
 *
 * @date February, 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <iostream>
#include <gtest/gtest.h>
#include <float.h>
#include "../../include/ecl/type_traits/numeric_limits.hpp"

/*****************************************************************************
** Main
*****************************************************************************/

int main(int argc, char **argv) {

    std::cout << "Sizeof Float: " << __SIZEOF_FLOAT__ << std::endl;
    std::cout << "Sizeof Double: " << __SIZEOF_DOUBLE__ << std::endl;
    std::cout << "Sizeof Long Double: " << __SIZEOF_LONG_DOUBLE__ << std::endl;
    int i = 1 + ecl::numeric_limits<char>::one;
    std::cout << i << std::endl;
    i = 1 + ecl::numeric_limits<ecl::uint8>::one;
    std::cout << i << std::endl;
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


