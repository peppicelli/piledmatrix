/**
 * @file PiLedMatrix.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Main class to control everything. All calls are wrapped in python.
 * @version 0.1
 * @date 2019-05-27
 *
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com).
 * All rights reserved. Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */
#pragma once

#include <string>
#include <memory>

#include "src/Runtime.h"
#include "src/Sure3208LedMatrix.h"
#include "src/SimpleMessageGraphicsProvider.h"

namespace ledmatrix {

/**
 * @brief Main entry point. Exported to python.
 */
class PiLedMatrix {
 public:
  /**
   * Constructor. This will start the display (runtime).
   */
  PiLedMatrix();

  /**
   * Destructor.
   */
  virtual ~PiLedMatrix() {}

  // Prevent wrong usage of these operators.
  PiLedMatrix(const PiLedMatrix& other) = delete;
  PiLedMatrix& operator=(const PiLedMatrix& other) = delete;
  PiLedMatrix(PiLedMatrix&& other) = delete;
  PiLedMatrix& operator=(PiLedMatrix&& other) = delete;
  bool operator==(PiLedMatrix& other) const = delete;
  bool operator!=(PiLedMatrix& other) const = delete;

  /**
   * Start the display.
   */
  void Start() const;

  /**
   * Stop the Runtime. Wait for the two thread to finish properly.
   */
  void Stop() const;

  /**
   * Display a string message.
   * @param message The message to display.
   */
  void AddMessage(const std::string& message) const;

 private:
  ledmatrix::Sure3208LedMatrix hardware;
  std::unique_ptr<ledmatrix::Runtime> pRuntime;
  ledmatrix::SimpleMessageGraphicsProvider* m_pMessageProvider;
};

}  // namespace ledmatrix
