if (NOT TARGET jsoncpp-project)
  include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

  if (NOT MSVC)
    set (CXX_FLAGS_OPTION_TO_PASS "-DCMAKE_CXX_FLAGS=-fPIC")
  endif()

  ExternalProject_Add(jsoncpp-project
    GIT_REPOSITORY    https://github.com/open-source-parsers/jsoncpp.git
    GIT_TAG           1.8.2
    PREFIX            "${CMAKE_BINARY_DIR}/jsoncpp"
    # Since the tag is fixed, do not update each time !
    UPDATE_COMMAND    ""
    CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/jsoncpp/${BUILD_TYPE_FOLDER}/install"
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
    "-DJSONCPP_WITH_TESTS=OFF"
    "-DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF"
    "-DJSONCPP_WITH_STRICT_ISO=OFF"
    "-DJSONCPP_WITH_PKGCONFIG_SUPPORT=OFF"
    "-DJSONCPP_WITH_CMAKE_PACKAGE=OFF"
    "-DBUILD_SHARED_LIBS=OFF"
    "-DBUILD_STATIC_LIBS=ON"
    # Fix for gcc (and possibly clang)
    "${CXX_FLAGS_OPTION_TO_PASS}"
    )

  include(GNUInstallDirs)

  add_library(jsoncpp INTERFACE)
  target_link_libraries(jsoncpp INTERFACE
  "${CMAKE_BINARY_DIR}/jsoncpp/${CMAKE_BUILD_TYPE}/install/${CMAKE_INSTALL_LIBDIR}/${CMAKE_STATIC_LIBRARY_PREFIX}jsoncpp${CMAKE_STATIC_LIBRARY_SUFFIX}")
  target_include_directories(jsoncpp INTERFACE "${CMAKE_BINARY_DIR}/jsoncpp/${CMAKE_BUILD_TYPE}/install/include/")

  add_dependencies(jsoncpp jsoncpp-project)

endif(NOT TARGET jsoncpp-project)
