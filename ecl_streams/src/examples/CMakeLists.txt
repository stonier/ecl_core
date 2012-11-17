##############################################################################
# Files
##############################################################################

ecl_add_example(demo_console_streams console_streams.cpp)
target_link_libraries(demo_console_streams ${PROJECT_NAME})

ecl_add_example(demo_log_streams log_streams.cpp)
target_link_libraries(demo_log_streams ${PROJECT_NAME})
