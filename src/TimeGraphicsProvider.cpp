/**
 * @file TimeGraphicsProvider.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Provides the current time as an IGraphics object.
 * @version 0.1
 * @date 2019-05-23
 *
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com).
 * All rights reserved. Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */

#include "src/TimeGraphicsProvider.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

#include "src/GraphicsToolBox.h"

namespace ledmatrix {

const char TimeGraphicsProvider::PROVIDER_NAME[] = "time";

TimeGraphicsProvider::TimeGraphicsProvider(
    std::unique_ptr<GraphicsFactory> pGraphicsFactory, uint16_t graphicsWidth)
    : m_font(), m_priority(0), m_canBePreampted(true) {
  if (pGraphicsFactory) {
    m_pGraphics = std::move(pGraphicsFactory->GetIGraphics());
    if (m_pGraphics) {
      m_pGraphics->SetWidth(graphicsWidth);
    }
  }
}

TimeGraphicsProvider::~TimeGraphicsProvider() {}

void TimeGraphicsProvider::ExecuteDisplayCycle(
    __attribute__((unused)) unsigned int cycleNumber) {
  if (m_pGraphics) {
    time_t t = time(0);
    struct tm now;
    localtime_r(&t, &now);
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << now.tm_hour << ':';
    ss << std::setfill('0') << std::setw(2) << now.tm_min << ':';
    ss << std::setfill('0') << std::setw(2) << now.tm_sec;
    m_pGraphics->Reset();
    graphics_toolbox::WriteOnScreen(*m_pGraphics, m_font, ss.str(),
                                    AlignCenter);
  }
}

void TimeGraphicsProvider::ExecuteComputeCycle(
    __attribute__((unused)) unsigned int cycleNumber) {}

IGraphics* TimeGraphicsProvider::GetIGraphics() const {
  return (m_pGraphics.get());
}

bool TimeGraphicsProvider::IsActive() const {
  // always active
  return (true);
}

unsigned char TimeGraphicsProvider::GetPriority() const { return (m_priority); }

bool TimeGraphicsProvider::CanBePreampted() const { return (m_canBePreampted); }

std::string TimeGraphicsProvider::GetName() const { return (PROVIDER_NAME); }

}  // namespace ledmatrix
