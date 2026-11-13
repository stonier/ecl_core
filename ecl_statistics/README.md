## Compiling & Linking

Include the following at the top of any translation unit:



```cplusplus
#include <ecl/statistics.hpp>

// Statistics Classes
using ecl::CovarianceEllipsoid;
using ecl::CovarianceEllipsoid2f; // also 2d, 3f, 3d typedef variants
```



If outside of ros, you will also need to link to *ecl_statistics*.

## Tutorials

Currently we've only implemented simple, fast algorithms for 2x2, 3x3
covariance matrices.

- [Covariance Ellipsoids](#covariance-ellipsoids) -
  covariances ellipsoids, typically used in slam.

## Covariance Ellipsoids

- **Description:** Algorithms for 2d and 3d covariance ellipsoids,
  typically used in slam.
- **Keywords:** ecl statistics
- **Tutorial Level:** INTERMEDIATE

### Overview

Implemented by the template class `CovarianceEllipsoid` - this takes
two template parameters. The first is the float type used (usually
`float`/`double`) and the second, the dimension of the ellipsoid to
be determined.

Specialisations are enabled for 2 and 3 dimensional types only as we
haven't had a need to develop a general implementation.

### Typedefs

Typedefs exist for the template class in the eigen style:



```cplusplus
using ecl::CovarianceEllipsoid2f;
using ecl::CovarianceEllipsoid2d;
using ecl::CovarianceEllipsoid3f;
using ecl::CovarianceEllipsoid3d;
```



### Usage

You typically feed the covariance ellipsoid with a positive definite
symmetric matrix (`eigen` matrix). Take care entering the positive
definite symmetric matrix - the class does not yet do checking to make
sure it is positive definite symmetric.

You can either input the matrix via the constructor - in which case it
will automatically calculate the ellipsoid properties, or pass it in
later via the `compute()` method:



```cplusplus
Matrix2d M;
M << 3.0, 1.0, 1.0, 5.0; // must be a positive definite, symmetric matrix

CovarianceEllipsoid2d ellipse(M);

// OR

CovarianceEllipsoid2d ellipse;
ellipse.compute(M);
```





```cplusplus
Matrix2d M;
M << 3.0, 1.0, 1.0, 5.0;
CovarianceEllipsoid2d ellipse(M);

// ellipse minor and major axis lengths
const Vector2d& lengths = ellipse.lengths(); 
double eigen_value_0 = lengths[0]*lengths[0];

// angle between x-axis and major axis of the ellipse
double angle = ellipse.rotation(); 

// values of the intercepts of the ellipse with x and y axes
const Vector2d& intercepts = ellipse.intercepts(); 

// the ellipse axes/covariance eigenvectors as column vectors in a matrix
const Matrix2d& axes = ellipse.axes();
```



The 3d version is similar, but will only calculate intercepts and axes
respectively. Note that the axes are sorted (to ensure a right-handed
co-ordinate system) and normalised.



```cplusplus
Matrix3d P;
double sigmaX(0.1);
double sigmaY(0.5);
double sigmaT(0.3);
P << sigmaX*sigmaX, 0, 0, 0, sigmaY*sigmaY, 0, 0, 0, sigmaT*sigmaT;
CovarianceEllipsoid3d ellipse(P);

const Vector3d& lengths = ellipse.lengths();
double eigen_value_0 = lengths[0]*lengths[0];
const Matrix3d& axes = ellipse.axes();
```

## Tutorials

- [Covariance Ellipsoids](#covariance-ellipsoids):
  Algorithms for 2d and 3d covariance ellipsoids, typically used in
  slam.
