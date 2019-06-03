/**
 * @file MockIMatrixDrawable.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Mock for the IMatrixDrawable class.
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
#include <utility>

#include "src/IMatrixDrawable.h"

namespace ledmatrix {

class MockIMatrixDrawable : public IMatrixDrawable {
 public:
  MOCK_CONST_METHOD2(GetPixel, bool(uint16_t x, uint16_t y));
  // The following line won't really compile, as the return
  // type has multiple template arguments.  To fix it, use a
  // typedef for the return type.
  MOCK_CONST_METHOD0(GetSize, std::pair<uint32_t, uint32_t>());
};

}  // namespace ledmatrix
