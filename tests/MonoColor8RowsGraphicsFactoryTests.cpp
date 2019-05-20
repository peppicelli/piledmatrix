/**
 * @file MonoColor8RowsGraphicsFactoryTests.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Test for the factory for MonoColor8RowsGraphics classes
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

#include "src/MonoColor8RowsGraphicsFactory.h"

TEST(MonoColor8RowsGraphicsFactory, GetIGraphics) {
  std::unique_ptr<ledmatrix::IGraphics> pGraphics =
      ledmatrix::GraphicsFactory::CreateFactory(
          ledmatrix::GraphicsFactory::MonoColor8RowsGraphicsFactoryType)
          ->GetIGraphics();

  EXPECT_EQ(pGraphics->GetWidth(), 0);
  EXPECT_EQ(pGraphics->GetHeight(), 8);
}
