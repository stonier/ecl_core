##############################################################################
# Files
##############################################################################

add_executable(demo_float_converters float_converters.cpp)
target_link_libraries(demo_float_converters 
  ${ecl_config_LIBRARIES}
  ${ecl_mpl_LIBRARIES}
  ${ecl_errors_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
  ${ecl_concepts_LIBRARIES}
  )
install(TARGETS demo_float_converters RUNTIME DESTINATION bin)

#target_link_libraries(demo_exceptions ${PROJECT_NAME})
