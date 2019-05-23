/**
 * @file MockIFont.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Mock for the IFont class.
 * @version 0.1
 * @date 2019-05-23
 * 
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com). All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.apache.org/licenses/LICENSE-2.0
 * 
 */

#include <gmock/gmock.h>
#include <src/IFont.h>

namespace ledmatrix {

class MockIFont : public IFont {
 public:
  MOCK_CONST_METHOD0(GetSingleCharacterMaxWidth,
      uint16_t());
  MOCK_CONST_METHOD1(GetSingleCharacterWidth,
      uint16_t(unsigned char c));
  MOCK_CONST_METHOD0(GetSingleCharacterHeight,
      uint16_t());
  MOCK_CONST_METHOD0(GetLetterSpacing,
      uint16_t());
  MOCK_METHOD1(SetLetterSpacing,
      void(uint16_t letterSpacing));
  MOCK_CONST_METHOD3(GetCharacterPixel,
      bool(unsigned char c, uint16_t x, uint16_t y));
};

}  // namespace ledmatrix
