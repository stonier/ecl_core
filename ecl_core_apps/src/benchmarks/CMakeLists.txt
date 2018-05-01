###############################################################################
# Macro
###############################################################################

macro(ecl_add_benchmark name)
  add_executable(ecl_bench_${name} ${name}.cpp)
  target_link_libraries(
    ecl_bench_${name}
    PRIVATE
      ecl_config::ecl_config
      ecl_command_line::ecl_command_line
      ecl_converters::ecl_converters
      ecl_containers::ecl_containers
      ecl_devices::ecl_devices
      ecl_errors::ecl_errors
      ecl_exceptions::ecl_exceptions
      ecl_formatters::ecl_formatters
      ecl_geometry::ecl_geometry
      ecl_ipc::ecl_ipc
      ecl_linear_algebra::ecl_linear_algebra
      ecl_sigslots::ecl_sigslots
      ecl_streams::ecl_streams
      ecl_threads::ecl_threads
      ecl_time_lite::ecl_time_lite
      ecl_type_traits::ecl_type_traits
  )
  install(TARGETS ecl_bench_${name} RUNTIME DESTINATION bin)
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
