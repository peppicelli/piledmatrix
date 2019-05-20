/**
 * @file MonoColor8RowsGraphicsTests.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Test for the Single color 8 rows Led Matrix
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

#include <gtest/gtest.h>

#include "src/MonoColor8RowsGraphics.h"

TEST(MonoColor8RowsGraphics, GetSetPixel) {
  // Size test
  ledmatrix::MonoColor8RowsGraphics graphics;
  EXPECT_EQ(graphics.GetWidth(), 0);
  EXPECT_EQ(graphics.GetHeight(), MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS);

  // Set pixels inside the boundaries
  graphics.SetPixel(0, 0, true);
  graphics.SetPixel(0, 7, true);
  EXPECT_EQ(graphics.GetPixel(0, 0), true);
  EXPECT_EQ(graphics.GetPixel(0, 1), false);
  EXPECT_EQ(graphics.GetPixel(0, 2), false);
  EXPECT_EQ(graphics.GetPixel(0, 3), false);
  EXPECT_EQ(graphics.GetPixel(0, 4), false);
  EXPECT_EQ(graphics.GetPixel(0, 5), false);
  EXPECT_EQ(graphics.GetPixel(0, 6), false);
  EXPECT_EQ(graphics.GetPixel(0, 7), true);
  graphics.SetPixel(0, 0, false);
  graphics.SetPixel(0, 7, false);
  for (int i = 0; i < MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS; ++i) {
    EXPECT_EQ(graphics.GetPixel(0, i), false);
  }

  // Set pixel a few columns outside of the bound
  graphics.SetPixel(4, 4, true);
  EXPECT_EQ(graphics.GetWidth(), 5);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS; ++j) {
      EXPECT_EQ(graphics.GetPixel(i, j), false);
    }
  }
  EXPECT_EQ(graphics.GetPixel(4, 0), false);
  EXPECT_EQ(graphics.GetPixel(4, 1), false);
  EXPECT_EQ(graphics.GetPixel(4, 2), false);
  EXPECT_EQ(graphics.GetPixel(4, 3), false);
  EXPECT_EQ(graphics.GetPixel(4, 4), true);
  EXPECT_EQ(graphics.GetPixel(4, 5), false);
  EXPECT_EQ(graphics.GetPixel(4, 6), false);
  EXPECT_EQ(graphics.GetPixel(4, 7), false);

  // Get a pixel outside of the new bounds
  EXPECT_EQ(graphics.GetPixel(25, 4), false);
  EXPECT_EQ(graphics.GetPixel(25, 32), false);
}

TEST(MonoColor8RowsGraphics, Clear) {
  ledmatrix::MonoColor8RowsGraphics graphics;
  EXPECT_EQ(graphics.GetWidth(), 0);
  EXPECT_EQ(graphics.GetHeight(), MONO_COLOR_GRAPHICS_NUMBER_OF_ROWS);

  graphics.SetPixel(0, 0, true);
  graphics.SetPixel(3, 7, true);
  EXPECT_EQ(graphics.GetWidth(), 4);
  graphics.Clear();
  EXPECT_EQ(graphics.GetWidth(), 0);
}

TEST(MonoColor8RowsGraphics, Rotate) {
  ledmatrix::MonoColor8RowsGraphics graphics;

  // We try to rotate an empty matrix
  EXPECT_EQ(graphics.GetWidth(), 0);
  graphics.Rotate(ledmatrix::Left, 2);
  EXPECT_EQ(graphics.GetWidth(), 0);
  graphics.Rotate(ledmatrix::Right, 2);
  EXPECT_EQ(graphics.GetWidth(), 0);
  graphics.Rotate(ledmatrix::Right, 0);
  EXPECT_EQ(graphics.GetWidth(), 0);

  // Now we try with a real matrix
  graphics.SetPixel(0, 0, true);
  graphics.SetPixel(1, 1, true);
  graphics.SetPixel(2, 2, true);
  graphics.SetPixel(3, 3, true);

  graphics.Rotate(ledmatrix::Left, 1);
  EXPECT_EQ(graphics.GetPixel(0, 1), true);
  EXPECT_EQ(graphics.GetPixel(1, 2), true);
  EXPECT_EQ(graphics.GetPixel(2, 3), true);
  EXPECT_EQ(graphics.GetPixel(3, 0), true);

  graphics.Rotate(ledmatrix::Left, 2);
  EXPECT_EQ(graphics.GetPixel(0, 3), true);
  EXPECT_EQ(graphics.GetPixel(1, 0), true);
  EXPECT_EQ(graphics.GetPixel(2, 1), true);
  EXPECT_EQ(graphics.GetPixel(3, 2), true);

  graphics.Rotate(ledmatrix::Right, 1);
  EXPECT_EQ(graphics.GetPixel(0, 2), true);
  EXPECT_EQ(graphics.GetPixel(1, 3), true);
  EXPECT_EQ(graphics.GetPixel(2, 0), true);
  EXPECT_EQ(graphics.GetPixel(3, 1), true);

  graphics.Rotate(ledmatrix::Right, 2);
  EXPECT_EQ(graphics.GetPixel(0, 0), true);
  EXPECT_EQ(graphics.GetPixel(1, 1), true);
  EXPECT_EQ(graphics.GetPixel(2, 2), true);
  EXPECT_EQ(graphics.GetPixel(3, 3), true);

  graphics.Rotate(ledmatrix::Right, 0);
  EXPECT_EQ(graphics.GetPixel(0, 0), true);
  EXPECT_EQ(graphics.GetPixel(1, 1), true);
  EXPECT_EQ(graphics.GetPixel(2, 2), true);
  EXPECT_EQ(graphics.GetPixel(3, 3), true);

  graphics.Rotate(ledmatrix::Left, 0);
  EXPECT_EQ(graphics.GetPixel(0, 0), true);
  EXPECT_EQ(graphics.GetPixel(1, 1), true);
  EXPECT_EQ(graphics.GetPixel(2, 2), true);
  EXPECT_EQ(graphics.GetPixel(3, 3), true);

  graphics.Rotate(ledmatrix::Left, 4);
  EXPECT_EQ(graphics.GetPixel(0, 0), true);
  EXPECT_EQ(graphics.GetPixel(1, 1), true);
  EXPECT_EQ(graphics.GetPixel(2, 2), true);
  EXPECT_EQ(graphics.GetPixel(3, 3), true);
}

TEST(MonoColor8RowsGraphics, Shift) {
  ledmatrix::MonoColor8RowsGraphics graphics;

  // We try to shift an empty matrix
  EXPECT_EQ(graphics.GetWidth(), 0);
  graphics.Shift(ledmatrix::Left, 2);
  EXPECT_EQ(graphics.GetWidth(), 0);
  graphics.Shift(ledmatrix::Right, 2);
  EXPECT_EQ(graphics.GetWidth(), 0);
  graphics.Shift(ledmatrix::Right, 0);
  EXPECT_EQ(graphics.GetWidth(), 0);

  // Now we try with a real matrix
  graphics.SetPixel(0, 0, true);
  graphics.SetPixel(1, 1, true);
  graphics.SetPixel(2, 2, true);
  graphics.SetPixel(3, 3, true);
  graphics.SetPixel(4, 4, true);
  graphics.SetPixel(5, 5, true);

  EXPECT_EQ(graphics.GetWidth(), 6);

  graphics.Shift(ledmatrix::Left, 1);
  EXPECT_EQ(graphics.GetWidth(), 5);
  EXPECT_EQ(graphics.GetPixel(0, 1), true);
  EXPECT_EQ(graphics.GetPixel(1, 2), true);
  EXPECT_EQ(graphics.GetPixel(2, 3), true);
  EXPECT_EQ(graphics.GetPixel(3, 4), true);
  EXPECT_EQ(graphics.GetPixel(4, 5), true);

  graphics.Shift(ledmatrix::Right, 2);
  EXPECT_EQ(graphics.GetWidth(), 7);
  EXPECT_EQ(graphics.GetPixel(2, 1), true);
  EXPECT_EQ(graphics.GetPixel(3, 2), true);
  EXPECT_EQ(graphics.GetPixel(4, 3), true);

  graphics.Shift(ledmatrix::Left, 2);
  EXPECT_EQ(graphics.GetWidth(), 5);
  EXPECT_EQ(graphics.GetPixel(2, 3), true);
}
