##############################################################################
# Files
##############################################################################

ecl_add_example(demo_exceptions exceptions.cpp)
target_link_libraries(demo_exceptions ${PROJECT_NAME})

ecl_add_example(demo_exception_tracer exception_tracer.cpp)
