###############################################################################
# Macro
###############################################################################

macro(ecl_devices_add_gtest test_name)
  ament_add_gtest(ecl_test_${test_name} ${test_name}.cpp)
  if(TARGET ecl_test_${test_name})
    target_link_libraries(ecl_test_${test_name}
      ${PROJECT_NAME}
      ecl_config::ecl_config
      ecl_containers::ecl_containers
      ecl_errors::ecl_errors
      ecl_mpl::ecl_mpl
      ecl_threads::ecl_threads
      ecl_type_traits::ecl_type_traits
      ecl_utilities::ecl_utilities
    )
  endif()
endmacro()

###############################################################################
# Google Tests
###############################################################################

ecl_devices_add_gtest(shared_files)
ecl_devices_add_gtest(files)


