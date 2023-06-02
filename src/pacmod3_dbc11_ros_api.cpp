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

#include "pacmod3_dbc11_ros_api.h"
#include "autogen/pacmod11.h"

#include <vector>
#include <string>
#include <memory>


namespace pacmod3_common
{

std::shared_ptr<void> Dbc11Api::ParseAccelAuxRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::AccelAuxRpt>();

  ACCEL_AUX_RPT_t parsed_rpt;
  Unpack_ACCEL_AUX_RPT_pacmod11(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->operator_interaction = parsed_rpt.OPERATOR_INTERACTION;
  new_msg->accel_limiting_active = parsed_rpt.ACCEL_LIMITING_ACTIVE;
  new_msg->park_brake_interlock_active = parsed_rpt.PRK_BRK_INTERLOCK_ACTIVE;
  new_msg->brake_interlock_active = parsed_rpt.BRAKE_INTERLOCK_ACTIVE;

  new_msg->operator_interaction_avail = parsed_rpt.OPERATOR_INTERACTION_AVAIL;
  new_msg->accel_limiting_active_avail = parsed_rpt.ACCEL_LIMITING_ACTIVE_AVAIL;
  new_msg->park_brake_interlock_active_avail = parsed_rpt.PRK_BRK_INTERLOCK_ACTIVE_AVAIL;
  new_msg->brake_interlock_active_avail = parsed_rpt.BRAKE_INTERLOCK_ACTIVE_AVAIL;

  return new_msg;
}

std::shared_ptr<void> Dbc11Api::ParseBrakeAuxRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::BrakeAuxRpt>();

  BRAKE_AUX_RPT_t parsed_rpt;
  Unpack_BRAKE_AUX_RPT_pacmod11(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->brake_pressure = parsed_rpt.BRAKE_PRESSURE_phys;
  new_msg->operator_interaction = parsed_rpt.OPERATOR_INTERACTION;
  new_msg->brake_on_off = parsed_rpt.BRAKE_ON_OFF;
  new_msg->brake_limiting_active = parsed_rpt.BRAKE_LIMITING_ACTIVE;
  new_msg->brake_reduced_assist = parsed_rpt.BRAKE_REDUCED_ASSIST;

  new_msg->brake_pressure_avail = parsed_rpt.BRAKE_PRESSURE_AVAIL;
  new_msg->operator_interaction_avail = parsed_rpt.OPERATOR_INTERACTION_AVAIL;
  new_msg->brake_on_off_avail = parsed_rpt.BRAKE_ON_OFF_AVAIL;
  new_msg->brake_limiting_active_avail = parsed_rpt.BRAKE_LIMITING_ACTIVE_AVAIL;
  new_msg->brake_reduced_assist_avail = parsed_rpt.BRAKE_REDUCED_ASSIST_AVAIL;

  return new_msg;
}

}  // namespace pacmod3_common
