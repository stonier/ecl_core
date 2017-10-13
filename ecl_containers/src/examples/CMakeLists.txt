###############################################################################
# Examples
###############################################################################

add_executable(demo_container_formatters formatters.cpp)
target_link_libraries(demo_container_formatters 
  ${ecl_config_LIBRARIES}
  ${ecl_errors_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_formatters_LIBRARIES}
  ${ecl_converters_LIBRARIES}
  ${ecl_mpl_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
  ${ecl_utilities_LIBRARIES}
)
install(TARGETS demo_container_formatters RUNTIME DESTINATION bin)
