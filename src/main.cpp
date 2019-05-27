/**
 * @file main.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Main entry point
 * @version 0.1
 * @date 2019-05-17
 *
 * @copyright Copyright 2019 {author} ({email}). All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 */

#include <csignal>
#include <iostream>

#include "spdlog/spdlog.h"
#include "src/Runtime.h"
#include "src/Sure3208LedMatrix.h"
#include "src/TimeGraphicsProvider.h"

namespace {
volatile bool g_stopRequest = false;
}

/**
 * Main signal handler
 * @param signal received signal
 */
void signalHandler(int signal) {
  spdlog::warn("Interrupt signal received: {}.", signal);
  g_stopRequest = true;
}

std::unique_ptr<ledmatrix::Runtime> initRuntime(
    const ledmatrix::Sure3208LedMatrix& hardware) {
  std::unique_ptr<ledmatrix::Runtime> pRuntime(new ledmatrix::Runtime());

  // Time provider
  std::unique_ptr<ledmatrix::GraphicsFactory> pTimeGraphicsFactory =
      std::move(ledmatrix::GraphicsFactory::CreateFactory(
          ledmatrix::GraphicsFactory::MonoColor8RowsGraphicsFactoryType));
  std::unique_ptr<ledmatrix::IGraphicsProvider> pTimeGraphicsProvider =
      std::unique_ptr<ledmatrix::IGraphicsProvider>(
          new ledmatrix::TimeGraphicsProvider(std::move(pTimeGraphicsFactory),
                                              hardware.GetWidth()));

  pRuntime->AddGraphicsProvider(std::move(pTimeGraphicsProvider));

  return std::move(pRuntime);
}

/**
 * Main entry point.
 * @return int the exit code of the program.
 */
int main() {
  spdlog::info("Installing signal handler.");
  std::signal(SIGINT, signalHandler);

  spdlog::info("Initializing hardware.");
  ledmatrix::Sure3208LedMatrix hardware(true);
  hardware.SetBrightness(15);

  spdlog::info("Initializing runtime.");
  std::unique_ptr<ledmatrix::Runtime> pRuntime =
      std::move(initRuntime(hardware));

  spdlog::info("Starting runtime.");
  pRuntime->Start();

  while (!g_stopRequest) {
    sleep(1);
  }

  pRuntime->Stop();
  spdlog::info("Clear the screen.");
  hardware.Clear();

  return 0;
}