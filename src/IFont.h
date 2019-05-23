/**
 * @file IFont.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Interface for a font class
 * @version 0.1
 * @date 2019-05-17
 * 
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com). All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 * 
 */
#pragma once

#include <stdint.h>

namespace ledmatrix {

/**
 * Alignement enum (for horizontal alignment)
 */
enum Alignment {
    AlignLeft = 0,
    AlignRight,
    AlignCenter
};

/**
 * \a IFont is an interface that every font has to implement. The goal is to have a generic way
 * to use fonts from \a GraphicsToolBox and \a IGraphicsProvider implementing classes.
 */
class IFont {
 public:
    /**
     * Destructor
     */
    virtual ~IFont() {}

    /**
     * Get the maximum width of a single character.
     * @return width of a single character.
     */
    virtual uint16_t GetSingleCharacterMaxWidth() const = 0;

    /**
     * Get the width of a single character.
     * @param c character from which width is needed
     * @return width of the character
     */
    virtual uint16_t GetSingleCharacterWidth(unsigned char c) const = 0;

    /**
     * Get the height of a single character. This function assume that every character in
     * the font has the same height
     * @return height of a single character
     */
    virtual uint16_t GetSingleCharacterHeight() const = 0;

    /**
     * Get the space between letters, also named tracking by typographers.
     * @return space in pixel between two letters
     */
    virtual uint16_t GetLetterSpacing() const = 0;

    /**
     * Set the space between letters, also named tracking by typographers.
     * @param letterSpacing space in pixel between two letters
     */
    virtual void SetLetterSpacing(uint16_t letterSpacing) = 0;

    /**
     * Get the status of one pixel (true = ON) in a character at position (x,y). If \a x or
     * \a y is outside of the boundaries, this function will return false (= OFF).
     * @param c character from which pixel is needed
     * @param x X position of the pixel (starts at 0)
     * @param y Y position of the pixel (starts at 0)
     * @return
     */
    virtual bool GetCharacterPixel(unsigned char c,
                                   uint16_t x,
                                   uint16_t y) const = 0;
};
}  // namespace ledmatrix

