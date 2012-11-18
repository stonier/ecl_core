###############################################################################
# FILES
###############################################################################

FILE(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

INSTALL(FILES ${HEADERS} DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/ecl/threads)

