/**
 * @file MockGraphicsFactory.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Mock for the IFont class.
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

#include <memory>

#include "src/GraphicsFactory.h"

namespace ledmatrix {

class MockGraphicsFactory : public GraphicsFactory {
 public:
  MOCK_METHOD0(GetIGraphics, std::unique_ptr<IGraphics>());
};

}  // namespace ledmatrix
