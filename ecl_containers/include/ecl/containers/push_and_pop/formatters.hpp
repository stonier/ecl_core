/**
 * @file /ecl_containers/include/ecl/containers/push_and_pop/formatters.hpp
 *
 * @brief File comment
 *
 * File comment
 *
 * @date Jun 4, 2012
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_CONTAINERS_PUSH_AND_POP_FORMATTERS_HPP_
#define ECL_CONTAINERS_PUSH_AND_POP_FORMATTERS_HPP_

/*****************************************************************************
 ** Includes
 *****************************************************************************/

#include <cmath>
#include <ecl/config/macros.hpp>
#include <ecl/formatters/common.hpp>
#include <ecl/formatters/number.hpp>
#include <ecl/formatters/floats.hpp>
#include "../common/formatters.hpp"
#include "../push_and_pop.hpp"

/*****************************************************************************
 ** Namespaces
 *****************************************************************************/

namespace ecl
{
namespace formatters
{

/*****************************************************************************
 ** Using
 *****************************************************************************/

/**
 * @brief Pseudo formatter for integral type arrays.
 *
 * These do nothing but pass the array back for streaming. Do not use this
 * class directly, rather call it via either the Array or Format classes
 * explicitly. This makes the code more readable. e.g.
 *
 * @code
 * // fixed array
 * PushAndPop<int, 5>::Formatter format_1;
 * Format< PushAndPop<int,4> > format_2;    // same thing
 *
 * // dynamic array
 * PushAndPop<int>::Formatter float_dynamic_formatter_1;
 * Format< PushAndPop<int> > format_dynamic_formatter_2;
 * @endcode
 *
 * @tparam Type : the value type of the fixed size Array.
 * @tparam N : the size of the container to be formatted.
 *
 * @todo Specialise the formatting for these integral type arrays so that they return
 * formatting possibilities equivalent to their base type.
 */
template<typename Type, size_t N>
class ECL_PUBLIC PushAndPopFormatter
{
public:
  virtual ~PushAndPopFormatter()
  {}
  /**
   * Pseudo formatter method, simply returns the underlying array which
   * has its own stream operator.
   * @param array : the array to be formatted.
   * @return PushAndPop<Type,N> : just returns the input array.
   */
  ecl::PushAndPop<Type,N>& operator()(ecl::PushAndPop<Type,N> &container) {
    return container;
  }
};

/*****************************************************************************
 ** Specialisations [PushAndPopFormatter][Char Types]
 *****************************************************************************/

/**
 * @brief Convenience formatter for viewing an unsigned char push and pop containers in hex format.
 *
 * We dont accept a wide range of arguments for this class, it is simply
 * designed to present byte push and pop containers in hex format byte by byte. If you
 * want specialised formatting for the byte array, iterate over it
 * with the Format<unsigned char> class.
 *
 * Todo: It will also accept stencils which have an underlying array of the
 * required type.
 *
 * @tparam N : the size of the container to be formatted.
 */
template<size_t N>
class ECL_PUBLIC PushAndPopFormatter< unsigned char,N >
{
public:
  // should really be using const with the arg here, but it needs some framework updates to allow
  // for the likes of Stencil< const Array<...)
  typename ecl::formatters::ByteArrayFormatter<unsigned char, N>& operator()(ecl::PushAndPop<unsigned char> &container) {
    //Stencil< Array<unsigned char, N> > stencil(container.data, 0, container.size());
    //return array_formatter(stencil);
    return array_formatter(container.data.stencil(0,container.size()));
  }

private:
  typename ecl::formatters::ByteArrayFormatter<unsigned char, N> array_formatter;
};


/*****************************************************************************
** Not Yet Implemented
*****************************************************************************/
///**
// * @brief Convenience formatter for viewing a signed char array in hex format.
// *
// * We dont accept a wide range of arguments for this class, it is simply
// * designed to present byte arrays in hex format byte by byte. If you
// * want specialised formatting for the byte array, iterate over it
// * with the Format<char> (or signed/unsigned char) class.
// *
// * It will also accept stencils which have an underlying array of the
// * required type.
// *
// * @tparam N : the size of the container to be formatted.
// */
//template<size_t N>
//class ECL_PUBLIC PushAndPopFormatter< signed char,N > : public BytePushAndPopFormatter<signed char, N>
//{};
//
///**
// * @brief Convenience formatter for viewing a char array in hex format.
// *
// * We dont accept a wide range of arguments for this class, it is simply
// * designed to present byte arrays in hex format byte by byte. If you
// * want specialised formatting for the byte array, iterate over it
// * with the Format<char> (or signed/unsigned char) class.
// *
// * It will also accept stencils which have an underlying array of the
// * required type.
// *
// * @tparam N : the size of the container to be formatted.
// */
//template<size_t N>
//class ECL_PUBLIC PushAndPopFormatter< char,N > : public BytePushAndPopFormatter<char, N>
//{};

///**
// * @brief Formatter for fixed size float arrays.
// *
// * Allows precision settings for formatting of fixed size float arrays.
// *
// * @tparam N : the size of the fixed size float array to be formatted.
// *
// * @sa @ref ecl::formatters::FloatContainerFormatter "FloatContainerFormatter".
// */
//template<size_t N>
//class ECL_PUBLIC PushAndPopFormatter< float,N > : public FloatContainerFormatter< Array<float,N> >
//{
//public:
//  /**
//   * @brief Default constructor.
//   *
//   * Optionally accepts a precision setting for the contents of the array.
//   *
//   * @param p : the number of decimal places of precision [default : 2].
//   * @param w : width [default : no width constraint]
//   */
//  PushAndPopFormatter(const int p=2, const int w=-1) : FloatContainerFormatter< Array<float,N> >(p,w)
//  {};
//  virtual ~PushAndPopFormatter()
//  {}
//};
///**
// * @brief Formatter for fixed size double arrays.
// *
// * Allows precision settings for formatting of fixed size double arrays.
// *
// * @tparam N : the size of the fixed size double array to be formatted.
// *
// * @sa @ref ecl::formatters::FloatContainerFormatter "FloatContainerFormatter".
// */
//template<size_t N>
//class ECL_PUBLIC PushAndPopFormatter< double,N > : public FloatContainerFormatter< Array<double,N> >
//{
//public:
//  /**
//   * @brief Default constructor.
//   *
//   * Optionally accepts a precision setting for the contents of the array.
//   *
//   * @param p : the number of decimal places of precision [default : 2].
//   * @param w : width [default : no width constraint]
//   */
//  PushAndPopFormatter(const int p=2, const int w=-1) : FloatContainerFormatter< Array<double,N> >(p,w)
//  {};
//  virtual ~PushAndPopFormatter()
//  {}
//};

} // namespace formatters
} // namespace ecl


#endif /* ECL_CONTAINERS_PUSH_AND_POP_FORMATTERS_HPP_ */
