if (NOT TARGET wiringpi-project)
  INCLUDE(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

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

  ADD_LIBRARY(wiringpi INTERFACE)
  TARGET_LINK_LIBRARIES(wiringpi INTERFACE
  "${CMAKE_BINARY_DIR}/wiringpi/${CMAKE_BUILD_TYPE}/install/local/lib/${CMAKE_STATIC_LIBRARY_PREFIX}wiringPi${CMAKE_SHARED_LIBRARY_SUFFIX}.2.46")
  TARGET_INCLUDE_DIRECTORIES(wiringpi INTERFACE "${CMAKE_BINARY_DIR}/wiringpi/${CMAKE_BUILD_TYPE}/install/local/include/")

  ADD_DEPENDENCIES(wiringpi wiringpi-project)

ENDIF(NOT TARGET wiringpi-project)
