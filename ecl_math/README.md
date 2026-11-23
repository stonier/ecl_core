## Compiling & Linking

Include the following at the top of any translation unit:



```cplusplus
#include <ecl/math.hpp>

// constants
using ecl::pi; // also pi_2, pi_4

// simple functions
using ecl::EuclideanNorm;
using ecl::isApprox;
using ecl::isApproxOrLessThan;
using ecl::sign; // also psign
using ecl::cube_root; // only for real numbers/solutions
```



## Tutorial

- [Simple Math](#-multi-line-description-to-be-displayed-in-search) -
  simple math constants and functions.

## ## multi-line description to be displayed in search

- **Description:** Simple Math
- **Keywords:** ecl math
- **Tutorial Level:** BEGINNER

### Macros for PI

Usually there will always be macros for pi defined in <i>math.h</i>,
namely M_PI, M_PI_2, etc\... (sometimes they're unavailable, e.g.
windoze!). For typesafe definitions, the ecl also defines these as
constants in the ecl namespace.



```cplusplus
if ( 3.141592653589793238462643383279502884197169399375105820974944 == ecl::pi ) {
  // ...
}
```



### Simple Functions

Various regularly used functions are also present - usually in the form
of functors (useful for passing around should it ever be necessary).

**Sign**



```cplusplus
if ( sign(3) == 1 ) {  // returns -1, 0, 1 
if ( psign(0) == 1 ) { // returns -1, 1 (0->1)
```



**Euclidean Norms**



```cplusplus
double d1 = EuclideanNorm()(3.0,4.0)) // functor form
double d2 = euclidean_norm(3.0,4.0);  // function form
```



**Cube Root**



```cplusplus
double d = ecl::cube_root(8.0); // 2.0
```



### Fuzzy Operators

Not, 'fuzzy logic'\...

**Approximately**



```cplusplus
if ( ecl::isApprox(3.0,3.0000000000000001) ) { // ...
if ( ecl::isApproxOrLessThan(3.0,3.0000000000000001) ) { // ...
```



The bound of the approximation is by default, determined by the machine
precision on your machine. If a user specified epsilon bound is
preferred, that can be added as an optional third argument to either
function.

## Tutorials

- [\## multi-line description to be displayed in search](#-multi-line-description-to-be-displayed-in-search):
  Simple Math
