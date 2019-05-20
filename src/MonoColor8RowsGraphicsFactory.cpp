/**
 * @file MonoColor8RowsGraphicsFactory.cpp
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Factory for MonoColor8RowsGraphics classes
 * @version 0.1
 * @date 2019-05-20
 * 
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com). All rights reserved.
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at http://www.apache.org/licenses/LICENSE-2.0
 * 
 */
#include "src/MonoColor8RowsGraphicsFactory.h"
#include "src/MonoColor8RowsGraphics.h"

namespace ledmatrix {

MonoColor8RowsGraphicsFactory::MonoColor8RowsGraphicsFactory() {}

MonoColor8RowsGraphicsFactory::~MonoColor8RowsGraphicsFactory() {}

std::unique_ptr<IGraphics> MonoColor8RowsGraphicsFactory::GetIGraphics() {
  return (std::unique_ptr<IGraphics>(new MonoColor8RowsGraphics()));
}

}  // namespace ledmatrix
