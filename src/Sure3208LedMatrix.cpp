/**
 * @file Sure3208LedMatrix.cpp
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
#include "src/Sure3208LedMatrix.h"

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <algorithm>

#include "spdlog/spdlog.h"
#include "src/IGraphics.h"
#include "wiringPiSPI.h"

namespace ledmatrix {
Sure3208LedMatrix::Sure3208LedMatrix(bool isDouble) : m_isDouble(isDouble) {
  InitChannel(0);
  if (isDouble) {
    InitChannel(1);
  }
  Clear();
}

Sure3208LedMatrix::~Sure3208LedMatrix() {}

void Sure3208LedMatrix::Clear() {
  Clear(0);
  if (m_isDouble) {
    Clear(1);
  }
}

void Sure3208LedMatrix::WriteIGraphics(const IGraphics &graphics) {
  WriteIGraphics(0, 0, graphics);
  if (m_isDouble) {
    WriteIGraphics(1, 32, graphics);
  }
}

void Sure3208LedMatrix::SetBrightness(unsigned char level) {
  SendCommand(0, COMMAND_PWM_DUTY | level);
  if (m_isDouble) {
    SendCommand(1, COMMAND_PWM_DUTY | level);
  }
}

void Sure3208LedMatrix::Blink(bool on) {
  unsigned char commandToSend;

  if (on) {
    commandToSend = COMMAND_BLINK_ON;
  } else {
    commandToSend = COMMAND_BLINK_OFF;
  }

  SendCommand(0, commandToSend);

  if (m_isDouble) {
    SendCommand(1, commandToSend);
  }
}

void Sure3208LedMatrix::WriteIGraphics(int channel, uint16_t firstX,
                                       const IGraphics &graphics) {
  unsigned char data[34];

  // Set all pixel to OFF by default.
  memset(data, 0, sizeof(data));

  data[0] = 0xa0;  // 0x10100000 101 is the command and 00000 are the first 5
                   // bits of the address.
  data[1] = 0x00;  // 0x00000000 the two first bits are the end of the address.
                   // The remaining 6 bits will be filled later on.

  uint16_t dataIndex = 1;
  uint16_t positionWithinWord = 5;
  for (uint16_t x = firstX; x < firstX + MATRIX_WIDTH; ++x) {
    for (uint16_t y = 0; y < graphics.GetHeight(); ++y) {
      if (graphics.GetPixel(x, y)) {
        data[dataIndex] |= (0x1 << positionWithinWord);
      }

      if (0 == positionWithinWord) {
        positionWithinWord = 7;
        ++dataIndex;
      } else {
        --positionWithinWord;
      }
    }
  }
  /* Nasty overlap with the last data index. The problem is that
   * our SPI driver let us only send word (8 bits). The matrix
   * has a maximum size of 32 * 8 pixel = 256. On top of that,
   * we are sending the command header (header + address), which is
   * composed of 3 bits for the command (101) and 7 bits for the
   * address. 10 bits in total, which let us 6 bits unused a the
   * end of our data array. We have to fill them correctly.
   */

  positionWithinWord = 5;
  for (uint16_t y = 0; y < 6; ++y) {
    if (graphics.GetPixel(firstX, y)) {
      data[33] |= (0x1 << positionWithinWord);
    }
    --positionWithinWord;
  }

  wiringPiSPIDataRW(channel, data, 34);
}

uint16_t Sure3208LedMatrix::GetWidth() const {
  if (m_isDouble) {
    return (2 * MATRIX_WIDTH);
  } else {
    return (MATRIX_WIDTH);
  }
}

void Sure3208LedMatrix::SendCommand(unsigned char cmd) { SendCommand(0, cmd); }

void Sure3208LedMatrix::SendCommand(int channel, unsigned char cmd) {
  uint16_t data = 0;
  data = COMMAND_HEADER;
  data <<= 8;
  data |= cmd;
  data <<= 5;
  ReverseEndian(&data, sizeof(data));
  wiringPiSPIDataRW(channel, (unsigned char *)&data, 2);
}

void Sure3208LedMatrix::InitChannel(int channel) {
  spdlog::info("Wiring Pi SPI setup for channel {}", channel);
  if (wiringPiSPISetup(channel, (256 * 1024)) < 0) {
    spdlog::error("SPI channel {} setup failed with error {} ", channel,
                  strerror(errno));
  }
  spdlog::info("Wiring Pi SPI setup for channel {} done", channel);
  SendCommand(channel, COMMAND_SYS_DYS);
  SendCommand(channel, COMMAND_N_MOS_COM8);
  SendCommand(channel, COMMAND_RC_MASTER_MODE);
  SendCommand(channel, COMMAND_SYS_EN);
  SendCommand(channel, COMMAND_LED_ON);
  SendCommand(channel, COMMAND_BLINK_OFF);
}

void Sure3208LedMatrix::Clear(int channel) {
  unsigned char data[34];
  memset(data, 0, sizeof(data));
  data[0] = 0xa0;  // 0x10100000 101 is the command and 00000 are the first 5
                   // bits of the address.
  wiringPiSPIDataRW(channel, data, 34);
}

void *Sure3208LedMatrix::ReverseEndian(void *p, size_t size) {
  char *head = reinterpret_cast<char *>(p);
  char *tail = head + size - 1;

  for (; tail > head; --tail, ++head) {
    char temp = *head;
    *head = *tail;
    *tail = temp;
  }
  return (p);
}

}  // namespace ledmatrix
