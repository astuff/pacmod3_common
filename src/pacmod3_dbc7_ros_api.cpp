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

#include "pacmod3_dbc7_ros_api.h"
#include "autogen/pacmod7.h"

#include <vector>
#include <string>
#include <memory>


namespace pacmod3_common
{

std::shared_ptr<void> Dbc7Api::ParseComponentRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::ComponentRpt>();

  COMPONENT_RPT_00_t parsed_rpt;
  Unpack_COMPONENT_RPT_00_pacmod7(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

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
  new_msg->rear_pass_door = parsed_rpt.REAR_PASS_DOOR;
  new_msg->engine_brake = parsed_rpt.ENGINE_BRAKE;
  new_msg->marker_lamp = parsed_rpt.MARKER_LAMP;

  // Following fields not present in dbc7
  new_msg->cabin_climate = 0;
  new_msg->cabin_fan_speed = 0;
  new_msg->cabin_temp = 0;

  new_msg->counter = parsed_rpt.COUNTER;
  new_msg->complement = parsed_rpt.COMPLEMENT;
  new_msg->config_fault = parsed_rpt.CONFIG_FAULT;
  new_msg->can_timeout_fault = parsed_rpt.CAN_TIMEOUT_FAULT;
  new_msg->internal_supply_voltage_fault = parsed_rpt.INTERNAL_SUPPLY_VOLTAGE_FAULT;
  new_msg->supervisory_timeout = parsed_rpt.SUPERVISORY_TIMEOUT;
  new_msg->supervisory_sanity_fault = parsed_rpt.SUPERVISORY_SANITY_FAULT;

  // Following fields not present in dbc7
  new_msg->watchdog_sanity_fault = 0;
  new_msg->watchdog_system_present_fault = 0;

  return new_msg;
}

std::shared_ptr<void> Dbc7Api::ParseGlobalRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::GlobalRpt>();

  GLOBAL_RPT_t parsed_rpt;
  Unpack_GLOBAL_RPT_pacmod7(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->enabled = parsed_rpt.PACMOD_SYSTEM_ENABLED;
  new_msg->override_active = parsed_rpt.PACMOD_SYSTEM_OVERRIDE_ACTIVE;
  new_msg->pacmod_sys_fault_active = parsed_rpt.PACMOD_SYSTEM_FAULT_ACTIVE;
  new_msg->config_fault_active = parsed_rpt.CONFIG_FAULT_ACTIVE;
  new_msg->user_can_timeout = parsed_rpt.USR_CAN_TIMEOUT;
  new_msg->steering_can_timeout = parsed_rpt.STR_CAN_TIMEOUT;
  new_msg->brake_can_timeout = parsed_rpt.BRK_CAN_TIMEOUT;
  new_msg->subsystem_can_timeout = parsed_rpt.PACMOD_SUBSYSTEM_TIMEOUT;
  new_msg->vehicle_can_timeout = parsed_rpt.VEH_CAN_TIMEOUT;
  new_msg->user_can_read_errors = parsed_rpt.USR_CAN_READ_ERRORS;
  new_msg->supervisory_enable_required = parsed_rpt.SUPERVISORY_ENABLE_REQUIRED;

  return new_msg;
}

std::shared_ptr<void> Dbc7Api::ParseInteriorLightsRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::InteriorLightsRpt>();

  INTERIOR_LIGHTS_RPT_t parsed_rpt;
  Unpack_INTERIOR_LIGHTS_RPT_pacmod7(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->front_dome_lights_on = parsed_rpt.FRONT_DOME_LIGHTS_ON;
  new_msg->front_dome_lights_on_avail = parsed_rpt.FRONT_DOME_LIGHTS_ON_AVAIL;
  new_msg->rear_dome_lights_on = parsed_rpt.REAR_DOME_LIGHTS_ON;
  new_msg->rear_dome_lights_on_avail = parsed_rpt.REAR_DOME_LIGHTS_ON_AVAIL;
  new_msg->mood_lights_on = parsed_rpt.MOOD_LIGHTS_ON;
  new_msg->mood_lights_on_avail = parsed_rpt.MOOD_LIGHTS_ON_AVAIL;
  new_msg->dim_level = parsed_rpt.DIM_LEVEL;
  new_msg->dim_level_avail = parsed_rpt.DIM_LEVEL_AVAIL;
  new_msg->ambient_light_sensor = parsed_rpt.AMBIENT_LIGHT_SENSOR;
  new_msg->ambient_light_sensor_avail = parsed_rpt.AMBIENT_LIGHT_SENSOR_AVAIL;

  return new_msg;
}

std::shared_ptr<void> Dbc7Api::ParseShiftAuxRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::ShiftAuxRpt>();

  SHIFT_AUX_RPT_t parsed_rpt;
  Unpack_SHIFT_AUX_RPT_pacmod7(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->between_gears = parsed_rpt.BETWEEN_GEARS;
  new_msg->stay_in_neutral_mode = parsed_rpt.STAY_IN_NEUTRAL_MODE;
  new_msg->brake_interlock_active = parsed_rpt.BRAKE_INTERLOCK_ACTIVE;
  new_msg->speed_interlock_active = parsed_rpt.SPEED_INTERLOCK_ACTIVE;
  new_msg->write_to_config = parsed_rpt.WRITE_TO_CONFIG;
  new_msg->gear_number = parsed_rpt.GEAR_NUMBER;

  new_msg->between_gears_avail = parsed_rpt.BETWEEN_GEARS_AVAIL;
  new_msg->stay_in_neutral_mode_avail = parsed_rpt.STAY_IN_NEUTRAL_MODE_AVAIL;
  new_msg->brake_interlock_active_avail = parsed_rpt.BRAKE_INTERLOCK_ACTIVE_AVAIL;
  new_msg->speed_interlock_active_avail = parsed_rpt.SPEED_INTERLOCK_ACTIVE_AVAIL;
  new_msg->write_to_config_is_valid = parsed_rpt.WRITE_TO_CONFIG_IS_VALID;
  new_msg->gear_number_avail = parsed_rpt.GEAR_NUMBER_AVAIL;

  return new_msg;
}

std::shared_ptr<void> Dbc7Api::ParseSteeringAuxRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::SteeringAuxRpt>();

  STEERING_AUX_RPT_t parsed_rpt;
  Unpack_STEERING_AUX_RPT_pacmod7(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->steering_torque = parsed_rpt.RAW_TORQUE_phys;
  new_msg->rotation_rate = parsed_rpt.ROTATION_RATE_phys;
  new_msg->operator_interaction = parsed_rpt.OPERATOR_INTERACTION;
  new_msg->rotation_rate_sign = parsed_rpt.ROTATION_RATE_SIGN;

  new_msg->steering_torque_avail = parsed_rpt.RAW_TORQUE_AVAIL;
  new_msg->rotation_rate_avail = parsed_rpt.ROTATION_RATE_AVAIL;
  new_msg->operator_interaction_avail = parsed_rpt.OPERATOR_INTERACTION_AVAIL;
  new_msg->rotation_rate_sign_avail = parsed_rpt.ROTATION_RATE_SIGN_AVAIL;

  // Following fields not present in dbc7
  new_msg->vehicle_angle_calib_status = false;
  new_msg->steering_limiting_active = false;
  new_msg->vehicle_angle_calib_status_avail = false;
  new_msg->steering_limiting_active_avail = false;

  return new_msg;
}

}  // namespace pacmod3_common
