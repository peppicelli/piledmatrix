cmake_minimum_required(VERSION 3.10)
project(piledmatrix VERSION 1.0.0.0)

set(CMAKE_CXX_STANDARD 11)

# Require dot, treat the other components as optional
find_package(Doxygen REQUIRED dot)

include("cmake/jsoncpp.cmake")
include("cmake/pybind11.cmake")
include("cmake/spdlog.cmake")
include("cmake/wiringPi.cmake")

find_package(Threads)

# Main target

set(app_SRCS
    src/Font8x5.cpp
    src/GraphicsFactory.cpp
    src/GraphicsToolBox.cpp
    src/HorizontalGraphicsAnimation.cpp
    src/MonoColor8RowsGraphics.cpp
    src/MonoColor8RowsGraphicsFactory.cpp
    src/PiLedMatrix.cpp
    src/Runtime.cpp
    src/SimpleMessageGraphicsProvider.cpp
    src/Sure3208LedMatrix.cpp
    src/TimeGraphicsProvider.cpp)

add_library(_${PROJECT_NAME} SHARED ${app_SRCS} src/PyPiLedMatrix.cpp)

target_compile_options(_${PROJECT_NAME}
                       PRIVATE -Wall
                               -Wextra
                               -pedantic
                               -Wno-unused-function
                               -Werror)

target_link_libraries(_${PROJECT_NAME}
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                              wiringpi
                              spdlog
                              pybind)

target_include_directories(_${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(_${PROJECT_NAME}
                      PROPERTIES INSTALL_RPATH
                                 "$ORIGIN/../lib:$ORIGIN"
                                 BUILD_WITH_INSTALL_RPATH
                                 TRUE
                                 BUILD_RPATH
                                 "$ORIGIN/../lib:$ORIGIN")

set_target_properties(_${PROJECT_NAME} PROPERTIES PREFIX "")

install(TARGETS _${PROJECT_NAME} DESTINATION
                "/usr/share/pyshared/piledmatrix/piledmatrix")

# Python part

add_subdirectory(python)

# Documentation

doxygen_add_docs(${PROJECT_NAME}_docs
                 src/
                 COMMENT
                 "Generate documentation")

# Test target

include("cmake/gtest.cmake")
include(GoogleTest)

set(tests_SRCS
    tests/Font8x5Tests.cpp
    tests/GraphicsToolBoxTests.cpp
    tests/HorizontalGraphicsAnimationTests.cpp
    tests/MonoColor8RowsGraphicsFactoryTests.cpp
    tests/MonoColor8RowsGraphicsTests.cpp
    tests/PiLedMatrixTests.cpp
    tests/RuntimeTests.cpp
    tests/SimpleMessageGraphicsProviderTests.cpp
    tests/TimeGraphicsProviderTests.cpp)

add_executable(${PROJECT_NAME}_tests ${app_SRCS} ${tests_SRCS} tests/main.cpp)

target_link_libraries(${PROJECT_NAME}_tests
                      PRIVATE ${CMAKE_THREAD_LIBS_INIT}
                              wiringpi
                              spdlog
                              gtest)

target_include_directories(${PROJECT_NAME}_tests
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(
    ${PROJECT_NAME}_tests
    PRIVATE "--coverage" "-fprofile-arcs" "-ftest-coverage")
  target_link_libraries(${PROJECT_NAME}_tests PRIVATE "--coverage")
endif()

gtest_add_tests(TARGET
                ${PROJECT_NAME}_tests
                WORKING_DIRECTORY
                "${CMAKE_CURRENT_SOURCE_DIR}/tests/data")

set_target_properties(${PROJECT_NAME}_tests
                      PROPERTIES INSTALL_RPATH
                                 "$ORIGIN/../lib:$ORIGIN"
                                 BUILD_WITH_INSTALL_RPATH
                                 TRUE
                                 BUILD_RPATH
                                 "$ORIGIN/../lib:$ORIGIN")

install(TARGETS ${PROJECT_NAME}_tests RUNTIME DESTINATION "bin")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Daniel Peppicelli")
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "python3.5, python3-setuptools, python3-docutils")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "armhf")
set(
  CPACK_PACKAGE_DESCRIPTION
  "Lib and deamon for displaying message on a Sure led matrix on a raspberry PI SPI port."
  )
set(CPACK_PACKAGE_CONTACT "daniel.peppicelli@gmail.com")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/peppicelli/pi-led-matrix")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
    "${CMAKE_SOURCE_DIR}/python/postinst;${CMAKE_SOURCE_DIR}/python/prerm;")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/python/setup.py.in
               ${CMAKE_CURRENT_SOURCE_DIR}/python/setup.py)

include(CPack)
