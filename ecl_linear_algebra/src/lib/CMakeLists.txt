##############################################################################
# Sources
##############################################################################

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp) 

##############################################################################
# Library
##############################################################################

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} )
# This is a way of ensuring that users of this library will also compile
# with the -std=c++11 flag. Otherwise they have to go and insert the option
# manually themselves in every library that calls this one. Only works for
# cmake > 2.8.12. This trick comes from ceres-solver:
#
#    https://ceres-solver.googlesource.com/ceres-solver/+/master/internal/ceres/CMakeLists.txt
#
# Note, there are better ways of doing this in 3.1+.
#
# Another alternative is to use target_compile_features if there is a
# specific feature that you require. I can't find anything that enables
# shared pointers though (see below for a list
#
#   https://cmake.org/cmake/help/v3.1/prop_gbl/CMAKE_CXX_KNOWN_FEATURES.html
#
target_compile_options(
    ${PROJECT_NAME}
    PUBLIC 
    $<$<NOT:$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,C>>:-std=c++11>
)

##############################################################################
# Installs
##############################################################################

install(TARGETS ${PROJECT_NAME}
   RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
 
