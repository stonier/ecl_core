/**
 * @file /ecl_type_traits/include/ecl/type_traits/numeric_limits.hpp
 *
 * @brief Expand on the std numeric limits classes.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ECL_TYPE_TRAITS_NUMERIC_LIMITS_HPP_
#define ECL_TYPE_TRAITS_NUMERIC_LIMITS_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <limits>
#include <climits>
#include <ecl/config/portable_types.hpp>
#include "macros.hpp"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Parent Template
*****************************************************************************/
/**
 * @brief Expands the std numeric_limits class.
 *
 * This (the non-specialized template) simply returns the same
 * functionality (via inheritance) as the std::numeric_limits class.
 *
 * - http://www.cplusplus.com/reference/std/limits/numeric_limits/
 *
 * Specialisations of this class expand its definitions.
 *
 * Note that since this class and all its specialisations inherit
 * the std::numeric_limits class, it
 * is only really usable for fundamental c++ types. To extend
 * non-fundamental types however, it is perfectly ok to specialise
 * and add your own numeric_limits functionality.
 *
 * Also note that once the future c++0x standard is in, support
 * in std::numeric_limits will be better and we can do away with much
 * of the implementation in the derived classes here.
 *
 * @tparam T : the type to check (currently must be a fundamental type).
 * 
 * Dummy precision is a useful concept borrowed from eigen. It is used to help define
 * fuzzy operators which is especially handy for comparing floats which are notorious with
 * a strict '=' operator.
 *
 * @sa eigen/include/ecl/Eigen3/src/Core/NumTraits.h
 */
template <typename T>
class numeric_limits : public std::numeric_limits<T>
{
};

/*****************************************************************************
** Specialisations
*****************************************************************************/
/**
 * @brief Expands the std numeric_limits class for char.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<char> : public std::numeric_limits<char> {
public:
	static const char one = 1;
	static const uint16 bits = ECL_SIZE_OF_CHAR*8;
	static const uint16 bytes = ECL_SIZE_OF_CHAR;

	typedef float Precision;
	static constexpr Precision dummy_precision = 1e-5f;

	static const char minimum = lowest();
	static const char maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for unsigned char.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<unsigned char> : public std::numeric_limits<unsigned char> {
public:
	static const unsigned char one = 1U;
	static const uint16 bits = ECL_SIZE_OF_CHAR*8;
	static const uint16 bytes = ECL_SIZE_OF_CHAR;

	typedef float Precision;
	static constexpr Precision dummy_precision = 1e-5f;

	static const unsigned char minimum = lowest();
	static const unsigned char maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for short.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<short> : public std::numeric_limits<short> {
public:
	static const short one = 1;
	static const uint16 bits = ECL_SIZE_OF_SHORT*8;
	static const uint16 bytes = ECL_SIZE_OF_SHORT;

	typedef float Precision;
	static constexpr Precision dummy_precision = 1e-5f;

	static const short minimum = lowest();
	static const short maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for unsigned short.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<unsigned short> : public std::numeric_limits<unsigned short> {
public:
	static const unsigned short one = 1U;
	static const uint16 bits = ECL_SIZE_OF_SHORT*8;
	static const uint16 bytes = ECL_SIZE_OF_SHORT;

	typedef float Precision;
	static constexpr Precision dummy_precision = 1e-5f;

	static const unsigned short minimum = lowest();
	static const unsigned short maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for int.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<int> : public std::numeric_limits<int> {
public:
	static const int one = 1;
	static const uint16 bits = ECL_SIZE_OF_INT*8;
	static const uint16 bytes = ECL_SIZE_OF_INT;

	typedef float Precision;
	static constexpr Precision dummy_precision = 0;

	static const int minimum = lowest();
	static const int maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for unsigned int.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<unsigned int> : public std::numeric_limits<unsigned int> {
public:
	static const unsigned int one = 1U;
	static const uint16 bits = ECL_SIZE_OF_INT*8;
	static const uint16 bytes = ECL_SIZE_OF_INT;

	typedef float Precision;
	static constexpr Precision dummy_precision = 0;

	static const unsigned int minimum = lowest();
	static const unsigned int maximum = max();
};


/**
 * @brief Expands the std numeric_limits class for long.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<long> : public std::numeric_limits<long> {
public:
	static const long one = 1L;
	static const uint16 bits = ECL_SIZE_OF_LONG*8;
	static const uint16 bytes = ECL_SIZE_OF_LONG;

	typedef float Precision;
	static constexpr Precision dummy_precision = 0;

	static const long minimum = lowest();
	static const long maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for unsigned long.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<unsigned long> : public std::numeric_limits<unsigned long> {
public:
	static const unsigned long one = 1UL;
	static const uint16 bits = ECL_SIZE_OF_LONG*8;
	static const uint16 bytes = ECL_SIZE_OF_LONG;

	typedef float Precision;
	static constexpr Precision dummy_precision = 0;

	static const unsigned long minimum = lowest();
	static const unsigned long maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for long long.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<long long> : public std::numeric_limits<long long> {
public:
	static const long long one = 1LL;
	static const uint16 bits = ECL_SIZE_OF_LONG_LONG*8;
	static const uint16 bytes = ECL_SIZE_OF_LONG_LONG;

	typedef float Precision;
	static constexpr Precision dummy_precision = 0;

	static const long long minimum = lowest();
	static const long long maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for unsigned long long.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<unsigned long long> : public std::numeric_limits<unsigned long long> {
public:
	static const unsigned long long one = 1ULL;
	static const uint16 bits = ECL_SIZE_OF_LONG_LONG*8;
	static const uint16 bytes = ECL_SIZE_OF_LONG_LONG;

	typedef float Precision;
	static constexpr Precision dummy_precision = 0;

	static const unsigned long long minimum = lowest();
	static const unsigned long long maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for float.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<float> : public std::numeric_limits<float> {
public:
	static const uint16 bits = ECL_SIZE_OF_FLOAT*8;
	static const uint16 bytes = ECL_SIZE_OF_FLOAT;

	typedef float Precision;
	static constexpr Precision dummy_precision = 1e-5f;

	static constexpr float minimum = lowest();
	static constexpr float maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for float.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<double> : public std::numeric_limits<double> {
public:
	static const uint16 bits = ECL_SIZE_OF_DOUBLE*8;
	static const uint16 bytes = ECL_SIZE_OF_DOUBLE;

	typedef double Precision;
	static constexpr Precision dummy_precision = 1e-12;

	static constexpr double minimum = lowest();
	static constexpr double maximum = max();
};

/**
 * @brief Expands the std numeric_limits class for float.
 *
 * @sa ecl::numeric_limits
 */
template <>
class numeric_limits<long double> : public std::numeric_limits<long double> {
public:
	static const uint16 bits = ECL_SIZE_OF_LONG_DOUBLE*8;
	static const uint16 bytes = ECL_SIZE_OF_LONG_DOUBLE;

	typedef long double Precision;
	static constexpr Precision dummy_precision = 1e-15;

	static constexpr long double minimum = lowest();
	static constexpr long double maximum = max();
};


} // namespace ecl

#endif /* ECL_TYPE_TRAITS_NUMERIC_LIMITS_HPP_ */
