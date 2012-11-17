###############################################################################
# GTEST SETUP
###############################################################################

ecl_add_example(demo_sleep sleep.cpp)
target_link_libraries(demo_sleep ecl_time)
