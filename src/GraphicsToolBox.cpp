/**
 * @file GraphicsToolBox.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Toolbox to manipulate IGraphics objects.
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

#include "src/GraphicsToolBox.h"

#include <algorithm>

#include "spdlog/spdlog.h"

namespace {

static uint16_t GetStringWidth(const ledmatrix::IFont& font,
                               std::string message) {
  uint16_t result = 0;
  bool isSpecialChar = false;
  uint16_t specialCharMask = 0;
  for (unsigned char c : message) {
    // We only support latin extension of utf-8.
    if (195 == c) {
      isSpecialChar = true;
      specialCharMask = 0xC0;
      continue;
    } else if (194 == c) {
      isSpecialChar = true;
      specialCharMask = 0;
      continue;
    } else if (isSpecialChar) {
      // 0xE2 0x80 0x99
      // To map to our ascii table, bit 6 and 7 have to be 1 (if first char was
      // 195). See
      // http://stackoverflow.com/questions/7136421/why-does-utf-8-use-more-than-one-byte-to-represent-some-characters
      c |= specialCharMask;
      isSpecialChar = false;
      specialCharMask = 0;
    }

    result += font.GetSingleCharacterWidth(c);
    result += font.GetLetterSpacing();
  }
  result -= font.GetLetterSpacing();  // No spacing for the last character.
  return (result);
}

static uint16_t GetStartXPosition(ledmatrix::IGraphics& graphics,
                                  const ledmatrix::IFont& font,
                                  const std::string& message,
                                  ledmatrix::Alignment alignment) {
  uint16_t result = 0;
  uint16_t messageWidth = GetStringWidth(font, message);
  uint16_t graphicsWidth = graphics.GetWidth();
  if (messageWidth > graphicsWidth) {
    spdlog::warn(
        "Trying to center a string (\"{}\") with a width ({}) larger"
        " than the current matrix width ({})",
        message, messageWidth, graphicsWidth);
    result = 0;
  } else {
    switch (alignment) {
      case ledmatrix::AlignLeft:
        result = 0;
        break;

      case ledmatrix::AlignRight:
        result = graphicsWidth - messageWidth;
        break;

      case ledmatrix::AlignCenter:
        result = ((graphicsWidth - messageWidth) / 2);
        break;

      default:
        result = 0;
        break;
    }
  }

  return (result);
}

}  // namespace

namespace ledmatrix {

void graphics_toolbox::WriteOnScreen(IGraphics& graphics, const IFont& font,
                                     const std::string& message) {
  WriteOnScreen(graphics, font, 0, graphics.GetHeight() - 1, message);
}

void graphics_toolbox::WriteOnScreen(IGraphics& graphics, const IFont& font,
                                     const std::string& message,
                                     Alignment alignment) {
  WriteOnScreen(graphics, font,
                GetStartXPosition(graphics, font, message, alignment),
                graphics.GetHeight() - 1, message);
}

void graphics_toolbox::WriteOnScreen(IGraphics& graphics, const IFont& font,
                                     uint16_t x, uint16_t y,
                                     std::string message) {
  uint16_t charHeight = font.GetSingleCharacterHeight();
  uint16_t writeX = x;
  bool first = true;
  bool isSpecialChar = false;
  uint16_t specialCharMask = 0;
  for (unsigned char c : message) {
    // We only support latin extension of utf-8.
    if (195 == c) {
      isSpecialChar = true;
      specialCharMask = 0xC0;
      continue;
    } else if (194 == c) {
      isSpecialChar = true;
      specialCharMask = 0;
      continue;
    } else if (isSpecialChar) {
      // To map to our ascii table, bit 6 and 7 have to be 1 (if first char was
      // 195). See
      // http://stackoverflow.com/questions/7136421/why-does-utf-8-use-more-than-one-byte-to-represent-some-characters

      c |= specialCharMask;
      isSpecialChar = false;
      specialCharMask = 0;
    }
    if (!first) {
      // Write n empty column (n = font.GetLetterSpacing())
      x = writeX;
      for (; writeX < x + font.GetLetterSpacing(); ++writeX) {
        for (int16_t writeY = 0; writeY < font.GetSingleCharacterHeight();
             writeY++) {
          graphics.SetPixel(writeX, writeY, false);
        }
      }
    } else {
      first = false;
    }
    uint16_t charWidth = font.GetSingleCharacterWidth(c);
    uint16_t charX = 0;
    x = writeX;
    for (; writeX < x + charWidth; ++writeX, ++charX) {
      uint16_t charY = charHeight - 1;

      for (int16_t writeY = y; writeY > (y - (charHeight)); --writeY, --charY) {
        graphics.SetPixel(
            writeX, writeY,
            font.GetCharacterPixel(c, (unsigned)(charX), (unsigned)(charY)));
      }
    }
  }
  // Write an empty pixel at the end to add a blank column
  graphics.SetPixel(writeX, 0, false);
}

void graphics_toolbox::WriteOnScreen(IGraphics& graphics,
                                     IMatrixDrawable* drawable, int16_t x,
                                     int16_t y) {
  if (drawable) {
    auto size = drawable->GetSize();
    int xMax = x + size.first;
    int yMax = std::min((y + size.second), 8u);

    if ((xMax <= 0) || (yMax <= 0)) {
      return;
    }

    uint16_t drawableX = 0;
    uint16_t writeX = 0;
    if (x >= 0) {
      writeX = x;
    } else {
      drawableX = drawableX - x;
    }
    for (; writeX < xMax; ++writeX, ++drawableX) {
      uint16_t drawableY = 0;
      uint16_t writeY = 0;
      if (y >= 0) {
        writeY = y;
      } else {
        drawableY = drawableY - y;
      }
      for (; writeY < yMax; ++writeY, ++drawableY) {
        graphics.SetPixel(writeX, writeY,
                          drawable->GetPixel(drawableX, drawableY));
      }
    }
  }
}

}  // namespace ledmatrix
