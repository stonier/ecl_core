
find_package(ecl_build REQUIRED)

ecl_detect_threads()

if(ECL_PLATFORM_HAS_POSIX_THREADS)
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
endif()
