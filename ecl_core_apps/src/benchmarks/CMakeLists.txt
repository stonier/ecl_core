###############################################################################
# Macro
###############################################################################

macro(ecl_add_benchmark name)
  rosbuild_add_executable(bench_${name} ${name}.cpp)
  install(TARGETS bench_${name} RUNTIME DESTINATION bin) 
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

ecl_add_benchmark(eigen_sparse)
ecl_add_benchmark(eigen3_inverse)
ecl_add_benchmark(eigen3_decompositions)
ecl_add_benchmark(eigen3_transforms)
