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
PYBIND11_MODULE(_piledmatrix, m) {
  py::class_<ledmatrix::PiLedMatrix> piLedMatrix(m, "PiLedMatrix");

  py::enum_<spdlog::level::level_enum>(m, "LogLevel", py::arithmetic())
      .value("trace", spdlog::level::trace)
      .value("debug", spdlog::level::debug)
      .value("info", spdlog::level::info)
      .value("warn", spdlog::level::warn)
      .value("err", spdlog::level::err)
      .value("critical", spdlog::level::critical)
      .value("off", spdlog::level::off);

  piLedMatrix.def(py::init<>())
      .def("is_started", &ledmatrix::PiLedMatrix::IsStarted)
      .def("start", &ledmatrix::PiLedMatrix::Start)
      .def("stop", &ledmatrix::PiLedMatrix::Stop)
      .def("add_message", &ledmatrix::PiLedMatrix::AddMessage)
      .def("set_loglevel", &ledmatrix::PiLedMatrix::SetLoglevel);
}
