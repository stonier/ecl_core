###############################################################################
# Examples
###############################################################################

ecl_add_example(demo_serial_timeouts serial_timeouts.cpp)
target_link_libraries(demo_serial_timeouts -lecl_devices)

