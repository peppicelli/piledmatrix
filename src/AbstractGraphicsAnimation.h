/**
 * @file AbstractGraphicsAnimation.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Abstract animation class (stores the IGraphics object and other
 * helpers)
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

#include "src/IGraphicsAnimation.h"

namespace ledmatrix {

/**
 * \a IGraphics is an interface to a model a graphic animation (such as moving
 * left or right).
 */
class AbstractGraphicsAnimation : public IGraphicsAnimation {
 public:
  virtual ~AbstractGraphicsAnimation() {}

  /**
   * @brief Construct a new Abstract Graphics Animation object
   *
   * @param graphics The underlying graphics object
   * @param screenSize The real size of the hardware
   */
  AbstractGraphicsAnimation(IGraphics& graphics, uint16_t screenSize)
      : m_graphics(graphics), m_screenSize(screenSize) {}

  virtual bool IsAnimationDone() { return (m_isAnimationDone); }

  virtual void PerformStep() = 0;

 protected:
  /**
   * The graphics object on which to apply the animation.
   */
  IGraphics& m_graphics;

  /**
   * The size of the screen.
   */
  uint16_t m_screenSize;

  /**
   * Indicates if an animation is done.
   */
  bool m_isAnimationDone = false;
};
}  // namespace ledmatrix
