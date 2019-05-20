/**
 * @file MonoColor8RowsGraphics.cpp
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

#include "src/MonoColor8RowsGraphics.h"

#include <algorithm>

#include "spdlog/spdlog.h"

namespace ledmatrix {

MonoColor8RowsGraphics::MonoColor8RowsGraphics() : m_screenOriginPostion(0) {}

MonoColor8RowsGraphics::~MonoColor8RowsGraphics() {}

void MonoColor8RowsGraphics::SetPixel(uint16_t x, uint16_t y, bool on) {
  x += m_screenOriginPostion;
  if (y >= MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS) {
    /*  We are outside of the bounds. That is ok, we just ignore the call
            and log a message. */
    spdlog::error(
        "Tried to set a pixel outside of the bound (at ({}, {}) with a matrix "
        "of size {}x{}.",
        x, y, GetWidth(), GetHeight());
    return;
  }

  // Increase the size of our matrix in case we are outside the x boundaries
  if (x >= m_matrix.size()) {
    SetWidth(x + 1);
  }

  m_matrix[x][y] = on;
}

bool MonoColor8RowsGraphics::GetPixel(uint16_t x, uint16_t y) const {
  x += m_screenOriginPostion;
  // Everything outside of the bounds is considered as not set
  if ((x >= m_matrix.size()) || (y >= MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS)) {
    return (false);
  }
  return (m_matrix[x][y]);
}

uint16_t MonoColor8RowsGraphics::GetHeight() const {
  return (MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS);
}

uint16_t MonoColor8RowsGraphics::GetWidth() const {
  return (m_matrix.size() - m_screenOriginPostion);
}

void MonoColor8RowsGraphics::SetWidth(uint16_t width) {
  width += m_screenOriginPostion;
  if (m_matrix.size() < width) {
    for (int i = m_matrix.size(); i < width; ++i) {
      m_matrix.push_back(std::bitset<MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS>());
    }
  }
}

void MonoColor8RowsGraphics::Clear() {
  m_matrix.clear();
  m_screenOriginPostion = 0;
}

void MonoColor8RowsGraphics::Reset() {
  for (unsigned int i = 0; i < m_matrix.size(); ++i) {
    m_matrix[i].reset();
  }
  m_screenOriginPostion = 0;
}

void MonoColor8RowsGraphics::Rotate(Direction direction,
                                    uint16_t numberOfRows) {
  // numberOfRows has to be within the size of the vector
  if ((Right == direction) || (Left == direction)) {
    if ((0 != numberOfRows) && (m_matrix.size() != 0)) {
      numberOfRows %= m_matrix.size();

      if (Right == direction) {
        numberOfRows = m_matrix.size() - numberOfRows;
      }
      std::rotate(m_matrix.begin(), m_matrix.begin() + numberOfRows,
                  m_matrix.end());
    }
  } else if (Up == direction) {
    for (unsigned int i = 0; i < m_matrix.size(); ++i) {
      m_matrix[i] <<= numberOfRows;
    }
  } else if (Down == direction) {
    for (unsigned int i = 0; i < m_matrix.size(); ++i) {
      m_matrix[i] >>= numberOfRows;
    }
  }
}

void MonoColor8RowsGraphics::Shift(Direction direction, uint16_t numberOfRows) {
  // numberOfRows has to be within the size of the vector
  if (0 == m_matrix.size()) {
    spdlog::error("Trying to shift a led matrix of size 0.");
    return;
  }
  if (0 != numberOfRows) {
    spdlog::debug("Shifting {} rows to the {}", numberOfRows,
                  direction == Left ? "left" : "right");
    for (int i = 0; i < numberOfRows; ++i) {
      if (Right == direction) {
        if (m_screenOriginPostion > 0) {
          --m_screenOriginPostion;
        } else {
          m_matrix.insert(m_matrix.begin(),
                          std::bitset<MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS>());
        }
      } else {
        ++m_screenOriginPostion;
      }
    }
  }
  spdlog::debug("New size after shift: {}", GetWidth());
  spdlog::debug("New origin position after shift: {}", m_screenOriginPostion);
}

}  // namespace ledmatrix
