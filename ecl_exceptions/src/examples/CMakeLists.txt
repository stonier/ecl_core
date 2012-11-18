##############################################################################
# Files
##############################################################################

add_executable(demo_exceptions exceptions.cpp)
target_link_libraries(demo_exceptions ${PROJECT_NAME})
install(TARGETS demo_exceptions RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})


add_executable(demo_exception_tracer exception_tracer.cpp)
install(TARGETS demo_exception_tracer RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
