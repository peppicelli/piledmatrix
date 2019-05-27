/**
 * @file Runtime.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief This is where all gets coordinated.
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

#include "src/Runtime.h"

#include <pthread.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <utility>

#include "spdlog/spdlog.h"

namespace ledmatrix {

const unsigned int Runtime::DISPLAY_CYCLE_TIME_MILLI = 15;
const unsigned int Runtime::COMPUTE_CYCLE_TIME_MILLI = 1000;

Runtime::Runtime()
    : m_bRun(false),
      m_hardware(true),
      m_pCurrentGraphicsProvider(NULL) {
  m_hardware.SetBrightness(15);
}

Runtime::~Runtime() {
  if (m_computeThread.joinable() || m_displayThread.joinable()) {
    Stop();
  }
  spdlog::info("Clearing all graphic providers");
  m_graphicsProviders.clear();
}

void Runtime::AddGraphicsProvider(
    std::unique_ptr<IGraphicsProvider> pGraphicsProvider) {
  m_graphicsProviders.push_back(std::move(pGraphicsProvider));
}

void Runtime::Start() {
  m_bRun = true;
  m_computeThread = std::move(std::thread(&Runtime::ComputeTask, this));
  pthread_setname_np(m_computeThread.native_handle(), "Runtime_compute");
  m_displayThread = std::move(std::thread(&Runtime::DisplayTask, this));
  pthread_setname_np(m_displayThread.native_handle(), "Runtime_display");

  // Set the display thread as "real time". In case you are wondering how to
  // check that, you can use this command: ps -Leo
  // pid,tid,class,rtprio,stat,comm,wchan
  sched_param sch;
  int policy;
  pthread_getschedparam(m_displayThread.native_handle(), &policy, &sch);
  sch.sched_priority = 20;
  if (pthread_setschedparam(m_displayThread.native_handle(), SCHED_FIFO,
                            &sch)) {
    spdlog::error("Failed to setschedparam: {}", std::strerror(errno));
  }
}

void Runtime::Stop() {
  m_bRun = false;
  if (m_computeThread.joinable()) {
    m_computeThread.join();
  }
  spdlog::info("Computing thread finished.");
  if (m_displayThread.joinable()) {
    m_displayThread.join();
  }
  spdlog::info("Display thread finished.");
}

void Runtime::DisplayTask() {
  unsigned int cycleNumber = 0;
  IGraphics* pGraphicsToDisplay = NULL;
  while (m_bRun) {
    std::chrono::high_resolution_clock::time_point const timeout =
        std::chrono::high_resolution_clock::now() +
        std::chrono::milliseconds(DISPLAY_CYCLE_TIME_MILLI);

    // First, we display the graphics, this helps avoiding flickering issues
    // when the ExecuteDisplayCycle method takes non constant time to execute.
    if (pGraphicsToDisplay) {
      m_hardware.WriteIGraphics(*pGraphicsToDisplay);
    }

    {
      std::lock_guard<std::mutex> guard(m_currentGraphicsProviderMutex);
      if (m_pCurrentGraphicsProvider) {
        m_pCurrentGraphicsProvider->ExecuteDisplayCycle(cycleNumber);
        pGraphicsToDisplay = m_pCurrentGraphicsProvider->GetIGraphics();
      }
    }

    ++cycleNumber;

    std::this_thread::sleep_until(timeout);
  }
}

void Runtime::ComputeTask() {
  unsigned int cycleNumber = 0;
  while (m_bRun) {
    unsigned int numberOfActiveProviders = 0;
    if (!m_graphicsProviders.empty()) {
      // Execute the compute cycle of each graphic provider.
      std::for_each(m_graphicsProviders.begin(), m_graphicsProviders.end(),
                    [&](const std::unique_ptr<IGraphicsProvider>& p) {
                      p->ExecuteComputeCycle(cycleNumber);
                      if (p->IsActive()) {
                        numberOfActiveProviders++;
                      }
                    });
    }

    bool bReSchedule = false;

    // Reset the current provider if this one has finish.
    if (m_pCurrentGraphicsProvider) {
      if ((!m_pCurrentGraphicsProvider->IsActive()) ||
          (m_pCurrentGraphicsProvider->CanBePreampted() &&
           (numberOfActiveProviders > 1))) {
        bReSchedule = true;
      }
    } else {
      bReSchedule = true;
    }

    // We need to choose another provider
    if (bReSchedule) {
      IGraphicsProviderPriorityCompare comparator;
      std::sort(m_graphicsProviders.begin(), m_graphicsProviders.end(),
                comparator);
      {
        std::lock_guard<std::mutex> guard(m_currentGraphicsProviderMutex);
        m_pCurrentGraphicsProvider = m_graphicsProviders[0].get();
      }
    }

    ++cycleNumber;

    std::chrono::milliseconds duration(COMPUTE_CYCLE_TIME_MILLI);
    std::this_thread::sleep_for(duration);
  }
}

}  // namespace ledmatrix
