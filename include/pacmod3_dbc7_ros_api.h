// Copyright (c) 2022 AutonomouStuff, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef PACMOD3_DBC7_ROS_API_H
#define PACMOD3_DBC7_ROS_API_H

#include "pacmod3_dbc6_ros_api.h"

#include <string>
#include <vector>
#include <memory>
#include <mutex>

namespace pacmod3_common
{

// Derived from previous DBC API version
// The only overridden functions that exist here are due to changes to those msg types relative to the previous DBC version.
class Dbc7Api : public Dbc6Api
{
public:
  explicit Dbc7Api(uint32_t version = 4):Dbc6Api(version){};
  virtual ~Dbc7Api() = default;

  std::shared_ptr<void> ParseComponentRpt(const cn_msgs::Frame& can_msg) override;
  std::shared_ptr<void> ParseGlobalRpt(const cn_msgs::Frame& can_msg) override;
  std::shared_ptr<void> ParseInteriorLightsRpt(const cn_msgs::Frame& can_msg) override;
  std::shared_ptr<void> ParseShiftAuxRpt(const cn_msgs::Frame& can_msg) override;
  std::shared_ptr<void> ParseSteeringAuxRpt(const cn_msgs::Frame& can_msg) override;
};
}  // namespace pacmod3_common

#endif  // PACMOD3_DBC7_ROS_API_H
