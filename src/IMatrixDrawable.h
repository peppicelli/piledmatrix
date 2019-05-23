/**
 * @file IMatrixDrawable.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Interface for any object that could be draw on an IGraphic object.
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
#include <utility>

namespace ledmatrix {

/**
 * Interface for any object that could be draw on an IGraphic object.
 */
class IMatrixDrawable {
 public:
  /**
   * Destructor
   */
  virtual ~IMatrixDrawable() {}

  /**
   * Read a pixel
   * @param x X position of the pixel (starts at 0)
   * @param y Y position of the pixel (starts at 0)
   * @return true if the pixel is not blank.
   */
  virtual bool GetPixel(uint16_t x, uint16_t y) const = 0;

  /**
   * Return the size of the current IDrawable. Width and Height in a std::pair.
   */
  virtual std::pair<uint32_t, uint32_t> GetSize() const = 0;
};

}  // namespace ledmatrix

