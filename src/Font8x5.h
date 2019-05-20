/**
 * @file Font8x5.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Implementation of a 8 by 5 pixels font.
 * @version 0.1
 * @date 2019-05-17
 * 
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com). All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 * 
 */

#pragma once

#include "src/IFont.h"

namespace ledmatrix {

/**
 * 8x5 font (inspired from https://woody-stoker-control.googlecode.com/svn/trunk/font8x5.h).
 */
class Font8x5: public IFont {
 public:
    Font8x5();
    virtual ~Font8x5();

    // Prevent wrong usage of these operators.
    Font8x5(const Font8x5& other) = delete;
    Font8x5& operator=(const Font8x5& other) = delete;
    Font8x5(Font8x5&& other) = delete;
    Font8x5& operator=(Font8x5&& other) = delete;
    bool operator==(const Font8x5& other) const = delete;
    bool operator!=(const Font8x5& other) const = delete;

    virtual uint16_t GetSingleCharacterMaxWidth() const;
    virtual uint16_t GetSingleCharacterWidth(unsigned char c) const;
    virtual uint16_t GetSingleCharacterHeight() const;
    virtual uint16_t GetLetterSpacing() const;
    virtual void SetLetterSpacing(uint16_t letterSpacing);
    virtual bool GetCharacterPixel(unsigned char c,
                                   uint16_t x,
                                   uint16_t y) const;

 private:
    uint16_t m_letterSpacing;
    static const uint16_t WIDTH = 5;
    static const uint16_t HEIGHT = 8;
    static const uint16_t DEFAULT_LETTER_SPACING = 1;
    static const unsigned char FONT_MAP[][WIDTH+1];
};
}  // namespace ledmatrix
