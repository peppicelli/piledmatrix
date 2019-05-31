/**
 * @file SimpleMessageGraphicsProviderTests.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief
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

#include "src/SimpleMessageGraphicsProvider.h"

#include "mocks/MockGraphicsFactory.h"
#include "mocks/MockIGraphics.h"

TEST(SimpleMessageGraphicsProvider, CommonAttributes) {
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
  ledmatrix::SimpleMessageGraphicsProvider messageProvider(
      std::move(mockGraphicsFactory), mockGraphicsWidth);
  EXPECT_FALSE(messageProvider.CanBePreampted());
  EXPECT_EQ(messageProvider.GetPriority(), 10);
  EXPECT_STREQ(messageProvider.GetName().c_str(), "message");
  EXPECT_FALSE(messageProvider.IsActive());
  EXPECT_EQ(messageProvider.GetIGraphics(), pMockGraphics);
}

TEST(SimpleMessageGraphicsProvider, NoMessage) {
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
  ledmatrix::SimpleMessageGraphicsProvider messageProvider(
      std::move(mockGraphicsFactory), mockGraphicsWidth);
  EXPECT_FALSE(messageProvider.IsActive());
  for (uint32_t i = 0; i < 100; i++) {
    messageProvider.ExecuteDisplayCycle(i);
    messageProvider.ExecuteComputeCycle(i);
    EXPECT_FALSE(messageProvider.IsActive());
  }
}

TEST(SimpleMessageGraphicsProvider, SingleMessage) {
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
  ledmatrix::SimpleMessageGraphicsProvider messageProvider(
      std::move(mockGraphicsFactory), mockGraphicsWidth);
  EXPECT_FALSE(messageProvider.IsActive());
  uint32_t i = 0;
  messageProvider.ExecuteDisplayCycle(i);
  messageProvider.ExecuteComputeCycle(i);
  EXPECT_FALSE(messageProvider.IsActive());
  messageProvider.DisplayMessage("a");
  const uint16_t messageSize = 5;
  i++;
  messageProvider.ExecuteDisplayCycle(i);
  messageProvider.ExecuteComputeCycle(i);
  EXPECT_TRUE(messageProvider.IsActive());
  for (; i < mockGraphicsWidth; i++) {
    messageProvider.ExecuteDisplayCycle(i);
    messageProvider.ExecuteComputeCycle(i);
    EXPECT_TRUE(messageProvider.IsActive());
  }
  messageProvider.ExecuteDisplayCycle(i);
  messageProvider.ExecuteComputeCycle(i);
  EXPECT_FALSE(messageProvider.IsActive());
}

TEST(SimpleMessageGraphicsProvider, LoadTest) {
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
  ledmatrix::SimpleMessageGraphicsProvider messageProvider(
      std::move(mockGraphicsFactory), mockGraphicsWidth);
  std::thread displayMessageThread(
      [](ledmatrix::SimpleMessageGraphicsProvider& mp) -> void {
        std::mt19937_64 eng{std::random_device {}()};
        std::uniform_int_distribution<> dist{20, 500};
        for (uint32_t i = 0; i < 100; i++) {
          mp.DisplayMessage("a");
          std::this_thread::sleep_for(std::chrono::microseconds{dist(eng)});
        }
      }, std::ref(messageProvider));

  std::thread executeCycleThread(
      [](ledmatrix::SimpleMessageGraphicsProvider& mp) -> void {
        std::mt19937_64 eng{std::random_device {}()};
        std::uniform_int_distribution<> dist{1, 50};
        for (uint32_t i = 0; i < 2000; i++) {
          mp.ExecuteDisplayCycle(i);
          mp.ExecuteComputeCycle(i);
          std::this_thread::sleep_for(std::chrono::microseconds{dist(eng)});
        }
      }, std::ref(messageProvider));
  displayMessageThread.join();
  executeCycleThread.join();
}