/**
 * @file HorizontalGraphicsAnimation.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Horizontal animation
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
#include "src/HorizontalGraphicsAnimation.h"

#include "spdlog/spdlog.h"

namespace ledmatrix {

HorizontalGraphicsAnimation::HorizontalGraphicsAnimation(
    IGraphics& graphics, uint16_t screenSize, Direction direction,
    uint16_t speedDivisor)
    : AbstractGraphicsAnimation(graphics, screenSize),
      m_speedDivisor(speedDivisor),
      m_direction(direction),
      m_currentStep(0) {
  // Move the display in order to start with a blank screen.
  m_numberOfShiftLeft = m_graphics.GetWidth() + m_screenSize;
  if (Left == m_direction) {
    m_graphics.Shift(Right, m_screenSize);
  } else if (Right == m_direction) {
    m_graphics.Shift(Left, m_graphics.GetWidth());
  }
}

void HorizontalGraphicsAnimation::PerformStep() {
  if (!m_isAnimationDone) {
    m_currentStep++;
    if (0 == (m_currentStep % m_speedDivisor)) {
      m_graphics.Shift(m_direction, 1);
      --m_numberOfShiftLeft;
      if (0 == m_numberOfShiftLeft) {
        m_isAnimationDone = true;
      }
    }
  }
}

}  // namespace ledmatrix
