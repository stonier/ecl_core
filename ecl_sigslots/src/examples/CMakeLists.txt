##############################################################################
# Files
##############################################################################

ecl_add_example(demo_sigslots_manager sigslots_manager.cpp)
target_link_libraries(demo_sigslots_manager ${PROJECT_NAME})

ecl_add_example(demo_sigslots sigslots.cpp)
target_link_libraries(demo_sigslots ${PROJECT_NAME})
