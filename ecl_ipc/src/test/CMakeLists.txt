###############################################################################
# Gtest
###############################################################################


macro(ecl_ipc_add_gtest test_name)
  catkin_add_gtest(test_${test_name} ${test_name}.cpp)
  target_link_libraries(test_${test_name} ${PROJECT_NAME} ${catkin_LIBRARIES})
endmacro()

ecl_ipc_add_gtest(shared_memory)
ecl_ipc_add_gtest(semaphores)
ecl_ipc_add_gtest(semaphores_timed)

