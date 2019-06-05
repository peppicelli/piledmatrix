/**
 * @file PiLedMatrix.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Main class to control everything. All calls are wrapped in python.
 * @version 0.1
 * @date 2019-05-27
 *
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com).
 * All rights reserved. Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */

#include "src/PiLedMatrix.h"

#include <utility>

#include "spdlog/spdlog.h"

#include "src/SimpleMessageGraphicsProvider.h"
#include "src/TimeGraphicsProvider.h"

namespace ledmatrix {

PiLedMatrix::PiLedMatrix()
    : hardware(true), pRuntime(new ledmatrix::Runtime()) {
  // Time provider
  std::unique_ptr<ledmatrix::GraphicsFactory> pTimeGraphicsFactory =
      std::move(ledmatrix::GraphicsFactory::CreateFactory(
          ledmatrix::GraphicsFactory::MonoColor8RowsGraphicsFactoryType));
  std::unique_ptr<ledmatrix::IGraphicsProvider> pTimeGraphicsProvider =
      std::unique_ptr<ledmatrix::IGraphicsProvider>(
          new ledmatrix::TimeGraphicsProvider(std::move(pTimeGraphicsFactory),
                                              hardware.GetWidth()));

  // Message provider
  std::unique_ptr<ledmatrix::GraphicsFactory> pSimpleMessageGraphicsFactory =
      std::move(ledmatrix::GraphicsFactory::CreateFactory(
          ledmatrix::GraphicsFactory::MonoColor8RowsGraphicsFactoryType));
  std::unique_ptr<ledmatrix::IGraphicsProvider> pSimpleMessageGraphicsProvider =
      std::unique_ptr<ledmatrix::IGraphicsProvider>(
          new ledmatrix::SimpleMessageGraphicsProvider(
              std::move(pSimpleMessageGraphicsFactory), hardware.GetWidth()));

  m_pMessageProvider = static_cast<ledmatrix::SimpleMessageGraphicsProvider*>(
      pSimpleMessageGraphicsProvider.get());
  pRuntime->AddGraphicsProvider(std::move(pTimeGraphicsProvider));
  pRuntime->AddGraphicsProvider(std::move(pSimpleMessageGraphicsProvider));
}

void PiLedMatrix::Start() const {
  if (!pRuntime->IsStarted()) {
    pRuntime->Start();
  }
}

void PiLedMatrix::Stop() const {
  if (pRuntime->IsStarted()) {
    pRuntime->Stop();
  }
}

bool PiLedMatrix::IsStarted() const { return pRuntime->IsStarted(); }

void PiLedMatrix::AddMessage(const std::string& message) const {
  if (m_pMessageProvider) {
    m_pMessageProvider->DisplayMessage(message);
  }
}

void PiLedMatrix::SetLoglevel(const spdlog::level::level_enum& level) const {
  spdlog::set_level(level);
}


}  // namespace ledmatrix
