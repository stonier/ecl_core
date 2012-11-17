###############################################################################
# GTEST SETUP
###############################################################################

ecl_add_example(demo_formatters formatters.cpp)
target_link_libraries(demo_formatters ecl_formatters)
