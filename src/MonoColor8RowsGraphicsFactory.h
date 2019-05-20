/**
 * @file MonoColor8RowsGraphicsFactory.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Factory for MonoColor8RowsGraphics classes
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

#include "GraphicsFactory.h"

#include <memory>

namespace ledmatrix {

class MonoColor8RowsGraphicsFactory : public GraphicsFactory {
 public:
  MonoColor8RowsGraphicsFactory();
  virtual ~MonoColor8RowsGraphicsFactory();

  // Prevent wrong usage of these operators.
  MonoColor8RowsGraphicsFactory(const MonoColor8RowsGraphicsFactory& other) =
      delete;
  MonoColor8RowsGraphicsFactory& operator=(
      const MonoColor8RowsGraphicsFactory& other) = delete;
  MonoColor8RowsGraphicsFactory(MonoColor8RowsGraphicsFactory&& other) = delete;
  MonoColor8RowsGraphicsFactory& operator=(
      MonoColor8RowsGraphicsFactory&& other) = delete;
  bool operator==(const MonoColor8RowsGraphicsFactory& other) const = delete;
  bool operator!=(const MonoColor8RowsGraphicsFactory& other) const = delete;

  virtual std::unique_ptr<IGraphics> GetIGraphics();
};

}  // namespace ledmatrix
