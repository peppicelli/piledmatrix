if(NOT TARGET pybind11)

  include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

  find_package(PythonLibs 3 REQUIRED)

  set(PYBIND11_CPP_STANDARD -std=c++11)
  ExternalProject_Add(pybind11
                      GIT_REPOSITORY https://github.com/pybind/pybind11.git
                      GIT_TAG v2.2.4
                      PREFIX "${CMAKE_BINARY_DIR}/pybind11"
                      # Since the tag is fixed, do not update each time !
                      UPDATE_COMMAND ""
                      UPDATE_DISCONNECTED 1
                      # Do not build, do not install, we only need the headers.
                      CONFIGURE_COMMAND ""
                      BUILD_COMMAND ""
                      INSTALL_COMMAND "")

  add_library(pybind INTERFACE)
  target_include_directories(
    pybind SYSTEM
    INTERFACE "${CMAKE_BINARY_DIR}/pybind11/src/pybind11/include/"
              "${PYTHON_INCLUDE_DIRS}")
  target_link_libraries(pybind INTERFACE ${PYTHON_LIBRARIES})
  target_compile_options(pybind
                         INTERFACE ${PYBIND11_CPP_STANDARD}
                                   "-fvisibility=hidden")

  add_dependencies(pybind pybind11)

endif(NOT TARGET pybind11)
