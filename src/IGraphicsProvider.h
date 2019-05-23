/**
 * @file IGraphicsProvider.h
 * @author Daniel Peppicelli (daniel.peppicelli@gmail.com)
 * @brief Interface for classes proving graphics to the runtime.
 * @version 0.1
 * @date 2019-05-23
 *
 * @copyright Copyright 2019 Daniel Peppicelli (daniel.peppicelli@gmail.com).
 * All rights reserved. Licensed under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 */

#pragma once

#include <memory>
#include <functional>
#include <string>
#include <cstdint>

#include "src/IGraphics.h"

namespace ledmatrix {
/**
 * Classes implementing this interface are "graphics providers". For example,
 * TimeGraphicsProvider will provide the current time as an IGraphic object. The
 * runtime will schedule the graphic provider by calling ExecuteComputeCycle for
 * long operation to be executed in the background and ExecuteDisplayCycle for
 * updating the IGraphic object sent to the driver.
 *
 */
class IGraphicsProvider {
 public:
  virtual ~IGraphicsProvider() {}

  /**
   * The runtime will call this method inbetween two display cycles. The goal is
   * to have long operations executed here.
   * @param cycleNumber The current cycle number.
   */
  virtual void ExecuteComputeCycle(const uint32_t cycleNumber) = 0;

  /**
   * The runtime will call this method just before accessing the IGraphics 
   * object through GetIGraphics().
   * @param cycleNumber The current cycle number.
   */
  virtual void ExecuteDisplayCycle(const uint32_t cycleNumber) = 0;

  /**
   * Return the current IGraphics of the provider.
   * @return IGraphics* A pointer to the current IGraphics object.
   */
  virtual IGraphics* GetIGraphics() const = 0;

  /**
   * Indication of whether there is something to be displayed or not.
   * 
   * @return true If there are still things to be displayed (more cycles needed 
   * for the message to be displayed).
   * @return false Otherwise.
   */
  virtual bool IsActive() const = 0;

  /**
   * Get the priority (as a 8 bit number) of the graphic provider. This value
   * will be used by the runtime to determine which provider should be chosen.
   * @return unsigned char The priority of the current provider.
   */
  virtual unsigned char GetPriority() const = 0;

  /**
   * Indicates if a provider can be preempted. In other words, indicates if
   * the runtime could stop displaying IGraphics from this provider even though 
   * the method IsActive is returning true.
   * 
   * @return true when the provider can be preempted.
   * @return false otherwise.
   */
  virtual bool CanBePreampted() const = 0;

  /**
   * Get the name of the provider.
   * 
   * @return std::string The name of the provider.
   */
  virtual std::string GetName() const = 0;
};

/**
 * Comparator for IGraphics provider. Useful to determine which provider should
 * be selected from a list.
 */
struct IGraphicsProviderPriorityCompare
    : public std::binary_function<std::unique_ptr<IGraphicsProvider>,
                                  std::unique_ptr<IGraphicsProvider>, bool> {
  /**
   * @brief Compare two providers to determine which one should be selected first
   * 
   * @param left the first provider to test.
   * @param right the second provider to test.
   * @return true if left should be chosen.
   * @return false if right should be chosen.
   */
  bool operator()(const std::unique_ptr<IGraphicsProvider>& left,
                  const std::unique_ptr<IGraphicsProvider>& right) const {
    if ((left->IsActive()) && (!(right->IsActive()))) {
      return (true);
    } else if ((!left->IsActive()) && ((right->IsActive()))) {
      return (false);
    } else {
      return (left->GetPriority() > right->GetPriority());
    }
  }
};
}  // namespace ledmatrix
