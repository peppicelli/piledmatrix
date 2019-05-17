if (NOT TARGET wiringpi-project)
  include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

  find_program(MAKE_EXE NAMES gmake nmake make)
  ExternalProject_Add(wiringpi-project
    GIT_REPOSITORY               git://git.drogon.net/wiringPi
    GIT_TAG                      2.50
    # Since the tag is fixed, do not update each time !                                                                                                                                                     
    UPDATE_COMMAND               ""    
    CONFIGURE_COMMAND            ""
    BUILD_COMMAND                ${MAKE_EXE} CC="${CMAKE_C_COMPILER}" LDCONFIG= -C ../wiringpi-project/wiringPi
    INSTALL_COMMAND              mkdir -p ${CMAKE_BINARY_DIR}/wiringpi/${CMAKE_BUILD_TYPE}/install/lib && ${MAKE_EXE} install LDCONFIG= DESTDIR=${CMAKE_BINARY_DIR}/wiringpi/${CMAKE_BUILD_TYPE}/install -C ../wiringpi-project/wiringPi
  )

  set(WIRING_PI_LIB "${CMAKE_BINARY_DIR}/wiringpi/${CMAKE_BUILD_TYPE}/install/local/lib/${CMAKE_STATIC_LIBRARY_PREFIX}wiringPi${CMAKE_SHARED_LIBRARY_SUFFIX}.2.46")

  add_library(wiringpi INTERFACE)
  target_link_libraries(wiringpi 
    INTERFACE 
      ${WIRING_PI_LIB}
  )
  target_include_directories(wiringpi INTERFACE "${CMAKE_BINARY_DIR}/wiringpi/${CMAKE_BUILD_TYPE}/install/local/include/")
  install(FILES ${WIRING_PI_LIB} 
    DESTINATION "lib"
    RENAME "${CMAKE_STATIC_LIBRARY_PREFIX}wiringPi${CMAKE_SHARED_LIBRARY_SUFFIX}"
  )
  add_dependencies(wiringpi wiringpi-project)

endif(NOT TARGET wiringpi-project)
