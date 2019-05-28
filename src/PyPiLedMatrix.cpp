/**
 * @file PyPiLedMatrix.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Python entry point
 * @version 0.1
 * @date 2019-05-28
 *
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com).
 * All rights reserved. Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */

#include <src/PiLedMatrix.h>

#include <pybind11/pybind11.h>

namespace py = pybind11;

/**
 * Construct a new pybind11 module object
 */
PYBIND11_MODULE(piledmatrix, m) {
  py::class_<ledmatrix::PiLedMatrix> piLedMatrix(m, "PiLedMatrix");
  piLedMatrix.def(py::init<>())
             .def("Start", &ledmatrix::PiLedMatrix::Start)
             .def("Stop", &ledmatrix::PiLedMatrix::Stop)
             .def("AddMessage", &ledmatrix::PiLedMatrix::AddMessage);
}
