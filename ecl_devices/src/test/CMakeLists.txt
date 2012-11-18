###############################################################################
# GTEST SETUP
###############################################################################

macro(ecl_devices_add_gtest test_name)
  catkin_add_gtest(ecl_test_${test_name} ${test_name}.cpp)
  target_link_libraries(ecl_test_${test_name} ${PROJECT_NAME} ${catkin_LIBRARIES})
endmacro()

ecl_devices_add_gtest(shared_files)
ecl_devices_add_gtest(files)


