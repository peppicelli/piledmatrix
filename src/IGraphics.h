/**
 * @file IGraphics.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Interface for a led matrix class
 * @version 0.1
 * @date 2019-05-20
 * 
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com). All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.apache.org/licenses/LICENSE-2.0
 * 
 */

#pragma once

#include <stdint.h>

namespace ledmatrix {
/**
 * Define direction in which pixel can be moved.
 */
enum Direction {
  Left = 0,  //!< Left
  Right,     //!< Right
  Up,        //!< Up
  Down       //!< Down
};

/**
 * \a IGraphics is an interface to a model representation of some Led Matrix
 * hardware. The goal is to define generic functions that allows more elaborate
 * classes to prepare graphics in a generic way.
 */
class IGraphics {
 public:
  virtual ~IGraphics() {}

  /**
   * Return the height of the matrix.
   * @return height of the led matrix
   */
  virtual uint16_t GetHeight() const = 0;

  /**
   * Returns the width of the matrix.
   * @return width of the led matrix
   */
  virtual uint16_t GetWidth() const = 0;

  /**
   * Set the width of the matrix.
   * @param width width of the led matrix.
   */
  virtual void SetWidth(uint16_t width) = 0;

  /**
   * Clear out every pixel in the matrix. After a clear, the width of the matrix
   * will be 0.
   */
  virtual void Clear() = 0;

  /**
   * Clear out every pixel in the matrix without changing the width.
   */
  virtual void Reset() = 0;

  /**
   * Light on or off one pixel. If the pixel is outside of the y boundaries,
   * nothing happens. If the pixel is outside the x boundaries, the size of
   * the matrix will be increased accordingly.
   * @param x X position of the pixel (starts at 0)
   * @param y Y position of the pixel (starts at 0)
   * @param on requested state of the pixel (true is ON)
   */
  virtual void SetPixel(uint16_t x, uint16_t y, bool on) = 0;

  /**
   * Return the state of a pixel.
   * @param x X position of the pixel (starts at 0)
   * @param y Y position of the pixel (starts at 0)
   * @return State of the pixel at (x,y) (true is ON)
   */
  virtual bool GetPixel(uint16_t x, uint16_t y) const = 0;

  /**
   * Rotate the matrix in the wanted direction.
   * @param direction left or right.
   * @param numberOfRows number of rows to rotate. 0 will do nothing.
   */
  virtual void Rotate(Direction direction,
                      uint16_t numberOfRows) = 0;

  /**
   * Shift the matrix in the wanted direction. Each shift will remove
   * \a numberOfRows from the matrix.
   * @param direction left or right
   * @param numberOfRows number of rows to shift. 0 will do nothing. if the
   * number of row is larger than the size of the matrix, the matrix will
   * be cleared.
   */
  virtual void Shift(Direction direction,
                     uint16_t numberOfRows) = 0;
};
}  // namespace ledmatrix
