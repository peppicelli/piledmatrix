/**
 * @file MonoColor8RowsGraphics.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Single color 8 rows Led Matrix
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

#include <bitset>
#include <vector>

#include "src/IGraphics.h"

#define MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS 8

namespace ledmatrix {

/**
 * Represent a single color 8 rows Led Matrix such as the sure electronic
 * HT1632 based led matrix.
 */
class MonoColor8RowsGraphics : public IGraphics {
 public:
  MonoColor8RowsGraphics();
  virtual ~MonoColor8RowsGraphics();

  // Prevent wrong usage of these operators.
  MonoColor8RowsGraphics(const MonoColor8RowsGraphics& other) = delete;
  MonoColor8RowsGraphics& operator=(const MonoColor8RowsGraphics& other) =
      delete;
  MonoColor8RowsGraphics(MonoColor8RowsGraphics&& other) = delete;
  MonoColor8RowsGraphics& operator=(MonoColor8RowsGraphics&& other) = delete;
  bool operator==(const MonoColor8RowsGraphics& other) const = delete;
  bool operator!=(const MonoColor8RowsGraphics& other) const = delete;

  /* Pixel operations */
  virtual void SetPixel(uint16_t x, uint16_t y, bool on);
  virtual bool GetPixel(uint16_t x, uint16_t y) const;

  /* Full matrix operations */
  virtual uint16_t GetHeight() const;
  virtual uint16_t GetWidth() const;
  virtual void SetWidth(uint16_t width);

  virtual void Clear();
  virtual void Reset();
  virtual void Rotate(Direction direction,
                      uint16_t numberOfRows);
  virtual void Shift(Direction direction,
                     uint16_t numberOfRows);

 private:
  std::vector<std::bitset<MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS> > m_matrix;
  uint16_t m_screenOriginPostion;
};

}  // namespace ledmatrix
