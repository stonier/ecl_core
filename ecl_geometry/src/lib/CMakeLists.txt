###############################################################################
# SOURCES
###############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

###############################################################################
# INSTALL
###############################################################################

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} 
  ${ecl_build_LIBRARIES}
  ${ecl_config_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
  ${ecl_containers_LIBRARIES}
  ${ecl_formatters_LIBRARIES}
  ${ecl_linear_algebra_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_math_LIBRARIES}
  ${ecl_mpl_LIBRARIES}
)
install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION bin
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
