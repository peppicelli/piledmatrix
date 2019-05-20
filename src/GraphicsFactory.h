/**
 * @file GraphicsFactory.h
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
#pragma once

#include "IGraphics.h"

#include <memory>

namespace ledmatrix {

/**
 * Abstract factory for IGraphics.
 */
class GraphicsFactory {
 public:
  /**
   * Type of IGraphics objects
   */
  enum GraphicsFactoryType { MonoColor8RowsGraphicsFactoryType };

  GraphicsFactory();
  virtual ~GraphicsFactory();

  // Prevent wrong usage of these operators.
  GraphicsFactory(const GraphicsFactory& other) = delete;
  GraphicsFactory& operator=(const GraphicsFactory& other) = delete;
  GraphicsFactory(GraphicsFactory&& other) = delete;
  GraphicsFactory& operator=(GraphicsFactory&& other) = delete;
  bool operator==(const GraphicsFactory& other) const = delete;
  bool operator!=(const GraphicsFactory& other) const = delete;

  /**
   * Get IGraphics (return different types depending on the implementing class)
   * @return IGraphics IGraphics is an interface to a model representation of
   * some Led Matrix hardware.
   */
  virtual std::unique_ptr<IGraphics> GetIGraphics() = 0;

  /**
   * Return an IGraphics factory for the given type.
   */
  static std::unique_ptr<GraphicsFactory> CreateFactory(
      GraphicsFactoryType type);
};

}  // namespace ledmatrix
