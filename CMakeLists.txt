cmake_minimum_required (VERSION 3.10)
project (piledmatrix)

set (CMAKE_CXX_STANDARD 11)

include("cmake/spdlog.cmake")
include("cmake/wiringPi.cmake")

# Main target

set(app_SRCS
  src/Font8x5.cpp
  src/MonoColor8RowsGraphics.cpp
  src/Sure3208LedMatrix.cpp
)

add_executable(${PROJECT_NAME} 
  ${app_SRCS} 
  src/main.cpp
)

target_compile_options(${PROJECT_NAME} 
  PRIVATE 
    -Wall 
    -Wextra 
    -pedantic 
    -Werror
)

target_link_libraries(${PROJECT_NAME} 
  PRIVATE 
    wiringpi
    spdlog
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES 
    INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE
    BUILD_RPATH "$ORIGIN/../lib:$ORIGIN"
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")

# Test target

include("cmake/gtest.cmake")
include(GoogleTest)

set(tests_SRCS
  tests/Font8x5Tests.cpp
  tests/MonoColor8RowsGraphicsTests.cpp
)

add_executable(${PROJECT_NAME}_tests 
  ${app_SRCS} 
  ${tests_SRCS} 
  tests/main.cpp
)

target_link_libraries(${PROJECT_NAME}_tests
  PRIVATE
    wiringpi
    spdlog
    gtest
)

target_include_directories(${PROJECT_NAME}_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

gtest_add_tests(TARGET
                ${PROJECT_NAME}_tests
                WORKING_DIRECTORY
                "${CMAKE_CURRENT_SOURCE_DIR}/tests/data")

set_target_properties(${PROJECT_NAME}_tests
  PROPERTIES 
    INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE
    BUILD_RPATH "$ORIGIN/../lib:$ORIGIN"
)

install(TARGETS ${PROJECT_NAME}_tests RUNTIME DESTINATION "bin")

include(CPack)
