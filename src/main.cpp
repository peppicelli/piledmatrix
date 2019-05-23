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

#include <iostream>

#include "spdlog/spdlog.h"

/**
 * Main entry point.
 * @return int the exit code of the program.
 */
int main() {
  spdlog::info("Hello, {}!", "World");
  return 0;
}