/**
 * @file Font8x5Tests.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Tests for the font 8x5 class
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

#include "src/Font8x5.h"

TEST(Font8x5, GetCharacterPixel) {
  ledmatrix::Font8x5 font;

  EXPECT_EQ(font.GetCharacterPixel('a', 0, 0), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 0, 1), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 0, 2), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 0, 3), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 0, 4), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 0, 5), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 0, 6), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 0, 7), false);

  EXPECT_EQ(font.GetCharacterPixel('a', 1, 0), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 1, 1), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 1, 2), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 1, 3), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 1, 4), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 1, 5), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 1, 6), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 1, 7), false);

  EXPECT_EQ(font.GetCharacterPixel('a', 2, 0), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 2, 1), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 2, 2), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 2, 3), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 2, 4), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 2, 5), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 2, 6), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 2, 7), false);

  EXPECT_EQ(font.GetCharacterPixel('a', 3, 0), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 3, 1), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 3, 2), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 3, 3), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 3, 4), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 3, 5), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 3, 6), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 3, 7), false);

  EXPECT_EQ(font.GetCharacterPixel('a', 4, 0), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 4, 1), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 4, 2), false);
  EXPECT_EQ(font.GetCharacterPixel('a', 4, 3), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 4, 4), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 4, 5), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 4, 6), true);
  EXPECT_EQ(font.GetCharacterPixel('a', 4, 7), false);

  EXPECT_EQ(font.GetCharacterPixel('a', 66, 66), false);
}

TEST(Font8x5, LetterSpacing) {
  ledmatrix::Font8x5 font;
  font.SetLetterSpacing(22);
  EXPECT_EQ(font.GetLetterSpacing(), 22);
}

TEST(Font8x5, GetCharacterWidth) {
  ledmatrix::Font8x5 font;
  EXPECT_EQ(font.GetSingleCharacterWidth('a'), 5);
  EXPECT_EQ(font.GetSingleCharacterWidth(':'), 2);
  EXPECT_EQ(font.GetSingleCharacterMaxWidth(), 5);
}
