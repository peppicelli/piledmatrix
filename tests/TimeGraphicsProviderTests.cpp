/**
 * @file TimeGraphicsProviderTests.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Test class for TimeGraphicsProvider
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

#include <chrono>
#include <memory>
#include <random>
#include <thread>

#include "src/TimeGraphicsProvider.h"

#include "mocks/MockGraphicsFactory.h"
#include "mocks/MockIGraphics.h"

TEST(TimeGraphicsProvider, CommonAttributes) {
  auto mockGraphicsFactory =
      std::unique_ptr<testing::NiceMock<ledmatrix::MockGraphicsFactory>>(
          new testing::NiceMock<ledmatrix::MockGraphicsFactory>());
  auto mockGraphics =
      std::unique_ptr<testing::NiceMock<ledmatrix::MockIGraphics>>(
          new testing::NiceMock<ledmatrix::MockIGraphics>());
  auto pMockGraphics = mockGraphics.get();
  const uint16_t mockGraphicsWidth = 25;
  EXPECT_CALL(*mockGraphics, SetWidth(mockGraphicsWidth)).Times(1);
  ON_CALL(*mockGraphicsFactory, GetIGraphics())
      .WillByDefault(testing::Return(testing::ByMove(std::move(mockGraphics))));
  ledmatrix::TimeGraphicsProvider timeProvider(
      std::move(mockGraphicsFactory), mockGraphicsWidth);
  EXPECT_TRUE(timeProvider.CanBePreampted());
  EXPECT_EQ(timeProvider.GetPriority(), 0);
  EXPECT_STREQ(timeProvider.GetName().c_str(), "time");
  EXPECT_TRUE(timeProvider.IsActive());
  EXPECT_EQ(timeProvider.GetIGraphics(), pMockGraphics);
}

TEST(TimeGraphicsProvider, DisplayTime) {
  auto mockGraphicsFactory =
      std::unique_ptr<testing::NiceMock<ledmatrix::MockGraphicsFactory>>(
          new testing::NiceMock<ledmatrix::MockGraphicsFactory>());
  auto mockGraphics =
      std::unique_ptr<testing::NiceMock<ledmatrix::MockIGraphics>>(
          new testing::NiceMock<ledmatrix::MockIGraphics>());
  auto pMockGraphics = mockGraphics.get();
  const uint16_t mockGraphicsWidth = 25;
  const uint16_t numberOfCalls = 100;
  EXPECT_CALL(*mockGraphics, SetWidth(mockGraphicsWidth)).Times(1);
  EXPECT_CALL(*mockGraphics, Reset()).Times(numberOfCalls);
  ON_CALL(*mockGraphicsFactory, GetIGraphics())
      .WillByDefault(testing::Return(testing::ByMove(std::move(mockGraphics))));
  ledmatrix::TimeGraphicsProvider timeProvider(
      std::move(mockGraphicsFactory), mockGraphicsWidth);
  EXPECT_TRUE(timeProvider.IsActive());
  for (uint32_t i = 0; i < numberOfCalls; i++) {
    timeProvider.ExecuteDisplayCycle(i);
    timeProvider.ExecuteComputeCycle(i);
    EXPECT_TRUE(timeProvider.IsActive());
  }
}