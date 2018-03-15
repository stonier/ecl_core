###############################################################################
# GTEST SETUP
###############################################################################

add_executable(demo_formatters formatters.cpp)
target_link_libraries(demo_formatters ${PROJECT_NAME})
install(TARGETS demo_formatters RUNTIME DESTINATION bin)
