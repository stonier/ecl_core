###############################################################################
# SETUP
###############################################################################

rosbuild_add_executable(ecl_process process.cpp)
install(TARGETS ecl_process RUNTIME DESTINATION bin) 

rosbuild_add_executable(ecl_hex hex.cpp)
install(TARGETS ecl_hex RUNTIME DESTINATION bin) 

rosbuild_add_executable(ecl_serial serial.cpp)
install(TARGETS ecl_serial RUNTIME DESTINATION bin) 

rosbuild_add_executable(ecl_socket_client socket_client.cpp)
install(TARGETS ecl_socket_client RUNTIME DESTINATION bin) 

rosbuild_add_executable(ecl_socket_server socket_server.cpp)
install(TARGETS ecl_socket_server RUNTIME DESTINATION bin) 
