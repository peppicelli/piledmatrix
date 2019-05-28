/**
 * @file HorizontalGraphicsAnimation.h
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
#pragma once

#include <cstdint>

#include "src/AbstractGraphicsAnimation.h"

namespace ledmatrix {

/**
 * \a Right to Left and vice-versa graphics animation
 */
class HorizontalGraphicsAnimation : public AbstractGraphicsAnimation {
 public:
  virtual ~HorizontalGraphicsAnimation() {}

  /**
   * @brief Construct a new Horizontal Graphics Animation object
   *
   * @param graphics The graphic object on which to apply the animation
   * @param screenSize The size of the screen
   * @param direction The direction (left or right)
   * @param speedDivisor The speed of the animation. The more high, the less
   * quick will be the animation
   */
  HorizontalGraphicsAnimation(IGraphics& graphics, uint16_t screenSize,
                              Direction direction, uint16_t speedDivisor);

  // Prevent wrong usage of these operators.
  HorizontalGraphicsAnimation(const HorizontalGraphicsAnimation& other) =
      delete;
  HorizontalGraphicsAnimation& operator=(
      const HorizontalGraphicsAnimation& other) = delete;
  HorizontalGraphicsAnimation(HorizontalGraphicsAnimation&& other) = delete;
  HorizontalGraphicsAnimation& operator=(HorizontalGraphicsAnimation&& other) =
      delete;
  bool operator==(HorizontalGraphicsAnimation& other) const = delete;
  bool operator!=(HorizontalGraphicsAnimation& other) const = delete;

  virtual void PerformStep();

 protected:
  /**
   * The speed of the animation. The more high, the less
   * quick will be the animation
   */
  uint16_t m_speedDivisor;
  /**
   * The direction of the animation
   */
  Direction m_direction;
  /**
   * The current step (used with the speed divisor)
   */
  uint16_t m_currentStep;
  /**
   * Used to know when the animation will be done
   */
  uint16_t m_numberOfShiftLeft;
};
}  // namespace ledmatrix
