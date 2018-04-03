##############################################################################
# Google Test Macro
##############################################################################

macro(ecl_linear_algebra_add_gtest test_name)
  ament_add_gtest(ecl_test_linear_algebra_${test_name} ${test_name}.cpp)
  if(TARGET ecl_test_linear_algebra_${test_name})
    target_include_directories(
      ecl_test_linear_algebra_${test_name}
      PRIVATE
        $<INSTALL_INTERFACE:${Sophus_INCLUDE_DIRS}>
    )
    target_link_libraries(ecl_test_linear_algebra_${test_name}
      ${PROJECT_NAME}
	  ecl_eigen::ecl_eigen
	  ecl_exceptions::ecl_exceptions
	  ecl_formatters::ecl_formatters
	  ecl_math::ecl_math
    )
    # Hack just to make sure our tests pass if we're using external eigen3
    # Note that this is covered for dependant packages
    # in the manifest.xml externally via a hunt for pkg-config
    if ( EIGEN3_INCLUDE_DIR )
      set_target_properties(ecl_test_linear_algebra_${test_name} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS} -I${EIGEN3_INCLUDE_DIR}")
    endif()
  endif()
endmacro()

##############################################################################
# Google Tests
##############################################################################

ecl_linear_algebra_add_gtest(plugin)
ecl_linear_algebra_add_gtest(formatters)
ecl_linear_algebra_add_gtest(interpolators)

