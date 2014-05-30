###############################################################################
# Directories
###############################################################################

if(DEFINED ECL_EIGEN_IS_INTERNAL_3_1_2)
    install(DIRECTORY eigen3.1.2 DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION})
elseif(DEFINED ECL_EIGEN_IS_INTERNAL_3_2_1)
    install(DIRECTORY eigen3.2.1 DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION})
endif()