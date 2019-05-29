/**
 * @file MonoColor8RowsGraphicsTests.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Test for the runtime (This is where all gets coordinated.)
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

#include <chrono>
#include <thread>

#include "mocks/MockIGraphics.h"
#include "mocks/MockIGraphicsProvider.h"

#include "src/Runtime.h"

namespace {
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}  // namespace

TEST(Runtime, StartAndStop) {
  ledmatrix::Runtime runtime;

  runtime.Start();
  EXPECT_TRUE(runtime.IsStarted());
  // Calling start on an already started runtime should have no effect.
  runtime.Start();
  EXPECT_TRUE(runtime.IsStarted());

  runtime.Stop();
  EXPECT_FALSE(runtime.IsStarted());
  // Calling stop on an already stopped runtime should have no effect.
  runtime.Stop();
  EXPECT_FALSE(runtime.IsStarted());
}

TEST(Runtime, StopFailsafe) {
  auto pRuntime = new ledmatrix::Runtime();

  pRuntime->Start();
  EXPECT_TRUE(pRuntime->IsStarted());

  delete pRuntime;
}

TEST(Runtime, OneSingleProvider) {
  ledmatrix::Runtime runtime;

  auto provider =
      make_unique<testing::NiceMock<ledmatrix::MockIGraphicsProvider>>();
  auto pRawProvider = provider.get();
  ON_CALL(*pRawProvider, IsActive()).WillByDefault(testing::Return(true));
  ON_CALL(*pRawProvider, GetName())
      .WillByDefault(testing::Return("Mock provider"));

  testing::NiceMock<ledmatrix::MockIGraphics> graphics;

  uint32_t timeToRun = 1000;

  EXPECT_CALL(*pRawProvider, GetIGraphics())
      .Times(
          testing::Between(timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI - 2,
                           timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI + 2));

  EXPECT_CALL(*pRawProvider, ExecuteDisplayCycle(testing::_))
      .Times(
          testing::Between(timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI - 2,
                           timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI + 2));

  ON_CALL(*pRawProvider, GetIGraphics())
      .WillByDefault(testing::Return(&graphics));

  runtime.AddGraphicsProvider(std::move(provider));
  runtime.Start();

  std::this_thread::sleep_for(std::chrono::milliseconds(timeToRun));

  runtime.Stop();
}

TEST(Runtime, TwoProvidersNoPreamption) {
  ledmatrix::Runtime runtime;

  auto providerHighPriority =
      make_unique<testing::NiceMock<ledmatrix::MockIGraphicsProvider>>();
  auto pRawProviderHighPriority = providerHighPriority.get();
  ON_CALL(*pRawProviderHighPriority, IsActive())
      .WillByDefault(testing::Return(true));
  ON_CALL(*pRawProviderHighPriority, GetPriority())
      .WillByDefault(testing::Return(10));
  ON_CALL(*pRawProviderHighPriority, GetName())
      .WillByDefault(testing::Return("High priority mock provider"));

  auto providerLowPriority =
      make_unique<testing::NiceMock<ledmatrix::MockIGraphicsProvider>>();
  auto pRawProviderLowPriority = providerLowPriority.get();
  ON_CALL(*pRawProviderLowPriority, IsActive())
      .WillByDefault(testing::Return(true));
  ON_CALL(*pRawProviderLowPriority, GetPriority())
      .WillByDefault(testing::Return(1));
  ON_CALL(*pRawProviderLowPriority, GetName())
      .WillByDefault(testing::Return("Low priority mock provider"));

  testing::NiceMock<ledmatrix::MockIGraphics> graphics;

  uint32_t timeToRun = 500;

  EXPECT_CALL(*providerHighPriority, GetIGraphics())
      .Times(
          testing::Between(timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI - 2,
                           timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI + 2));

  EXPECT_CALL(*providerHighPriority, ExecuteDisplayCycle(testing::_))
      .Times(
          testing::Between(timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI - 2,
                           timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI + 2));

  EXPECT_CALL(*providerLowPriority, GetIGraphics()).Times(0);

  EXPECT_CALL(*providerLowPriority, ExecuteDisplayCycle(testing::_)).Times(0);

  ON_CALL(*providerHighPriority, GetIGraphics())
      .WillByDefault(testing::Return(&graphics));

  runtime.AddGraphicsProvider(std::move(providerLowPriority));
  runtime.AddGraphicsProvider(std::move(providerHighPriority));
  runtime.Start();

  std::this_thread::sleep_for(std::chrono::milliseconds(timeToRun));

  runtime.Stop();
}

TEST(Runtime, TwoProvidersWithPreamption) {
  ledmatrix::Runtime runtime;

  // The idea here is to have the high priority provider inactive at the start
  // and then preampting the low priority provider.

  auto providerHighPriority =
      make_unique<testing::NiceMock<ledmatrix::MockIGraphicsProvider>>();
  auto pRawProviderHighPriority = providerHighPriority.get();
  EXPECT_CALL(*pRawProviderHighPriority, IsActive())
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(false))
      .WillOnce(testing::Return(false))
      .WillRepeatedly(testing::Return(true));
  ON_CALL(*pRawProviderHighPriority, GetPriority())
      .WillByDefault(testing::Return(10));
  ON_CALL(*pRawProviderHighPriority, GetName())
      .WillByDefault(testing::Return("High priority mock provider"));

  auto providerLowPriority =
      make_unique<testing::NiceMock<ledmatrix::MockIGraphicsProvider>>();
  auto pRawProviderLowPriority = providerLowPriority.get();
  ON_CALL(*pRawProviderLowPriority, IsActive())
      .WillByDefault(testing::Return(true));
  ON_CALL(*pRawProviderLowPriority, GetPriority())
      .WillByDefault(testing::Return(1));
  ON_CALL(*pRawProviderLowPriority, CanBePreampted())
      .WillByDefault(testing::Return(true));
  ON_CALL(*pRawProviderLowPriority, GetName())
      .WillByDefault(testing::Return("Low priority mock provider"));

  testing::NiceMock<ledmatrix::MockIGraphics> graphics;

  uint32_t timeToRun = 2000;

  EXPECT_CALL(*providerHighPriority, GetIGraphics())
      .Times(testing::Between(
          ((timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI) / 2) - 2,
          ((timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI) / 2) + 2));

  EXPECT_CALL(*providerHighPriority, ExecuteDisplayCycle(testing::_))
      .Times(testing::Between(
          ((timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI) / 2) - 2,
          ((timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI) / 2) + 2));

  EXPECT_CALL(*providerLowPriority, GetIGraphics())
      .Times(testing::Between(
          ((timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI) / 2) - 2,
          ((timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI) / 2) + 2));

  EXPECT_CALL(*providerLowPriority, ExecuteDisplayCycle(testing::_))
      .Times(testing::Between(
          ((timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI) / 2) - 2,
          ((timeToRun / runtime.DISPLAY_CYCLE_TIME_MILLI) / 2) + 2));

  ON_CALL(*providerHighPriority, GetIGraphics())
      .WillByDefault(testing::Return(&graphics));

  runtime.AddGraphicsProvider(std::move(providerLowPriority));
  runtime.AddGraphicsProvider(std::move(providerHighPriority));
  runtime.Start();

  std::this_thread::sleep_for(std::chrono::milliseconds(timeToRun));

  runtime.Stop();
}
