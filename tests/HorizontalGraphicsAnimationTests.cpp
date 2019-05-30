/**
 * @file HorizontalGraphicsAnimationTests.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Horizontal animation tests
 * @version 0.1
 * @date 2019-05-30
 *
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com).
 * All rights reserved. Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */

#include <gtest/gtest.h>

#include "src/HorizontalGraphicsAnimation.h"

#include "mocks/MockIGraphics.h"

TEST(HorizontalGraphicsAnimation, StepLeft) {
  testing::NiceMock<ledmatrix::MockIGraphics> graphics;
  const uint32_t width = 20;
  const uint32_t screenSize = 5;
  ON_CALL(graphics, GetWidth()).WillByDefault(testing::Return(width));
  EXPECT_CALL(graphics, Shift(ledmatrix::Direction::Right, screenSize))
      .Times(1);
  EXPECT_CALL(graphics, Shift(ledmatrix::Direction::Left, 1))
      .Times(width + screenSize);

  ledmatrix::HorizontalGraphicsAnimation animation(
      graphics, screenSize, ledmatrix::Direction::Left, 1);
  for (uint32_t i = 0; i < (screenSize + width) - 1; i++) {
    animation.PerformStep();
    ASSERT_FALSE(animation.IsAnimationDone());
  }
  animation.PerformStep();
  ASSERT_TRUE(animation.IsAnimationDone());
  // Execute a few more step just to verify that the system is still stable
  animation.PerformStep();
  animation.PerformStep();
  animation.PerformStep();
  ASSERT_TRUE(animation.IsAnimationDone());
}


TEST(HorizontalGraphicsAnimation, StepRight) {
  testing::NiceMock<ledmatrix::MockIGraphics> graphics;
  const uint32_t width = 20;
  const uint32_t screenSize = 5;
  ON_CALL(graphics, GetWidth()).WillByDefault(testing::Return(width));
  EXPECT_CALL(graphics, Shift(ledmatrix::Direction::Left, width))
      .Times(1);
  EXPECT_CALL(graphics, Shift(ledmatrix::Direction::Right, 1))
      .Times(width + screenSize);

  ledmatrix::HorizontalGraphicsAnimation animation(
      graphics, screenSize, ledmatrix::Direction::Right, 1);
  for (uint32_t i = 0; i < (screenSize + width) - 1; i++) {
    animation.PerformStep();
    ASSERT_FALSE(animation.IsAnimationDone());
  }
  animation.PerformStep();
  ASSERT_TRUE(animation.IsAnimationDone());
  // Execute a few more step just to verify that the system is still stable
  animation.PerformStep();
  animation.PerformStep();
  animation.PerformStep();
  ASSERT_TRUE(animation.IsAnimationDone());
}