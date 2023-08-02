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

#include "pacmod3_dbc13_ros_api.h"
#include "autogen/pacmod13.h"

#include <vector>
#include <string>
#include <memory>


namespace pacmod3_common
{

std::shared_ptr<void> Dbc13Api::ParseBrakeAuxRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::BrakeAuxRpt>();

  BRAKE_AUX_RPT_t parsed_rpt;
  Unpack_BRAKE_AUX_RPT_pacmod13(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->brake_pressure_2 = parsed_rpt.BRAKE_PRESSURE_2_phys;
  new_msg->brake_pressure = parsed_rpt.BRAKE_PRESSURE_phys;
  new_msg->operator_interaction = parsed_rpt.OPERATOR_INTERACTION;
  new_msg->brake_on_off = parsed_rpt.BRAKE_ON_OFF;
  new_msg->brake_limiting_active = parsed_rpt.BRAKE_LIMITING_ACTIVE;
  new_msg->brake_reduced_assist = parsed_rpt.BRAKE_REDUCED_ASSIST;
  new_msg->calibration_status = parsed_rpt.CALIBRATION_STATUS;
  new_msg->brake_pressure_2_avail = parsed_rpt.BRAKE_PRESSURE_2_AVAIL;
  new_msg->brake_pressure_avail = parsed_rpt.BRAKE_PRESSURE_AVAIL;
  new_msg->brake_on_off_avail = parsed_rpt.BRAKE_ON_OFF_AVAIL;
  new_msg->brake_limiting_active_avail = parsed_rpt.BRAKE_LIMITING_ACTIVE_AVAIL;
  new_msg->brake_reduced_assist_avail = parsed_rpt.BRAKE_REDUCED_ASSIST_AVAIL;

  return new_msg;
}

std::shared_ptr<void> Dbc13Api::ParseGlobalRpt2(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::GlobalRpt2>();

  GLOBAL_RPT_2_t parsed_rpt;
  Unpack_GLOBAL_RPT_2_pacmod13(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->system_enabled = parsed_rpt.SYSTEM_ENABLED;
  new_msg->system_override_active = parsed_rpt.SYSTEM_OVERRIDE_ACTIVE;
  new_msg->system_fault_active = parsed_rpt.SYSTEM_FAULT_ACTIVE;
  new_msg->supervisory_enable_required = parsed_rpt.SUPERVISORY_ENABLE_REQUIRED;
  new_msg->disable_all_systems = parsed_rpt.DISABLE_ALL_SYSTEMS;
  new_msg->system_ready = parsed_rpt.SYSTEM_READY;
  new_msg->enable_method = parsed_rpt.ENABLE_METHOD;
  new_msg->override_mode = parsed_rpt.OVERRIDE_MODE;
  new_msg->development_mode = parsed_rpt.DEVELOPMENT_MODE;
  new_msg->development_mode_allowed = parsed_rpt.DEVELOPMENT_MODE_ALLOWED;

  return new_msg;
}

std::shared_ptr<void> Dbc13Api::ParseParkingBrakeRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::ParkingBrakeRpt>();

  PARKING_BRAKE_RPT_t parsed_rpt;
  Unpack_PARKING_BRAKE_RPT_pacmod13(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->enabled = parsed_rpt.ENABLED;
  new_msg->override_active = parsed_rpt.OVERRIDE_ACTIVE;
  new_msg->command_output_fault = parsed_rpt.COMMAND_OUTPUT_FAULT;
  new_msg->input_output_fault = parsed_rpt.INPUT_OUTPUT_FAULT;
  new_msg->output_reported_fault = parsed_rpt.OUTPUT_REPORTED_FAULT;
  new_msg->pacmod_fault = parsed_rpt.PACMOD_FAULT;
  new_msg->vehicle_fault = parsed_rpt.VEHICLE_FAULT;
  new_msg->command_timeout = parsed_rpt.COMMAND_TIMEOUT;
  new_msg->manual_input = parsed_rpt.MANUAL_INPUT;
  new_msg->command = parsed_rpt.COMMANDED_VALUE;
  new_msg->output = parsed_rpt.OUTPUT_VALUE;
  new_msg->control_status = parsed_rpt.CONTROL_STATUS;
  new_msg->controlling_systems = parsed_rpt.CONTROLLING_SYSTEMS;
  new_msg->performance_status = parsed_rpt.PERFORMANCE_STATUS;

  return new_msg;
}

std::shared_ptr<void> Dbc13Api::ParseShiftRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::ShiftRpt>();

  SHIFT_RPT_t parsed_rpt;
  Unpack_SHIFT_RPT_pacmod13(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->enabled = parsed_rpt.ENABLED;
  new_msg->override_active = parsed_rpt.OVERRIDE_ACTIVE;
  new_msg->command_output_fault = parsed_rpt.COMMAND_OUTPUT_FAULT;
  new_msg->input_output_fault = parsed_rpt.INPUT_OUTPUT_FAULT;
  new_msg->output_reported_fault = parsed_rpt.OUTPUT_REPORTED_FAULT;
  new_msg->pacmod_fault = parsed_rpt.PACMOD_FAULT;
  new_msg->vehicle_fault = parsed_rpt.VEHICLE_FAULT;
  new_msg->command_timeout = parsed_rpt.COMMAND_TIMEOUT;
  new_msg->manual_input = parsed_rpt.MANUAL_INPUT;
  new_msg->command = parsed_rpt.COMMANDED_VALUE;
  new_msg->output = parsed_rpt.OUTPUT_VALUE;
  new_msg->control_status = parsed_rpt.CONTROL_STATUS;
  new_msg->controlling_systems = parsed_rpt.CONTROLLING_SYSTEMS;
  new_msg->performance_status = parsed_rpt.PERFORMANCE_STATUS;

  return new_msg;
}

std::shared_ptr<void> Dbc13Api::ParseShiftAuxRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::ShiftAuxRpt>();

  SHIFT_AUX_RPT_t parsed_rpt;
  Unpack_SHIFT_AUX_RPT_pacmod13(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->between_gears = parsed_rpt.BETWEEN_GEARS;
  new_msg->stay_in_neutral_mode = parsed_rpt.STAY_IN_NEUTRAL_MODE;
  new_msg->brake_interlock_active = parsed_rpt.BRAKE_INTERLOCK_ACTIVE;
  new_msg->speed_interlock_active = parsed_rpt.SPEED_INTERLOCK_ACTIVE;
  new_msg->write_to_config = parsed_rpt.WRITE_TO_CONFIG;
  new_msg->calibration_status = parsed_rpt.CALIBRATION_STATUS;
  new_msg->between_gears_avail = parsed_rpt.BETWEEN_GEARS_AVAIL;
  new_msg->stay_in_neutral_mode_avail = parsed_rpt.STAY_IN_NEUTRAL_MODE_AVAIL;
  new_msg->brake_interlock_active_avail = parsed_rpt.BRAKE_INTERLOCK_ACTIVE_AVAIL;
  new_msg->speed_interlock_active_avail = parsed_rpt.SPEED_INTERLOCK_ACTIVE_AVAIL;
  new_msg->write_to_config_is_valid = parsed_rpt.WRITE_TO_CONFIG_IS_VALID;
  new_msg->gear_number_avail = parsed_rpt.GEAR_NUMBER_AVAIL;
  new_msg->shift_mode_avail = parsed_rpt.SHIFT_MODE_AVAIL;
  new_msg->shift_in_progress_avail = parsed_rpt.SHIFT_IN_PROGRESS_AVAIL;
  new_msg->gear_number = parsed_rpt.GEAR_NUMBER;
  new_msg->shift_mode = parsed_rpt.SHIFT_MODE;
  new_msg->shift_in_progress = parsed_rpt.SHIFT_IN_PROGRESS;
  new_msg->driveline_engaged = parsed_rpt.DRIVELINE_ENGAGED;
  new_msg->actual_gear_ratio = parsed_rpt.ACTUAL_GEAR_RATIO_phys;
  new_msg->driveline_engaged_avail = parsed_rpt.DRIVELINE_ENGAGED_AVAIL;
  new_msg->actual_gear_ratio_avail = parsed_rpt.ACTUAL_GEAR_RATIO_AVAIL;

  return new_msg;
}

std::shared_ptr<void> Dbc13Api::ParseSteeringAuxRpt(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::SteeringAuxRpt>();

  STEERING_AUX_RPT_t parsed_rpt;
  Unpack_STEERING_AUX_RPT_pacmod13(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->steering_fluid_pressure = parsed_rpt.STEERING_FLUID_PRESSURE_phys;
  new_msg->steering_torque = parsed_rpt.STEERING_TORQUE_phys;
  new_msg->rotation_rate = parsed_rpt.ROTATION_RATE_phys;
  new_msg->operator_interaction = parsed_rpt.OPERATOR_INTERACTION;
  new_msg->rotation_rate_sign = parsed_rpt.ROTATION_RATE_SIGN;
  new_msg->vehicle_angle_calib_status = parsed_rpt.VEHICLE_ANGLE_CALIB_STATUS;
  new_msg->steering_limiting_active = parsed_rpt.STEERING_LIMITING_ACTIVE;
  new_msg->calibration_status = parsed_rpt.CALIBRATION_STATUS;
  new_msg->steering_controller_type = parsed_rpt.STEERING_CONTROLLER_TYPE;
  new_msg->steering_torque_avail = parsed_rpt.STEERING_TORQUE_AVAIL;
  new_msg->rotation_rate_avail = parsed_rpt.ROTATION_RATE_AVAIL;
  new_msg->operator_interaction_avail = parsed_rpt.OPERATOR_INTERACTION_AVAIL;
  new_msg->vehicle_angle_calib_status_avail = parsed_rpt.VEHICLE_ANGLE_CALIB_STATUS_AVAIL;
  new_msg->steering_limiting_active_avail = parsed_rpt.STEERING_LIMITING_ACTIVE_AVAIL;
  new_msg->steering_controller_type_avail = parsed_rpt.STEERING_CONTROLLER_TYPE_AVAIL;

  return new_msg;
}

std::shared_ptr<void> Dbc13Api::ParseSystemRptFloat(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::SystemRptFloat>();

  ACCEL_RPT_t parsed_rpt;
  Unpack_ACCEL_RPT_pacmod13(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->enabled = parsed_rpt.ENABLED;
  new_msg->override_active = parsed_rpt.OVERRIDE_ACTIVE;
  new_msg->command_output_fault = parsed_rpt.COMMAND_OUTPUT_FAULT;
  new_msg->input_output_fault = parsed_rpt.INPUT_OUTPUT_FAULT;
  new_msg->output_reported_fault = parsed_rpt.OUTPUT_REPORTED_FAULT;
  new_msg->pacmod_fault = parsed_rpt.PACMOD_FAULT;
  new_msg->vehicle_fault = parsed_rpt.VEHICLE_FAULT;
  new_msg->command_timeout = parsed_rpt.COMMAND_TIMEOUT;
  new_msg->manual_input = parsed_rpt.MANUAL_INPUT_phys;
  new_msg->command = parsed_rpt.COMMANDED_VALUE_phys;
  new_msg->output = parsed_rpt.OUTPUT_VALUE_phys;
  new_msg->control_status = parsed_rpt.CONTROL_STATUS;
  new_msg->controlling_systems = parsed_rpt.CONTROLLING_SYSTEMS;
  new_msg->performance_status = parsed_rpt.PERFORMANCE_STATUS;

  return new_msg;
}

std::shared_ptr<void> Dbc13Api::ParseSafetyFuncRpt2(const cn_msgs::Frame& can_msg)
{
  auto new_msg = std::make_shared<pm_msgs::SafetyFuncRpt2>();

  SAFETY_FUNC_RPT_2_t parsed_rpt;
  Unpack_SAFETY_FUNC_RPT_2_pacmod13(&parsed_rpt, static_cast<const uint8_t*>(&can_msg.data[0]), static_cast<uint8_t>(can_msg.dlc));

  new_msg->commanded_state = parsed_rpt.COMMANDED_STATE;
  new_msg->state = parsed_rpt.STATE;
  new_msg->manual_state_obtainable = parsed_rpt.MANUAL_STATE_OBTAINABLE;
  new_msg->auto_ready_state_obtainable = parsed_rpt.AUTOMS_READY_STATE_OBTAINABLE;
  new_msg->auto_state_obtainable = parsed_rpt.AUTOMS_STATE_OBTAINABLE;
  new_msg->manual_ready_state_obtainable = parsed_rpt.MANUAL_READY_STATE_OBTAINABLE;

  return new_msg;
}

cn_msgs::Frame Dbc13Api::EncodeCmd(const pm_msgs::GlobalCmd& msg)
{
  cn_msgs::Frame packed_frame;

  GLOBAL_CMD_t unpacked_cmd;
  unpacked_cmd.CLEAR_FAULTS = msg.clear_faults;
  unpacked_cmd.SANITY_CHECK_REQUIRED = msg.sanity_check_required;
  unpacked_cmd.CLEAR_OVERRIDES = msg.clear_overrides;
  unpacked_cmd.DEVELOPMENT_MODE_REQUEST = msg.development_mode_request;
  unpacked_cmd.COUNTER = msg.counter;
  unpacked_cmd.COMPLEMENT = msg.complement;

  uint8_t unused_ide;
  Pack_GLOBAL_CMD_pacmod13(&unpacked_cmd, static_cast<uint8_t*>(&packed_frame.data[0]), static_cast<uint8_t*>(&packed_frame.dlc), &unused_ide);

  return packed_frame;
}

cn_msgs::Frame Dbc13Api::EncodeCmd(const pm_msgs::SafetyFuncCmd& msg)
{
  cn_msgs::Frame packed_frame;

  SAFETY_FUNC_CMD_t unpacked_cmd;
  unpacked_cmd.COMMAND = msg.command;

  uint8_t unused_ide;
  Pack_SAFETY_FUNC_CMD_pacmod13(&unpacked_cmd, static_cast<uint8_t*>(&packed_frame.data[0]), static_cast<uint8_t*>(&packed_frame.dlc), &unused_ide);

  return packed_frame;
}

}  // namespace pacmod3_common
