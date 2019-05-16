cmake_minimum_required (VERSION 3.10)
project (pi-led-matrix)

include("cmake/spdlog.cmake")
include("cmake/wiringPi.cmake")

add_executable(piledmatrix src/blink.c)

target_link_libraries(piledmatrix PUBLIC wiringpi)