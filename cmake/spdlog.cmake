if (NOT TARGET spdlog-project)
  INCLUDE(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

  find_program(MAKE_EXE NAMES gmake nmake make)
  ExternalProject_Add(spdlog-project
    GIT_REPOSITORY               https://github.com/gabime/spdlog
    GIT_TAG                      v1.3.1
    # Since the tag is fixed, do not update each time !                                                                                                                                                     
    UPDATE_COMMAND               ""                                                                                                                                                                                    
    CMAKE_ARGS                                                                                                                                                                                              
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/spdlog/${CMAKE_BUILD_TYPE}/install"                                                                                                                       
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
    "-DSPDLOG_BUILD_BENCH=OFF"
  )

  ADD_LIBRARY(spdlog INTERFACE)
  TARGET_INCLUDE_DIRECTORIES(spdlog INTERFACE "${CMAKE_BINARY_DIR}/spdlog/${CMAKE_BUILD_TYPE}/install/include/")

  ADD_DEPENDENCIES(spdlog spdlog-project)

ENDIF(NOT TARGET spdlog-project)
