##############################################################################
# Files
##############################################################################

add_executable(demo_console_streams console_streams.cpp)
target_link_libraries(demo_console_streams ${PROJECT_NAME} 
  ${ecl_errors_LIBRARIES}
  ${ecl_concepts_LIBRARIES}
  ${ecl_devices_LIBRARIES}
  ${ecl_time_LIBRARIES}
  ${ecl_converters_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
)
install(TARGETS demo_console_streams RUNTIME DESTINATION bin)

add_executable(demo_log_streams log_streams.cpp)
target_link_libraries(demo_log_streams ${PROJECT_NAME} 
  ${ecl_errors_LIBRARIES}
  ${ecl_concepts_LIBRARIES}
  ${ecl_devices_LIBRARIES}
  ${ecl_time_LIBRARIES}
  ${ecl_converters_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
)
install(TARGETS demo_log_streams RUNTIME DESTINATION bin)
