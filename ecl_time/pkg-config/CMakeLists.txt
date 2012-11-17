###############################################################################
# Configuration
###############################################################################

set(PKG_CONFIG_FILE ecl_time.pc)

if(PLATFORM_HAS_RT_TIMERS)
  set(PRIVATE_LIBS "-lrt")
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${PKG_CONFIG_FILE}.in 
    ${CMAKE_CURRENT_SOURCE_DIR}/${PKG_CONFIG_FILE}
    @ONLY )
    
###############################################################################
# Install
###############################################################################

install(FILES ${PKG_CONFIG_FILE} DESTINATION lib/pkgconfig)

