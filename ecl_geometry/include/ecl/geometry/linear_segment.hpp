/**
 * @file /ecl_geometry/include/ecl/geometry/linear_segment.hpp
 */
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ecl_geometry_GEOMETRY_LINEAR_SEGMENT_HPP_
#define ecl_geometry_GEOMETRY_LINEAR_SEGMENT_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ecl/utilities/parameter.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ecl {

/*****************************************************************************
** Interfaces
*****************************************************************************/

class LinearSegment {
public:
  LinearSegment(const double& x_1,
                const double& y_1,
                const double& x_2,
                const double& y_2);

  double squaredDistanceFromPoint(const double& x,
                                  const double& y);

  ecl::Parameter<double> A, B, C;

private:
  double x_1, y_1;
  double x_2, y_2;
};

/*****************************************************************************
** Trailers
*****************************************************************************/

} // namespace ecl

#endif /* ecl_geometry_GEOMETRY_LINEAR_SEGMENT_HPP_ */
