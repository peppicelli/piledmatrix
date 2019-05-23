/**
 * @file TimeGraphicsProvider.h
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
#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "src/Font8x5.h"
#include "src/GraphicsFactory.h"
#include "src/IGraphicsProvider.h"

namespace ledmatrix {

/**
 * Provides the current time as an IGraphics object.
 */
class TimeGraphicsProvider : public IGraphicsProvider {
 public:
  /**
   * @brief Construct a new Time Graphics Provider object
   * 
   * @param pGraphicsFactory The factory to create an IGraphics object.
   * @param graphicsWidth The size of the screen.
   */
  TimeGraphicsProvider(std::unique_ptr<GraphicsFactory> pGraphicsFactory,
                       uint16_t graphicsWidth = 0);
  virtual ~TimeGraphicsProvider();

  // Prevent wrong usage of these operators.
  TimeGraphicsProvider() = delete;
  TimeGraphicsProvider(const TimeGraphicsProvider& other) = delete;
  TimeGraphicsProvider& operator=(const TimeGraphicsProvider& other) = delete;
  TimeGraphicsProvider(TimeGraphicsProvider&& other) = delete;
  TimeGraphicsProvider& operator=(TimeGraphicsProvider&& other) = delete;
  bool operator==(const TimeGraphicsProvider& other) const = delete;
  bool operator!=(const TimeGraphicsProvider& other) const = delete;

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
  IGraphics* GetIGraphics() const;
  virtual bool IsActive() const;
  virtual bool CanBePreampted() const;
  virtual unsigned char GetPriority() const;
  virtual std::string GetName() const;

 private:
  std::unique_ptr<IGraphics> m_pGraphics;
  Font8x5 m_font;

  unsigned int m_priority;
  bool m_canBePreampted;

  static const char PROVIDER_NAME[];
};

}  // namespace ledmatrix
