/**
 * @file MonoColor8RowsGraphicsFactoryTests.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Test for the toolbox to manipulate IGraphics objects.
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
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mocks/MockIFont.h"
#include "mocks/MockIGraphics.h"
#include "mocks/MockIMatrixDrawable.h"
#include "src/GraphicsToolBox.h"

TEST(GraphicsToolBox, WriteOnScreenFixed) {
  testing::NiceMock<ledmatrix::MockIFont> font;
  testing::NiceMock<ledmatrix::MockIGraphics> graphics;

  const uint16_t characterHeight = 8;
  const uint16_t aCharacterWidth = 2;
  const uint16_t bCharacterWidth = 3;
  const uint16_t letterSpacing = 2;

  ON_CALL(graphics, GetHeight())
      .WillByDefault(testing::Return(characterHeight));
  ON_CALL(font, GetSingleCharacterHeight())
      .WillByDefault(testing::Return(characterHeight));
  ON_CALL(font, GetSingleCharacterWidth('a'))
      .WillByDefault(testing::Return(aCharacterWidth));
  ON_CALL(font, GetSingleCharacterWidth('b'))
      .WillByDefault(testing::Return(bCharacterWidth));
  ON_CALL(font, GetLetterSpacing())
      .WillByDefault(testing::Return(letterSpacing));

  // Mock character a is all "true" pixels
  ON_CALL(font, GetCharacterPixel('a', testing::_, testing::_))
      .WillByDefault(testing::Return(true));
  // Mock character b is all "false" pixels
  ON_CALL(font, GetCharacterPixel('b', testing::_, testing::_))
      .WillByDefault(testing::Return(false));

  // Verify that the pixels of character a are correctly written on screen
  for (uint16_t currentX = 0; currentX < aCharacterWidth; currentX++) {
    for (uint16_t currentY = characterHeight; currentY > 0; currentY--) {
      EXPECT_CALL(graphics, SetPixel(currentX, currentY - 1, true));
    }
  }

  // Verify the spacing is correct.
  for (uint16_t currentX = aCharacterWidth;
       currentX < aCharacterWidth + letterSpacing; currentX++) {
    for (uint16_t currentY = characterHeight; currentY > 0; currentY--) {
      EXPECT_CALL(graphics, SetPixel(currentX, currentY - 1, false));
    }
  }

  // Verify that the pixels of character a are correctly written on screen
  for (uint16_t currentX = aCharacterWidth + letterSpacing;
       currentX < aCharacterWidth + letterSpacing + bCharacterWidth;
       currentX++) {
    for (uint16_t currentY = characterHeight; currentY > 0; currentY--) {
      EXPECT_CALL(graphics, SetPixel(currentX, currentY - 1, false));
    }
  }

  // Verify that a single pixel is added at the end in order to a blank column
  EXPECT_CALL(
      graphics,
      SetPixel(aCharacterWidth + letterSpacing + bCharacterWidth, 0, false));

  ledmatrix::graphics_toolbox::WriteOnScreen(graphics, font, "ab");
}

TEST(GraphicsToolBox, WriteOnScreenWithAlignment) {
  testing::NiceMock<ledmatrix::MockIFont> font;
  testing::NiceMock<ledmatrix::MockIGraphics> graphics;

  const uint16_t characterHeight = 8;
  const uint16_t aCharacterWidth = 1;
  const uint16_t letterSpacing = 2;
  const uint16_t graphicsWidth = 16;

  ON_CALL(graphics, GetHeight())
      .WillByDefault(testing::Return(characterHeight));
  ON_CALL(graphics, GetWidth()).WillByDefault(testing::Return(graphicsWidth));
  ON_CALL(font, GetSingleCharacterHeight())
      .WillByDefault(testing::Return(characterHeight));
  ON_CALL(font, GetSingleCharacterWidth('a'))
      .WillByDefault(testing::Return(aCharacterWidth));
  ON_CALL(font, GetLetterSpacing())
      .WillByDefault(testing::Return(letterSpacing));

  // Mock character a is all "true" pixels
  ON_CALL(font, GetCharacterPixel('a', testing::_, testing::_))
      .WillByDefault(testing::Return(true));

  // Left expectations

  // Verify that the pixels of character a are correctly written on screen
  for (uint16_t currentX = 0; currentX < aCharacterWidth; currentX++) {
    for (uint16_t currentY = characterHeight; currentY > 0; currentY--) {
      EXPECT_CALL(graphics, SetPixel(currentX, currentY - 1, true));
    }
  }

  // Verify that a single pixel is added at the end in order to a blank
  // column
  EXPECT_CALL(graphics, SetPixel(aCharacterWidth, 0, false));

  // Center expectations

  uint16_t center = (graphicsWidth - aCharacterWidth) / 2;
  // Verify that the pixels of character a are correctly written on screen
  for (uint16_t currentX = center; currentX < center + aCharacterWidth;
       currentX++) {
    for (uint16_t currentY = characterHeight; currentY > 0; currentY--) {
      EXPECT_CALL(graphics, SetPixel(currentX, currentY - 1, true));
    }
  }

  // Verify that a single pixel is added at the end in order to a blank
  // column
  EXPECT_CALL(graphics, SetPixel(aCharacterWidth + center, 0, false));

  // Right expectations

  uint16_t right = graphicsWidth - aCharacterWidth;
  // Verify that the pixels of character a are correctly written on screen
  for (uint16_t currentX = right; currentX < right + aCharacterWidth;
       currentX++) {
    for (uint16_t currentY = characterHeight; currentY > 0; currentY--) {
      EXPECT_CALL(graphics, SetPixel(currentX, currentY - 1, true));
    }
  }

  // Verify that a single pixel is added at the end in order to a blank
  // column
  EXPECT_CALL(graphics, SetPixel(graphicsWidth, 0, false));

  ledmatrix::graphics_toolbox::WriteOnScreen(graphics, font, "a",
                                             ledmatrix::AlignLeft);
  ledmatrix::graphics_toolbox::WriteOnScreen(graphics, font, "a",
                                             ledmatrix::AlignCenter);
  ledmatrix::graphics_toolbox::WriteOnScreen(graphics, font, "a",
                                             ledmatrix::AlignRight);
}

TEST(GraphicsToolBox, WriteOnScreenMatrixDrawable) {
  testing::NiceMock<ledmatrix::MockIFont> font;
  ledmatrix::MockIGraphics graphics;
  testing::NiceMock<ledmatrix::MockIMatrixDrawable> matrixDrawable;

  ON_CALL(matrixDrawable, GetSize())
      .WillByDefault(testing::Return(std::make_pair(3, 4)));

  // Two columns are on
  ON_CALL(matrixDrawable, GetPixel(testing::_, testing::Le(1)))
      .WillByDefault(testing::Return(true));

  // And the two next one are off
  ON_CALL(matrixDrawable, GetPixel(testing::_, testing::Gt(1)))
      .WillByDefault(testing::Return(false));

  ON_CALL(graphics, GetHeight()).WillByDefault(testing::Return(10));

  const uint16_t startX = 2;
  const uint16_t startY = 3;

  // Verify that the pixels of character a are correctly written on screen
  for (uint16_t currentX = startX; currentX < startX + 3; currentX++) {
    for (uint16_t currentY = startY; currentY < startY + 2; currentY++) {
      EXPECT_CALL(graphics, SetPixel(currentX, currentY, true));
    }
  }

  // Verify that the pixels of character a are correctly written on screen
  for (uint16_t currentX = startX; currentX < startX + 3; currentX++) {
    for (uint16_t currentY = startY + 2; currentY < startY + 4; currentY++) {
      EXPECT_CALL(graphics, SetPixel(currentX, currentY, false));
    }
  }

  ledmatrix::graphics_toolbox::WriteOnScreen(graphics, &matrixDrawable, startX,
                                             startY);
}