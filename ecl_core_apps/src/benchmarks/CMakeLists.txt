###############################################################################
# Macro
###############################################################################

macro(ecl_add_benchmark name)
  add_executable(bench_${name} ${name}.cpp)
  target_link_libraries(bench_${name}
  ${ecl_build_LIBRARIES}
  ${ecl_config_LIBRARIES}
  ${ecl_linear_algebra_LIBRARIES}
  ${ecl_command_line_LIBRARIES}
  ${ecl_converters_LIBRARIES}
  ${ecl_containers_LIBRARIES}
  ${ecl_devices_LIBRARIES}
  ${ecl_errors_LIBRARIES}
  ${ecl_exceptions_LIBRARIES}
  ${ecl_formatters_LIBRARIES}
  ${ecl_geometry_LIBRARIES}
  ${ecl_ipc_LIBRARIES}
  ${ecl_sigslots_LIBRARIES}
  ${ecl_streams_LIBRARIES}
  ecl_threads::ecl_threads
  ${ecl_time_lite_LIBRARIES}
  ${ecl_type_traits_LIBRARIES}
  )
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

# Sparse is still unstable...and got modified in quantal, comment out for now.
#ecl_add_benchmark(eigen_sparse)
ecl_add_benchmark(eigen3_inverse)
ecl_add_benchmark(eigen3_decompositions)
ecl_add_benchmark(eigen3_transforms)
