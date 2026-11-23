## Compiling & Linking

Include the following at the top of any translation unit:



```cplusplus
#include <ecl/type_traits.hpp>

// The error interfaces
using ecl::numeric_limits;
using ecl::is_integral;
using ecl::is_float;
using ecl::is_signed;
using ecl::is_unsigned;
using ecl::is_byte;
```



If outside ros, you will also need to link to *ecl_type_traits*.

## Tutorials

- [Numerical Limits](#numerical-limits) -
  fixing a few rough edges around c++ numeric limits.
- [The 'Is A' Traits](#the-is-a-traits) -
  temporary fillers for the 'is a xxx' fundamental type traits till
  C++0x is widespread.

## Numerical Limits

- **Description:** Fixing a few rough edges around c++ numeric limits.
- **Keywords:** ecl numeric limits
- **Tutorial Level:** INTERMEDIATE

This extends c++'s numeric_limits class for fundamental types,
providing in addition, static constants that can be utilised as template
arguments (as opposed to c macros or c++ functions in numeric_limits).
For integral types, an example of the extras available:



```cplusplus
ecl::uint16 bits = NumericLimits<int>::bits;
ecl::uint16 bytes = NumericLimits<int>::bytes;
int j = NumericLimits<int>::one;
int i = NumericLimits<int>::minimum;
int k = NumericLimits<int>::maximum;
```



An example of some extras for a float type:



```cplusplus
ecl::uint16 bits = NumericLimits<float>::bits;
ecl::uint16 bytes = NumericLimits<float>::bytes;

// precision setting is a rough, but useful aid to bounding the accuracy for some math calculations
NumericLimits<float>::Precision p = NumericLimits<float>::dummy_precision();

// note, numeric_limits<float>::min() is the smallest
// positive value, this is the smallest negative value.
float minimum = NumericLimits<float>::minimum;
float maximum = NumericLimits<float>::maximum;
```



Note that it inherits the numeric_limits class, so all the functions
therein can also be used.

## The 'Is A' Traits

- **Description:** Temporary fillers for the 'is a xxx' fundamental
  type traits till C++0x is widespread.
- **Keywords:** ecl type traits
- **Tutorial Level:** INTERMEDIATE

These are in the upcoming C++0x standard, so are only a temporary
feature in the ecl. They are a subset and work just like boosts type
traits. More will be added as needed. The code snippet below is for
runtime code, but they're actually more useful with `enable_if` in
determining which compile time template specialisations to instantiate.



```cplusplus
if ( is_float<double>::value ) {
  // take some action
}
```



The current list include:

- `ecl::is_integral`
- `ecl::is_signed`
- `ecl::is_unsigned`
- `ecl::is_float`
- `ecl::is_byte`
- `ecl::is_signed_byte`
- `ecl::is_unsigned_byte`

## Tutorials

- [Numerical Limits](#numerical-limits):
  Fixing a few rough edges around c++ numeric limits.
- [The 'Is A' Traits](#the-is-a-traits):
  Temporary fillers for the 'is a xxx' fundamental type traits till
  C++0x is widespread.
