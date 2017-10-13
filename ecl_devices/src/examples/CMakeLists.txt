###############################################################################
# Examples
###############################################################################

add_executable(demo_serial_timeouts serial_timeouts.cpp)
target_link_libraries(demo_serial_timeouts ${PROJECT_NAME} 
  ${ecl_config_LIBRARIES}
  ${ecl_errors_LIBRARIES}
  ${ecl_mpl_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
  ${ecl_utilities_LIBRARIES}
  ${ecl_containers_LIBRARIES}
  ${ecl_threads_LIBRARIES}
)
install(TARGETS demo_serial_timeouts RUNTIME DESTINATION bin)
