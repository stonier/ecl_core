###############################################################################
# Macro
###############################################################################

macro(ecl_add_benchmark name)
  add_executable(bench_${name} ${name}.cpp)
  target_link_libraries(bench_${name} ${catkin_LIBRARIES})
  install(TARGETS bench_${name} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
endmacro()

###############################################################################
# Setup
###############################################################################

ecl_add_benchmark(containers)
ecl_add_benchmark(files)
ecl_add_benchmark(flops)
ecl_add_benchmark(exceptions)
ecl_add_benchmark(snooze)
ecl_add_benchmark(streams)
ecl_add_benchmark(string_conversions)

# Sparse is still unstable...and got modified in quantal, comment out for now.
#ecl_add_benchmark(eigen_sparse)
ecl_add_benchmark(eigen3_inverse)
ecl_add_benchmark(eigen3_decompositions)
ecl_add_benchmark(eigen3_transforms)
