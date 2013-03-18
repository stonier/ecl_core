###############################################################################
# Sources
###############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

###############################################################################
# External Library Dependencies
###############################################################################

if(ECL_PLATFORM_HAS_POSIX_THREADS) 
  set (thread_LIBRARIES "-pthread")
endif()

# Remove leading and trailing whitespace
string(STRIP "${LIBRARIES}" LIBRARIES) 

###############################################################################
# Install
###############################################################################

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${thread_LIBRARIES})
install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

