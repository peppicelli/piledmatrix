/**
 * @file MockIGraphics.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Mock for the IGrpahicsProvider class.
 * @version 0.1
 * @date 2019-05-23
 *
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com).
 * All rights reserved. Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */
#pragma once

#include <gmock/gmock.h>

#include <string>

#include "src/IGraphicsProvider.h"

namespace ledmatrix {

class MockIGraphicsProvider : public IGraphicsProvider {
 public:
  MOCK_METHOD1(ExecuteComputeCycle, void(const uint32_t cycleNumber));
  MOCK_METHOD1(ExecuteDisplayCycle, void(const uint32_t cycleNumber));
  MOCK_CONST_METHOD0(GetIGraphics, IGraphics*());
  MOCK_CONST_METHOD0(IsActive, bool());
  MOCK_CONST_METHOD0(GetPriority, unsigned char());
  MOCK_CONST_METHOD0(CanBePreampted, bool());
  MOCK_CONST_METHOD0(GetName, std::string());
};

}  // namespace ledmatrix
