/**
 * @file Sure3208LedMatrix.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Driver for the Sure 3208 hardware
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
#pragma once

#include <stdint.h>
#include <cstddef>
#include "IGraphics.h"

namespace ledmatrix {
/**
 * Manage one or two Sure 3208 led matrix(es) through SPI. This class rely on an
 * IGraphic object to print things on screen.
 */
class Sure3208LedMatrix {
 public:
  /**
   * Constructor. Initialize the Led Matrix(s) and clear the screens.
   * @param isDouble must be true when two Sure 3208 Led Matrixes are connected
   * together.
   */
  explicit Sure3208LedMatrix(bool isDouble);

  /**
   * Destructor
   */
  virtual ~Sure3208LedMatrix();

  // Prevent wrong usage of these operators.
  Sure3208LedMatrix() = delete;
  Sure3208LedMatrix(const Sure3208LedMatrix& other) = delete;
  Sure3208LedMatrix& operator=(const Sure3208LedMatrix& other) = delete;
  Sure3208LedMatrix(Sure3208LedMatrix&& other) = delete;
  Sure3208LedMatrix& operator=(Sure3208LedMatrix&& other) = delete;
  bool operator==(const Sure3208LedMatrix& other) const = delete;
  bool operator!=(const Sure3208LedMatrix& other) const = delete;

  /**
   * Clear the screen
   */
  void Clear();

  /**
   * Print the content of graphics on the screen. Will start at position (0,0).
   * The size of the graphics object does not really matter, everything outside
   * the boundaries will result in an OFF pixel.
   * @param graphics contains what will be printed.
   */
  void WriteIGraphics(const IGraphics& graphics);

  /**
   * Set the brightness of the screen
   * @param level level of brightness. Range from 0 (least bright) to 16 (most
   * bright).
   */
  void SetBrightness(unsigned char level);

  void Blink(bool on);

  /**
   * Return the actual width of the physical screen
   */
  uint16_t GetWidth() const;

 private:
  bool m_isDouble;

  /**
   * Send a command according to the HT1632 datasheet on channel 0.
   * @param cmd command to send.
   */
  void SendCommand(unsigned char cmd);

  /**
   * Send a command according to the HT1632 datasheet.
   * @param channel SPI channel (only 0 and 1 are supported).
   * @param cmd command to send.
   */
  void SendCommand(int channel, unsigned char cmd);

  /**
   * Print the content of graphics on the screen selected by channel (0 or 1).
   * Will start at position (0,firstX).
   * @param channel SPI channel (correspond to screen) on which to write.
   * @param firstX start x position in graphics.
   * @param graphics contains what will be printed.
   */
  void WriteIGraphics(int channel, uint16_t firstX,
                      const IGraphics& graphics);

  /**
   * Send all the init commands needed on one channel (screen) in order to be
   * ready to turn pixels ON or OFF.
   * @param channel SPI channel (correspond to screen) on which to write.
   */
  void InitChannel(int channel);

  /**
   * Clear the screen identified by channel.
   * @param channel screen to clear.
   */
  void Clear(int channel);

  void* ReverseEndian(void* p, size_t size);

  static const unsigned char MATRIX_WIDTH = 32;

  static const unsigned char COMMAND_HEADER =
      0x4;  // Header, every command starts with 101
  static const unsigned char COMMAND_SYS_EN = 0x01;  // Enable system oscillator
  static const unsigned char COMMAND_SYS_DYS =
      0x00;  // Disable system oscillator
  static const unsigned char COMMAND_LED_ON =
      0x03;  // Turn on LED duty cycle generator
  static const unsigned char COMMAND_LED_OFF =
      0x02;  // Turn off LED duty cycle generator
  static const unsigned char COMMAND_RC_MASTER_MODE =
      0x18;  // Set master mode and clock source from on-chip RC oscillator
  static const unsigned char COMMAND_N_MOS_COM8 =
      0x20;  // N-MOS open drain output and 32 row * 8 COM
  static const unsigned char COMMAND_BLINK_ON =
      0x09;  // Turn on blinking function
  static const unsigned char COMMAND_BLINK_OFF =
      0x08;  // Turn on blinking function
  static const unsigned char COMMAND_PWM_DUTY =
      0xa0;  // This command with a logical or on anumber between 0 and 16 sets
             // the brightness.
};
}  // namespace ledmatrix
