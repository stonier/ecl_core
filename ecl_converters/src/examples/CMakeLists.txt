##############################################################################
# Files
##############################################################################

add_executable(demo_float_converters float_converters.cpp)
target_link_libraries(demo_float_converters ${catkin_LIBRARIES})
install(TARGETS demo_float_converters RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

#target_link_libraries(demo_exceptions ${PROJECT_NAME})
