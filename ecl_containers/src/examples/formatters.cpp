/**
 * @file /ecl_containers/src/examples/array_formatters.cpp
 *
 * @brief Example (and coverage) for the array formatters.
 *
 * Can't easily do tests on this as its just streaming to cout.
 *
 * @date September 2010
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <iostream>
#include <gtest/gtest.h>
#include <ecl/formatters.hpp>
#include "../../include/ecl/containers/array.hpp"
#include "../../include/ecl/containers/push_and_pop.hpp"
#include "../../include/ecl/containers/stencil.hpp"

/*****************************************************************************
** Using
*****************************************************************************/

using ecl::Array;
using ecl::Format;
using ecl::Hex;
using ecl::NoAlign;
using ecl::Stencil;

/*****************************************************************************
** Main program
*****************************************************************************/

int main(int argc, char **argv) {

    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "                         Arrays" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    Array<int,4> int_array;
    int_array << 1,2,3,4;
    Array<float,4> float_array;
    float_array << 1,2,3.32235,-324;
    Format< Array<int,4> > format_array;
//    Format< Array<float,4> > format_array_float;
    Array<float,4>::Formatter format_array_float;
    format_array_float.precision(3);
    std::cout << format_array(int_array) << std::endl;
    std::cout << format_array_float(float_array) << std::endl;

    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "                    Dynamic Arrays" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    Array<float> float_array_dynamic(4);
    Format< Array<float> > format_array_dynamic_float;
    format_array_dynamic_float.precision(3);
    float_array_dynamic << 1,2,3.32235,-324;
    std::cout << format_array_dynamic_float(float_array_dynamic) << std::endl;

    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "                      Float Stencils" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    Array<float> float_array_under(20);
    float_array_under << 1,2,3.32235,-324;
    Format< Stencil< Array<float> > > format_stencil;
    format_stencil.precision(3);
    std::cout << format_stencil(float_array_under.stencil(1,2)) << std::endl;
    Array<double> double_array_under(20);
    double_array_under << 1,2,3.32235,-324;
    Format< Stencil< Array<double> > > format_double_stencil;
    format_double_stencil.precision(3);
    std::cout << format_double_stencil(double_array_under.stencil(1,2)) << std::endl;

    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "                         Byte Arrays" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;

    Array<signed char,4> schar_array;
    schar_array << 'a','b','c','d';
    Format< Array<signed char,4> > format_sbytes;
    std::cout << schar_array << std::endl;
    std::cout << format_sbytes(schar_array) << std::endl;
    std::cout << format_sbytes(schar_array.stencil(0,2)) << std::endl;
    Array<char,4> char_array;
    char_array << 'a','b','c','d';
    Array<char,4>::Formatter format_bytes;
//    Format< Array<char,4> > format_bytes;
    std::cout << char_array << std::endl;
    std::cout << format_bytes(char_array) << std::endl;
    std::cout << format_bytes(char_array.stencil(0,2)) << std::endl;
    Array<unsigned char,4> uchar_array;
    uchar_array << 0x01, 0x02, 0x03, 0x04;
    Format< Array<unsigned char,4> > format_ubytes;
    Format<unsigned char> format_uchar(-1,NoAlign,Hex);
    std::cout << "[ ";
    for ( unsigned int i = 0; i < uchar_array.size(); ++i ) {
        std::cout << format_uchar(uchar_array[i]) << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << format_ubytes(uchar_array) << std::endl;
    std::cout << format_ubytes(uchar_array.stencil(0,2)) << std::endl;

    ecl::PushAndPop<unsigned char> push_and_pop;
    push_and_pop.resize(4);
    push_and_pop.push_back(0xaa);
    push_and_pop.push_back(0x55);
    ecl::PushAndPop<unsigned char>::Formatter format;
    std::cout << format(push_and_pop) << std::endl;

    std::cout << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << "                      Passed" << std::endl;
    std::cout << "***********************************************************" << std::endl;
    std::cout << std::endl;
    return 0;
}

