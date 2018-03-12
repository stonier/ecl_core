###############################################################################
# Macro
###############################################################################

macro(ecl_devices_add_gtest test_name)
  ament_add_gtest(ecl_test_${test_name} ${test_name}.cpp)
  if(TARGET ecl_test_${test_name})
    target_link_libraries(ecl_test_${test_name} ${PROJECT_NAME}
      ${ecl_config_LIBRARIES}
      ${ecl_errors_LIBRARIES}
      ${ecl_mpl_LIBRARIES}
      ${ecl_type_traits_LIBRARIES}
      ${ecl_utilities_LIBRARIES}
      ${ecl_containers_LIBRARIES}
      ${ecl_threads_LIBRARIES}
    )
  endif()
endmacro()

###############################################################################
# Google Tests
###############################################################################

ecl_devices_add_gtest(shared_files)
ecl_devices_add_gtest(files)


