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

#include "pacmod3_dbc5_ros_api.h"
#include "autogen/pacmod5.h"

#include <vector>
#include <string>
#include <memory>


namespace pacmod3_common
{

std::shared_ptr<void> Dbc5Api::ParseComponentRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::ComponentRpt>();

  COMPONENT_RPT_00_t parsed_rpt;
  Unpack_COMPONENT_RPT_00_pacmod5(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->component_type = parsed_rpt.COMPONENT_TYPE;
  new_msg->accel = parsed_rpt.ACCEL;
  new_msg->brake = parsed_rpt.BRAKE;
  new_msg->cruise_control_buttons = parsed_rpt.CRUISE_CONTROL_BUTTONS;
  new_msg->dash_controls_left = parsed_rpt.DASH_CONTROLS_LEFT;
  new_msg->dash_controls_right = parsed_rpt.DASH_CONTROLS_RIGHT;
  new_msg->hazard_lights = parsed_rpt.HAZARD_LIGHTS;
  new_msg->headlight = parsed_rpt.HEADLIGHT;
  new_msg->horn = parsed_rpt.HORN;
  new_msg->media_controls = parsed_rpt.MEDIA_CONTROLS;
  new_msg->parking_brake = parsed_rpt.PARKING_BRAKE;
  new_msg->shift = parsed_rpt.SHIFT;
  new_msg->sprayer = parsed_rpt.SPRAY;
  new_msg->steering = parsed_rpt.STEERING;
  new_msg->turn = parsed_rpt.TURN;
  new_msg->wiper = parsed_rpt.WIPER;
  new_msg->watchdog = parsed_rpt.WATCHDOG;
  new_msg->brake_deccel = parsed_rpt.BRAKE_DECCEL;

  // Following fields not present in dbc5
  new_msg->cabin_climate = 0;
  new_msg->cabin_fan_speed = 0;
  new_msg->cabin_temp = 0;
  new_msg->engine_brake = 0;
  new_msg->marker_lamp = 0;
  new_msg->rear_pass_door = 0;

  new_msg->counter = parsed_rpt.COUNTER;
  new_msg->complement = parsed_rpt.COMPLEMENT;
  new_msg->config_fault = parsed_rpt.CONFIG_FAULT;
  new_msg->can_timeout_fault = parsed_rpt.CAN_TIMEOUT_FAULT;
  new_msg->internal_supply_voltage_fault = parsed_rpt.INTERNAL_SUPPLY_VOLTAGE_FAULT;

  // Following fields not present in dbc5
  new_msg->supervisory_timeout = 0;
  new_msg->supervisory_sanity_fault = 0;
  new_msg->watchdog_sanity_fault = 0;
  new_msg->watchdog_system_present_fault = 0;

  return new_msg;
}

std::shared_ptr<void> Dbc5Api::ParseShiftAuxRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::ShiftAuxRpt>();

  SHIFT_AUX_RPT_t parsed_rpt;
  Unpack_SHIFT_AUX_RPT_pacmod5(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->between_gears = parsed_rpt.BETWEEN_GEARS;
  new_msg->stay_in_neutral_mode = parsed_rpt.STAY_IN_NEUTRAL_MODE;
  new_msg->brake_interlock_active = parsed_rpt.BRAKE_INTERLOCK_ACTIVE;
  new_msg->speed_interlock_active = parsed_rpt.SPEED_INTERLOCK_ACTIVE;
  new_msg->between_gears_avail = parsed_rpt.BETWEEN_GEARS_IS_VALID;
  new_msg->stay_in_neutral_mode_avail = parsed_rpt.STAY_IN_NEUTRAL_MODE_IS_VALID;
  new_msg->brake_interlock_active_avail = parsed_rpt.BRAKE_INTERLOCK_ACTIVE_IS_VALID;
  new_msg->speed_interlock_active_avail = parsed_rpt.SPEED_INTERLOCK_ACTIVE_IS_VALID;
  new_msg->write_to_config = parsed_rpt.WRITE_TO_CONFIG;

  // Following fields not present in dbc5
  new_msg->gear_number = 0;
  new_msg->gear_number_avail = false;
  new_msg->write_to_config_is_valid = false;

  return new_msg;
}

std::shared_ptr<void> Dbc5Api::ParseWheelSpeedRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::WheelSpeedRpt>();

  WHEEL_SPEED_RPT_t parsed_rpt;
  Unpack_WHEEL_SPEED_RPT_pacmod5(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->front_left_wheel_speed = parsed_rpt.WHEEL_SPD_FRONT_LEFT_phys;
  new_msg->front_right_wheel_speed = parsed_rpt.WHEEL_SPD_FRONT_RIGHT_phys;
  new_msg->rear_left_wheel_speed = parsed_rpt.WHEEL_SPD_REAR_LEFT_phys;
  new_msg->rear_right_wheel_speed = parsed_rpt.WHEEL_SPD_REAR_RIGHT_phys;

  return new_msg;
}

}  // namespace pacmod3_common
