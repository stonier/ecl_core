###############################################################################
# Configuration
###############################################################################

set(PKG_CONFIG_FILE ecl_devices.pc)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${PKG_CONFIG_FILE}.in 
    ${CMAKE_CURRENT_SOURCE_DIR}/${PKG_CONFIG_FILE}
    @ONLY )

###############################################################################
# Install
###############################################################################

install(FILES ${PKG_CONFIG_FILE} DESTINATION lib/pkgconfig)

