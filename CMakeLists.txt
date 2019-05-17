cmake_minimum_required (VERSION 3.10)
project (piledmatrix)

set (CMAKE_CXX_STANDARD 11)

include("cmake/spdlog.cmake")
include("cmake/wiringPi.cmake")

set(app_SRCS
  src/main.cpp
)

add_executable(${PROJECT_NAME} ${app_SRCS})

target_link_libraries(${PROJECT_NAME} 
  PUBLIC 
    wiringpi
    spdlog
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES 
    INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN"
    BUILD_WITH_INSTALL_RPATH TRUE
    BUILD_RPATH "$ORIGIN/../lib:$ORIGIN"
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "bin")

include(CPack)