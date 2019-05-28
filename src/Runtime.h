/**
 * @file Runtime.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Runtime. This is where all gets coordinated.
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

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "src/IGraphicsProvider.h"
#include "src/Sure3208LedMatrix.h"

namespace ledmatrix {

/**
 * Class managing the threads used to display and animate the screen.
 */
class Runtime {
 public:
  /**
   * Constructor. Will not start the runtime
   */
  Runtime();

  /**
   * Destructor. Stop the runtime if it's not already stopped.
   */
  virtual ~Runtime();

  // Prevent wrong usage of these operators.
  Runtime(const Runtime& other) = delete;
  Runtime& operator=(const Runtime& other) = delete;
  Runtime(Runtime&& other) = delete;
  Runtime& operator=(Runtime&& other) = delete;
  bool operator==(Runtime& other) const = delete;
  bool operator!=(Runtime& other) const = delete;

  /**
   * Add another graphics provider to the set of providers. After this
   * operation, Runtime class will have the ownership of the graphicsProvider
   * @param pGraphicsProvider A graphicsProvider to add.
   */
  void AddGraphicsProvider(
      std::unique_ptr<IGraphicsProvider> pGraphicsProvider);

  /**
   * Start the Runtime. Two thread are started from here.
   * <ul>
   * <li>One to handle the display through SPI. This thread will run a fixed
   * clock rate.</li> <li>One to handle background tasks such as retrieving
   * information from Internet.</li>
   * </ul>
   */
  void Start();

  /**
   * Stop the Runtime. Wait for the two thread to finish properly.
   */
  void Stop();

  /**
   * @return true if the runtime is started.
   * @return false otherwise.
   */
  bool IsStarted() {return m_bRun;}

 private:
  std::vector<std::unique_ptr<IGraphicsProvider>> m_graphicsProviders;

  volatile bool m_bRun;

  Sure3208LedMatrix m_hardware;

  IGraphicsProvider* m_pCurrentGraphicsProvider;
  std::mutex m_currentGraphicsProviderMutex;

  std::thread m_computeThread;
  std::thread m_displayThread;

  void DisplayTask();
  void ComputeTask();

  static const unsigned int DISPLAY_CYCLE_TIME_MILLI;
  static const unsigned int COMPUTE_CYCLE_TIME_MILLI;
};

}  // namespace ledmatrix
