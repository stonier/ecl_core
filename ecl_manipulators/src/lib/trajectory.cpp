/**
 * @file /ecl_manipulators/src/lib/trajectory.cpp
 *
 * @brief Implementation of joint angle trajectories.
 *
 * @date October 2010
 **/

/*****************************************************************************
 ** Includes
 *****************************************************************************/

#include <ecl/linear_algebra.hpp> // has to be first (eigen stdvector defn).
#include "../../include/ecl/manipulators/waypoint.hpp"
#include "../../include/ecl/manipulators/trajectory.hpp"
#include <ecl/geometry/function_math.hpp>
#include <ecl/geometry/polynomial.hpp>
#include <ecl/math/simple.hpp>

/*****************************************************************************
 ** Debug Macros
 *****************************************************************************/

//#define DEBUG_LINEAR_INTERPOLATION
/*****************************************************************************
 ** Namespaces
 *****************************************************************************/

namespace ecl
{

/*****************************************************************************
 ** Implementation [Trajectory][QuinticTensionSplineInterpolation]
 *****************************************************************************/

void Trajectory<JointAngles>::tensionSplineInterpolation(const double &tension)
{
  bool result;
  unsigned int n = waypoints.size() - 1; // n = number of segments

  // who the hell made the constraint that this should be 5, shouldn't we only need 3 since we calculate 2 more pseudo points?
  ecl_assert_throw(
      n+1 >= 5,
      StandardException(LOC,ConfigurationError,"Not enough waypoints for a tension spline interpolation (must be >= 5)."));

  result = validateWaypoints(5);
  ecl_assert_throw(
      result,
      StandardException(LOC,ConfigurationError,"Not all the waypoint maximum rates have been specified correctly (must be > 0.0)."));

  result = initialiseWaypointDurations();
  ecl_assert_throw( result,
                   StandardException(LOC,ConfigurationError,"A waypoint was configured with a zero duration."));

  /******************************************
   ** Reserve Spline Storage Space
   *******************************************/
  clearSplines(); // Clean up any pre-existing definition.
  for (unsigned int j = 0; j < dimension(); ++j)
  {
    spline_functions[j].resize(3, NULL);
  }
  Array<TensionSpline> tension_splines(dimension());
  Array<QuinticPolynomial> leading_quintics(dimension()), trailing_quintics(dimension());

  /******************************************
   ** Roughly Generate Tension Spline
   *******************************************/
  bool splines_constrained = false;
  while (!splines_constrained)
  {
    tension_splines = generateTensionSplines(tension, 0.0);
    /*********************
     ** Check Max Accel
     **********************/
    Array<double> domain = tension_splines[0].domain();
    splines_constrained = true; // This changes to false if we break the max accel constraint
    // - tension splines have high accelerations at the joins.
    // - inbetween the joins, the acceleration goes towards zero.
    // - so we just check the size of the acceleration at the joins to find trouble spots.
    for (unsigned int i = 1; i < domain.size() - 1; ++i)
    { // Natural spline, first and last accelerations are always zero, so dont worry about them
      for (unsigned int j = 0; j < dimension(); ++j)
      {
        double accel = fabs(tension_splines[j].dderivative(domain[i]));
        /*********************
         ** Debugging
         **********************/
//                std::cout << "Accel checking" << std::endl;
//                std::cout << "  Domain: " << domain << std::endl;
//                std::cout << "  Accel[" << i << "," << j << "]: " << accel << std::endl;
//                sleep(1);
        if (accel > max_accelerations[j])
        {
          splines_constrained = false;
          double slope_before = fabs(
              (waypoints[i].angles()[j] - waypoints[i - 1].angles()[j]) / waypoints[i - 1].duration());
          double slope_after = fabs(
              (waypoints[i + 1].angles()[j] - waypoints[i].angles()[j]) / waypoints[i].duration());
//                    std::cout << "  Slope_Before[" << i << "," << j << "]: " << slope_before << std::endl;
//                    std::cout << "  Slope_After [" << i << "," << j << "]: " << slope_after << std::endl;
          if (slope_before > slope_after)
          {
            waypoints[i - 1].duration(waypoints[i - 1].duration() * 1.1); // 10% increase
          }
          else
          {
            waypoints[i].duration(waypoints[i].duration() * 1.1); // 10% increase
          }
//                    i = domain.size(); // Force it to restart <-- This doesn't actually work so well - dampen the whole curve at once instead of gradually from one end!
          break;
        }
      }
    }
  }
  /******************************************
   ** Check rates are set for head/tail
   *******************************************/
  // Note that we may yet change values[1] and values[n+1] when fixing the pseudo points below
  // Set them all to zero (default option, i.e. starting at rest).
  if (!waypoints[0].rates_configured())
  {
    waypoints[0].rates() = WayPoint<JointAngles>::JointDataArray::Constant(waypoints[0].dimension(), 0.0);
  }
  if (!waypoints[n].rates_configured())
  {
    waypoints[n].rates() = WayPoint<JointAngles>::JointDataArray::Constant(waypoints[n].dimension(), 0.0);
  }

  /******************************************
   ** Make the pre pseudo point.
   *******************************************/
  double leading_quintic_time = 0.0;
  bool quintic_constrained = false;
  while (!quintic_constrained)
  {
    quintic_constrained = true;
    for (unsigned int i = 1; i <= 5; ++i)
    {
      double t = i * waypoints[0].duration() / 10;
      // move the tension spline to the right, i.e. give us some space to insert a quintic
      tension_splines = generateTensionSplines(tension, t); // t <-- is the initial time to start the tension spline
      for (unsigned int j = 0; j < dimension(); ++j)
      {
        // find the right side boundary conditions for the quintic we want to insert
        double y_dot = tension_splines[j].derivative(2 * t);
        double y = tension_splines[j](2 * t);
        // the left side boundary conditions for the quintic
        double y_0 = waypoints[0].angles()[j];
        double y_0_dot = waypoints[0].rates()[j];
        leading_quintics[j] = QuinticPolynomial::Interpolation(0.0, y_0, y_0_dot, 0.0, 2 * t, y, y_dot, 0.0);

        /*********************
         ** Debugging
         **********************/
//			    std::cout << "Pre Pseudo Point" << std::endl;
//				std::cout << "  Domain: " << tension_splines[0].domain() << std::endl;
//				std::cout << "    y[" << i << "," << j << "]     : " << y << std::endl;
//				std::cout << "    y_dot[" << i << "," << j << "] : " << ydot << std::endl;
//				double accel_max = fabs( Maximum<CubicPolynomial>()(0.0,2*t,leading_quintics[j].derivative().derivative()));
//				if ( accel_max < fabs( Minimum<CubicPolynomial>()(0.0,2*t,leading_quintics[j].derivative().derivative()))  ) {
//					accel_max = fabs( Minimum<CubicPolynomial>()(0.0,2*t,leading_quintics[j].derivative().derivative()));
//				}
//				std::cout << "    accel[" << i << "," << j << "] : " << accel_max << std::endl;
//				sleep(1);
        if ((fabs(ecl::Maximum<CubicPolynomial>()(0.0, 2 * t, leading_quintics[j].derivative().derivative()))
            < fabs(max_accelerations[j]))
            && (fabs(ecl::Minimum<CubicPolynomial>()(0.0, 2 * t, leading_quintics[j].derivative().derivative()))
                < fabs(max_accelerations[j])))
        {
          if (j == dimension() - 1)
          { // all joints are constrained, great!
            leading_quintic_time = 2 * t;
            // Everything done, force it to completely bail out of these loops.
            quintic_constrained = true;
            i = 5;
          }
        }
        else
        { // failed to constrain for this i value.
          if (i == 5)
          { // If we get here, even up to half the length of the segment has failed.
            quintic_constrained = false;
          }
          break;
        }
      }
      if (!quintic_constrained)
      { // give up, go back to start of while loop with increased duration
//				std::cout << "Quintic unconstrained, increasing the first duration : " << waypoints[0].duration() << std::endl;
        waypoints[0].duration(waypoints[0].duration() * 1.1); // 10% increase
        break; // from the for loop
      }
    }
  }

  /******************************************
   ** Make the post pseudo point.
   *******************************************/
  double trailing_quintic_time_0 = 0.0;
  double trailing_quintic_time_f = 0.0;
  quintic_constrained = false;
  while (!quintic_constrained)
  {
    quintic_constrained = true;
    tension_splines = generateTensionSplines(tension, leading_quintic_time / 2);
    for (unsigned int i = 1; i <= 5; ++i)
    {
      double t = i * waypoints[n - 1].duration() / 10;
      double t_f = tension_splines[0].domain().back();
      for (unsigned int j = 0; j < dimension(); ++j)
      {
        double y_dot = tension_splines[j].derivative(t_f - t);
        double y = tension_splines[j](t_f - t);
        double y_f = waypoints[n].angles()[j];
        double y_f_dot = waypoints[n].rates()[j];
        trailing_quintics[j] = QuinticPolynomial::Interpolation(t_f - t, y, y_dot, 0.0, t_f + t, y_f, y_f_dot, 0.0);

        /*********************
         ** Debugging
         **********************/
//			    std::cout << "Post Pseudo Point" << std::endl;
//				std::cout << "  Domain: " << tension_splines[0].domain() << std::endl;
//				std::cout << "    y[" << i << "," << j << "]     : " << y << std::endl;
//				std::cout << "    y_dot[" << i << "," << j << "] : " << ydot << std::endl;
//				double accel_max = fabs( Maximum<CubicPolynomial>()(t_f-t,t_f+t,trailing_quintics[j].derivative().derivative()));
//				if ( accel_max < fabs( Minimum<CubicPolynomial>()(t_f-t,t_f+t,trailing_quintics[j].derivative().derivative()))  ) {
//					accel_max = fabs( Minimum<CubicPolynomial>()(t_f-t,t_f+t,trailing_quintics[j].derivative().derivative()));
//				}
//				std::cout << "    accel[" << i << "," << j << "] : " << accel_max << std::endl;
//				sleep(1);
        if ((fabs(Maximum<CubicPolynomial>()(t_f - t, t_f + t, trailing_quintics[j].derivative().derivative()))
            < fabs(max_accelerations[j]))
            && (fabs(Minimum<CubicPolynomial>()(t_f - t, t_f + t, trailing_quintics[j].derivative().derivative()))
                < fabs(max_accelerations[j])))
        {
          if (j == dimension() - 1)
          { // all joints are constrained, great!
            trailing_quintic_time_0 = tension_splines[j].domain().back() - t;
            trailing_quintic_time_f = tension_splines[j].domain().back() + t;
            // Everything done, force it to completely bail out of these loops.
            quintic_constrained = true;
            i = 5;
          }
        }
        else
        { // failed to constrain for this i value.
          if (i == 5)
          { // If we get here, even up to half the length of the segment has failed.
            quintic_constrained = false;
          }
          break;
        }
      }
      if (!quintic_constrained)
      { // give up, go back to start of while loop with increased duration
        waypoints[n - 1].duration(waypoints[n - 1].duration() * 1.1); // 10% increase
        break;
      }
    }
  }

  /*********************
   ** Debugging
   **********************/
//    std::cout << "Leading Quintic Time :" << leading_quintic_time << std::endl;
//    std::cout << "Trailing Quintic Time:" << trailing_quintic_time_0 << " "  << trailing_quintic_time_f << std::endl;
  /******************************************
   ** Finalise
   *******************************************/
  trajectory_duration = trailing_quintic_time_f;
  for (unsigned int j = 0; j < dimension(); ++j)
  {
    spline_functions[j][0] = new SplineFunction<QuinticPolynomial>(0.0, leading_quintic_time, leading_quintics[j]);
    spline_functions[j][1] = new SplineFunction<TensionSpline>(leading_quintic_time, trailing_quintic_time_0,
                                                               tension_splines[j]);
    spline_functions[j][2] = new SplineFunction<QuinticPolynomial>(trailing_quintic_time_0, trailing_quintic_time_f,
                                                                   trailing_quintics[j]);
  }
  (void) result; // for unused variable warnings, in case the asserts weren't triggered
}

void Trajectory<JointAngles>::linearSplineInterpolation()
{
  if (!validateWaypoints(2))
  {
    throw StandardException(LOC, ConfigurationError,
                            "Not all the waypoint maximum rates have been specified correctly (must be > 0.0).");
  }
  if (!initialiseWaypointDurations())
  {
    throw StandardException(LOC, ConfigurationError, "A waypoint was configured with a zero duration.");
  }

  /******************************************
   ** Reserve Spline Storage Space
   *******************************************/
  clearSplines(); // Clean up any pre-existing definition.
  for (unsigned int j = 0; j < dimension(); ++j)
  {
    spline_functions[j].resize(1, NULL);
  }
  Array<SmoothLinearSpline> splines(dimension());

  /******************************************
   ** Generate Splines
   *******************************************/
  bool splines_constrained = false;
  int n = waypoints.size() - 1;
  while (!splines_constrained)
  {
    try
    {
      splines = generateLinearSplines();
      splines_constrained = true;
#ifdef DEBUG_LINEAR_INTERPOLATION
      std::cout << "Linear Interpolation: spline generation success" << std::endl;
#endif
    }
    catch (DataException<int> &e)
    {
      /*********************
       ** Stretch Waypoints
       **********************/
      if (e.data() <= 0)
      {
#ifdef DEBUG_LINEAR_INTERPOLATION
        std::cout << "Linear Interpolation: spline generation failed trying to create pre-pseudo, stretching first segment" << std::endl;
#endif
        waypoints[0].duration(waypoints[0].duration() * 1.1); // 10% increase to w_{0}-w_{1} duration
      }
      else if (e.data() == 1)
      { // error at corner prepseudo-w0-w1
#ifdef DEBUG_LINEAR_INTERPOLATION
        std::cout << "Linear Interpolation: spline generation failed, stretching at corner " << e.data() << std::endl;
#endif
        waypoints[0].duration(waypoints[0].duration() * 1.1); // 10% increase to w_{0}-w_{1} duration
      }
      else if (e.data() >= n + 1)
      { // error at corner w_{n-1}-w_{n}-postpseudo
#ifdef DEBUG_LINEAR_INTERPOLATION
        std::cout << "Linear Interpolation: spline generation failed, stretching at corner " << e.data() << std::endl;
#endif
        waypoints[n - 1].duration(waypoints[n - 1].duration() * 1.1); // 10% increase to w_{n-1}-w_{n} duration
      }
      else if (e.data() >= n + 2)
      {
        // occurs when trying to create the post-pseudo point
        waypoints[n - 1].duration(waypoints[n - 1].duration() * 1.1); // 10% increase to w_{n-1}-w_{n} duration
#ifdef DEBUG_LINEAR_INTERPOLATION
        std::cout << "Linear Interpolation: spline generation failed trying to create post-pseudo, stretching last segment" << std::endl;
#endif
      }
      else
      {
#ifdef DEBUG_LINEAR_INTERPOLATION
        std::cout << "Linear Interpolation: spline generation failed, stretching at corner " << e.data() << std::endl;
#endif
        waypoints[e.data() - 2].duration(waypoints[e.data() - 2].duration() * 1.05); // 5% increase on either side
        waypoints[e.data() - 1].duration(waypoints[e.data() - 1].duration() * 1.05); // 5% increase on either side
      }
    }
  }

  /******************************************
   ** Finalise
   *******************************************/
  trajectory_duration = splines[0].domain().back() - splines[0].domain().front();
  for (unsigned int j = 0; j < dimension(); ++j)
  {
    spline_functions[j][0] = new SplineFunction<SmoothLinearSpline>(0.0, splines[j].domain().back(), splines[j]);
  }
}

/*****************************************************************************
 ** Implementation [Trajectory][Access]
 *****************************************************************************/

double Trajectory<JointAngles>::operator ()(const unsigned int& joint, const double& time)

{

  double t_f = spline_functions[joint][spline_functions[joint].size() - 1]->domain()[1];
  ecl_assert_throw( ( time >= 0.0 ) && ( time <= t_f + 0.0001 ), StandardException(LOC,OutOfRangeError));
  unsigned int i;
  for (i = 0; i < spline_functions[joint].size(); ++i)
  {
    if (time <= spline_functions[joint][i]->domain()[1])
    {
      return (*(spline_functions[joint][i]))(time);
    }
  }
  // Sometimes machine precision can kill off some of the inequality arguments above (like e^{-16} error). Fallback:
  return (*(spline_functions[joint][spline_functions[joint].size() - 1]))(t_f);
}

double Trajectory<JointAngles>::derivative(const unsigned int& joint, const double& time)

{

  double t_f = spline_functions[joint][spline_functions[joint].size() - 1]->domain()[1];
  ecl_assert_throw( ( time >= 0.0 ) && ( time <= t_f + 0.0001 ), StandardException(LOC,OutOfRangeError));
  unsigned int i;
  for (i = 0; i < spline_functions[joint].size(); ++i)
  {
    if (time <= spline_functions[joint][i]->domain()[1])
    {
      return spline_functions[joint][i]->derivative(time);
      break;
    }
  }
  // Sometimes machine precision can kill off some of the inequality arguments above (like e^{-16} error). Fallback:
  return spline_functions[joint][spline_functions[joint].size() - 1]->derivative(t_f);
}

double Trajectory<JointAngles>::dderivative(const unsigned int& joint, const double& time)

{

  double t_f = spline_functions[joint][spline_functions[joint].size() - 1]->domain()[1];
  ecl_assert_throw( ( time >= 0.0 ) && ( time <= t_f + 0.0001 ), StandardException(LOC,OutOfRangeError));
  unsigned int i;
  for (i = 0; i < spline_functions[joint].size(); ++i)
  {
    if (time <= spline_functions[joint][i]->domain()[1])
    {
      return spline_functions[joint][i]->dderivative(time);
      break;
    }
  }
  // Sometimes machine precision can kill off some of the inequality arguments above (like e^{-16} error). Fallback:
  return spline_functions[joint][spline_functions[joint].size() - 1]->dderivative(t_f);
}

/*****************************************************************************
 ** Implementation [Trajectory][Private]
 *****************************************************************************/

bool Trajectory<JointAngles>::validateWaypoints(unsigned int min_no_waypoints)
{

  unsigned int n = waypoints.size() - 1; // n = number of segments
  if (n + 1 < min_no_waypoints)
  {
    return false;
  }

  for (unsigned int i = 0; i < n; ++i)
  { // Dont care about the last waypoint w_n
    for (unsigned int j = 0; j < waypoints[i].nominalRates().size(); ++j)
    {
      if (waypoints[i].nominalRates()[j] <= 0.0)
      {
        return false;
      }
    }
  }
  return true;
}

bool Trajectory<JointAngles>::initialiseWaypointDurations()
{

  unsigned int n = waypoints.size() - 1; // n = number of segments

  // Waypoint durations are often not configured and default to 0.0

  // Here we check the nominal rates and angle differences to automatically guess a
  // duration. If the checks are ok, and this is bigger than the configured
  // waypoint duration, then replace the waypoint duration with this calculation.
  for (unsigned int i = 0; i < n; ++i)
  { // Dont need to worry about the w_n's duration.
    double max_duration = 0.0;
    for (unsigned int j = 0; j < dimension(); ++j)
    {
      double distance = fabs(waypoints[i + 1].angles()[j] - waypoints[i].angles()[j]);
      if (waypoints[i].nominalRates()[j] != 0.0)
      {
        double segment_duration = distance / waypoints[i].nominalRates()[j]; // Time = Distance/Velocity
        if (segment_duration > max_duration)
        {
          max_duration = segment_duration;
        }
      }
    }
    if (max_duration > waypoints[i].duration())
    {
      waypoints[i].duration(max_duration);
    }
    if (waypoints[i].duration() == 0.0)
    {
      return false;
    }
  }
  return true;
}

void Trajectory<JointAngles>::clearSplines()
{
  for (unsigned int joint = 0; joint < dimension(); ++joint)
  {
    for (unsigned int function = 0; function < spline_functions[joint].size(); ++function)
    {
      if (spline_functions[joint][function] != NULL)
      {
        delete spline_functions[joint][function];
        spline_functions[joint][function] = NULL;
      }
    }
    spline_functions[joint].clear();
  }
}

void Trajectory<JointAngles>::updateDuration()
{
  double total_time = 0.0;
//    std::cout << "Durations: ";
  for (unsigned int i = 0; i < waypoints.size() - 1; ++i)
  {
    total_time += waypoints[i].duration();
//        std::cout << waypoints[i].duration() << " ";
  }
//    std::cout << std::endl;
  trajectory_duration = total_time;
}

Array<SmoothLinearSpline> Trajectory<JointAngles>::generateLinearSplines()
{
  // n = number of segments
  // n+1 = number of input waypoints
  // n+3 = number of waypoints (inc. pre-post pseudo)

  // This is a bit different from the cubic as we don't  use this in a combo interpolater.
  Array<SmoothLinearSpline> splines(dimension());
  unsigned int n = waypoints.size() - 1; // n = number of segments
  Array<double> waypoint_times(n + 3), values(n + 3); // Including pre and post points

  /******************************************
   ** Check rates are set for head/tail
   *******************************************/
  // Note that we may yet change values[1] and values[n+1] when fixing the pseudo points below
  // Set them all to zero (default option, i.e. starting at rest).
  if (!waypoints[0].rates_configured())
  {
    waypoints[0].rates() = WayPoint<JointAngles>::JointDataArray::Constant(waypoints[0].dimension(), 0.0);
  }
  if (!waypoints[n].rates_configured())
  {
    waypoints[n].rates() = WayPoint<JointAngles>::JointDataArray::Constant(waypoints[n].dimension(), 0.0);
  }

  /******************************************
   ** Make the pre pseudo point.
   *******************************************/
  /*
   * Pull back the first waypoint, find intersection of initial tangent line and the nominal rate line.
   * Why? This lets us ensure the first segment is of the specified velocity, and the second segment will
   * fall the correct between nominal rates required to get to w_1.
   *
   *    x_
   *   ^  \__
   *  /      \
   * o ------ o
   *         /
   *        /
   *       x
   *
   * - diagonal lines : nominal rate slopes
   * - x : possible pseudo waypoints (at intersection of initial velocity line and nominal rate line)
   *
   * Basic process:
   *
   *  - pullback a bit
   *  - get intersections as above
   *  - find minimum time intersection time (t_first_duration)
   *  - synchronise a pseudo waypoint at that time on the initial tangents for each joint (only 1 of these will be an actual intersection point)
   *  - check acceleration constraints of quintics for this waypoint at each joint
   *  - if fail, pullback again, if success, done!
   */
  std::vector<LinearFunction> initial_tangents; // these are the lines from potential pseudo point to w_1, our eventual pseudo point must lie on it.
  std::vector<double> initial_angles, initial_rates;
  for (unsigned int j = 0; j < dimension(); ++j)
  {
    initial_angles.push_back(waypoints[0].angles()[j]);
    initial_rates.push_back(waypoints[0].rates()[j]);
    initial_tangents.push_back(LinearFunction::PointSlopeForm(0, initial_angles[j], initial_rates[j]));
  }
  std::vector<CartesianPoint2d, Eigen::aligned_allocator<CartesianPoint2d> > pseudo_points(dimension());
  std::vector<LinearFunction> nominal_rate_lines(dimension());
  WayPoint<JointAngles> pre_pseudo_waypoint(dimension());
  double t_pullback = 0.001; // start with 1ms
  double t_pullback_max_ = waypoints[0].duration();
  double t_pre_intersect_duration = 0.0; // duration from the pulled back wp0 to the intersection point
  bool acceleration_constraint_broken = true;
  while (acceleration_constraint_broken && (t_pullback <= t_pullback_max_))
  {
    // establish t_pre_intersect_duration as the minimum time to the intersection of initial tangent
    // and nominal rate line
    t_pre_intersect_duration = t_pullback_max_ / 2;
    for (unsigned int j = 0; j < dimension(); ++j)
    {
      LinearFunction nominal_rate_line = LinearFunction::PointSlopeForm(
          t_pullback, initial_angles[j], -1 * ecl::psign(initial_rates[j]) * waypoints[0].nominalRates()[j]);
      CartesianPoint2d pseudo_point = LinearFunction::Intersection(initial_tangents[j], nominal_rate_line);
      if (pseudo_point.x() < t_pre_intersect_duration)
      {
        t_pre_intersect_duration = pseudo_point.x();
      }
      nominal_rate_lines[j] = nominal_rate_line;
    }
    acceleration_constraint_broken = false;
    for (unsigned int j = 0; j < dimension(); ++j)
    {
      CartesianPoint2d pseudo_point(t_pre_intersect_duration, initial_tangents[j](t_pre_intersect_duration));
      // from the pseudo way point to the next way point (wp1)
      double pseudo_point_duration = t_pullback + waypoints[0].duration() - t_pre_intersect_duration;
      // Will test 5 positions, which cover all of t_pre_intersect_duration
      // and half of pseudo_point_duration
      for (unsigned int i = 1; i <= 5; ++i)
      {
        double t_l = t_pre_intersect_duration - i * t_pre_intersect_duration / 5.0;
        double t_r = t_pre_intersect_duration + i * pseudo_point_duration / 10.0;
        LinearFunction segment = LinearFunction::Interpolation(pseudo_point.x(), pseudo_point.y(),
                                                               t_pullback + waypoints[0].duration(),
                                                               waypoints[1].angles()[j]);
        double y_0 = initial_tangents[j](t_l);
        double y_0_dot = initial_tangents[j].derivative(t_l);
        double y = segment(t_r);
        double y_dot = segment.derivative(t_r); // slope
        QuinticPolynomial quintic = QuinticPolynomial::Interpolation(t_l, y_0, y_0_dot, 0.0, t_r, y, y_dot, 0.0);
        if ((fabs(CubicPolynomial::Maximum(t_l, t_r, quintic.derivative().derivative())) < fabs(max_accelerations[j]))
            && (fabs(CubicPolynomial::Minimum(t_l, t_r, quintic.derivative().derivative())) < fabs(max_accelerations[j])))
        {
          acceleration_constraint_broken = false;
          break; // we're good, get out and continue through all the joints
        }
        if (i == 5)
        {
#ifdef DEBUG_LINEAR_INTERPOLATION
          std::cout << "Linear Interpolation: pre psuedo point failed with acceleration checks [" << t_pre_intersect_duration << "][" << t_pullback << "]" << std::endl;
#endif
          acceleration_constraint_broken = true;
        }
      }
    }
    t_pullback = t_pullback * 2; // takes 11 runs to get from 1ms to 1s; adjust, if this is too much
  }
  if (acceleration_constraint_broken)
  {
    throw DataException<int>(LOC, ConstructorError, "Max acceleration bound broken by pre pseudo point.", 0);
  }
  pre_pseudo_waypoint.duration(t_pullback + waypoints[0].duration() - t_pre_intersect_duration);
  for (unsigned int j = 0; j < dimension(); ++j)
  {
    pre_pseudo_waypoint.angles()[j] = initial_tangents[j](t_pre_intersect_duration);
  }
#ifdef DEBUG_LINEAR_INTERPOLATION
  std::cout << "Linear Interpolation: pre psuedo point done!" << std::endl;
  std::cout << "                    : angles " << pre_pseudo_waypoint.angles() << std::endl;
  std::cout << "                    : pre pseudo duration " << t_pre_intersect_duration << std::endl;
  std::cout << "                    : modified first waypoint duration " << pre_pseudo_waypoint.duration() << std::endl;
#endif

  /******************************************
   ** Make the post pseudo point.
   *******************************************/
  std::vector<double> final_angles, final_rates;
  for (unsigned int j = 0; j < dimension(); ++j)
  {
    final_angles.push_back(waypoints[n].angles()[j]);
    final_rates.push_back(waypoints[n].rates()[j]);
    nominal_rate_lines[j] = LinearFunction::PointSlopeForm(
        0, final_angles[j], -1 * ecl::psign(final_rates[j]) * waypoints[n - 1].nominalRates()[j]);
  }
  std::vector<LinearFunction> final_tangents(dimension());
  WayPoint<JointAngles> post_pseudo_waypoint(dimension());
  double t_pullforward = 0.001; // start with 1ms
  double t_pullforward_max_ = waypoints[n - 1].duration();
  double t_post_intersect_duration = 0.0; // duration from the pulled back wp0 to the intersection point
  acceleration_constraint_broken = true;
  while (acceleration_constraint_broken && (t_pullforward <= t_pullforward_max_))
  {
    // establish t_final as the maximum time to the intersection of final tangent and nominal rate line
    t_post_intersect_duration = 0.0;
    for (unsigned int j = 0; j < dimension(); ++j)
    {
      LinearFunction final_tangent = LinearFunction::PointSlopeForm(t_pullforward, final_angles[j], final_rates[j]);
      final_tangents[j] = final_tangent;
      CartesianPoint2d pseudo_point = LinearFunction::Intersection(final_tangents[j], nominal_rate_lines[j]);
      if (pseudo_point.x() > t_post_intersect_duration)
      {
        t_post_intersect_duration = pseudo_point.x();
      }
    }
    // check acceleration constraints
    acceleration_constraint_broken = false;
    for (unsigned int j = 0; j < dimension(); ++j)
    {
      CartesianPoint2d pseudo_point(t_post_intersect_duration, final_tangents[j](t_post_intersect_duration));
      double pseudo_point_duration = t_pullforward - t_post_intersect_duration;
      for (unsigned int i = 1; i <= 5; ++i)
      {
        double t_l = t_post_intersect_duration - i * (waypoints[n - 1].duration() + t_post_intersect_duration) / 10.0;
        double t_r = t_post_intersect_duration + i * pseudo_point_duration / 5.0;
        LinearFunction segment = LinearFunction::Interpolation(-waypoints[n - 1].duration(),
                                                               waypoints[n - 1].angles()[j], pseudo_point.x(),
                                                               pseudo_point.y());
        double y_0 = segment(t_l);
        double y_0_dot = segment.derivative(t_l);
        double y = final_tangents[j](t_r);
        double y_dot = final_tangents[j].derivative(t_r);
        QuinticPolynomial quintic = QuinticPolynomial::Interpolation(t_l, y_0, y_0_dot, 0.0, t_r, y, y_dot, 0.0);
        if ((fabs(CubicPolynomial::Maximum(t_l, t_r, quintic.derivative().derivative())) < fabs(max_accelerations[j]))
            && (fabs(CubicPolynomial::Minimum(t_l, t_r, quintic.derivative().derivative())) < fabs(max_accelerations[j])))
        {
          acceleration_constraint_broken = false;
          break; // we're good, get out and continue through all the joints
        }
        if (i == 5)
        {
#ifdef DEBUG_LINEAR_INTERPOLATION
          std::cout << "Linear Interpolation: post psuedo point failed with acceleration checks [" << t_post_intersect_duration << "][" << t_pullforward << "]" << std::endl;
#endif
          acceleration_constraint_broken = true;
        }
      }
    }
    t_pullforward = t_pullforward * 2; // takes 12 runs to get from 1ms to 1s, adjust, if this is too much
  }
  if (acceleration_constraint_broken)
  {
    throw DataException<int>(LOC, ConstructorError, "Max acceleration bound broken by pre pseudo point.", 0);
  }
  post_pseudo_waypoint.duration(t_pullforward - t_post_intersect_duration);
  for (unsigned int j = 0; j < dimension(); ++j)
  {
    post_pseudo_waypoint.angles()[j] = final_tangents[j](t_post_intersect_duration);
  }
#ifdef DEBUG_LINEAR_INTERPOLATION
  std::cout << "Linear Interpolation: post psuedo point done!" << std::endl;
  std::cout << "                    : angles " << post_pseudo_waypoint.angles() << std::endl;
  std::cout << "                    : modified last point duration " << waypoints[n-1].duration() + t_post_intersect_duration << std::endl;
  std::cout << "                    : post pseudo duration " << post_pseudo_waypoint.duration() << std::endl;
#endif

  /*********************
   ** Waypoint Times
   **********************/
  // n+3 points (w_0...w_n + pre and post pseudos)
  // n+3 waypoint_times
  waypoint_times[0] = 0.0;
  waypoint_times[1] = t_pre_intersect_duration;
  waypoint_times[2] = t_pre_intersect_duration + pre_pseudo_waypoint.duration();
  for (unsigned int i = 2; i < n; ++i)
  {
    waypoint_times[i + 1] = waypoint_times[i] + waypoints[i - 1].duration();
  }
  waypoint_times[n + 1] = waypoint_times[n] + waypoints[n - 1].duration() + t_post_intersect_duration;
  waypoint_times[n + 2] = waypoint_times[n + 1] + post_pseudo_waypoint.duration();

#ifdef DEBUG_LINEAR_INTERPOLATION
  std::cout << "Linear Interpolation: waypoint time estimates before interpolation: " << waypoint_times << std::endl;
#endif

  for (unsigned int j = 0; j < dimension(); ++j)
  {
    /******************************************
     ** Set Values
     *******************************************/
    values[0] = waypoints[0].angles()[j];
    values[1] = pre_pseudo_waypoint.angles()[j];
    for (unsigned int i = 2; i <= n; ++i)
    {
      values[i] = waypoints[i - 1].angles()[j];
    }
    values[n + 1] = post_pseudo_waypoint.angles()[j];
    values[n + 2] = waypoints[n].angles()[j];
#ifdef DEBUG_LINEAR_INTERPOLATION
    std::cout << "Linear Interpolation: values[" << j << "]: " << values << std::endl;
#endif

    /******************************************
     ** Generate Spline
     *******************************************/
    try
    {
      splines[j] = SmoothLinearSpline::Interpolation(waypoint_times, values, max_accelerations[j]);
    }
    catch (DataException<int> &e)
    {
      throw DataException<int>(LOC, e);
    }
  }
#ifdef DEBUG_LINEAR_INTERPOLATION
  for ( unsigned int j = 0; j < dimension(); ++j)
  {
    std::cout << "Linear Interpolation: discretised domain [" << j << "]: " << splines[j].domain() << std::endl;
  }
#endif
  return splines;
}

Array<TensionSpline> Trajectory<JointAngles>::generateTensionSplines(const double& tension, const double initial_time)
{

  Array<TensionSpline> tension_splines(dimension());
  unsigned int n = waypoints.size() - 1; // n = number of segments
  // Include all waypoints (even w_0 and w_n). We set up pre and post pseudo points later.
  Array<double> waypoint_times(n + 1), values(n + 1);
  waypoint_times[0] = initial_time;
  for (unsigned int i = 1; i < n + 1; ++i)
  {
    waypoint_times[i] = waypoint_times[i - 1] + waypoints[i - 1].duration();
  }

  for (unsigned int j = 0; j < dimension(); ++j)
  {
    for (unsigned int i = 0; i < n + 1; ++i)
    {
      values[i] = waypoints[i].angles()[j];
    }
    tension_splines[j] = TensionSpline::Natural(waypoint_times, values, tension);
  }
  return tension_splines;
}

} // namespace ecl
