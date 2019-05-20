if (NOT TARGET spdlog-project)
  include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

  ExternalProject_Add(spdlog-project
    GIT_REPOSITORY               https://github.com/gabime/spdlog
    GIT_TAG                      v1.3.1
    # Since the tag is fixed, do not update each time !                                                                                                                                                     
    UPDATE_COMMAND               ""
    UPDATE_DISCONNECTED          1                                                                                                                                                                                    
    CMAKE_ARGS                                                                                                                                                                                              
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/spdlog/${CMAKE_BUILD_TYPE}/install"                                                                                                                       
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
    "-DSPDLOG_BUILD_BENCH=OFF"
  )

  add_library(spdlog INTERFACE)
  target_include_directories(spdlog INTERFACE "${CMAKE_BINARY_DIR}/spdlog/${CMAKE_BUILD_TYPE}/install/include/")

  add_dependencies(spdlog spdlog-project)

endif(NOT TARGET spdlog-project)
