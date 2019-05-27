/**
 * @file MockIGraphics.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Mock for the IGraphics class.
 * @version 0.1
 * @date 2019-05-23
 * 
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com). All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.apache.org/licenses/LICENSE-2.0
 * 
 */
#pragma once

#include <gmock/gmock.h>
#include <src/IGraphics.h>

namespace ledmatrix {

class MockIGraphics : public IGraphics {
 public:
  MOCK_CONST_METHOD0(GetHeight,
      uint16_t());
  MOCK_CONST_METHOD0(GetWidth,
      uint16_t());
  MOCK_METHOD1(SetWidth,
      void(uint16_t width));
  MOCK_METHOD0(Clear,
      void());
  MOCK_METHOD0(Reset,
      void());
  MOCK_METHOD3(SetPixel,
      void(uint16_t x, uint16_t y, bool on));
  MOCK_CONST_METHOD2(GetPixel,
      bool(uint16_t x, uint16_t y));
  MOCK_METHOD2(Rotate,
      void(Direction direction, uint16_t numberOfRows));
  MOCK_METHOD2(Shift,
      void(Direction direction, uint16_t numberOfRows));
};

}  // namespace ledmatrix
