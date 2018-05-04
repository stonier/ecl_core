##############################################################################
# Files
##############################################################################

add_executable(demo_float_converters float_converters.cpp)
target_link_libraries(demo_float_converters
  ${PROJECT_NAME}
)
install(TARGETS demo_float_converters RUNTIME DESTINATION lib/${PROJECT_NAME})
