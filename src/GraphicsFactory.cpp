/**
 * @file GraphicsFactory.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Abstract factory for IGraphics classes
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

#include "src/GraphicsFactory.h"

#include <utility>

#include "src/MonoColor8RowsGraphicsFactory.h"

namespace ledmatrix {

GraphicsFactory::GraphicsFactory() {}

GraphicsFactory::~GraphicsFactory() {}

std::unique_ptr<GraphicsFactory> GraphicsFactory::CreateFactory(
    GraphicsFactoryType type) {
  switch (type) {
    case (MonoColor8RowsGraphicsFactoryType):
    default:
      std::unique_ptr<GraphicsFactory> pGraphicsFactory(
          new MonoColor8RowsGraphicsFactory());
      return (std::move(pGraphicsFactory));
      break;
  }

  // needed to avoid warning. Default case of the default case.
  std::unique_ptr<GraphicsFactory> pGraphicsFactory(
      new MonoColor8RowsGraphicsFactory());
  return (std::move(pGraphicsFactory));
}

}  // namespace ledmatrix
