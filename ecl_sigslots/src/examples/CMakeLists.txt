##############################################################################
# Files
##############################################################################

add_executable(demo_sigslots_manager sigslots_manager.cpp)
target_link_libraries(demo_sigslots_manager 
  ${ecl_config_LIBRARIES}
  ${ecl_threads_LIBRARIES}
  )
install(TARGETS demo_sigslots_manager RUNTIME DESTINATION bin)

add_executable(demo_sigslots sigslots.cpp)
target_link_libraries(demo_sigslots 
  ${ecl_config_LIBRARIES}
  ${ecl_threads_LIBRARIES}
)
install(TARGETS demo_sigslots RUNTIME DESTINATION bin)
