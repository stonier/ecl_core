###############################################################################
# SUBDIRECTORIES
###############################################################################

if(ECL_PLATFORM_HAS_POSIX_THREADS) 
    add_subdirectory(lib)
endif()

add_subdirectory(test)
