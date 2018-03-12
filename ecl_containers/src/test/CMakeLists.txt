###############################################################################
# Google Tests Macro
###############################################################################

macro(ecl_containers_add_gtest test_name)
  ament_add_gtest(ecl_test_${test_name} ${test_name}.cpp)
  if(TARGET ecl_test_${test_name})
    target_link_libraries(ecl_test_${test_name}
      ${ecl_config_LIBRARIES}
      ${ecl_errors_LIBRARIES}
      ${ecl_exceptions_LIBRARIES}
      ${ecl_formatters_LIBRARIES}
      ${ecl_converters_LIBRARIES}
      ${ecl_mpl_LIBRARIES}
      ${ecl_type_traits_LIBRARIES}
      ${ecl_utilities_LIBRARIES}
    )
  endif()
endmacro()

###############################################################################
# Google Tests
###############################################################################

ecl_containers_add_gtest(arrays)
ecl_containers_add_gtest(arrays_mem_check)
ecl_containers_add_gtest(container_converters)
ecl_containers_add_gtest(stencil)
ecl_containers_add_gtest(fifo)
ecl_containers_add_gtest(push_and_pop)


