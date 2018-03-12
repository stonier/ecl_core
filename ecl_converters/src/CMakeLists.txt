##############################################################################
# Subdirectories
##############################################################################

add_subdirectory(examples)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
  add_subdirectory(test)
endif()
