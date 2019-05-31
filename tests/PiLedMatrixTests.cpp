/**
 * @file PiLedMatrixTests.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Main wrapper tests
 * @version 0.1
 * @date 2019-05-30
 *
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com).
 * All rights reserved. Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */

#include <gtest/gtest.h>

#include "src/PiLedMatrix.h"

TEST(PiLedMatrix, StartAndStop) {
    ledmatrix::PiLedMatrix piLedMatrix;
    EXPECT_FALSE(piLedMatrix.IsStarted());

    // Start (several times)
    piLedMatrix.Start();
    EXPECT_TRUE(piLedMatrix.IsStarted());
    piLedMatrix.Start();
    EXPECT_TRUE(piLedMatrix.IsStarted());

    piLedMatrix.AddMessage("a");

    // Stop (several times)
    piLedMatrix.Stop();
    EXPECT_FALSE(piLedMatrix.IsStarted());
    piLedMatrix.Stop();
    EXPECT_FALSE(piLedMatrix.IsStarted());

    piLedMatrix.AddMessage("b");

    // Restart
    piLedMatrix.Start();
    EXPECT_TRUE(piLedMatrix.IsStarted());
    piLedMatrix.Stop();
    EXPECT_FALSE(piLedMatrix.IsStarted());
}

TEST(PiLedMatrix, DeallocatingDestructor)
{
    auto piLedMatrix = new ledmatrix::PiLedMatrix();
    EXPECT_FALSE(piLedMatrix->IsStarted());
    delete piLedMatrix;
}
