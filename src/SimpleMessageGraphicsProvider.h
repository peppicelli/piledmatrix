/**
 * @file SimpleMessageGraphicsProvider.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Allows the display of "one shot" messages.
 * @version 0.1
 * @date 2019-05-20
 *
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com).
 * All rights reserved. Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */
#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <queue>
#include <mutex>

#include "src/Font8x5.h"
#include "src/GraphicsFactory.h"
#include "src/IGraphicsProvider.h"
#include "src/IGraphicsAnimation.h"

namespace ledmatrix {

/**
 * Allows the display of "one shot" messages.
 */
class SimpleMessageGraphicsProvider : public IGraphicsProvider {
 public:
  /**
   * @brief Construct a new Simple Message Graphics Provider object
   * @param pGraphicsFactory The factory to create an IGraphics object.
   * @param graphicsWidth The size of the screen.
   */
  SimpleMessageGraphicsProvider(
      std::unique_ptr<GraphicsFactory> pGraphicsFactory,
      uint16_t graphicsWidth = 0);
  /**
   * Destructor.
   */
  virtual ~SimpleMessageGraphicsProvider();

  // Prevent wrong usage of these operators.
  SimpleMessageGraphicsProvider(const SimpleMessageGraphicsProvider& other) =
      delete;
  SimpleMessageGraphicsProvider& operator=(
      const SimpleMessageGraphicsProvider& other) = delete;
  SimpleMessageGraphicsProvider(SimpleMessageGraphicsProvider&& other) = delete;
  SimpleMessageGraphicsProvider& operator=(
      SimpleMessageGraphicsProvider&& other) = delete;
  bool operator==(SimpleMessageGraphicsProvider& other) const = delete;
  bool operator!=(SimpleMessageGraphicsProvider& other) const = delete;

  /**
   * This function does nothing as there are no computation to be done.
   * @param cycleNumber Unused. The current cycle.
   */
  void ExecuteComputeCycle(unsigned int cycleNumber);

  /**
   * Writes the current time on the IGraphics object.
   * @param cycleNumber
   */
  void ExecuteDisplayCycle(unsigned int cycleNumber);

  /**
   * Add a message to the message queue.
   * @param message The message to be displayed.
   */
  void DisplayMessage(const std::string& message);

  IGraphics* GetIGraphics() const;
  virtual bool IsActive() const;
  virtual bool CanBePreampted() const;
  virtual unsigned char GetPriority() const;
  virtual std::string GetName() const;

 private:
  std::unique_ptr<IGraphics> m_pGraphics;

  std::mutex m_messageQueueMutex;
  std::queue<std::string> m_messageQueue;
  std::string m_currentMessage;

  std::unique_ptr<IGraphicsAnimation> m_pAnimation;

  Font8x5 m_font;
  uint16_t m_graphicsWidth;

  unsigned int m_priority;
  bool m_canBePreampted;

  static const char PROVIDER_NAME[];
};
}  // namespace ledmatrix
