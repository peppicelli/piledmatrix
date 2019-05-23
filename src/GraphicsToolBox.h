/**
 * @file GraphicsToolBox.h
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
#pragma once

#include <string>
#include "src/IFont.h"
#include "src/IGraphics.h"
#include "src/IMatrixDrawable.h"

namespace ledmatrix {

namespace graphics_toolbox {

/**
 * Write a string on one IGraphics matrix with a IFont.
 * The string starts at the bottom left corner of the IGraphics object.
 * @param graphics Matrix model on which to write
 * @param font Font used to write
 * @param message Message to write
 */
void WriteOnScreen(IGraphics& graphics, const IFont& font,
                          const std::string& message);

/**
 * Write a string on one IGraphics matrix with a IFont. The string position is
 * calculated depending on the provided position.
 * @param graphics Matrix model on which to write.
 * @param font Font used to write.
 * @param message Message to write.
 * @param alignment Alignment of the message (Left, Right or Center);
 */
void WriteOnScreen(IGraphics& graphics, const IFont& font,
                          const std::string& message, Alignment alignment);

/**
 * Write a string on one IGraphics matrix with a IFont.
 * The string starts at position (x,y).
 * @param graphics Matrix model on which to write.
 * @param font Font used to write.
 * @param x X position where to start to write message (starts at 0).
 * @param y Y position where to start to write message (starts at 0).
 * @param message Message to write.
 */
void WriteOnScreen(IGraphics& graphics, const IFont& font, uint16_t x,
                          uint16_t y, std::string message);

/**
 * Write a drawable object on one IGraphics matrix
 * @param graphics Matrix model on which to write.
 * @param drawable Object implementing the IMatrixDrawable interface
 * @param x X position where to start to write message (starts at 0).
 * @param y Y position where to start to write message (starts at 0).
 */
void WriteOnScreen(IGraphics& graphics, IMatrixDrawable* drawable,
                          int16_t x, int16_t y) __attribute__((unused));

}  // namespace graphics_toolbox

}  // namespace ledmatrix
