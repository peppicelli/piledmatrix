/**
 * @file main.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Entry point for all the tests
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

#include <gtest/gtest.h>

#include "spdlog/spdlog.h"

int main(int argc, char **argv) {
  // Change the following line to debug.
  spdlog::set_level(spdlog::level::debug);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}