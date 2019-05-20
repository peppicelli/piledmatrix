if (NOT TARGET googletest)

  find_package( Threads )

  include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

  ExternalProject_Add(googletest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           release-1.8.1
    PREFIX            "${CMAKE_BINARY_DIR}/googletest"
    # Since the tag is fixed, do not update each time !
    UPDATE_COMMAND    ""
    UPDATE_DISCONNECTED 1
    CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/googletest/${CMAKE_BUILD_TYPE}/install"
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
    # This options forces gtest to build with /Md on MSVC
    "-Dgtest_force_shared_crt=ON"
  )

  add_library(gtest INTERFACE)
  target_link_libraries(gtest INTERFACE
    "${CMAKE_BINARY_DIR}/googletest/${CMAKE_BUILD_TYPE}/install/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}"
    ${CMAKE_THREAD_LIBS_INIT})
  target_include_directories(gtest INTERFACE "${CMAKE_BINARY_DIR}/googletest/${CMAKE_BUILD_TYPE}/install/include/")

  add_dependencies(gtest googletest)

endif(NOT TARGET googletest)
