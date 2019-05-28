/**
 * @file IGraphicsAnimation.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Interface for classes providing animation
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

#include "IGraphics.h"

namespace ledmatrix {

/**
 * \a IGraphics is an interface to a model a graphic animation (such as moving
 * left or right).
 */
class IGraphicsAnimation {
 public:
  virtual ~IGraphicsAnimation() {}

  /**
   * Indicate that an animation is done
   *
   * @return true if the animation is done
   * @return false otherwise
   */
  virtual bool IsAnimationDone() = 0;

  /**
   * Perform an animation step
   */
  virtual void PerformStep() = 0;
};
}  // namespace ledmatrix
