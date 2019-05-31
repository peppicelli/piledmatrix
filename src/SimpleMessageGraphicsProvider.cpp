/**
 * @file SimpleMessageGraphicsProvider.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Allows the display of "one shot" messages.
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

#include "src/SimpleMessageGraphicsProvider.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

#include "src/GraphicsToolBox.h"
#include "src/HorizontalGraphicsAnimation.h"

#include "spdlog/spdlog.h"

namespace ledmatrix {

const char SimpleMessageGraphicsProvider::PROVIDER_NAME[] = "message";

SimpleMessageGraphicsProvider::SimpleMessageGraphicsProvider(
    std::unique_ptr<GraphicsFactory> pGraphicsFactory, uint16_t graphicsWidth)
    : m_messageQueueMutex(),
      m_messageQueue(),
      m_currentMessage(""),
      m_font(),
      m_graphicsWidth(graphicsWidth),
      m_priority(10),
      m_canBePreampted(false) {
  if (pGraphicsFactory) {
    m_pGraphics = std::move(pGraphicsFactory->GetIGraphics());
    if (m_pGraphics) {
      m_pGraphics->SetWidth(graphicsWidth);
    }
  }
}

SimpleMessageGraphicsProvider::~SimpleMessageGraphicsProvider() {}

void SimpleMessageGraphicsProvider::ExecuteDisplayCycle(
    __attribute__((unused)) unsigned int cycleNumber) {
  if (nullptr != m_pGraphics) {
    // Find out if a new message is here to be displayed
    if (m_currentMessage.empty()) {
      std::lock_guard<std::mutex> guard(m_messageQueueMutex);
      if (!m_messageQueue.empty()) {
        m_currentMessage = m_messageQueue.front();
        spdlog::info("Displaying message: {}", m_currentMessage);
        m_messageQueue.pop();
      }
    }

    // Perform animation
    if (!m_currentMessage.empty()) {
      // Do we already have an animation for it ?
      if (nullptr == m_pAnimation) {
        spdlog::info("Creating new animation for message: {}",
                     m_currentMessage);
        graphics_toolbox::WriteOnScreen(*m_pGraphics, m_font, 0, 7,
                                        m_currentMessage);
        m_pAnimation =
            std::unique_ptr<IGraphicsAnimation>(new HorizontalGraphicsAnimation(
                *m_pGraphics, m_graphicsWidth, Left, 1));
      } else {
        // Is the animation finished ?
        if (m_pAnimation->IsAnimationDone()) {
          spdlog::info("Animation for message {} is done.", m_currentMessage);
          m_pAnimation.release();
          m_currentMessage.clear();
          m_pGraphics->Clear();
        } else {
          spdlog::debug("Animation step for message {}.", m_currentMessage);
          m_pAnimation->PerformStep();
        }
      }
    }
  }
}

void SimpleMessageGraphicsProvider::ExecuteComputeCycle(
    __attribute__((unused)) unsigned int cycleNumber) {}

void SimpleMessageGraphicsProvider::DisplayMessage(const std::string& message) {
  std::lock_guard<std::mutex> guard(m_messageQueueMutex);
  m_messageQueue.push(message);
}

IGraphics* SimpleMessageGraphicsProvider::GetIGraphics() const {
  return (m_pGraphics.get());
}

bool SimpleMessageGraphicsProvider::IsActive() const {
  return (!m_messageQueue.empty() ||
          (m_pAnimation && (!m_pAnimation->IsAnimationDone())));
}

unsigned char SimpleMessageGraphicsProvider::GetPriority() const {
  return (m_priority);
}

bool SimpleMessageGraphicsProvider::CanBePreampted() const {
  return (m_canBePreampted);
}

std::string SimpleMessageGraphicsProvider::GetName() const {
  return (PROVIDER_NAME);
}

}  // namespace ledmatrix
