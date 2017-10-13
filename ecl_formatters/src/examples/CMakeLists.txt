###############################################################################
# GTEST SETUP
###############################################################################

add_executable(demo_formatters formatters.cpp)
target_link_libraries(demo_formatters ${PROJECT_NAME} 
  ${ecl_config_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_converters_LIBRARIES}
)
install(TARGETS demo_formatters RUNTIME DESTINATION bin)
