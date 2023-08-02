#include "pacmod13.h"


// DBC file version
#if (VER_PACMOD13_MAJ != (13U)) || (VER_PACMOD13_MIN != (1U))
#error The PACMOD13 dbc source files have different versions
#endif

#ifdef PACMOD13_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include <pacmod13-fmon.h>

#endif // PACMOD13_USE_DIAG_MONITORS

// This macro guard for the case when you need to enable
// using diag monitors but there is no necessity in proper
// SysTick provider. For providing one you need define macro
// before this line - in dbccodeconf.h

#ifndef GetSystemTick
#define GetSystemTick() (0u)
#endif

// This macro guard is for the case when you want to build
// app with enabled optoin auto CSM, but don't yet have
// proper getframehash implementation

#ifndef GetFrameHash
#define GetFrameHash(a,b,c,d,e) (0u)
#endif

// This function performs extension of sign for the signals
// which have non-aligned to power of 2 bit's width.
// The types 'bitext_t' and 'ubitext_t' define maximal bit width which
// can be correctly handled. You need to select type which can contain
// n+1 bits where n is the largest signed signal width. For example if
// the most wide signed signal has a width of 31 bits you need to set
// bitext_t as int32_t and ubitext_t as uint32_t
// Defined these typedefs in @dbccodeconf.h or locally in 'dbcdrvname'-config.h
static bitext_t __ext_sig__(ubitext_t val, uint8_t bits)
{
  ubitext_t const m = 1u << (bits - 1);
  return (val ^ m) - m;
}

uint32_t Unpack_GLOBAL_RPT_pacmod13(GLOBAL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PACMOD_SYSTEM_ENABLED = (_d[0] & (0x01U));
  _m->PACMOD_SYSTEM_OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->USR_CAN_TIMEOUT = ((_d[0] >> 2) & (0x01U));
  _m->STR_CAN_TIMEOUT = ((_d[0] >> 3) & (0x01U));
  _m->BRK_CAN_TIMEOUT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_SUBSYSTEM_TIMEOUT = ((_d[0] >> 5) & (0x01U));
  _m->VEH_CAN_TIMEOUT = ((_d[0] >> 6) & (0x01U));
  _m->PACMOD_SYSTEM_FAULT_ACTIVE = ((_d[0] >> 7) & (0x01U));
  _m->SUPERVISORY_ENABLE_REQUIRED = ((_d[1] >> 6) & (0x01U));
  _m->CONFIG_FAULT_ACTIVE = ((_d[1] >> 7) & (0x01U));
  _m->USR_CAN_READ_ERRORS = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < GLOBAL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_GLOBAL_RPT_pacmod13(&_m->mon1, GLOBAL_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return GLOBAL_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_GLOBAL_RPT_pacmod13(GLOBAL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < GLOBAL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->PACMOD_SYSTEM_ENABLED & (0x01U)) | ((_m->PACMOD_SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->USR_CAN_TIMEOUT & (0x01U)) << 2) | ((_m->STR_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->BRK_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->PACMOD_SUBSYSTEM_TIMEOUT & (0x01U)) << 5) | ((_m->VEH_CAN_TIMEOUT & (0x01U)) << 6) | ((_m->PACMOD_SYSTEM_FAULT_ACTIVE & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->SUPERVISORY_ENABLE_REQUIRED & (0x01U)) << 6) | ((_m->CONFIG_FAULT_ACTIVE & (0x01U)) << 7);
  cframe->Data[6] |= ((_m->USR_CAN_READ_ERRORS >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->USR_CAN_READ_ERRORS & (0xFFU));

  cframe->MsgId = GLOBAL_RPT_CANID;
  cframe->DLC = GLOBAL_RPT_DLC;
  cframe->IDE = GLOBAL_RPT_IDE;
  return GLOBAL_RPT_CANID;
}

#else

uint32_t Pack_GLOBAL_RPT_pacmod13(GLOBAL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < GLOBAL_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->PACMOD_SYSTEM_ENABLED & (0x01U)) | ((_m->PACMOD_SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->USR_CAN_TIMEOUT & (0x01U)) << 2) | ((_m->STR_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->BRK_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->PACMOD_SUBSYSTEM_TIMEOUT & (0x01U)) << 5) | ((_m->VEH_CAN_TIMEOUT & (0x01U)) << 6) | ((_m->PACMOD_SYSTEM_FAULT_ACTIVE & (0x01U)) << 7);
  _d[1] |= ((_m->SUPERVISORY_ENABLE_REQUIRED & (0x01U)) << 6) | ((_m->CONFIG_FAULT_ACTIVE & (0x01U)) << 7);
  _d[6] |= ((_m->USR_CAN_READ_ERRORS >> 8) & (0xFFU));
  _d[7] |= (_m->USR_CAN_READ_ERRORS & (0xFFU));

  *_len = GLOBAL_RPT_DLC;
  *_ide = GLOBAL_RPT_IDE;
  return GLOBAL_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_GLOBAL_RPT_2_pacmod13(GLOBAL_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SYSTEM_ENABLED = (_d[0] & (0x01U));
  _m->SYSTEM_OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->SYSTEM_FAULT_ACTIVE = ((_d[0] >> 2) & (0x01U));
  _m->SUPERVISORY_ENABLE_REQUIRED = ((_d[0] >> 3) & (0x01U));
  _m->DISABLE_ALL_SYSTEMS = ((_d[0] >> 4) & (0x01U));
  _m->SYSTEM_READY = ((_d[0] >> 5) & (0x01U));
  _m->ENABLE_METHOD = ((_d[0] >> 6) & (0x03U));
  _m->OVERRIDE_MODE = (_d[1] & (0x01U));
  _m->DEVELOPMENT_MODE = ((_d[1] >> 1) & (0x01U));
  _m->DEVELOPMENT_MODE_ALLOWED = ((_d[1] >> 2) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < GLOBAL_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_GLOBAL_RPT_2_pacmod13(&_m->mon1, GLOBAL_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return GLOBAL_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_GLOBAL_RPT_2_pacmod13(GLOBAL_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < GLOBAL_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SYSTEM_ENABLED & (0x01U)) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 2) | ((_m->SUPERVISORY_ENABLE_REQUIRED & (0x01U)) << 3) | ((_m->DISABLE_ALL_SYSTEMS & (0x01U)) << 4) | ((_m->SYSTEM_READY & (0x01U)) << 5) | ((_m->ENABLE_METHOD & (0x03U)) << 6);
  cframe->Data[1] |= (_m->OVERRIDE_MODE & (0x01U)) | ((_m->DEVELOPMENT_MODE & (0x01U)) << 1) | ((_m->DEVELOPMENT_MODE_ALLOWED & (0x01U)) << 2);

  cframe->MsgId = GLOBAL_RPT_2_CANID;
  cframe->DLC = GLOBAL_RPT_2_DLC;
  cframe->IDE = GLOBAL_RPT_2_IDE;
  return GLOBAL_RPT_2_CANID;
}

#else

uint32_t Pack_GLOBAL_RPT_2_pacmod13(GLOBAL_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < GLOBAL_RPT_2_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SYSTEM_ENABLED & (0x01U)) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 2) | ((_m->SUPERVISORY_ENABLE_REQUIRED & (0x01U)) << 3) | ((_m->DISABLE_ALL_SYSTEMS & (0x01U)) << 4) | ((_m->SYSTEM_READY & (0x01U)) << 5) | ((_m->ENABLE_METHOD & (0x03U)) << 6);
  _d[1] |= (_m->OVERRIDE_MODE & (0x01U)) | ((_m->DEVELOPMENT_MODE & (0x01U)) << 1) | ((_m->DEVELOPMENT_MODE_ALLOWED & (0x01U)) << 2);

  *_len = GLOBAL_RPT_2_DLC;
  *_ide = GLOBAL_RPT_2_IDE;
  return GLOBAL_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_00_pacmod13(COMPONENT_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMPONENT_TYPE = (_d[0] & (0x0FU));
  _m->ACCEL = ((_d[0] >> 4) & (0x01U));
  _m->BRAKE = ((_d[0] >> 5) & (0x01U));
  _m->CRUISE_CONTROL_BUTTONS = ((_d[0] >> 6) & (0x01U));
  _m->DASH_CONTROLS_LEFT = ((_d[0] >> 7) & (0x01U));
  _m->DASH_CONTROLS_RIGHT = (_d[1] & (0x01U));
  _m->HAZARD_LIGHTS = ((_d[1] >> 1) & (0x01U));
  _m->HEADLIGHT = ((_d[1] >> 2) & (0x01U));
  _m->HORN = ((_d[1] >> 3) & (0x01U));
  _m->MEDIA_CONTROLS = ((_d[1] >> 4) & (0x01U));
  _m->PARKING_BRAKE = ((_d[1] >> 5) & (0x01U));
  _m->SHIFT = ((_d[1] >> 6) & (0x01U));
  _m->SPRAYER = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECEL = ((_d[2] >> 4) & (0x01U));
  _m->REAR_PASS_DOOR = ((_d[2] >> 5) & (0x01U));
  _m->ENGINE_BRAKE = ((_d[2] >> 6) & (0x01U));
  _m->MARKER_LAMP = ((_d[2] >> 7) & (0x01U));
  _m->CABIN_CLIMATE = (_d[3] & (0x01U));
  _m->CABIN_FAN_SPEED = ((_d[3] >> 1) & (0x01U));
  _m->CABIN_TEMP = ((_d[3] >> 2) & (0x01U));
  _m->EXHAUST_BRAKE = ((_d[3] >> 3) & (0x01U));
  _m->POWER_TAKE_OFF = ((_d[3] >> 4) & (0x01U));
  _m->TIPPER_BODY_00 = ((_d[3] >> 5) & (0x01U));
  _m->TRAILER_AIR_SUPPLY = ((_d[3] >> 6) & (0x01U));
  _m->TRAILER_BRAKE = ((_d[3] >> 7) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));
  _m->SUPERVISORY_TIMEOUT = ((_d[5] >> 3) & (0x01U));
  _m->SUPERVISORY_SANITY_FAULT = ((_d[5] >> 4) & (0x01U));
  _m->WATCHDOG_SANITY_FAULT = ((_d[5] >> 5) & (0x01U));
  _m->WATCHDOG_SYSTEM_PRESENT_FAULT = ((_d[5] >> 6) & (0x01U));
  _m->COMPONENT_READY = ((_d[5] >> 7) & (0x01U));
  _m->ENGINE = (_d[6] & (0x01U));
  _m->TIPPER_BODY_01 = ((_d[6] >> 1) & (0x01U));
  _m->TIPPER_BODY_02 = ((_d[6] >> 2) & (0x01U));
  _m->SYSTEM_ENABLED = ((_d[6] >> 3) & (0x01U));
  _m->SYSTEM_OVERRIDE_ACTIVE = ((_d[6] >> 4) & (0x01U));
  _m->SYSTEM_FAULT_ACTIVE = ((_d[6] >> 5) & (0x01U));
  _m->USER_PC_HEALTH_FAULT_00 = ((_d[6] >> 6) & (0x03U));
  _m->USER_PC_HEALTH_FAULT_01 = (_d[7] & (0x03U));
  _m->DIFFERENTIAL_LOCKS = ((_d[7] >> 2) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_00_pacmod13(&_m->mon1, COMPONENT_RPT_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return COMPONENT_RPT_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_00_pacmod13(COMPONENT_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  cframe->Data[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  cframe->Data[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  cframe->Data[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_00_CANID;
  cframe->DLC = COMPONENT_RPT_00_DLC;
  cframe->IDE = COMPONENT_RPT_00_IDE;
  return COMPONENT_RPT_00_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_00_pacmod13(COMPONENT_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_00_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  _d[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  _d[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  _d[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  *_len = COMPONENT_RPT_00_DLC;
  *_ide = COMPONENT_RPT_00_IDE;
  return COMPONENT_RPT_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_01_pacmod13(COMPONENT_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMPONENT_TYPE = (_d[0] & (0x0FU));
  _m->ACCEL = ((_d[0] >> 4) & (0x01U));
  _m->BRAKE = ((_d[0] >> 5) & (0x01U));
  _m->CRUISE_CONTROL_BUTTONS = ((_d[0] >> 6) & (0x01U));
  _m->DASH_CONTROLS_LEFT = ((_d[0] >> 7) & (0x01U));
  _m->DASH_CONTROLS_RIGHT = (_d[1] & (0x01U));
  _m->HAZARD_LIGHTS = ((_d[1] >> 1) & (0x01U));
  _m->HEADLIGHT = ((_d[1] >> 2) & (0x01U));
  _m->HORN = ((_d[1] >> 3) & (0x01U));
  _m->MEDIA_CONTROLS = ((_d[1] >> 4) & (0x01U));
  _m->PARKING_BRAKE = ((_d[1] >> 5) & (0x01U));
  _m->SHIFT = ((_d[1] >> 6) & (0x01U));
  _m->SPRAYER = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECEL = ((_d[2] >> 4) & (0x01U));
  _m->REAR_PASS_DOOR = ((_d[2] >> 5) & (0x01U));
  _m->ENGINE_BRAKE = ((_d[2] >> 6) & (0x01U));
  _m->MARKER_LAMP = ((_d[2] >> 7) & (0x01U));
  _m->CABIN_CLIMATE = (_d[3] & (0x01U));
  _m->CABIN_FAN_SPEED = ((_d[3] >> 1) & (0x01U));
  _m->CABIN_TEMP = ((_d[3] >> 2) & (0x01U));
  _m->EXHAUST_BRAKE = ((_d[3] >> 3) & (0x01U));
  _m->POWER_TAKE_OFF = ((_d[3] >> 4) & (0x01U));
  _m->TIPPER_BODY_00 = ((_d[3] >> 5) & (0x01U));
  _m->TRAILER_AIR_SUPPLY = ((_d[3] >> 6) & (0x01U));
  _m->TRAILER_BRAKE = ((_d[3] >> 7) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));
  _m->SUPERVISORY_TIMEOUT = ((_d[5] >> 3) & (0x01U));
  _m->SUPERVISORY_SANITY_FAULT = ((_d[5] >> 4) & (0x01U));
  _m->WATCHDOG_SANITY_FAULT = ((_d[5] >> 5) & (0x01U));
  _m->WATCHDOG_SYSTEM_PRESENT_FAULT = ((_d[5] >> 6) & (0x01U));
  _m->COMPONENT_READY = ((_d[5] >> 7) & (0x01U));
  _m->ENGINE = (_d[6] & (0x01U));
  _m->TIPPER_BODY_01 = ((_d[6] >> 1) & (0x01U));
  _m->TIPPER_BODY_02 = ((_d[6] >> 2) & (0x01U));
  _m->SYSTEM_ENABLED = ((_d[6] >> 3) & (0x01U));
  _m->SYSTEM_OVERRIDE_ACTIVE = ((_d[6] >> 4) & (0x01U));
  _m->SYSTEM_FAULT_ACTIVE = ((_d[6] >> 5) & (0x01U));
  _m->USER_PC_HEALTH_FAULT_00 = ((_d[6] >> 6) & (0x03U));
  _m->USER_PC_HEALTH_FAULT_01 = (_d[7] & (0x03U));
  _m->DIFFERENTIAL_LOCKS = ((_d[7] >> 2) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_01_pacmod13(&_m->mon1, COMPONENT_RPT_01_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return COMPONENT_RPT_01_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_01_pacmod13(COMPONENT_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_01_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  cframe->Data[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  cframe->Data[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  cframe->Data[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_01_CANID;
  cframe->DLC = COMPONENT_RPT_01_DLC;
  cframe->IDE = COMPONENT_RPT_01_IDE;
  return COMPONENT_RPT_01_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_01_pacmod13(COMPONENT_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_01_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  _d[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  _d[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  _d[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  *_len = COMPONENT_RPT_01_DLC;
  *_ide = COMPONENT_RPT_01_IDE;
  return COMPONENT_RPT_01_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_02_pacmod13(COMPONENT_RPT_02_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMPONENT_TYPE = (_d[0] & (0x0FU));
  _m->ACCEL = ((_d[0] >> 4) & (0x01U));
  _m->BRAKE = ((_d[0] >> 5) & (0x01U));
  _m->CRUISE_CONTROL_BUTTONS = ((_d[0] >> 6) & (0x01U));
  _m->DASH_CONTROLS_LEFT = ((_d[0] >> 7) & (0x01U));
  _m->DASH_CONTROLS_RIGHT = (_d[1] & (0x01U));
  _m->HAZARD_LIGHTS = ((_d[1] >> 1) & (0x01U));
  _m->HEADLIGHT = ((_d[1] >> 2) & (0x01U));
  _m->HORN = ((_d[1] >> 3) & (0x01U));
  _m->MEDIA_CONTROLS = ((_d[1] >> 4) & (0x01U));
  _m->PARKING_BRAKE = ((_d[1] >> 5) & (0x01U));
  _m->SHIFT = ((_d[1] >> 6) & (0x01U));
  _m->SPRAYER = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECEL = ((_d[2] >> 4) & (0x01U));
  _m->REAR_PASS_DOOR = ((_d[2] >> 5) & (0x01U));
  _m->ENGINE_BRAKE = ((_d[2] >> 6) & (0x01U));
  _m->MARKER_LAMP = ((_d[2] >> 7) & (0x01U));
  _m->CABIN_CLIMATE = (_d[3] & (0x01U));
  _m->CABIN_FAN_SPEED = ((_d[3] >> 1) & (0x01U));
  _m->CABIN_TEMP = ((_d[3] >> 2) & (0x01U));
  _m->EXHAUST_BRAKE = ((_d[3] >> 3) & (0x01U));
  _m->POWER_TAKE_OFF = ((_d[3] >> 4) & (0x01U));
  _m->TIPPER_BODY_00 = ((_d[3] >> 5) & (0x01U));
  _m->TRAILER_AIR_SUPPLY = ((_d[3] >> 6) & (0x01U));
  _m->TRAILER_BRAKE = ((_d[3] >> 7) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));
  _m->SUPERVISORY_TIMEOUT = ((_d[5] >> 3) & (0x01U));
  _m->SUPERVISORY_SANITY_FAULT = ((_d[5] >> 4) & (0x01U));
  _m->WATCHDOG_SANITY_FAULT = ((_d[5] >> 5) & (0x01U));
  _m->WATCHDOG_SYSTEM_PRESENT_FAULT = ((_d[5] >> 6) & (0x01U));
  _m->COMPONENT_READY = ((_d[5] >> 7) & (0x01U));
  _m->ENGINE = (_d[6] & (0x01U));
  _m->TIPPER_BODY_01 = ((_d[6] >> 1) & (0x01U));
  _m->TIPPER_BODY_02 = ((_d[6] >> 2) & (0x01U));
  _m->SYSTEM_ENABLED = ((_d[6] >> 3) & (0x01U));
  _m->SYSTEM_OVERRIDE_ACTIVE = ((_d[6] >> 4) & (0x01U));
  _m->SYSTEM_FAULT_ACTIVE = ((_d[6] >> 5) & (0x01U));
  _m->USER_PC_HEALTH_FAULT_00 = ((_d[6] >> 6) & (0x03U));
  _m->USER_PC_HEALTH_FAULT_01 = (_d[7] & (0x03U));
  _m->DIFFERENTIAL_LOCKS = ((_d[7] >> 2) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_02_pacmod13(&_m->mon1, COMPONENT_RPT_02_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return COMPONENT_RPT_02_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_02_pacmod13(COMPONENT_RPT_02_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_02_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  cframe->Data[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  cframe->Data[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  cframe->Data[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_02_CANID;
  cframe->DLC = COMPONENT_RPT_02_DLC;
  cframe->IDE = COMPONENT_RPT_02_IDE;
  return COMPONENT_RPT_02_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_02_pacmod13(COMPONENT_RPT_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_02_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  _d[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  _d[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  _d[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  *_len = COMPONENT_RPT_02_DLC;
  *_ide = COMPONENT_RPT_02_IDE;
  return COMPONENT_RPT_02_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_03_pacmod13(COMPONENT_RPT_03_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMPONENT_TYPE = (_d[0] & (0x0FU));
  _m->ACCEL = ((_d[0] >> 4) & (0x01U));
  _m->BRAKE = ((_d[0] >> 5) & (0x01U));
  _m->CRUISE_CONTROL_BUTTONS = ((_d[0] >> 6) & (0x01U));
  _m->DASH_CONTROLS_LEFT = ((_d[0] >> 7) & (0x01U));
  _m->DASH_CONTROLS_RIGHT = (_d[1] & (0x01U));
  _m->HAZARD_LIGHTS = ((_d[1] >> 1) & (0x01U));
  _m->HEADLIGHT = ((_d[1] >> 2) & (0x01U));
  _m->HORN = ((_d[1] >> 3) & (0x01U));
  _m->MEDIA_CONTROLS = ((_d[1] >> 4) & (0x01U));
  _m->PARKING_BRAKE = ((_d[1] >> 5) & (0x01U));
  _m->SHIFT = ((_d[1] >> 6) & (0x01U));
  _m->SPRAYER = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECEL = ((_d[2] >> 4) & (0x01U));
  _m->REAR_PASS_DOOR = ((_d[2] >> 5) & (0x01U));
  _m->ENGINE_BRAKE = ((_d[2] >> 6) & (0x01U));
  _m->MARKER_LAMP = ((_d[2] >> 7) & (0x01U));
  _m->CABIN_CLIMATE = (_d[3] & (0x01U));
  _m->CABIN_FAN_SPEED = ((_d[3] >> 1) & (0x01U));
  _m->CABIN_TEMP = ((_d[3] >> 2) & (0x01U));
  _m->EXHAUST_BRAKE = ((_d[3] >> 3) & (0x01U));
  _m->POWER_TAKE_OFF = ((_d[3] >> 4) & (0x01U));
  _m->TIPPER_BODY_00 = ((_d[3] >> 5) & (0x01U));
  _m->TRAILER_AIR_SUPPLY = ((_d[3] >> 6) & (0x01U));
  _m->TRAILER_BRAKE = ((_d[3] >> 7) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));
  _m->SUPERVISORY_TIMEOUT = ((_d[5] >> 3) & (0x01U));
  _m->SUPERVISORY_SANITY_FAULT = ((_d[5] >> 4) & (0x01U));
  _m->WATCHDOG_SANITY_FAULT = ((_d[5] >> 5) & (0x01U));
  _m->WATCHDOG_SYSTEM_PRESENT_FAULT = ((_d[5] >> 6) & (0x01U));
  _m->COMPONENT_READY = ((_d[5] >> 7) & (0x01U));
  _m->ENGINE = (_d[6] & (0x01U));
  _m->TIPPER_BODY_01 = ((_d[6] >> 1) & (0x01U));
  _m->TIPPER_BODY_02 = ((_d[6] >> 2) & (0x01U));
  _m->SYSTEM_ENABLED = ((_d[6] >> 3) & (0x01U));
  _m->SYSTEM_OVERRIDE_ACTIVE = ((_d[6] >> 4) & (0x01U));
  _m->SYSTEM_FAULT_ACTIVE = ((_d[6] >> 5) & (0x01U));
  _m->USER_PC_HEALTH_FAULT_00 = ((_d[6] >> 6) & (0x03U));
  _m->USER_PC_HEALTH_FAULT_01 = (_d[7] & (0x03U));
  _m->DIFFERENTIAL_LOCKS = ((_d[7] >> 2) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_03_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_03_pacmod13(&_m->mon1, COMPONENT_RPT_03_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return COMPONENT_RPT_03_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_03_pacmod13(COMPONENT_RPT_03_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_03_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  cframe->Data[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  cframe->Data[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  cframe->Data[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_03_CANID;
  cframe->DLC = COMPONENT_RPT_03_DLC;
  cframe->IDE = COMPONENT_RPT_03_IDE;
  return COMPONENT_RPT_03_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_03_pacmod13(COMPONENT_RPT_03_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_03_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  _d[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  _d[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  _d[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  *_len = COMPONENT_RPT_03_DLC;
  *_ide = COMPONENT_RPT_03_IDE;
  return COMPONENT_RPT_03_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_04_pacmod13(COMPONENT_RPT_04_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMPONENT_TYPE = (_d[0] & (0x0FU));
  _m->ACCEL = ((_d[0] >> 4) & (0x01U));
  _m->BRAKE = ((_d[0] >> 5) & (0x01U));
  _m->CRUISE_CONTROL_BUTTONS = ((_d[0] >> 6) & (0x01U));
  _m->DASH_CONTROLS_LEFT = ((_d[0] >> 7) & (0x01U));
  _m->DASH_CONTROLS_RIGHT = (_d[1] & (0x01U));
  _m->HAZARD_LIGHTS = ((_d[1] >> 1) & (0x01U));
  _m->HEADLIGHT = ((_d[1] >> 2) & (0x01U));
  _m->HORN = ((_d[1] >> 3) & (0x01U));
  _m->MEDIA_CONTROLS = ((_d[1] >> 4) & (0x01U));
  _m->PARKING_BRAKE = ((_d[1] >> 5) & (0x01U));
  _m->SHIFT = ((_d[1] >> 6) & (0x01U));
  _m->SPRAYER = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECEL = ((_d[2] >> 4) & (0x01U));
  _m->REAR_PASS_DOOR = ((_d[2] >> 5) & (0x01U));
  _m->ENGINE_BRAKE = ((_d[2] >> 6) & (0x01U));
  _m->MARKER_LAMP = ((_d[2] >> 7) & (0x01U));
  _m->CABIN_CLIMATE = (_d[3] & (0x01U));
  _m->CABIN_FAN_SPEED = ((_d[3] >> 1) & (0x01U));
  _m->CABIN_TEMP = ((_d[3] >> 2) & (0x01U));
  _m->EXHAUST_BRAKE = ((_d[3] >> 3) & (0x01U));
  _m->POWER_TAKE_OFF = ((_d[3] >> 4) & (0x01U));
  _m->TIPPER_BODY_00 = ((_d[3] >> 5) & (0x01U));
  _m->TRAILER_AIR_SUPPLY = ((_d[3] >> 6) & (0x01U));
  _m->TRAILER_BRAKE = ((_d[3] >> 7) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));
  _m->SUPERVISORY_TIMEOUT = ((_d[5] >> 3) & (0x01U));
  _m->SUPERVISORY_SANITY_FAULT = ((_d[5] >> 4) & (0x01U));
  _m->WATCHDOG_SANITY_FAULT = ((_d[5] >> 5) & (0x01U));
  _m->WATCHDOG_SYSTEM_PRESENT_FAULT = ((_d[5] >> 6) & (0x01U));
  _m->COMPONENT_READY = ((_d[5] >> 7) & (0x01U));
  _m->ENGINE = (_d[6] & (0x01U));
  _m->TIPPER_BODY_01 = ((_d[6] >> 1) & (0x01U));
  _m->TIPPER_BODY_02 = ((_d[6] >> 2) & (0x01U));
  _m->SYSTEM_ENABLED = ((_d[6] >> 3) & (0x01U));
  _m->SYSTEM_OVERRIDE_ACTIVE = ((_d[6] >> 4) & (0x01U));
  _m->SYSTEM_FAULT_ACTIVE = ((_d[6] >> 5) & (0x01U));
  _m->USER_PC_HEALTH_FAULT_00 = ((_d[6] >> 6) & (0x03U));
  _m->USER_PC_HEALTH_FAULT_01 = (_d[7] & (0x03U));
  _m->DIFFERENTIAL_LOCKS = ((_d[7] >> 2) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_04_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_04_pacmod13(&_m->mon1, COMPONENT_RPT_04_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return COMPONENT_RPT_04_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_04_pacmod13(COMPONENT_RPT_04_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_04_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  cframe->Data[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  cframe->Data[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  cframe->Data[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_04_CANID;
  cframe->DLC = COMPONENT_RPT_04_DLC;
  cframe->IDE = COMPONENT_RPT_04_IDE;
  return COMPONENT_RPT_04_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_04_pacmod13(COMPONENT_RPT_04_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_04_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  _d[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  _d[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  _d[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  *_len = COMPONENT_RPT_04_DLC;
  *_ide = COMPONENT_RPT_04_IDE;
  return COMPONENT_RPT_04_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_USER_PC_HEALTH_RPT_00_pacmod13(USER_PC_HEALTH_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COUNTER = (_d[0] & (0xFFU));
  _m->CHECKSUM = (_d[1] & (0xFFU));
  _m->USER_PC_APPLICATION_FAULT = (_d[2] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < USER_PC_HEALTH_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_USER_PC_HEALTH_RPT_00_pacmod13(&_m->mon1, USER_PC_HEALTH_RPT_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return USER_PC_HEALTH_RPT_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_USER_PC_HEALTH_RPT_00_pacmod13(USER_PC_HEALTH_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < USER_PC_HEALTH_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COUNTER & (0xFFU));
  cframe->Data[1] |= (_m->CHECKSUM & (0xFFU));
  cframe->Data[2] |= (_m->USER_PC_APPLICATION_FAULT & (0x01U));

  cframe->MsgId = USER_PC_HEALTH_RPT_00_CANID;
  cframe->DLC = USER_PC_HEALTH_RPT_00_DLC;
  cframe->IDE = USER_PC_HEALTH_RPT_00_IDE;
  return USER_PC_HEALTH_RPT_00_CANID;
}

#else

uint32_t Pack_USER_PC_HEALTH_RPT_00_pacmod13(USER_PC_HEALTH_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < USER_PC_HEALTH_RPT_00_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COUNTER & (0xFFU));
  _d[1] |= (_m->CHECKSUM & (0xFFU));
  _d[2] |= (_m->USER_PC_APPLICATION_FAULT & (0x01U));

  *_len = USER_PC_HEALTH_RPT_00_DLC;
  *_ide = USER_PC_HEALTH_RPT_00_IDE;
  return USER_PC_HEALTH_RPT_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_USER_PC_HEALTH_RPT_01_pacmod13(USER_PC_HEALTH_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COUNTER = (_d[0] & (0xFFU));
  _m->CHECKSUM = (_d[1] & (0xFFU));
  _m->USER_PC_APPLICATION_FAULT = (_d[2] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < USER_PC_HEALTH_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_USER_PC_HEALTH_RPT_01_pacmod13(&_m->mon1, USER_PC_HEALTH_RPT_01_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return USER_PC_HEALTH_RPT_01_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_USER_PC_HEALTH_RPT_01_pacmod13(USER_PC_HEALTH_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < USER_PC_HEALTH_RPT_01_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COUNTER & (0xFFU));
  cframe->Data[1] |= (_m->CHECKSUM & (0xFFU));
  cframe->Data[2] |= (_m->USER_PC_APPLICATION_FAULT & (0x01U));

  cframe->MsgId = USER_PC_HEALTH_RPT_01_CANID;
  cframe->DLC = USER_PC_HEALTH_RPT_01_DLC;
  cframe->IDE = USER_PC_HEALTH_RPT_01_IDE;
  return USER_PC_HEALTH_RPT_01_CANID;
}

#else

uint32_t Pack_USER_PC_HEALTH_RPT_01_pacmod13(USER_PC_HEALTH_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < USER_PC_HEALTH_RPT_01_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COUNTER & (0xFFU));
  _d[1] |= (_m->CHECKSUM & (0xFFU));
  _d[2] |= (_m->USER_PC_APPLICATION_FAULT & (0x01U));

  *_len = USER_PC_HEALTH_RPT_01_DLC;
  *_ide = USER_PC_HEALTH_RPT_01_IDE;
  return USER_PC_HEALTH_RPT_01_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_05_pacmod13(COMPONENT_RPT_05_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMPONENT_TYPE = (_d[0] & (0x0FU));
  _m->ACCEL = ((_d[0] >> 4) & (0x01U));
  _m->BRAKE = ((_d[0] >> 5) & (0x01U));
  _m->CRUISE_CONTROL_BUTTONS = ((_d[0] >> 6) & (0x01U));
  _m->DASH_CONTROLS_LEFT = ((_d[0] >> 7) & (0x01U));
  _m->DASH_CONTROLS_RIGHT = (_d[1] & (0x01U));
  _m->HAZARD_LIGHTS = ((_d[1] >> 1) & (0x01U));
  _m->HEADLIGHT = ((_d[1] >> 2) & (0x01U));
  _m->HORN = ((_d[1] >> 3) & (0x01U));
  _m->MEDIA_CONTROLS = ((_d[1] >> 4) & (0x01U));
  _m->PARKING_BRAKE = ((_d[1] >> 5) & (0x01U));
  _m->SHIFT = ((_d[1] >> 6) & (0x01U));
  _m->SPRAYER = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECEL = ((_d[2] >> 4) & (0x01U));
  _m->REAR_PASS_DOOR = ((_d[2] >> 5) & (0x01U));
  _m->ENGINE_BRAKE = ((_d[2] >> 6) & (0x01U));
  _m->MARKER_LAMP = ((_d[2] >> 7) & (0x01U));
  _m->CABIN_CLIMATE = (_d[3] & (0x01U));
  _m->CABIN_FAN_SPEED = ((_d[3] >> 1) & (0x01U));
  _m->CABIN_TEMP = ((_d[3] >> 2) & (0x01U));
  _m->EXHAUST_BRAKE = ((_d[3] >> 3) & (0x01U));
  _m->POWER_TAKE_OFF = ((_d[3] >> 4) & (0x01U));
  _m->TIPPER_BODY_00 = ((_d[3] >> 5) & (0x01U));
  _m->TRAILER_AIR_SUPPLY = ((_d[3] >> 6) & (0x01U));
  _m->TRAILER_BRAKE = ((_d[3] >> 7) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));
  _m->SUPERVISORY_TIMEOUT = ((_d[5] >> 3) & (0x01U));
  _m->SUPERVISORY_SANITY_FAULT = ((_d[5] >> 4) & (0x01U));
  _m->WATCHDOG_SANITY_FAULT = ((_d[5] >> 5) & (0x01U));
  _m->WATCHDOG_SYSTEM_PRESENT_FAULT = ((_d[5] >> 6) & (0x01U));
  _m->COMPONENT_READY = ((_d[5] >> 7) & (0x01U));
  _m->ENGINE = (_d[6] & (0x01U));
  _m->TIPPER_BODY_01 = ((_d[6] >> 1) & (0x01U));
  _m->TIPPER_BODY_02 = ((_d[6] >> 2) & (0x01U));
  _m->SYSTEM_ENABLED = ((_d[6] >> 3) & (0x01U));
  _m->SYSTEM_OVERRIDE_ACTIVE = ((_d[6] >> 4) & (0x01U));
  _m->SYSTEM_FAULT_ACTIVE = ((_d[6] >> 5) & (0x01U));
  _m->USER_PC_HEALTH_FAULT_00 = ((_d[6] >> 6) & (0x03U));
  _m->USER_PC_HEALTH_FAULT_01 = (_d[7] & (0x03U));
  _m->DIFFERENTIAL_LOCKS = ((_d[7] >> 2) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_05_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_05_pacmod13(&_m->mon1, COMPONENT_RPT_05_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return COMPONENT_RPT_05_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_05_pacmod13(COMPONENT_RPT_05_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_05_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  cframe->Data[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  cframe->Data[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  cframe->Data[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_05_CANID;
  cframe->DLC = COMPONENT_RPT_05_DLC;
  cframe->IDE = COMPONENT_RPT_05_IDE;
  return COMPONENT_RPT_05_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_05_pacmod13(COMPONENT_RPT_05_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_05_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAYER & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECEL & (0x01U)) << 4) | ((_m->REAR_PASS_DOOR & (0x01U)) << 5) | ((_m->ENGINE_BRAKE & (0x01U)) << 6) | ((_m->MARKER_LAMP & (0x01U)) << 7);
  _d[3] |= (_m->CABIN_CLIMATE & (0x01U)) | ((_m->CABIN_FAN_SPEED & (0x01U)) << 1) | ((_m->CABIN_TEMP & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF & (0x01U)) << 4) | ((_m->TIPPER_BODY_00 & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY & (0x01U)) << 6) | ((_m->TRAILER_BRAKE & (0x01U)) << 7);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2) | ((_m->SUPERVISORY_TIMEOUT & (0x01U)) << 3) | ((_m->SUPERVISORY_SANITY_FAULT & (0x01U)) << 4) | ((_m->WATCHDOG_SANITY_FAULT & (0x01U)) << 5) | ((_m->WATCHDOG_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->COMPONENT_READY & (0x01U)) << 7);
  _d[6] |= (_m->ENGINE & (0x01U)) | ((_m->TIPPER_BODY_01 & (0x01U)) << 1) | ((_m->TIPPER_BODY_02 & (0x01U)) << 2) | ((_m->SYSTEM_ENABLED & (0x01U)) << 3) | ((_m->SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 4) | ((_m->SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->USER_PC_HEALTH_FAULT_00 & (0x03U)) << 6);
  _d[7] |= (_m->USER_PC_HEALTH_FAULT_01 & (0x03U)) | ((_m->DIFFERENTIAL_LOCKS & (0x01U)) << 2);

  *_len = COMPONENT_RPT_05_DLC;
  *_ide = COMPONENT_RPT_05_IDE;
  return COMPONENT_RPT_05_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SAFETY_FUNC_RPT_pacmod13(SAFETY_FUNC_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMMANDED_VALUE = (_d[0] & (0x0FU));
  _m->STATE = ((_d[0] >> 4) & (0x0FU));
  _m->AUTOMS_MAN_OPCTRL = (_d[1] & (0x03U));
  _m->CABIN_SAFETY_BRAKE_OPCTRL = ((_d[1] >> 2) & (0x03U));
  _m->REMOTE_STOP_STATUS = ((_d[1] >> 4) & (0x03U));
  _m->ENGINE_STATUS = ((_d[1] >> 6) & (0x01U));
  _m->PACMOD_SYSTEM_STATUS = ((_d[1] >> 7) & (0x01U));
  _m->USER_PC_FAULT = (_d[2] & (0x03U));
  _m->PACMOD_SYSTEM_FAULT = ((_d[2] >> 2) & (0x03U));
  _m->MANUAL_STATE_OBTAINABLE = (_d[3] & (0x01U));
  _m->AUTOMS_READY_STATE_OBTAINABLE = ((_d[3] >> 1) & (0x01U));
  _m->AUTOMS_STATE_OBTAINABLE = ((_d[3] >> 2) & (0x01U));
  _m->MANUAL_READY_STATE_OBTAINABLE = ((_d[3] >> 3) & (0x01U));
  _m->CRITICAL_STOP1_STATE_OBTAINABLE = ((_d[3] >> 4) & (0x01U));
  _m->CRITICAL_STOP2_STATE_OBTAINABLE = ((_d[3] >> 5) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFETY_FUNC_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFETY_FUNC_RPT_pacmod13(&_m->mon1, SAFETY_FUNC_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SAFETY_FUNC_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SAFETY_FUNC_RPT_pacmod13(SAFETY_FUNC_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SAFETY_FUNC_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMMANDED_VALUE & (0x0FU)) | ((_m->STATE & (0x0FU)) << 4);
  cframe->Data[1] |= (_m->AUTOMS_MAN_OPCTRL & (0x03U)) | ((_m->CABIN_SAFETY_BRAKE_OPCTRL & (0x03U)) << 2) | ((_m->REMOTE_STOP_STATUS & (0x03U)) << 4) | ((_m->ENGINE_STATUS & (0x01U)) << 6) | ((_m->PACMOD_SYSTEM_STATUS & (0x01U)) << 7);
  cframe->Data[2] |= (_m->USER_PC_FAULT & (0x03U)) | ((_m->PACMOD_SYSTEM_FAULT & (0x03U)) << 2);
  cframe->Data[3] |= (_m->MANUAL_STATE_OBTAINABLE & (0x01U)) | ((_m->AUTOMS_READY_STATE_OBTAINABLE & (0x01U)) << 1) | ((_m->AUTOMS_STATE_OBTAINABLE & (0x01U)) << 2) | ((_m->MANUAL_READY_STATE_OBTAINABLE & (0x01U)) << 3) | ((_m->CRITICAL_STOP1_STATE_OBTAINABLE & (0x01U)) << 4) | ((_m->CRITICAL_STOP2_STATE_OBTAINABLE & (0x01U)) << 5);

  cframe->MsgId = SAFETY_FUNC_RPT_CANID;
  cframe->DLC = SAFETY_FUNC_RPT_DLC;
  cframe->IDE = SAFETY_FUNC_RPT_IDE;
  return SAFETY_FUNC_RPT_CANID;
}

#else

uint32_t Pack_SAFETY_FUNC_RPT_pacmod13(SAFETY_FUNC_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SAFETY_FUNC_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMMANDED_VALUE & (0x0FU)) | ((_m->STATE & (0x0FU)) << 4);
  _d[1] |= (_m->AUTOMS_MAN_OPCTRL & (0x03U)) | ((_m->CABIN_SAFETY_BRAKE_OPCTRL & (0x03U)) << 2) | ((_m->REMOTE_STOP_STATUS & (0x03U)) << 4) | ((_m->ENGINE_STATUS & (0x01U)) << 6) | ((_m->PACMOD_SYSTEM_STATUS & (0x01U)) << 7);
  _d[2] |= (_m->USER_PC_FAULT & (0x03U)) | ((_m->PACMOD_SYSTEM_FAULT & (0x03U)) << 2);
  _d[3] |= (_m->MANUAL_STATE_OBTAINABLE & (0x01U)) | ((_m->AUTOMS_READY_STATE_OBTAINABLE & (0x01U)) << 1) | ((_m->AUTOMS_STATE_OBTAINABLE & (0x01U)) << 2) | ((_m->MANUAL_READY_STATE_OBTAINABLE & (0x01U)) << 3) | ((_m->CRITICAL_STOP1_STATE_OBTAINABLE & (0x01U)) << 4) | ((_m->CRITICAL_STOP2_STATE_OBTAINABLE & (0x01U)) << 5);

  *_len = SAFETY_FUNC_RPT_DLC;
  *_ide = SAFETY_FUNC_RPT_IDE;
  return SAFETY_FUNC_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SAFETY_BRAKE_RPT_pacmod13(SAFETY_BRAKE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMMANDED_VALUE = (_d[0] & (0x01U));
  _m->OUTPUT_VALUE = ((_d[0] >> 1) & (0x03U));
  _m->COMMAND_REPORTED_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 4) & (0x01U));
  _m->COMMAND_PERMITTED = ((_d[0] >> 5) & (0x01U));
  _m->REPORTED_FAULT = ((_d[0] >> 6) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFETY_BRAKE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFETY_BRAKE_RPT_pacmod13(&_m->mon1, SAFETY_BRAKE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SAFETY_BRAKE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SAFETY_BRAKE_RPT_pacmod13(SAFETY_BRAKE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SAFETY_BRAKE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMMANDED_VALUE & (0x01U)) | ((_m->OUTPUT_VALUE & (0x03U)) << 1) | ((_m->COMMAND_REPORTED_FAULT & (0x01U)) << 3) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 4) | ((_m->COMMAND_PERMITTED & (0x01U)) << 5) | ((_m->REPORTED_FAULT & (0x01U)) << 6);

  cframe->MsgId = SAFETY_BRAKE_RPT_CANID;
  cframe->DLC = SAFETY_BRAKE_RPT_DLC;
  cframe->IDE = SAFETY_BRAKE_RPT_IDE;
  return SAFETY_BRAKE_RPT_CANID;
}

#else

uint32_t Pack_SAFETY_BRAKE_RPT_pacmod13(SAFETY_BRAKE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SAFETY_BRAKE_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMMANDED_VALUE & (0x01U)) | ((_m->OUTPUT_VALUE & (0x03U)) << 1) | ((_m->COMMAND_REPORTED_FAULT & (0x01U)) << 3) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 4) | ((_m->COMMAND_PERMITTED & (0x01U)) << 5) | ((_m->REPORTED_FAULT & (0x01U)) << 6);

  *_len = SAFETY_BRAKE_RPT_DLC;
  *_ide = SAFETY_BRAKE_RPT_IDE;
  return SAFETY_BRAKE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_FAULT_RPT_pacmod13(VEHICLE_FAULT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENGINE_CHECK_LIGHT = (_d[0] & (0x01U));
  _m->ENGINE_CHECK_LIGHT_AVAIL = ((_d[0] >> 1) & (0x01U));
  _m->TRC_FAULT_LIGHT = ((_d[0] >> 2) & (0x01U));
  _m->TRC_FAULT_LIGHT_AVAIL = ((_d[0] >> 3) & (0x01U));
  _m->TRC_OFF_FAULT_LIGHT = ((_d[0] >> 4) & (0x01U));
  _m->TRC_OFF_FAULT_LIGHT_AVAIL = ((_d[0] >> 5) & (0x01U));
  _m->ANTILOCK_BRAKE_FAULT_LIGHT = ((_d[0] >> 6) & (0x01U));
  _m->ANTILOCK_BRAKE_FAULT_LIGHT_AVAIL = ((_d[0] >> 7) & (0x01U));
  _m->TIRE_FAULT_LIGHT = (_d[1] & (0x01U));
  _m->TIRE_FAULT_LIGHT_AVAIL = ((_d[1] >> 1) & (0x01U));
  _m->AIR_BAGS_FAULT_LIGHT = ((_d[1] >> 2) & (0x01U));
  _m->AIR_BAGS_FAULT_LIGHT_AVAIL = ((_d[1] >> 3) & (0x01U));
  _m->LOW_ENGINE_OIL_PRESSURE = ((_d[1] >> 4) & (0x01U));
  _m->LOW_ENGINE_OIL_PRESSURE_AVAIL = ((_d[1] >> 5) & (0x01U));
  _m->BRAKE_FAULT = ((_d[1] >> 6) & (0x01U));
  _m->BRAKE_FAULT_AVAIL = ((_d[1] >> 7) & (0x01U));
  _m->BRK_APPLIED_POWER_REDUCED = (_d[2] & (0x01U));
  _m->BRK_APPLIED_POWER_REDUCED_AVAIL = ((_d[2] >> 1) & (0x01U));
  _m->STEERING_LOSS_STOP_SAFELY = ((_d[2] >> 2) & (0x01U));
  _m->STEERING_LOSS_STOP_SAFELY_AVAIL = ((_d[2] >> 3) & (0x01U));
  _m->STEERING_FAULT_SERVICE_NOW = ((_d[2] >> 4) & (0x01U));
  _m->STEERING_FAULT_SERVICE_NOW_AVAIL = ((_d[2] >> 5) & (0x01U));
  _m->XMSN_FAULT_SERVICE_NOW = ((_d[2] >> 6) & (0x01U));
  _m->XMSN_FAULT_SERVICE_NOW_AVAIL = ((_d[2] >> 7) & (0x01U));
  _m->XMSN_OVER_TEMP_STOP_SAFELY = (_d[3] & (0x01U));
  _m->XMSN_OVER_TEMP_STOP_SAFELY_AVAIL = ((_d[3] >> 1) & (0x01U));
  _m->LOW_BATTERY_FEATURES_OFF = ((_d[3] >> 2) & (0x01U));
  _m->LOW_BATTERY_FEATURES_OFF_AVAIL = ((_d[3] >> 3) & (0x01U));
  _m->CHARGING_SYSTEM_FAULT = ((_d[3] >> 4) & (0x01U));
  _m->CHARGING_SYSTEM_FAULT_AVAIL = ((_d[3] >> 5) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_FAULT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_FAULT_RPT_pacmod13(&_m->mon1, VEHICLE_FAULT_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return VEHICLE_FAULT_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_VEHICLE_FAULT_RPT_pacmod13(VEHICLE_FAULT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < VEHICLE_FAULT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENGINE_CHECK_LIGHT & (0x01U)) | ((_m->ENGINE_CHECK_LIGHT_AVAIL & (0x01U)) << 1) | ((_m->TRC_FAULT_LIGHT & (0x01U)) << 2) | ((_m->TRC_FAULT_LIGHT_AVAIL & (0x01U)) << 3) | ((_m->TRC_OFF_FAULT_LIGHT & (0x01U)) << 4) | ((_m->TRC_OFF_FAULT_LIGHT_AVAIL & (0x01U)) << 5) | ((_m->ANTILOCK_BRAKE_FAULT_LIGHT & (0x01U)) << 6) | ((_m->ANTILOCK_BRAKE_FAULT_LIGHT_AVAIL & (0x01U)) << 7);
  cframe->Data[1] |= (_m->TIRE_FAULT_LIGHT & (0x01U)) | ((_m->TIRE_FAULT_LIGHT_AVAIL & (0x01U)) << 1) | ((_m->AIR_BAGS_FAULT_LIGHT & (0x01U)) << 2) | ((_m->AIR_BAGS_FAULT_LIGHT_AVAIL & (0x01U)) << 3) | ((_m->LOW_ENGINE_OIL_PRESSURE & (0x01U)) << 4) | ((_m->LOW_ENGINE_OIL_PRESSURE_AVAIL & (0x01U)) << 5) | ((_m->BRAKE_FAULT & (0x01U)) << 6) | ((_m->BRAKE_FAULT_AVAIL & (0x01U)) << 7);
  cframe->Data[2] |= (_m->BRK_APPLIED_POWER_REDUCED & (0x01U)) | ((_m->BRK_APPLIED_POWER_REDUCED_AVAIL & (0x01U)) << 1) | ((_m->STEERING_LOSS_STOP_SAFELY & (0x01U)) << 2) | ((_m->STEERING_LOSS_STOP_SAFELY_AVAIL & (0x01U)) << 3) | ((_m->STEERING_FAULT_SERVICE_NOW & (0x01U)) << 4) | ((_m->STEERING_FAULT_SERVICE_NOW_AVAIL & (0x01U)) << 5) | ((_m->XMSN_FAULT_SERVICE_NOW & (0x01U)) << 6) | ((_m->XMSN_FAULT_SERVICE_NOW_AVAIL & (0x01U)) << 7);
  cframe->Data[3] |= (_m->XMSN_OVER_TEMP_STOP_SAFELY & (0x01U)) | ((_m->XMSN_OVER_TEMP_STOP_SAFELY_AVAIL & (0x01U)) << 1) | ((_m->LOW_BATTERY_FEATURES_OFF & (0x01U)) << 2) | ((_m->LOW_BATTERY_FEATURES_OFF_AVAIL & (0x01U)) << 3) | ((_m->CHARGING_SYSTEM_FAULT & (0x01U)) << 4) | ((_m->CHARGING_SYSTEM_FAULT_AVAIL & (0x01U)) << 5);

  cframe->MsgId = VEHICLE_FAULT_RPT_CANID;
  cframe->DLC = VEHICLE_FAULT_RPT_DLC;
  cframe->IDE = VEHICLE_FAULT_RPT_IDE;
  return VEHICLE_FAULT_RPT_CANID;
}

#else

uint32_t Pack_VEHICLE_FAULT_RPT_pacmod13(VEHICLE_FAULT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < VEHICLE_FAULT_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENGINE_CHECK_LIGHT & (0x01U)) | ((_m->ENGINE_CHECK_LIGHT_AVAIL & (0x01U)) << 1) | ((_m->TRC_FAULT_LIGHT & (0x01U)) << 2) | ((_m->TRC_FAULT_LIGHT_AVAIL & (0x01U)) << 3) | ((_m->TRC_OFF_FAULT_LIGHT & (0x01U)) << 4) | ((_m->TRC_OFF_FAULT_LIGHT_AVAIL & (0x01U)) << 5) | ((_m->ANTILOCK_BRAKE_FAULT_LIGHT & (0x01U)) << 6) | ((_m->ANTILOCK_BRAKE_FAULT_LIGHT_AVAIL & (0x01U)) << 7);
  _d[1] |= (_m->TIRE_FAULT_LIGHT & (0x01U)) | ((_m->TIRE_FAULT_LIGHT_AVAIL & (0x01U)) << 1) | ((_m->AIR_BAGS_FAULT_LIGHT & (0x01U)) << 2) | ((_m->AIR_BAGS_FAULT_LIGHT_AVAIL & (0x01U)) << 3) | ((_m->LOW_ENGINE_OIL_PRESSURE & (0x01U)) << 4) | ((_m->LOW_ENGINE_OIL_PRESSURE_AVAIL & (0x01U)) << 5) | ((_m->BRAKE_FAULT & (0x01U)) << 6) | ((_m->BRAKE_FAULT_AVAIL & (0x01U)) << 7);
  _d[2] |= (_m->BRK_APPLIED_POWER_REDUCED & (0x01U)) | ((_m->BRK_APPLIED_POWER_REDUCED_AVAIL & (0x01U)) << 1) | ((_m->STEERING_LOSS_STOP_SAFELY & (0x01U)) << 2) | ((_m->STEERING_LOSS_STOP_SAFELY_AVAIL & (0x01U)) << 3) | ((_m->STEERING_FAULT_SERVICE_NOW & (0x01U)) << 4) | ((_m->STEERING_FAULT_SERVICE_NOW_AVAIL & (0x01U)) << 5) | ((_m->XMSN_FAULT_SERVICE_NOW & (0x01U)) << 6) | ((_m->XMSN_FAULT_SERVICE_NOW_AVAIL & (0x01U)) << 7);
  _d[3] |= (_m->XMSN_OVER_TEMP_STOP_SAFELY & (0x01U)) | ((_m->XMSN_OVER_TEMP_STOP_SAFELY_AVAIL & (0x01U)) << 1) | ((_m->LOW_BATTERY_FEATURES_OFF & (0x01U)) << 2) | ((_m->LOW_BATTERY_FEATURES_OFF_AVAIL & (0x01U)) << 3) | ((_m->CHARGING_SYSTEM_FAULT & (0x01U)) << 4) | ((_m->CHARGING_SYSTEM_FAULT_AVAIL & (0x01U)) << 5);

  *_len = VEHICLE_FAULT_RPT_DLC;
  *_ide = VEHICLE_FAULT_RPT_IDE;
  return VEHICLE_FAULT_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SAFETY_FUNC_RPT_2_pacmod13(SAFETY_FUNC_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMMANDED_STATE = (_d[0] & (0x0FU));
  _m->STATE = ((_d[0] >> 4) & (0x0FU));
  _m->MANUAL_STATE_OBTAINABLE = (_d[1] & (0x01U));
  _m->AUTOMS_READY_STATE_OBTAINABLE = ((_d[1] >> 1) & (0x01U));
  _m->AUTOMS_STATE_OBTAINABLE = ((_d[1] >> 2) & (0x01U));
  _m->MANUAL_READY_STATE_OBTAINABLE = ((_d[1] >> 3) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFETY_FUNC_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFETY_FUNC_RPT_2_pacmod13(&_m->mon1, SAFETY_FUNC_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SAFETY_FUNC_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SAFETY_FUNC_RPT_2_pacmod13(SAFETY_FUNC_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SAFETY_FUNC_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMMANDED_STATE & (0x0FU)) | ((_m->STATE & (0x0FU)) << 4);
  cframe->Data[1] |= (_m->MANUAL_STATE_OBTAINABLE & (0x01U)) | ((_m->AUTOMS_READY_STATE_OBTAINABLE & (0x01U)) << 1) | ((_m->AUTOMS_STATE_OBTAINABLE & (0x01U)) << 2) | ((_m->MANUAL_READY_STATE_OBTAINABLE & (0x01U)) << 3);

  cframe->MsgId = SAFETY_FUNC_RPT_2_CANID;
  cframe->DLC = SAFETY_FUNC_RPT_2_DLC;
  cframe->IDE = SAFETY_FUNC_RPT_2_IDE;
  return SAFETY_FUNC_RPT_2_CANID;
}

#else

uint32_t Pack_SAFETY_FUNC_RPT_2_pacmod13(SAFETY_FUNC_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SAFETY_FUNC_RPT_2_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMMANDED_STATE & (0x0FU)) | ((_m->STATE & (0x0FU)) << 4);
  _d[1] |= (_m->MANUAL_STATE_OBTAINABLE & (0x01U)) | ((_m->AUTOMS_READY_STATE_OBTAINABLE & (0x01U)) << 1) | ((_m->AUTOMS_STATE_OBTAINABLE & (0x01U)) << 2) | ((_m->MANUAL_READY_STATE_OBTAINABLE & (0x01U)) << 3);

  *_len = SAFETY_FUNC_RPT_2_DLC;
  *_ide = SAFETY_FUNC_RPT_2_IDE;
  return SAFETY_FUNC_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SAFETY_RESPONSE_RPT_pacmod13(SAFETY_RESPONSE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SAFETY_RESPONSE = (_d[0] & (0x0FU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFETY_RESPONSE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFETY_RESPONSE_RPT_pacmod13(&_m->mon1, SAFETY_RESPONSE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SAFETY_RESPONSE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SAFETY_RESPONSE_RPT_pacmod13(SAFETY_RESPONSE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SAFETY_RESPONSE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SAFETY_RESPONSE & (0x0FU));

  cframe->MsgId = SAFETY_RESPONSE_RPT_CANID;
  cframe->DLC = SAFETY_RESPONSE_RPT_DLC;
  cframe->IDE = SAFETY_RESPONSE_RPT_IDE;
  return SAFETY_RESPONSE_RPT_CANID;
}

#else

uint32_t Pack_SAFETY_RESPONSE_RPT_pacmod13(SAFETY_RESPONSE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SAFETY_RESPONSE_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SAFETY_RESPONSE & (0x0FU));

  *_len = SAFETY_RESPONSE_RPT_DLC;
  *_ide = SAFETY_RESPONSE_RPT_IDE;
  return SAFETY_RESPONSE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_GLOBAL_CMD_pacmod13(GLOBAL_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->CLEAR_FAULTS = (_d[0] & (0x01U));
  _m->SANITY_CHECK_REQUIRED = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDES = ((_d[0] >> 2) & (0x01U));
  _m->DEVELOPMENT_MODE_REQUEST = ((_d[0] >> 3) & (0x01U));
  _m->COUNTER = (_d[1] & (0x0FU));
  _m->COMPLEMENT = ((_d[1] >> 4) & (0x0FU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < GLOBAL_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_GLOBAL_CMD_pacmod13(&_m->mon1, GLOBAL_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return GLOBAL_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_GLOBAL_CMD_pacmod13(GLOBAL_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < GLOBAL_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CLEAR_FAULTS & (0x01U)) | ((_m->SANITY_CHECK_REQUIRED & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDES & (0x01U)) << 2) | ((_m->DEVELOPMENT_MODE_REQUEST & (0x01U)) << 3);
  cframe->Data[1] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);

  cframe->MsgId = GLOBAL_CMD_CANID;
  cframe->DLC = GLOBAL_CMD_DLC;
  cframe->IDE = GLOBAL_CMD_IDE;
  return GLOBAL_CMD_CANID;
}

#else

uint32_t Pack_GLOBAL_CMD_pacmod13(GLOBAL_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < GLOBAL_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->CLEAR_FAULTS & (0x01U)) | ((_m->SANITY_CHECK_REQUIRED & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDES & (0x01U)) << 2) | ((_m->DEVELOPMENT_MODE_REQUEST & (0x01U)) << 3);
  _d[1] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);

  *_len = GLOBAL_CMD_DLC;
  *_ide = GLOBAL_CMD_IDE;
  return GLOBAL_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SUPERVISORY_CTRL_pacmod13(SUPERVISORY_CTRL_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->COUNTER = (_d[1] & (0x0FU));
  _m->COMPLEMENT = ((_d[1] >> 4) & (0x0FU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SUPERVISORY_CTRL_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SUPERVISORY_CTRL_pacmod13(&_m->mon1, SUPERVISORY_CTRL_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SUPERVISORY_CTRL_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SUPERVISORY_CTRL_pacmod13(SUPERVISORY_CTRL_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SUPERVISORY_CTRL_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U));
  cframe->Data[1] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);

  cframe->MsgId = SUPERVISORY_CTRL_CANID;
  cframe->DLC = SUPERVISORY_CTRL_DLC;
  cframe->IDE = SUPERVISORY_CTRL_IDE;
  return SUPERVISORY_CTRL_CANID;
}

#else

uint32_t Pack_SUPERVISORY_CTRL_pacmod13(SUPERVISORY_CTRL_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SUPERVISORY_CTRL_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U));
  _d[1] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);

  *_len = SUPERVISORY_CTRL_DLC;
  *_ide = SUPERVISORY_CTRL_IDE;
  return SUPERVISORY_CTRL_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SAFETY_FUNC_CMD_pacmod13(SAFETY_FUNC_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->COMMAND = (_d[0] & (0x0FU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFETY_FUNC_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFETY_FUNC_CMD_pacmod13(&_m->mon1, SAFETY_FUNC_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SAFETY_FUNC_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SAFETY_FUNC_CMD_pacmod13(SAFETY_FUNC_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SAFETY_FUNC_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMMAND & (0x0FU));

  cframe->MsgId = SAFETY_FUNC_CMD_CANID;
  cframe->DLC = SAFETY_FUNC_CMD_DLC;
  cframe->IDE = SAFETY_FUNC_CMD_IDE;
  return SAFETY_FUNC_CMD_CANID;
}

#else

uint32_t Pack_SAFETY_FUNC_CMD_pacmod13(SAFETY_FUNC_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SAFETY_FUNC_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMMAND & (0x0FU));

  *_len = SAFETY_FUNC_CMD_DLC;
  *_ide = SAFETY_FUNC_CMD_IDE;
  return SAFETY_FUNC_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SAFETY_BRAKE_CMD_pacmod13(SAFETY_BRAKE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SAFETY_BRAKE_CMD = (_d[0] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFETY_BRAKE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFETY_BRAKE_CMD_pacmod13(&_m->mon1, SAFETY_BRAKE_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SAFETY_BRAKE_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SAFETY_BRAKE_CMD_pacmod13(SAFETY_BRAKE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SAFETY_BRAKE_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SAFETY_BRAKE_CMD & (0x01U));

  cframe->MsgId = SAFETY_BRAKE_CMD_CANID;
  cframe->DLC = SAFETY_BRAKE_CMD_DLC;
  cframe->IDE = SAFETY_BRAKE_CMD_IDE;
  return SAFETY_BRAKE_CMD_CANID;
}

#else

uint32_t Pack_SAFETY_BRAKE_CMD_pacmod13(SAFETY_BRAKE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SAFETY_BRAKE_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SAFETY_BRAKE_CMD & (0x01U));

  *_len = SAFETY_BRAKE_CMD_DLC;
  *_ide = SAFETY_BRAKE_CMD_IDE;
  return SAFETY_BRAKE_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ACCEL_CMD_pacmod13(ACCEL_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->ACCEL_CMD_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACCEL_CMD_phys = (sigfloat_t)(PACMOD13_ACCEL_CMD_ro_fromS(_m->ACCEL_CMD_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ACCEL_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ACCEL_CMD_pacmod13(&_m->mon1, ACCEL_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ACCEL_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ACCEL_CMD_pacmod13(ACCEL_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ACCEL_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACCEL_CMD_ro = PACMOD13_ACCEL_CMD_ro_toS(_m->ACCEL_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= ((_m->ACCEL_CMD_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->ACCEL_CMD_ro & (0xFFU));

  cframe->MsgId = ACCEL_CMD_CANID;
  cframe->DLC = ACCEL_CMD_DLC;
  cframe->IDE = ACCEL_CMD_IDE;
  return ACCEL_CMD_CANID;
}

#else

uint32_t Pack_ACCEL_CMD_pacmod13(ACCEL_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ACCEL_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACCEL_CMD_ro = PACMOD13_ACCEL_CMD_ro_toS(_m->ACCEL_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= ((_m->ACCEL_CMD_ro >> 8) & (0xFFU));
  _d[2] |= (_m->ACCEL_CMD_ro & (0xFFU));

  *_len = ACCEL_CMD_DLC;
  *_ide = ACCEL_CMD_IDE;
  return ACCEL_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_CMD_pacmod13(BRAKE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->BRAKE_CMD_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_CMD_phys = (sigfloat_t)(PACMOD13_BRAKE_CMD_ro_fromS(_m->BRAKE_CMD_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_CMD_pacmod13(&_m->mon1, BRAKE_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_CMD_pacmod13(BRAKE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_CMD_ro = PACMOD13_BRAKE_CMD_ro_toS(_m->BRAKE_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= ((_m->BRAKE_CMD_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_CMD_ro & (0xFFU));

  cframe->MsgId = BRAKE_CMD_CANID;
  cframe->DLC = BRAKE_CMD_DLC;
  cframe->IDE = BRAKE_CMD_IDE;
  return BRAKE_CMD_CANID;
}

#else

uint32_t Pack_BRAKE_CMD_pacmod13(BRAKE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_CMD_ro = PACMOD13_BRAKE_CMD_ro_toS(_m->BRAKE_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= ((_m->BRAKE_CMD_ro >> 8) & (0xFFU));
  _d[2] |= (_m->BRAKE_CMD_ro & (0xFFU));

  *_len = BRAKE_CMD_DLC;
  *_ide = BRAKE_CMD_IDE;
  return BRAKE_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_CRUISE_CONTROL_BUTTONS_CMD_pacmod13(CRUISE_CONTROL_BUTTONS_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->CRUISE_CONTROL_BUTTON = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CRUISE_CONTROL_BUTTONS_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CRUISE_CONTROL_BUTTONS_CMD_pacmod13(&_m->mon1, CRUISE_CONTROL_BUTTONS_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return CRUISE_CONTROL_BUTTONS_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_CRUISE_CONTROL_BUTTONS_CMD_pacmod13(CRUISE_CONTROL_BUTTONS_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < CRUISE_CONTROL_BUTTONS_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->CRUISE_CONTROL_BUTTON & (0xFFU));

  cframe->MsgId = CRUISE_CONTROL_BUTTONS_CMD_CANID;
  cframe->DLC = CRUISE_CONTROL_BUTTONS_CMD_DLC;
  cframe->IDE = CRUISE_CONTROL_BUTTONS_CMD_IDE;
  return CRUISE_CONTROL_BUTTONS_CMD_CANID;
}

#else

uint32_t Pack_CRUISE_CONTROL_BUTTONS_CMD_pacmod13(CRUISE_CONTROL_BUTTONS_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < CRUISE_CONTROL_BUTTONS_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->CRUISE_CONTROL_BUTTON & (0xFFU));

  *_len = CRUISE_CONTROL_BUTTONS_CMD_DLC;
  *_ide = CRUISE_CONTROL_BUTTONS_CMD_IDE;
  return CRUISE_CONTROL_BUTTONS_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DASH_CONTROLS_LEFT_CMD_pacmod13(DASH_CONTROLS_LEFT_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->DASH_CONTROLS_BUTTON = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DASH_CONTROLS_LEFT_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DASH_CONTROLS_LEFT_CMD_pacmod13(&_m->mon1, DASH_CONTROLS_LEFT_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DASH_CONTROLS_LEFT_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DASH_CONTROLS_LEFT_CMD_pacmod13(DASH_CONTROLS_LEFT_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_LEFT_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->DASH_CONTROLS_BUTTON & (0xFFU));

  cframe->MsgId = DASH_CONTROLS_LEFT_CMD_CANID;
  cframe->DLC = DASH_CONTROLS_LEFT_CMD_DLC;
  cframe->IDE = DASH_CONTROLS_LEFT_CMD_IDE;
  return DASH_CONTROLS_LEFT_CMD_CANID;
}

#else

uint32_t Pack_DASH_CONTROLS_LEFT_CMD_pacmod13(DASH_CONTROLS_LEFT_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_LEFT_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->DASH_CONTROLS_BUTTON & (0xFFU));

  *_len = DASH_CONTROLS_LEFT_CMD_DLC;
  *_ide = DASH_CONTROLS_LEFT_CMD_IDE;
  return DASH_CONTROLS_LEFT_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DASH_CONTROLS_RIGHT_CMD_pacmod13(DASH_CONTROLS_RIGHT_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->DASH_CONTROLS_BUTTON = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DASH_CONTROLS_RIGHT_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DASH_CONTROLS_RIGHT_CMD_pacmod13(&_m->mon1, DASH_CONTROLS_RIGHT_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DASH_CONTROLS_RIGHT_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DASH_CONTROLS_RIGHT_CMD_pacmod13(DASH_CONTROLS_RIGHT_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_RIGHT_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->DASH_CONTROLS_BUTTON & (0xFFU));

  cframe->MsgId = DASH_CONTROLS_RIGHT_CMD_CANID;
  cframe->DLC = DASH_CONTROLS_RIGHT_CMD_DLC;
  cframe->IDE = DASH_CONTROLS_RIGHT_CMD_IDE;
  return DASH_CONTROLS_RIGHT_CMD_CANID;
}

#else

uint32_t Pack_DASH_CONTROLS_RIGHT_CMD_pacmod13(DASH_CONTROLS_RIGHT_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_RIGHT_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->DASH_CONTROLS_BUTTON & (0xFFU));

  *_len = DASH_CONTROLS_RIGHT_CMD_DLC;
  *_ide = DASH_CONTROLS_RIGHT_CMD_IDE;
  return DASH_CONTROLS_RIGHT_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_HAZARD_LIGHTS_CMD_pacmod13(HAZARD_LIGHTS_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->HAZARD_LIGHTS_CMD = (_d[1] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HAZARD_LIGHTS_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HAZARD_LIGHTS_CMD_pacmod13(&_m->mon1, HAZARD_LIGHTS_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return HAZARD_LIGHTS_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_HAZARD_LIGHTS_CMD_pacmod13(HAZARD_LIGHTS_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < HAZARD_LIGHTS_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->HAZARD_LIGHTS_CMD & (0x01U));

  cframe->MsgId = HAZARD_LIGHTS_CMD_CANID;
  cframe->DLC = HAZARD_LIGHTS_CMD_DLC;
  cframe->IDE = HAZARD_LIGHTS_CMD_IDE;
  return HAZARD_LIGHTS_CMD_CANID;
}

#else

uint32_t Pack_HAZARD_LIGHTS_CMD_pacmod13(HAZARD_LIGHTS_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HAZARD_LIGHTS_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->HAZARD_LIGHTS_CMD & (0x01U));

  *_len = HAZARD_LIGHTS_CMD_DLC;
  *_ide = HAZARD_LIGHTS_CMD_IDE;
  return HAZARD_LIGHTS_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_HEADLIGHT_CMD_pacmod13(HEADLIGHT_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->HEADLIGHT_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HEADLIGHT_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HEADLIGHT_CMD_pacmod13(&_m->mon1, HEADLIGHT_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return HEADLIGHT_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_HEADLIGHT_CMD_pacmod13(HEADLIGHT_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < HEADLIGHT_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->HEADLIGHT_CMD & (0xFFU));

  cframe->MsgId = HEADLIGHT_CMD_CANID;
  cframe->DLC = HEADLIGHT_CMD_DLC;
  cframe->IDE = HEADLIGHT_CMD_IDE;
  return HEADLIGHT_CMD_CANID;
}

#else

uint32_t Pack_HEADLIGHT_CMD_pacmod13(HEADLIGHT_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HEADLIGHT_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->HEADLIGHT_CMD & (0xFFU));

  *_len = HEADLIGHT_CMD_DLC;
  *_ide = HEADLIGHT_CMD_IDE;
  return HEADLIGHT_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_HORN_CMD_pacmod13(HORN_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->HORN_CMD = (_d[1] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HORN_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HORN_CMD_pacmod13(&_m->mon1, HORN_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return HORN_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_HORN_CMD_pacmod13(HORN_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < HORN_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->HORN_CMD & (0x01U));

  cframe->MsgId = HORN_CMD_CANID;
  cframe->DLC = HORN_CMD_DLC;
  cframe->IDE = HORN_CMD_IDE;
  return HORN_CMD_CANID;
}

#else

uint32_t Pack_HORN_CMD_pacmod13(HORN_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HORN_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->HORN_CMD & (0x01U));

  *_len = HORN_CMD_DLC;
  *_ide = HORN_CMD_IDE;
  return HORN_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_MEDIA_CONTROLS_CMD_pacmod13(MEDIA_CONTROLS_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->MEDIA_CONTROLS_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < MEDIA_CONTROLS_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_MEDIA_CONTROLS_CMD_pacmod13(&_m->mon1, MEDIA_CONTROLS_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return MEDIA_CONTROLS_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_MEDIA_CONTROLS_CMD_pacmod13(MEDIA_CONTROLS_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < MEDIA_CONTROLS_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->MEDIA_CONTROLS_CMD & (0xFFU));

  cframe->MsgId = MEDIA_CONTROLS_CMD_CANID;
  cframe->DLC = MEDIA_CONTROLS_CMD_DLC;
  cframe->IDE = MEDIA_CONTROLS_CMD_IDE;
  return MEDIA_CONTROLS_CMD_CANID;
}

#else

uint32_t Pack_MEDIA_CONTROLS_CMD_pacmod13(MEDIA_CONTROLS_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < MEDIA_CONTROLS_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->MEDIA_CONTROLS_CMD & (0xFFU));

  *_len = MEDIA_CONTROLS_CMD_DLC;
  *_ide = MEDIA_CONTROLS_CMD_IDE;
  return MEDIA_CONTROLS_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_PARKING_BRAKE_CMD_pacmod13(PARKING_BRAKE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->PARKING_BRAKE_CMD = (_d[1] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < PARKING_BRAKE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_PARKING_BRAKE_CMD_pacmod13(&_m->mon1, PARKING_BRAKE_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return PARKING_BRAKE_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_PARKING_BRAKE_CMD_pacmod13(PARKING_BRAKE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->PARKING_BRAKE_CMD & (0x01U));

  cframe->MsgId = PARKING_BRAKE_CMD_CANID;
  cframe->DLC = PARKING_BRAKE_CMD_DLC;
  cframe->IDE = PARKING_BRAKE_CMD_IDE;
  return PARKING_BRAKE_CMD_CANID;
}

#else

uint32_t Pack_PARKING_BRAKE_CMD_pacmod13(PARKING_BRAKE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->PARKING_BRAKE_CMD & (0x01U));

  *_len = PARKING_BRAKE_CMD_DLC;
  *_ide = PARKING_BRAKE_CMD_IDE;
  return PARKING_BRAKE_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SHIFT_CMD_pacmod13(SHIFT_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->SHIFT_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SHIFT_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SHIFT_CMD_pacmod13(&_m->mon1, SHIFT_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SHIFT_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SHIFT_CMD_pacmod13(SHIFT_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SHIFT_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->SHIFT_CMD & (0xFFU));

  cframe->MsgId = SHIFT_CMD_CANID;
  cframe->DLC = SHIFT_CMD_DLC;
  cframe->IDE = SHIFT_CMD_IDE;
  return SHIFT_CMD_CANID;
}

#else

uint32_t Pack_SHIFT_CMD_pacmod13(SHIFT_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SHIFT_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->SHIFT_CMD & (0xFFU));

  *_len = SHIFT_CMD_DLC;
  *_ide = SHIFT_CMD_IDE;
  return SHIFT_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_CMD_pacmod13(STEERING_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->POSITION_ro = __ext_sig__(( ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->POSITION_phys = (sigfloat_t)(PACMOD13_POSITION_ro_fromS(_m->POSITION_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->ROTATION_RATE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROTATION_RATE_phys = (sigfloat_t)(PACMOD13_ROTATION_RATE_ro_fromS(_m->ROTATION_RATE_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_CMD_pacmod13(&_m->mon1, STEERING_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_CMD_pacmod13(STEERING_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->POSITION_ro = PACMOD13_POSITION_ro_toS(_m->POSITION_phys);
  _m->ROTATION_RATE_ro = PACMOD13_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= ((_m->POSITION_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->POSITION_ro & (0xFFU));
  cframe->Data[3] |= ((_m->ROTATION_RATE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->ROTATION_RATE_ro & (0xFFU));

  cframe->MsgId = STEERING_CMD_CANID;
  cframe->DLC = STEERING_CMD_DLC;
  cframe->IDE = STEERING_CMD_IDE;
  return STEERING_CMD_CANID;
}

#else

uint32_t Pack_STEERING_CMD_pacmod13(STEERING_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->POSITION_ro = PACMOD13_POSITION_ro_toS(_m->POSITION_phys);
  _m->ROTATION_RATE_ro = PACMOD13_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= ((_m->POSITION_ro >> 8) & (0xFFU));
  _d[2] |= (_m->POSITION_ro & (0xFFU));
  _d[3] |= ((_m->ROTATION_RATE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->ROTATION_RATE_ro & (0xFFU));

  *_len = STEERING_CMD_DLC;
  *_ide = STEERING_CMD_IDE;
  return STEERING_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TURN_CMD_pacmod13(TURN_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->TURN_SIGNAL_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TURN_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TURN_CMD_pacmod13(&_m->mon1, TURN_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TURN_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TURN_CMD_pacmod13(TURN_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TURN_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->TURN_SIGNAL_CMD & (0xFFU));

  cframe->MsgId = TURN_CMD_CANID;
  cframe->DLC = TURN_CMD_DLC;
  cframe->IDE = TURN_CMD_IDE;
  return TURN_CMD_CANID;
}

#else

uint32_t Pack_TURN_CMD_pacmod13(TURN_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TURN_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->TURN_SIGNAL_CMD & (0xFFU));

  *_len = TURN_CMD_DLC;
  *_ide = TURN_CMD_IDE;
  return TURN_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_WIPER_CMD_pacmod13(WIPER_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->WIPER_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WIPER_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WIPER_CMD_pacmod13(&_m->mon1, WIPER_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return WIPER_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_WIPER_CMD_pacmod13(WIPER_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < WIPER_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->WIPER_CMD & (0xFFU));

  cframe->MsgId = WIPER_CMD_CANID;
  cframe->DLC = WIPER_CMD_DLC;
  cframe->IDE = WIPER_CMD_IDE;
  return WIPER_CMD_CANID;
}

#else

uint32_t Pack_WIPER_CMD_pacmod13(WIPER_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WIPER_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->WIPER_CMD & (0xFFU));

  *_len = WIPER_CMD_DLC;
  *_ide = WIPER_CMD_IDE;
  return WIPER_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SPRAYER_CMD_pacmod13(SPRAYER_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->SPRAYER_CMD = (_d[1] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SPRAYER_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SPRAYER_CMD_pacmod13(&_m->mon1, SPRAYER_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SPRAYER_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SPRAYER_CMD_pacmod13(SPRAYER_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SPRAYER_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->SPRAYER_CMD & (0x01U));

  cframe->MsgId = SPRAYER_CMD_CANID;
  cframe->DLC = SPRAYER_CMD_DLC;
  cframe->IDE = SPRAYER_CMD_IDE;
  return SPRAYER_CMD_CANID;
}

#else

uint32_t Pack_SPRAYER_CMD_pacmod13(SPRAYER_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SPRAYER_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->SPRAYER_CMD & (0x01U));

  *_len = SPRAYER_CMD_DLC;
  *_ide = SPRAYER_CMD_IDE;
  return SPRAYER_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_DECEL_CMD_pacmod13(BRAKE_DECEL_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->BRAKE_DECEL_CMD_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_DECEL_CMD_phys = (sigfloat_t)(PACMOD13_BRAKE_DECEL_CMD_ro_fromS(_m->BRAKE_DECEL_CMD_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->XBR_EBI_MODE = (_d[3] & (0x03U));
  _m->XBR_PRIORITY = ((_d[3] >> 2) & (0x03U));
  _m->XBR_CONTROL_MODE = ((_d[3] >> 4) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_DECEL_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_DECEL_CMD_pacmod13(&_m->mon1, BRAKE_DECEL_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_DECEL_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_DECEL_CMD_pacmod13(BRAKE_DECEL_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECEL_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_DECEL_CMD_ro = PACMOD13_BRAKE_DECEL_CMD_ro_toS(_m->BRAKE_DECEL_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= ((_m->BRAKE_DECEL_CMD_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_DECEL_CMD_ro & (0xFFU));
  cframe->Data[3] |= (_m->XBR_EBI_MODE & (0x03U)) | ((_m->XBR_PRIORITY & (0x03U)) << 2) | ((_m->XBR_CONTROL_MODE & (0x03U)) << 4);

  cframe->MsgId = BRAKE_DECEL_CMD_CANID;
  cframe->DLC = BRAKE_DECEL_CMD_DLC;
  cframe->IDE = BRAKE_DECEL_CMD_IDE;
  return BRAKE_DECEL_CMD_CANID;
}

#else

uint32_t Pack_BRAKE_DECEL_CMD_pacmod13(BRAKE_DECEL_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECEL_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_DECEL_CMD_ro = PACMOD13_BRAKE_DECEL_CMD_ro_toS(_m->BRAKE_DECEL_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= ((_m->BRAKE_DECEL_CMD_ro >> 8) & (0xFFU));
  _d[2] |= (_m->BRAKE_DECEL_CMD_ro & (0xFFU));
  _d[3] |= (_m->XBR_EBI_MODE & (0x03U)) | ((_m->XBR_PRIORITY & (0x03U)) << 2) | ((_m->XBR_CONTROL_MODE & (0x03U)) << 4);

  *_len = BRAKE_DECEL_CMD_DLC;
  *_ide = BRAKE_DECEL_CMD_IDE;
  return BRAKE_DECEL_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_REAR_PASS_DOOR_CMD_pacmod13(REAR_PASS_DOOR_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->REAR_PASS_DOOR_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < REAR_PASS_DOOR_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_REAR_PASS_DOOR_CMD_pacmod13(&_m->mon1, REAR_PASS_DOOR_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return REAR_PASS_DOOR_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_REAR_PASS_DOOR_CMD_pacmod13(REAR_PASS_DOOR_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < REAR_PASS_DOOR_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->REAR_PASS_DOOR_CMD & (0xFFU));

  cframe->MsgId = REAR_PASS_DOOR_CMD_CANID;
  cframe->DLC = REAR_PASS_DOOR_CMD_DLC;
  cframe->IDE = REAR_PASS_DOOR_CMD_IDE;
  return REAR_PASS_DOOR_CMD_CANID;
}

#else

uint32_t Pack_REAR_PASS_DOOR_CMD_pacmod13(REAR_PASS_DOOR_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < REAR_PASS_DOOR_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->REAR_PASS_DOOR_CMD & (0xFFU));

  *_len = REAR_PASS_DOOR_CMD_DLC;
  *_ide = REAR_PASS_DOOR_CMD_IDE;
  return REAR_PASS_DOOR_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ENGINE_BRAKE_CMD_pacmod13(ENGINE_BRAKE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->ENGINE_BRAKE_CMD = (_d[1] & (0xFFU));
  _m->AUTO_CMD = (_d[2] & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ENGINE_BRAKE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ENGINE_BRAKE_CMD_pacmod13(&_m->mon1, ENGINE_BRAKE_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ENGINE_BRAKE_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ENGINE_BRAKE_CMD_pacmod13(ENGINE_BRAKE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ENGINE_BRAKE_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->ENGINE_BRAKE_CMD & (0xFFU));
  cframe->Data[2] |= (_m->AUTO_CMD & (0x03U));

  cframe->MsgId = ENGINE_BRAKE_CMD_CANID;
  cframe->DLC = ENGINE_BRAKE_CMD_DLC;
  cframe->IDE = ENGINE_BRAKE_CMD_IDE;
  return ENGINE_BRAKE_CMD_CANID;
}

#else

uint32_t Pack_ENGINE_BRAKE_CMD_pacmod13(ENGINE_BRAKE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ENGINE_BRAKE_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->ENGINE_BRAKE_CMD & (0xFFU));
  _d[2] |= (_m->AUTO_CMD & (0x03U));

  *_len = ENGINE_BRAKE_CMD_DLC;
  *_ide = ENGINE_BRAKE_CMD_IDE;
  return ENGINE_BRAKE_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_EXHAUST_BRAKE_CMD_pacmod13(EXHAUST_BRAKE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->EXHAUST_BRAKE_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EXHAUST_BRAKE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EXHAUST_BRAKE_CMD_pacmod13(&_m->mon1, EXHAUST_BRAKE_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return EXHAUST_BRAKE_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_EXHAUST_BRAKE_CMD_pacmod13(EXHAUST_BRAKE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < EXHAUST_BRAKE_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->EXHAUST_BRAKE_CMD & (0xFFU));

  cframe->MsgId = EXHAUST_BRAKE_CMD_CANID;
  cframe->DLC = EXHAUST_BRAKE_CMD_DLC;
  cframe->IDE = EXHAUST_BRAKE_CMD_IDE;
  return EXHAUST_BRAKE_CMD_CANID;
}

#else

uint32_t Pack_EXHAUST_BRAKE_CMD_pacmod13(EXHAUST_BRAKE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < EXHAUST_BRAKE_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->EXHAUST_BRAKE_CMD & (0xFFU));

  *_len = EXHAUST_BRAKE_CMD_DLC;
  *_ide = EXHAUST_BRAKE_CMD_IDE;
  return EXHAUST_BRAKE_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_MARKER_LAMP_CMD_pacmod13(MARKER_LAMP_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->MARKER_LAMP_CMD = (_d[1] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < MARKER_LAMP_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_MARKER_LAMP_CMD_pacmod13(&_m->mon1, MARKER_LAMP_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return MARKER_LAMP_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_MARKER_LAMP_CMD_pacmod13(MARKER_LAMP_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < MARKER_LAMP_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->MARKER_LAMP_CMD & (0x01U));

  cframe->MsgId = MARKER_LAMP_CMD_CANID;
  cframe->DLC = MARKER_LAMP_CMD_DLC;
  cframe->IDE = MARKER_LAMP_CMD_IDE;
  return MARKER_LAMP_CMD_CANID;
}

#else

uint32_t Pack_MARKER_LAMP_CMD_pacmod13(MARKER_LAMP_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < MARKER_LAMP_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->MARKER_LAMP_CMD & (0x01U));

  *_len = MARKER_LAMP_CMD_DLC;
  *_ide = MARKER_LAMP_CMD_IDE;
  return MARKER_LAMP_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_CABIN_TEMP_CMD_pacmod13(CABIN_TEMP_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->CABIN_TEMP_CMD_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->CABIN_TEMP_CMD_phys = (sigfloat_t)(PACMOD13_CABIN_TEMP_CMD_ro_fromS(_m->CABIN_TEMP_CMD_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CABIN_TEMP_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CABIN_TEMP_CMD_pacmod13(&_m->mon1, CABIN_TEMP_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return CABIN_TEMP_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_CABIN_TEMP_CMD_pacmod13(CABIN_TEMP_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < CABIN_TEMP_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->CABIN_TEMP_CMD_ro = PACMOD13_CABIN_TEMP_CMD_ro_toS(_m->CABIN_TEMP_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->CABIN_TEMP_CMD_ro & (0xFFU));

  cframe->MsgId = CABIN_TEMP_CMD_CANID;
  cframe->DLC = CABIN_TEMP_CMD_DLC;
  cframe->IDE = CABIN_TEMP_CMD_IDE;
  return CABIN_TEMP_CMD_CANID;
}

#else

uint32_t Pack_CABIN_TEMP_CMD_pacmod13(CABIN_TEMP_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < CABIN_TEMP_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->CABIN_TEMP_CMD_ro = PACMOD13_CABIN_TEMP_CMD_ro_toS(_m->CABIN_TEMP_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->CABIN_TEMP_CMD_ro & (0xFFU));

  *_len = CABIN_TEMP_CMD_DLC;
  *_ide = CABIN_TEMP_CMD_IDE;
  return CABIN_TEMP_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_CABIN_FAN_SPEED_CMD_pacmod13(CABIN_FAN_SPEED_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->CABIN_FAN_SPEED_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CABIN_FAN_SPEED_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CABIN_FAN_SPEED_CMD_pacmod13(&_m->mon1, CABIN_FAN_SPEED_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return CABIN_FAN_SPEED_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_CABIN_FAN_SPEED_CMD_pacmod13(CABIN_FAN_SPEED_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < CABIN_FAN_SPEED_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->CABIN_FAN_SPEED_CMD & (0xFFU));

  cframe->MsgId = CABIN_FAN_SPEED_CMD_CANID;
  cframe->DLC = CABIN_FAN_SPEED_CMD_DLC;
  cframe->IDE = CABIN_FAN_SPEED_CMD_IDE;
  return CABIN_FAN_SPEED_CMD_CANID;
}

#else

uint32_t Pack_CABIN_FAN_SPEED_CMD_pacmod13(CABIN_FAN_SPEED_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < CABIN_FAN_SPEED_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->CABIN_FAN_SPEED_CMD & (0xFFU));

  *_len = CABIN_FAN_SPEED_CMD_DLC;
  *_ide = CABIN_FAN_SPEED_CMD_IDE;
  return CABIN_FAN_SPEED_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_CABIN_CLIMATE_CMD_pacmod13(CABIN_CLIMATE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->CMD_AC_OFF_ON = (_d[1] & (0x03U));
  _m->CMD_MAX_AC_OFF_ON = ((_d[1] >> 2) & (0x03U));
  _m->CMD_DEFROST_OFF_ON = ((_d[1] >> 4) & (0x03U));
  _m->CMD_MAX_DEFROST_OFF_ON = ((_d[1] >> 6) & (0x03U));
  _m->CMD_DIR_UP_OFF_ON = (_d[2] & (0x03U));
  _m->CMD_DIR_DOWN_OFF_ON = ((_d[2] >> 2) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CABIN_CLIMATE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CABIN_CLIMATE_CMD_pacmod13(&_m->mon1, CABIN_CLIMATE_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return CABIN_CLIMATE_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_CABIN_CLIMATE_CMD_pacmod13(CABIN_CLIMATE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < CABIN_CLIMATE_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->CMD_AC_OFF_ON & (0x03U)) | ((_m->CMD_MAX_AC_OFF_ON & (0x03U)) << 2) | ((_m->CMD_DEFROST_OFF_ON & (0x03U)) << 4) | ((_m->CMD_MAX_DEFROST_OFF_ON & (0x03U)) << 6);
  cframe->Data[2] |= (_m->CMD_DIR_UP_OFF_ON & (0x03U)) | ((_m->CMD_DIR_DOWN_OFF_ON & (0x03U)) << 2);

  cframe->MsgId = CABIN_CLIMATE_CMD_CANID;
  cframe->DLC = CABIN_CLIMATE_CMD_DLC;
  cframe->IDE = CABIN_CLIMATE_CMD_IDE;
  return CABIN_CLIMATE_CMD_CANID;
}

#else

uint32_t Pack_CABIN_CLIMATE_CMD_pacmod13(CABIN_CLIMATE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < CABIN_CLIMATE_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->CMD_AC_OFF_ON & (0x03U)) | ((_m->CMD_MAX_AC_OFF_ON & (0x03U)) << 2) | ((_m->CMD_DEFROST_OFF_ON & (0x03U)) << 4) | ((_m->CMD_MAX_DEFROST_OFF_ON & (0x03U)) << 6);
  _d[2] |= (_m->CMD_DIR_UP_OFF_ON & (0x03U)) | ((_m->CMD_DIR_DOWN_OFF_ON & (0x03U)) << 2);

  *_len = CABIN_CLIMATE_CMD_DLC;
  *_ide = CABIN_CLIMATE_CMD_IDE;
  return CABIN_CLIMATE_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIPPER_BODY_CMD_00_pacmod13(TIPPER_BODY_CMD_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->TIPPER_CONTROL_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIPPER_BODY_CMD_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIPPER_BODY_CMD_00_pacmod13(&_m->mon1, TIPPER_BODY_CMD_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIPPER_BODY_CMD_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIPPER_BODY_CMD_00_pacmod13(TIPPER_BODY_CMD_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_CMD_00_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->TIPPER_CONTROL_CMD & (0xFFU));

  cframe->MsgId = TIPPER_BODY_CMD_00_CANID;
  cframe->DLC = TIPPER_BODY_CMD_00_DLC;
  cframe->IDE = TIPPER_BODY_CMD_00_IDE;
  return TIPPER_BODY_CMD_00_CANID;
}

#else

uint32_t Pack_TIPPER_BODY_CMD_00_pacmod13(TIPPER_BODY_CMD_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_CMD_00_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->TIPPER_CONTROL_CMD & (0xFFU));

  *_len = TIPPER_BODY_CMD_00_DLC;
  *_ide = TIPPER_BODY_CMD_00_IDE;
  return TIPPER_BODY_CMD_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_POWER_TAKE_OFF_CMD_pacmod13(POWER_TAKE_OFF_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->POWER_TAKE_OFF_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < POWER_TAKE_OFF_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_POWER_TAKE_OFF_CMD_pacmod13(&_m->mon1, POWER_TAKE_OFF_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return POWER_TAKE_OFF_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_POWER_TAKE_OFF_CMD_pacmod13(POWER_TAKE_OFF_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < POWER_TAKE_OFF_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->POWER_TAKE_OFF_CMD & (0xFFU));

  cframe->MsgId = POWER_TAKE_OFF_CMD_CANID;
  cframe->DLC = POWER_TAKE_OFF_CMD_DLC;
  cframe->IDE = POWER_TAKE_OFF_CMD_IDE;
  return POWER_TAKE_OFF_CMD_CANID;
}

#else

uint32_t Pack_POWER_TAKE_OFF_CMD_pacmod13(POWER_TAKE_OFF_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < POWER_TAKE_OFF_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->POWER_TAKE_OFF_CMD & (0xFFU));

  *_len = POWER_TAKE_OFF_CMD_DLC;
  *_ide = POWER_TAKE_OFF_CMD_IDE;
  return POWER_TAKE_OFF_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_BRAKE_CMD_pacmod13(TRAILER_BRAKE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->TRAILER_BRAKE_CMD_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TRAILER_BRAKE_CMD_phys = (sigfloat_t)(PACMOD13_TRAILER_BRAKE_CMD_ro_fromS(_m->TRAILER_BRAKE_CMD_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_BRAKE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_BRAKE_CMD_pacmod13(&_m->mon1, TRAILER_BRAKE_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_BRAKE_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_BRAKE_CMD_pacmod13(TRAILER_BRAKE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TRAILER_BRAKE_CMD_ro = PACMOD13_TRAILER_BRAKE_CMD_ro_toS(_m->TRAILER_BRAKE_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= ((_m->TRAILER_BRAKE_CMD_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->TRAILER_BRAKE_CMD_ro & (0xFFU));

  cframe->MsgId = TRAILER_BRAKE_CMD_CANID;
  cframe->DLC = TRAILER_BRAKE_CMD_DLC;
  cframe->IDE = TRAILER_BRAKE_CMD_IDE;
  return TRAILER_BRAKE_CMD_CANID;
}

#else

uint32_t Pack_TRAILER_BRAKE_CMD_pacmod13(TRAILER_BRAKE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TRAILER_BRAKE_CMD_ro = PACMOD13_TRAILER_BRAKE_CMD_ro_toS(_m->TRAILER_BRAKE_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= ((_m->TRAILER_BRAKE_CMD_ro >> 8) & (0xFFU));
  _d[2] |= (_m->TRAILER_BRAKE_CMD_ro & (0xFFU));

  *_len = TRAILER_BRAKE_CMD_DLC;
  *_ide = TRAILER_BRAKE_CMD_IDE;
  return TRAILER_BRAKE_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_AIR_SUPPLY_CMD_pacmod13(TRAILER_AIR_SUPPLY_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->TRAILER_AIR_SUPPLY_CMD = (_d[1] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_AIR_SUPPLY_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_AIR_SUPPLY_CMD_pacmod13(&_m->mon1, TRAILER_AIR_SUPPLY_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_AIR_SUPPLY_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_AIR_SUPPLY_CMD_pacmod13(TRAILER_AIR_SUPPLY_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_AIR_SUPPLY_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->TRAILER_AIR_SUPPLY_CMD & (0x01U));

  cframe->MsgId = TRAILER_AIR_SUPPLY_CMD_CANID;
  cframe->DLC = TRAILER_AIR_SUPPLY_CMD_DLC;
  cframe->IDE = TRAILER_AIR_SUPPLY_CMD_IDE;
  return TRAILER_AIR_SUPPLY_CMD_CANID;
}

#else

uint32_t Pack_TRAILER_AIR_SUPPLY_CMD_pacmod13(TRAILER_AIR_SUPPLY_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_AIR_SUPPLY_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->TRAILER_AIR_SUPPLY_CMD & (0x01U));

  *_len = TRAILER_AIR_SUPPLY_CMD_DLC;
  *_ide = TRAILER_AIR_SUPPLY_CMD_IDE;
  return TRAILER_AIR_SUPPLY_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ENGINE_CMD_pacmod13(ENGINE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->ENGINE_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ENGINE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ENGINE_CMD_pacmod13(&_m->mon1, ENGINE_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ENGINE_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ENGINE_CMD_pacmod13(ENGINE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ENGINE_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->ENGINE_CMD & (0xFFU));

  cframe->MsgId = ENGINE_CMD_CANID;
  cframe->DLC = ENGINE_CMD_DLC;
  cframe->IDE = ENGINE_CMD_IDE;
  return ENGINE_CMD_CANID;
}

#else

uint32_t Pack_ENGINE_CMD_pacmod13(ENGINE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ENGINE_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->ENGINE_CMD & (0xFFU));

  *_len = ENGINE_CMD_DLC;
  *_ide = ENGINE_CMD_IDE;
  return ENGINE_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIPPER_BODY_CMD_01_pacmod13(TIPPER_BODY_CMD_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->TIPPER_CONTROL_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIPPER_BODY_CMD_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIPPER_BODY_CMD_01_pacmod13(&_m->mon1, TIPPER_BODY_CMD_01_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIPPER_BODY_CMD_01_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIPPER_BODY_CMD_01_pacmod13(TIPPER_BODY_CMD_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_CMD_01_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->TIPPER_CONTROL_CMD & (0xFFU));

  cframe->MsgId = TIPPER_BODY_CMD_01_CANID;
  cframe->DLC = TIPPER_BODY_CMD_01_DLC;
  cframe->IDE = TIPPER_BODY_CMD_01_IDE;
  return TIPPER_BODY_CMD_01_CANID;
}

#else

uint32_t Pack_TIPPER_BODY_CMD_01_pacmod13(TIPPER_BODY_CMD_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_CMD_01_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->TIPPER_CONTROL_CMD & (0xFFU));

  *_len = TIPPER_BODY_CMD_01_DLC;
  *_ide = TIPPER_BODY_CMD_01_IDE;
  return TIPPER_BODY_CMD_01_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIPPER_BODY_CMD_02_pacmod13(TIPPER_BODY_CMD_02_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->TIPPER_CONTROL_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIPPER_BODY_CMD_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIPPER_BODY_CMD_02_pacmod13(&_m->mon1, TIPPER_BODY_CMD_02_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIPPER_BODY_CMD_02_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIPPER_BODY_CMD_02_pacmod13(TIPPER_BODY_CMD_02_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_CMD_02_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->TIPPER_CONTROL_CMD & (0xFFU));

  cframe->MsgId = TIPPER_BODY_CMD_02_CANID;
  cframe->DLC = TIPPER_BODY_CMD_02_DLC;
  cframe->IDE = TIPPER_BODY_CMD_02_IDE;
  return TIPPER_BODY_CMD_02_CANID;
}

#else

uint32_t Pack_TIPPER_BODY_CMD_02_pacmod13(TIPPER_BODY_CMD_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_CMD_02_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->TIPPER_CONTROL_CMD & (0xFFU));

  *_len = TIPPER_BODY_CMD_02_DLC;
  *_ide = TIPPER_BODY_CMD_02_IDE;
  return TIPPER_BODY_CMD_02_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DIFFERENTIAL_LOCKS_CMD_pacmod13(DIFFERENTIAL_LOCKS_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->FRONT_LOCK_CMD = (_d[1] & (0x03U));
  _m->CENTER_LOCK_CMD = ((_d[1] >> 2) & (0x03U));
  _m->REAR_LOCK_CMD = ((_d[1] >> 4) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DIFFERENTIAL_LOCKS_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DIFFERENTIAL_LOCKS_CMD_pacmod13(&_m->mon1, DIFFERENTIAL_LOCKS_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DIFFERENTIAL_LOCKS_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DIFFERENTIAL_LOCKS_CMD_pacmod13(DIFFERENTIAL_LOCKS_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DIFFERENTIAL_LOCKS_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= (_m->FRONT_LOCK_CMD & (0x03U)) | ((_m->CENTER_LOCK_CMD & (0x03U)) << 2) | ((_m->REAR_LOCK_CMD & (0x03U)) << 4);

  cframe->MsgId = DIFFERENTIAL_LOCKS_CMD_CANID;
  cframe->DLC = DIFFERENTIAL_LOCKS_CMD_DLC;
  cframe->IDE = DIFFERENTIAL_LOCKS_CMD_IDE;
  return DIFFERENTIAL_LOCKS_CMD_CANID;
}

#else

uint32_t Pack_DIFFERENTIAL_LOCKS_CMD_pacmod13(DIFFERENTIAL_LOCKS_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DIFFERENTIAL_LOCKS_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->FRONT_LOCK_CMD & (0x03U)) | ((_m->CENTER_LOCK_CMD & (0x03U)) << 2) | ((_m->REAR_LOCK_CMD & (0x03U)) << 4);

  *_len = DIFFERENTIAL_LOCKS_CMD_DLC;
  *_ide = DIFFERENTIAL_LOCKS_CMD_IDE;
  return DIFFERENTIAL_LOCKS_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ACCEL_RPT_pacmod13(ACCEL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD13_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD13_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD13_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->CONTROL_STATUS = (_d[7] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[7] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[7] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ACCEL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ACCEL_RPT_pacmod13(&_m->mon1, ACCEL_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ACCEL_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ACCEL_RPT_pacmod13(ACCEL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ACCEL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  cframe->Data[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = ACCEL_RPT_CANID;
  cframe->DLC = ACCEL_RPT_DLC;
  cframe->IDE = ACCEL_RPT_IDE;
  return ACCEL_RPT_CANID;
}

#else

uint32_t Pack_ACCEL_RPT_pacmod13(ACCEL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ACCEL_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  _d[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = ACCEL_RPT_DLC;
  *_ide = ACCEL_RPT_IDE;
  return ACCEL_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ACCEL_CMD_LIMIT_RPT_pacmod13(ACCEL_CMD_LIMIT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ACCEL_CMD_LIMIT_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACCEL_CMD_LIMIT_phys = (sigfloat_t)(PACMOD13_ACCEL_CMD_LIMIT_ro_fromS(_m->ACCEL_CMD_LIMIT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->LIMITED_ACCEL_CMD_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->LIMITED_ACCEL_CMD_phys = (sigfloat_t)(PACMOD13_LIMITED_ACCEL_CMD_ro_fromS(_m->LIMITED_ACCEL_CMD_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ACCEL_CMD_LIMIT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ACCEL_CMD_LIMIT_RPT_pacmod13(&_m->mon1, ACCEL_CMD_LIMIT_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ACCEL_CMD_LIMIT_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ACCEL_CMD_LIMIT_RPT_pacmod13(ACCEL_CMD_LIMIT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ACCEL_CMD_LIMIT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACCEL_CMD_LIMIT_ro = PACMOD13_ACCEL_CMD_LIMIT_ro_toS(_m->ACCEL_CMD_LIMIT_phys);
  _m->LIMITED_ACCEL_CMD_ro = PACMOD13_LIMITED_ACCEL_CMD_ro_toS(_m->LIMITED_ACCEL_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->ACCEL_CMD_LIMIT_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->ACCEL_CMD_LIMIT_ro & (0xFFU));
  cframe->Data[2] |= ((_m->LIMITED_ACCEL_CMD_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->LIMITED_ACCEL_CMD_ro & (0xFFU));

  cframe->MsgId = ACCEL_CMD_LIMIT_RPT_CANID;
  cframe->DLC = ACCEL_CMD_LIMIT_RPT_DLC;
  cframe->IDE = ACCEL_CMD_LIMIT_RPT_IDE;
  return ACCEL_CMD_LIMIT_RPT_CANID;
}

#else

uint32_t Pack_ACCEL_CMD_LIMIT_RPT_pacmod13(ACCEL_CMD_LIMIT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ACCEL_CMD_LIMIT_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACCEL_CMD_LIMIT_ro = PACMOD13_ACCEL_CMD_LIMIT_ro_toS(_m->ACCEL_CMD_LIMIT_phys);
  _m->LIMITED_ACCEL_CMD_ro = PACMOD13_LIMITED_ACCEL_CMD_ro_toS(_m->LIMITED_ACCEL_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->ACCEL_CMD_LIMIT_ro >> 8) & (0xFFU));
  _d[1] |= (_m->ACCEL_CMD_LIMIT_ro & (0xFFU));
  _d[2] |= ((_m->LIMITED_ACCEL_CMD_ro >> 8) & (0xFFU));
  _d[3] |= (_m->LIMITED_ACCEL_CMD_ro & (0xFFU));

  *_len = ACCEL_CMD_LIMIT_RPT_DLC;
  *_ide = ACCEL_CMD_LIMIT_RPT_IDE;
  return ACCEL_CMD_LIMIT_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_RPT_pacmod13(BRAKE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD13_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD13_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD13_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->CONTROL_STATUS = (_d[7] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[7] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[7] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_RPT_pacmod13(&_m->mon1, BRAKE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_RPT_pacmod13(BRAKE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  cframe->Data[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = BRAKE_RPT_CANID;
  cframe->DLC = BRAKE_RPT_DLC;
  cframe->IDE = BRAKE_RPT_IDE;
  return BRAKE_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_RPT_pacmod13(BRAKE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  _d[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = BRAKE_RPT_DLC;
  *_ide = BRAKE_RPT_IDE;
  return BRAKE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_CMD_LIMIT_RPT_pacmod13(BRAKE_CMD_LIMIT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_CMD_LIMIT_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_CMD_LIMIT_phys = (sigfloat_t)(PACMOD13_BRAKE_CMD_LIMIT_ro_fromS(_m->BRAKE_CMD_LIMIT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->LIMITED_BRAKE_CMD_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->LIMITED_BRAKE_CMD_phys = (sigfloat_t)(PACMOD13_LIMITED_BRAKE_CMD_ro_fromS(_m->LIMITED_BRAKE_CMD_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_CMD_LIMIT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_CMD_LIMIT_RPT_pacmod13(&_m->mon1, BRAKE_CMD_LIMIT_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_CMD_LIMIT_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_CMD_LIMIT_RPT_pacmod13(BRAKE_CMD_LIMIT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_CMD_LIMIT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_CMD_LIMIT_ro = PACMOD13_BRAKE_CMD_LIMIT_ro_toS(_m->BRAKE_CMD_LIMIT_phys);
  _m->LIMITED_BRAKE_CMD_ro = PACMOD13_LIMITED_BRAKE_CMD_ro_toS(_m->LIMITED_BRAKE_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->BRAKE_CMD_LIMIT_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->BRAKE_CMD_LIMIT_ro & (0xFFU));
  cframe->Data[2] |= ((_m->LIMITED_BRAKE_CMD_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->LIMITED_BRAKE_CMD_ro & (0xFFU));

  cframe->MsgId = BRAKE_CMD_LIMIT_RPT_CANID;
  cframe->DLC = BRAKE_CMD_LIMIT_RPT_DLC;
  cframe->IDE = BRAKE_CMD_LIMIT_RPT_IDE;
  return BRAKE_CMD_LIMIT_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_CMD_LIMIT_RPT_pacmod13(BRAKE_CMD_LIMIT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_CMD_LIMIT_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_CMD_LIMIT_ro = PACMOD13_BRAKE_CMD_LIMIT_ro_toS(_m->BRAKE_CMD_LIMIT_phys);
  _m->LIMITED_BRAKE_CMD_ro = PACMOD13_LIMITED_BRAKE_CMD_ro_toS(_m->LIMITED_BRAKE_CMD_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->BRAKE_CMD_LIMIT_ro >> 8) & (0xFFU));
  _d[1] |= (_m->BRAKE_CMD_LIMIT_ro & (0xFFU));
  _d[2] |= ((_m->LIMITED_BRAKE_CMD_ro >> 8) & (0xFFU));
  _d[3] |= (_m->LIMITED_BRAKE_CMD_ro & (0xFFU));

  *_len = BRAKE_CMD_LIMIT_RPT_DLC;
  *_ide = BRAKE_CMD_LIMIT_RPT_IDE;
  return BRAKE_CMD_LIMIT_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_RPT_2_pacmod13(BRAKE_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD13_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD13_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD13_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->CONTROL_STATUS = (_d[7] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[7] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[7] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_RPT_2_pacmod13(&_m->mon1, BRAKE_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_RPT_2_pacmod13(BRAKE_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  cframe->Data[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = BRAKE_RPT_2_CANID;
  cframe->DLC = BRAKE_RPT_2_DLC;
  cframe->IDE = BRAKE_RPT_2_IDE;
  return BRAKE_RPT_2_CANID;
}

#else

uint32_t Pack_BRAKE_RPT_2_pacmod13(BRAKE_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  _d[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = BRAKE_RPT_2_DLC;
  *_ide = BRAKE_RPT_2_IDE;
  return BRAKE_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_CRUISE_CONTROL_BUTTONS_RPT_pacmod13(CRUISE_CONTROL_BUTTONS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CRUISE_CONTROL_BUTTONS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CRUISE_CONTROL_BUTTONS_RPT_pacmod13(&_m->mon1, CRUISE_CONTROL_BUTTONS_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return CRUISE_CONTROL_BUTTONS_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_CRUISE_CONTROL_BUTTONS_RPT_pacmod13(CRUISE_CONTROL_BUTTONS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < CRUISE_CONTROL_BUTTONS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = CRUISE_CONTROL_BUTTONS_RPT_CANID;
  cframe->DLC = CRUISE_CONTROL_BUTTONS_RPT_DLC;
  cframe->IDE = CRUISE_CONTROL_BUTTONS_RPT_IDE;
  return CRUISE_CONTROL_BUTTONS_RPT_CANID;
}

#else

uint32_t Pack_CRUISE_CONTROL_BUTTONS_RPT_pacmod13(CRUISE_CONTROL_BUTTONS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < CRUISE_CONTROL_BUTTONS_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = CRUISE_CONTROL_BUTTONS_RPT_DLC;
  *_ide = CRUISE_CONTROL_BUTTONS_RPT_IDE;
  return CRUISE_CONTROL_BUTTONS_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DASH_CONTROLS_LEFT_RPT_pacmod13(DASH_CONTROLS_LEFT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DASH_CONTROLS_LEFT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DASH_CONTROLS_LEFT_RPT_pacmod13(&_m->mon1, DASH_CONTROLS_LEFT_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DASH_CONTROLS_LEFT_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DASH_CONTROLS_LEFT_RPT_pacmod13(DASH_CONTROLS_LEFT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_LEFT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = DASH_CONTROLS_LEFT_RPT_CANID;
  cframe->DLC = DASH_CONTROLS_LEFT_RPT_DLC;
  cframe->IDE = DASH_CONTROLS_LEFT_RPT_IDE;
  return DASH_CONTROLS_LEFT_RPT_CANID;
}

#else

uint32_t Pack_DASH_CONTROLS_LEFT_RPT_pacmod13(DASH_CONTROLS_LEFT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_LEFT_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = DASH_CONTROLS_LEFT_RPT_DLC;
  *_ide = DASH_CONTROLS_LEFT_RPT_IDE;
  return DASH_CONTROLS_LEFT_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DASH_CONTROLS_RIGHT_RPT_pacmod13(DASH_CONTROLS_RIGHT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DASH_CONTROLS_RIGHT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DASH_CONTROLS_RIGHT_RPT_pacmod13(&_m->mon1, DASH_CONTROLS_RIGHT_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DASH_CONTROLS_RIGHT_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DASH_CONTROLS_RIGHT_RPT_pacmod13(DASH_CONTROLS_RIGHT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_RIGHT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = DASH_CONTROLS_RIGHT_RPT_CANID;
  cframe->DLC = DASH_CONTROLS_RIGHT_RPT_DLC;
  cframe->IDE = DASH_CONTROLS_RIGHT_RPT_IDE;
  return DASH_CONTROLS_RIGHT_RPT_CANID;
}

#else

uint32_t Pack_DASH_CONTROLS_RIGHT_RPT_pacmod13(DASH_CONTROLS_RIGHT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_RIGHT_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = DASH_CONTROLS_RIGHT_RPT_DLC;
  *_ide = DASH_CONTROLS_RIGHT_RPT_IDE;
  return DASH_CONTROLS_RIGHT_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_HAZARD_LIGHTS_RPT_pacmod13(HAZARD_LIGHTS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0x01U));
  _m->COMMANDED_VALUE = (_d[2] & (0x01U));
  _m->OUTPUT_VALUE = (_d[3] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HAZARD_LIGHTS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HAZARD_LIGHTS_RPT_pacmod13(&_m->mon1, HAZARD_LIGHTS_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return HAZARD_LIGHTS_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_HAZARD_LIGHTS_RPT_pacmod13(HAZARD_LIGHTS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < HAZARD_LIGHTS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0x01U));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0x01U));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0x01U));

  cframe->MsgId = HAZARD_LIGHTS_RPT_CANID;
  cframe->DLC = HAZARD_LIGHTS_RPT_DLC;
  cframe->IDE = HAZARD_LIGHTS_RPT_IDE;
  return HAZARD_LIGHTS_RPT_CANID;
}

#else

uint32_t Pack_HAZARD_LIGHTS_RPT_pacmod13(HAZARD_LIGHTS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HAZARD_LIGHTS_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0x01U));
  _d[2] |= (_m->COMMANDED_VALUE & (0x01U));
  _d[3] |= (_m->OUTPUT_VALUE & (0x01U));

  *_len = HAZARD_LIGHTS_RPT_DLC;
  *_ide = HAZARD_LIGHTS_RPT_IDE;
  return HAZARD_LIGHTS_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_HEADLIGHT_RPT_pacmod13(HEADLIGHT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HEADLIGHT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HEADLIGHT_RPT_pacmod13(&_m->mon1, HEADLIGHT_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return HEADLIGHT_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_HEADLIGHT_RPT_pacmod13(HEADLIGHT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < HEADLIGHT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = HEADLIGHT_RPT_CANID;
  cframe->DLC = HEADLIGHT_RPT_DLC;
  cframe->IDE = HEADLIGHT_RPT_IDE;
  return HEADLIGHT_RPT_CANID;
}

#else

uint32_t Pack_HEADLIGHT_RPT_pacmod13(HEADLIGHT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HEADLIGHT_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = HEADLIGHT_RPT_DLC;
  *_ide = HEADLIGHT_RPT_IDE;
  return HEADLIGHT_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_HORN_RPT_pacmod13(HORN_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HORN_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HORN_RPT_pacmod13(&_m->mon1, HORN_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return HORN_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_HORN_RPT_pacmod13(HORN_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < HORN_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = HORN_RPT_CANID;
  cframe->DLC = HORN_RPT_DLC;
  cframe->IDE = HORN_RPT_IDE;
  return HORN_RPT_CANID;
}

#else

uint32_t Pack_HORN_RPT_pacmod13(HORN_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HORN_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = HORN_RPT_DLC;
  *_ide = HORN_RPT_IDE;
  return HORN_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_MEDIA_CONTROLS_RPT_pacmod13(MEDIA_CONTROLS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < MEDIA_CONTROLS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_MEDIA_CONTROLS_RPT_pacmod13(&_m->mon1, MEDIA_CONTROLS_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return MEDIA_CONTROLS_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_MEDIA_CONTROLS_RPT_pacmod13(MEDIA_CONTROLS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < MEDIA_CONTROLS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = MEDIA_CONTROLS_RPT_CANID;
  cframe->DLC = MEDIA_CONTROLS_RPT_DLC;
  cframe->IDE = MEDIA_CONTROLS_RPT_IDE;
  return MEDIA_CONTROLS_RPT_CANID;
}

#else

uint32_t Pack_MEDIA_CONTROLS_RPT_pacmod13(MEDIA_CONTROLS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < MEDIA_CONTROLS_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = MEDIA_CONTROLS_RPT_DLC;
  *_ide = MEDIA_CONTROLS_RPT_IDE;
  return MEDIA_CONTROLS_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_PARKING_BRAKE_RPT_pacmod13(PARKING_BRAKE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0x01U));
  _m->COMMANDED_VALUE = (_d[2] & (0x01U));
  _m->OUTPUT_VALUE = (_d[3] & (0x01U));
  _m->CONTROL_STATUS = (_d[4] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[4] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[4] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < PARKING_BRAKE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_PARKING_BRAKE_RPT_pacmod13(&_m->mon1, PARKING_BRAKE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return PARKING_BRAKE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_PARKING_BRAKE_RPT_pacmod13(PARKING_BRAKE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0x01U));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0x01U));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0x01U));
  cframe->Data[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = PARKING_BRAKE_RPT_CANID;
  cframe->DLC = PARKING_BRAKE_RPT_DLC;
  cframe->IDE = PARKING_BRAKE_RPT_IDE;
  return PARKING_BRAKE_RPT_CANID;
}

#else

uint32_t Pack_PARKING_BRAKE_RPT_pacmod13(PARKING_BRAKE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0x01U));
  _d[2] |= (_m->COMMANDED_VALUE & (0x01U));
  _d[3] |= (_m->OUTPUT_VALUE & (0x01U));
  _d[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = PARKING_BRAKE_RPT_DLC;
  *_ide = PARKING_BRAKE_RPT_IDE;
  return PARKING_BRAKE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_PARKING_BRAKE_RPT_2_pacmod13(PARKING_BRAKE_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0x01U));
  _m->COMMANDED_VALUE = (_d[2] & (0x01U));
  _m->OUTPUT_VALUE = (_d[3] & (0x01U));
  _m->CONTROL_STATUS = (_d[4] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[4] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[4] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < PARKING_BRAKE_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_PARKING_BRAKE_RPT_2_pacmod13(&_m->mon1, PARKING_BRAKE_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return PARKING_BRAKE_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_PARKING_BRAKE_RPT_2_pacmod13(PARKING_BRAKE_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0x01U));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0x01U));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0x01U));
  cframe->Data[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = PARKING_BRAKE_RPT_2_CANID;
  cframe->DLC = PARKING_BRAKE_RPT_2_DLC;
  cframe->IDE = PARKING_BRAKE_RPT_2_IDE;
  return PARKING_BRAKE_RPT_2_CANID;
}

#else

uint32_t Pack_PARKING_BRAKE_RPT_2_pacmod13(PARKING_BRAKE_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_RPT_2_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0x01U));
  _d[2] |= (_m->COMMANDED_VALUE & (0x01U));
  _d[3] |= (_m->OUTPUT_VALUE & (0x01U));
  _d[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = PARKING_BRAKE_RPT_2_DLC;
  *_ide = PARKING_BRAKE_RPT_2_IDE;
  return PARKING_BRAKE_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SHIFT_RPT_pacmod13(SHIFT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));
  _m->CONTROL_STATUS = (_d[4] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[4] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[4] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SHIFT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SHIFT_RPT_pacmod13(&_m->mon1, SHIFT_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SHIFT_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SHIFT_RPT_pacmod13(SHIFT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SHIFT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));
  cframe->Data[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = SHIFT_RPT_CANID;
  cframe->DLC = SHIFT_RPT_DLC;
  cframe->IDE = SHIFT_RPT_IDE;
  return SHIFT_RPT_CANID;
}

#else

uint32_t Pack_SHIFT_RPT_pacmod13(SHIFT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SHIFT_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));
  _d[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = SHIFT_RPT_DLC;
  *_ide = SHIFT_RPT_IDE;
  return SHIFT_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_RPT_pacmod13(STEERING_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT_ro = __ext_sig__(( ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD13_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = __ext_sig__(( ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD13_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = __ext_sig__(( ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD13_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->CONTROL_STATUS = (_d[7] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[7] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[7] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_RPT_pacmod13(&_m->mon1, STEERING_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_RPT_pacmod13(STEERING_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  cframe->Data[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = STEERING_RPT_CANID;
  cframe->DLC = STEERING_RPT_DLC;
  cframe->IDE = STEERING_RPT_IDE;
  return STEERING_RPT_CANID;
}

#else

uint32_t Pack_STEERING_RPT_pacmod13(STEERING_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  _d[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = STEERING_RPT_DLC;
  *_ide = STEERING_RPT_IDE;
  return STEERING_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_CMD_LIMIT_RPT_pacmod13(STEERING_CMD_LIMIT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->POSITION_CMD_LIMIT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->POSITION_CMD_LIMIT_phys = (sigfloat_t)(PACMOD13_POSITION_CMD_LIMIT_ro_fromS(_m->POSITION_CMD_LIMIT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->LIMITED_POSITION_CMD_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->LIMITED_POSITION_CMD_phys = (sigfloat_t)(PACMOD13_LIMITED_POSITION_CMD_ro_fromS(_m->LIMITED_POSITION_CMD_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->ROTATION_RATE_CMD_LIMIT_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROTATION_RATE_CMD_LIMIT_phys = (sigfloat_t)(PACMOD13_ROTATION_RATE_CMD_LIMIT_ro_fromS(_m->ROTATION_RATE_CMD_LIMIT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->LIMITED_ROTATION_RATE_ro = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->LIMITED_ROTATION_RATE_phys = (sigfloat_t)(PACMOD13_LIMITED_ROTATION_RATE_ro_fromS(_m->LIMITED_ROTATION_RATE_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_CMD_LIMIT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_CMD_LIMIT_RPT_pacmod13(&_m->mon1, STEERING_CMD_LIMIT_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_CMD_LIMIT_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_CMD_LIMIT_RPT_pacmod13(STEERING_CMD_LIMIT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_CMD_LIMIT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->POSITION_CMD_LIMIT_ro = PACMOD13_POSITION_CMD_LIMIT_ro_toS(_m->POSITION_CMD_LIMIT_phys);
  _m->LIMITED_POSITION_CMD_ro = PACMOD13_LIMITED_POSITION_CMD_ro_toS(_m->LIMITED_POSITION_CMD_phys);
  _m->ROTATION_RATE_CMD_LIMIT_ro = PACMOD13_ROTATION_RATE_CMD_LIMIT_ro_toS(_m->ROTATION_RATE_CMD_LIMIT_phys);
  _m->LIMITED_ROTATION_RATE_ro = PACMOD13_LIMITED_ROTATION_RATE_ro_toS(_m->LIMITED_ROTATION_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->POSITION_CMD_LIMIT_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->POSITION_CMD_LIMIT_ro & (0xFFU));
  cframe->Data[2] |= ((_m->LIMITED_POSITION_CMD_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->LIMITED_POSITION_CMD_ro & (0xFFU));
  cframe->Data[4] |= ((_m->ROTATION_RATE_CMD_LIMIT_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->ROTATION_RATE_CMD_LIMIT_ro & (0xFFU));
  cframe->Data[6] |= ((_m->LIMITED_ROTATION_RATE_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->LIMITED_ROTATION_RATE_ro & (0xFFU));

  cframe->MsgId = STEERING_CMD_LIMIT_RPT_CANID;
  cframe->DLC = STEERING_CMD_LIMIT_RPT_DLC;
  cframe->IDE = STEERING_CMD_LIMIT_RPT_IDE;
  return STEERING_CMD_LIMIT_RPT_CANID;
}

#else

uint32_t Pack_STEERING_CMD_LIMIT_RPT_pacmod13(STEERING_CMD_LIMIT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_CMD_LIMIT_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->POSITION_CMD_LIMIT_ro = PACMOD13_POSITION_CMD_LIMIT_ro_toS(_m->POSITION_CMD_LIMIT_phys);
  _m->LIMITED_POSITION_CMD_ro = PACMOD13_LIMITED_POSITION_CMD_ro_toS(_m->LIMITED_POSITION_CMD_phys);
  _m->ROTATION_RATE_CMD_LIMIT_ro = PACMOD13_ROTATION_RATE_CMD_LIMIT_ro_toS(_m->ROTATION_RATE_CMD_LIMIT_phys);
  _m->LIMITED_ROTATION_RATE_ro = PACMOD13_LIMITED_ROTATION_RATE_ro_toS(_m->LIMITED_ROTATION_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->POSITION_CMD_LIMIT_ro >> 8) & (0xFFU));
  _d[1] |= (_m->POSITION_CMD_LIMIT_ro & (0xFFU));
  _d[2] |= ((_m->LIMITED_POSITION_CMD_ro >> 8) & (0xFFU));
  _d[3] |= (_m->LIMITED_POSITION_CMD_ro & (0xFFU));
  _d[4] |= ((_m->ROTATION_RATE_CMD_LIMIT_ro >> 8) & (0xFFU));
  _d[5] |= (_m->ROTATION_RATE_CMD_LIMIT_ro & (0xFFU));
  _d[6] |= ((_m->LIMITED_ROTATION_RATE_ro >> 8) & (0xFFU));
  _d[7] |= (_m->LIMITED_ROTATION_RATE_ro & (0xFFU));

  *_len = STEERING_CMD_LIMIT_RPT_DLC;
  *_ide = STEERING_CMD_LIMIT_RPT_IDE;
  return STEERING_CMD_LIMIT_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_RPT_2_pacmod13(STEERING_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT_ro = __ext_sig__(( ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD13_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = __ext_sig__(( ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD13_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = __ext_sig__(( ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD13_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->CONTROL_STATUS = (_d[7] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[7] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[7] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_RPT_2_pacmod13(&_m->mon1, STEERING_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_RPT_2_pacmod13(STEERING_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  cframe->Data[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = STEERING_RPT_2_CANID;
  cframe->DLC = STEERING_RPT_2_DLC;
  cframe->IDE = STEERING_RPT_2_IDE;
  return STEERING_RPT_2_CANID;
}

#else

uint32_t Pack_STEERING_RPT_2_pacmod13(STEERING_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));
  _d[7] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = STEERING_RPT_2_DLC;
  *_ide = STEERING_RPT_2_IDE;
  return STEERING_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TURN_RPT_pacmod13(TURN_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TURN_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TURN_RPT_pacmod13(&_m->mon1, TURN_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TURN_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TURN_RPT_pacmod13(TURN_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TURN_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = TURN_RPT_CANID;
  cframe->DLC = TURN_RPT_DLC;
  cframe->IDE = TURN_RPT_IDE;
  return TURN_RPT_CANID;
}

#else

uint32_t Pack_TURN_RPT_pacmod13(TURN_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TURN_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = TURN_RPT_DLC;
  *_ide = TURN_RPT_IDE;
  return TURN_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_WIPER_RPT_pacmod13(WIPER_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WIPER_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WIPER_RPT_pacmod13(&_m->mon1, WIPER_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return WIPER_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_WIPER_RPT_pacmod13(WIPER_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < WIPER_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = WIPER_RPT_CANID;
  cframe->DLC = WIPER_RPT_DLC;
  cframe->IDE = WIPER_RPT_IDE;
  return WIPER_RPT_CANID;
}

#else

uint32_t Pack_WIPER_RPT_pacmod13(WIPER_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WIPER_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = WIPER_RPT_DLC;
  *_ide = WIPER_RPT_IDE;
  return WIPER_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SPRAYER_RPT_pacmod13(SPRAYER_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0x01U));
  _m->COMMANDED_VALUE = (_d[2] & (0x01U));
  _m->OUTPUT_VALUE = (_d[3] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SPRAYER_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SPRAYER_RPT_pacmod13(&_m->mon1, SPRAYER_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SPRAYER_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SPRAYER_RPT_pacmod13(SPRAYER_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SPRAYER_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0x01U));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0x01U));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0x01U));

  cframe->MsgId = SPRAYER_RPT_CANID;
  cframe->DLC = SPRAYER_RPT_DLC;
  cframe->IDE = SPRAYER_RPT_IDE;
  return SPRAYER_RPT_CANID;
}

#else

uint32_t Pack_SPRAYER_RPT_pacmod13(SPRAYER_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SPRAYER_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0x01U));
  _d[2] |= (_m->COMMANDED_VALUE & (0x01U));
  _d[3] |= (_m->OUTPUT_VALUE & (0x01U));

  *_len = SPRAYER_RPT_DLC;
  *_ide = SPRAYER_RPT_IDE;
  return SPRAYER_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_DECEL_RPT_pacmod13(BRAKE_DECEL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD13_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD13_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD13_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_DECEL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_DECEL_RPT_pacmod13(&_m->mon1, BRAKE_DECEL_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_DECEL_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_DECEL_RPT_pacmod13(BRAKE_DECEL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECEL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  cframe->MsgId = BRAKE_DECEL_RPT_CANID;
  cframe->DLC = BRAKE_DECEL_RPT_DLC;
  cframe->IDE = BRAKE_DECEL_RPT_IDE;
  return BRAKE_DECEL_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_DECEL_RPT_pacmod13(BRAKE_DECEL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECEL_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  *_len = BRAKE_DECEL_RPT_DLC;
  *_ide = BRAKE_DECEL_RPT_IDE;
  return BRAKE_DECEL_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_REAR_PASS_DOOR_RPT_pacmod13(REAR_PASS_DOOR_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < REAR_PASS_DOOR_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_REAR_PASS_DOOR_RPT_pacmod13(&_m->mon1, REAR_PASS_DOOR_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return REAR_PASS_DOOR_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_REAR_PASS_DOOR_RPT_pacmod13(REAR_PASS_DOOR_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < REAR_PASS_DOOR_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = REAR_PASS_DOOR_RPT_CANID;
  cframe->DLC = REAR_PASS_DOOR_RPT_DLC;
  cframe->IDE = REAR_PASS_DOOR_RPT_IDE;
  return REAR_PASS_DOOR_RPT_CANID;
}

#else

uint32_t Pack_REAR_PASS_DOOR_RPT_pacmod13(REAR_PASS_DOOR_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < REAR_PASS_DOOR_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = REAR_PASS_DOOR_RPT_DLC;
  *_ide = REAR_PASS_DOOR_RPT_IDE;
  return REAR_PASS_DOOR_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ENGINE_BRAKE_RPT_pacmod13(ENGINE_BRAKE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));
  _m->MAN_AUTO = (_d[4] & (0x03U));
  _m->CMD_AUTO = ((_d[4] >> 2) & (0x03U));
  _m->OUT_AUTO = ((_d[4] >> 4) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ENGINE_BRAKE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ENGINE_BRAKE_RPT_pacmod13(&_m->mon1, ENGINE_BRAKE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ENGINE_BRAKE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ENGINE_BRAKE_RPT_pacmod13(ENGINE_BRAKE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ENGINE_BRAKE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));
  cframe->Data[4] |= (_m->MAN_AUTO & (0x03U)) | ((_m->CMD_AUTO & (0x03U)) << 2) | ((_m->OUT_AUTO & (0x03U)) << 4);

  cframe->MsgId = ENGINE_BRAKE_RPT_CANID;
  cframe->DLC = ENGINE_BRAKE_RPT_DLC;
  cframe->IDE = ENGINE_BRAKE_RPT_IDE;
  return ENGINE_BRAKE_RPT_CANID;
}

#else

uint32_t Pack_ENGINE_BRAKE_RPT_pacmod13(ENGINE_BRAKE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ENGINE_BRAKE_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));
  _d[4] |= (_m->MAN_AUTO & (0x03U)) | ((_m->CMD_AUTO & (0x03U)) << 2) | ((_m->OUT_AUTO & (0x03U)) << 4);

  *_len = ENGINE_BRAKE_RPT_DLC;
  *_ide = ENGINE_BRAKE_RPT_IDE;
  return ENGINE_BRAKE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_EXHAUST_BRAKE_RPT_pacmod13(EXHAUST_BRAKE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < EXHAUST_BRAKE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_EXHAUST_BRAKE_RPT_pacmod13(&_m->mon1, EXHAUST_BRAKE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return EXHAUST_BRAKE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_EXHAUST_BRAKE_RPT_pacmod13(EXHAUST_BRAKE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < EXHAUST_BRAKE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = EXHAUST_BRAKE_RPT_CANID;
  cframe->DLC = EXHAUST_BRAKE_RPT_DLC;
  cframe->IDE = EXHAUST_BRAKE_RPT_IDE;
  return EXHAUST_BRAKE_RPT_CANID;
}

#else

uint32_t Pack_EXHAUST_BRAKE_RPT_pacmod13(EXHAUST_BRAKE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < EXHAUST_BRAKE_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = EXHAUST_BRAKE_RPT_DLC;
  *_ide = EXHAUST_BRAKE_RPT_IDE;
  return EXHAUST_BRAKE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_MARKER_LAMP_RPT_pacmod13(MARKER_LAMP_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0x01U));
  _m->COMMANDED_VALUE = (_d[2] & (0x01U));
  _m->OUTPUT_VALUE = (_d[3] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < MARKER_LAMP_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_MARKER_LAMP_RPT_pacmod13(&_m->mon1, MARKER_LAMP_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return MARKER_LAMP_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_MARKER_LAMP_RPT_pacmod13(MARKER_LAMP_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < MARKER_LAMP_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0x01U));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0x01U));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0x01U));

  cframe->MsgId = MARKER_LAMP_RPT_CANID;
  cframe->DLC = MARKER_LAMP_RPT_DLC;
  cframe->IDE = MARKER_LAMP_RPT_IDE;
  return MARKER_LAMP_RPT_CANID;
}

#else

uint32_t Pack_MARKER_LAMP_RPT_pacmod13(MARKER_LAMP_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < MARKER_LAMP_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0x01U));
  _d[2] |= (_m->COMMANDED_VALUE & (0x01U));
  _d[3] |= (_m->OUTPUT_VALUE & (0x01U));

  *_len = MARKER_LAMP_RPT_DLC;
  *_ide = MARKER_LAMP_RPT_IDE;
  return MARKER_LAMP_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_CABIN_TEMP_RPT_pacmod13(CABIN_TEMP_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD13_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD13_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD13_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CABIN_TEMP_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CABIN_TEMP_RPT_pacmod13(&_m->mon1, CABIN_TEMP_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return CABIN_TEMP_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_CABIN_TEMP_RPT_pacmod13(CABIN_TEMP_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < CABIN_TEMP_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  cframe->MsgId = CABIN_TEMP_RPT_CANID;
  cframe->DLC = CABIN_TEMP_RPT_DLC;
  cframe->IDE = CABIN_TEMP_RPT_IDE;
  return CABIN_TEMP_RPT_CANID;
}

#else

uint32_t Pack_CABIN_TEMP_RPT_pacmod13(CABIN_TEMP_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < CABIN_TEMP_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  *_len = CABIN_TEMP_RPT_DLC;
  *_ide = CABIN_TEMP_RPT_IDE;
  return CABIN_TEMP_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_CABIN_FAN_SPEED_RPT_pacmod13(CABIN_FAN_SPEED_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CABIN_FAN_SPEED_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CABIN_FAN_SPEED_RPT_pacmod13(&_m->mon1, CABIN_FAN_SPEED_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return CABIN_FAN_SPEED_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_CABIN_FAN_SPEED_RPT_pacmod13(CABIN_FAN_SPEED_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < CABIN_FAN_SPEED_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = CABIN_FAN_SPEED_RPT_CANID;
  cframe->DLC = CABIN_FAN_SPEED_RPT_DLC;
  cframe->IDE = CABIN_FAN_SPEED_RPT_IDE;
  return CABIN_FAN_SPEED_RPT_CANID;
}

#else

uint32_t Pack_CABIN_FAN_SPEED_RPT_pacmod13(CABIN_FAN_SPEED_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < CABIN_FAN_SPEED_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = CABIN_FAN_SPEED_RPT_DLC;
  *_ide = CABIN_FAN_SPEED_RPT_IDE;
  return CABIN_FAN_SPEED_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_CABIN_CLIMATE_RPT_pacmod13(CABIN_CLIMATE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MAN_AC_OFF_ON = (_d[1] & (0x03U));
  _m->MAN_MAX_AC_OFF_ON = ((_d[1] >> 2) & (0x03U));
  _m->MAN_DEFROST_OFF_ON = ((_d[1] >> 4) & (0x03U));
  _m->MAN_MAX_DEFROST_OFF_ON = ((_d[1] >> 6) & (0x03U));
  _m->MAN_DIR_UP_OFF_ON = (_d[2] & (0x03U));
  _m->MAN_DIR_DOWN_OFF_ON = ((_d[2] >> 2) & (0x03U));
  _m->CMD_AC_OFF_ON = (_d[3] & (0x03U));
  _m->CMD_MAX_AC_OFF_ON = ((_d[3] >> 2) & (0x03U));
  _m->CMD_DEFROST_OFF_ON = ((_d[3] >> 4) & (0x03U));
  _m->CMD_MAX_DEFROST_OFF_ON = ((_d[3] >> 6) & (0x03U));
  _m->CMD_DIR_UP_OFF_ON = (_d[4] & (0x03U));
  _m->CMD_DIR_DOWN_OFF_ON = ((_d[4] >> 2) & (0x03U));
  _m->OUT_AC_OFF_ON = (_d[5] & (0x03U));
  _m->OUT_MAX_AC_OFF_ON = ((_d[5] >> 2) & (0x03U));
  _m->OUT_DEFROST_OFF_ON = ((_d[5] >> 4) & (0x03U));
  _m->OUT_MAX_DEFROST_OFF_ON = ((_d[5] >> 6) & (0x03U));
  _m->OUT_DIR_UP_OFF_ON = (_d[6] & (0x03U));
  _m->OUT_DIR_DOWN_OFF_ON = ((_d[6] >> 2) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CABIN_CLIMATE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CABIN_CLIMATE_RPT_pacmod13(&_m->mon1, CABIN_CLIMATE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return CABIN_CLIMATE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_CABIN_CLIMATE_RPT_pacmod13(CABIN_CLIMATE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < CABIN_CLIMATE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MAN_AC_OFF_ON & (0x03U)) | ((_m->MAN_MAX_AC_OFF_ON & (0x03U)) << 2) | ((_m->MAN_DEFROST_OFF_ON & (0x03U)) << 4) | ((_m->MAN_MAX_DEFROST_OFF_ON & (0x03U)) << 6);
  cframe->Data[2] |= (_m->MAN_DIR_UP_OFF_ON & (0x03U)) | ((_m->MAN_DIR_DOWN_OFF_ON & (0x03U)) << 2);
  cframe->Data[3] |= (_m->CMD_AC_OFF_ON & (0x03U)) | ((_m->CMD_MAX_AC_OFF_ON & (0x03U)) << 2) | ((_m->CMD_DEFROST_OFF_ON & (0x03U)) << 4) | ((_m->CMD_MAX_DEFROST_OFF_ON & (0x03U)) << 6);
  cframe->Data[4] |= (_m->CMD_DIR_UP_OFF_ON & (0x03U)) | ((_m->CMD_DIR_DOWN_OFF_ON & (0x03U)) << 2);
  cframe->Data[5] |= (_m->OUT_AC_OFF_ON & (0x03U)) | ((_m->OUT_MAX_AC_OFF_ON & (0x03U)) << 2) | ((_m->OUT_DEFROST_OFF_ON & (0x03U)) << 4) | ((_m->OUT_MAX_DEFROST_OFF_ON & (0x03U)) << 6);
  cframe->Data[6] |= (_m->OUT_DIR_UP_OFF_ON & (0x03U)) | ((_m->OUT_DIR_DOWN_OFF_ON & (0x03U)) << 2);

  cframe->MsgId = CABIN_CLIMATE_RPT_CANID;
  cframe->DLC = CABIN_CLIMATE_RPT_DLC;
  cframe->IDE = CABIN_CLIMATE_RPT_IDE;
  return CABIN_CLIMATE_RPT_CANID;
}

#else

uint32_t Pack_CABIN_CLIMATE_RPT_pacmod13(CABIN_CLIMATE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < CABIN_CLIMATE_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MAN_AC_OFF_ON & (0x03U)) | ((_m->MAN_MAX_AC_OFF_ON & (0x03U)) << 2) | ((_m->MAN_DEFROST_OFF_ON & (0x03U)) << 4) | ((_m->MAN_MAX_DEFROST_OFF_ON & (0x03U)) << 6);
  _d[2] |= (_m->MAN_DIR_UP_OFF_ON & (0x03U)) | ((_m->MAN_DIR_DOWN_OFF_ON & (0x03U)) << 2);
  _d[3] |= (_m->CMD_AC_OFF_ON & (0x03U)) | ((_m->CMD_MAX_AC_OFF_ON & (0x03U)) << 2) | ((_m->CMD_DEFROST_OFF_ON & (0x03U)) << 4) | ((_m->CMD_MAX_DEFROST_OFF_ON & (0x03U)) << 6);
  _d[4] |= (_m->CMD_DIR_UP_OFF_ON & (0x03U)) | ((_m->CMD_DIR_DOWN_OFF_ON & (0x03U)) << 2);
  _d[5] |= (_m->OUT_AC_OFF_ON & (0x03U)) | ((_m->OUT_MAX_AC_OFF_ON & (0x03U)) << 2) | ((_m->OUT_DEFROST_OFF_ON & (0x03U)) << 4) | ((_m->OUT_MAX_DEFROST_OFF_ON & (0x03U)) << 6);
  _d[6] |= (_m->OUT_DIR_UP_OFF_ON & (0x03U)) | ((_m->OUT_DIR_DOWN_OFF_ON & (0x03U)) << 2);

  *_len = CABIN_CLIMATE_RPT_DLC;
  *_ide = CABIN_CLIMATE_RPT_IDE;
  return CABIN_CLIMATE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIPPER_BODY_RPT_00_pacmod13(TIPPER_BODY_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIPPER_BODY_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIPPER_BODY_RPT_00_pacmod13(&_m->mon1, TIPPER_BODY_RPT_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIPPER_BODY_RPT_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIPPER_BODY_RPT_00_pacmod13(TIPPER_BODY_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = TIPPER_BODY_RPT_00_CANID;
  cframe->DLC = TIPPER_BODY_RPT_00_DLC;
  cframe->IDE = TIPPER_BODY_RPT_00_IDE;
  return TIPPER_BODY_RPT_00_CANID;
}

#else

uint32_t Pack_TIPPER_BODY_RPT_00_pacmod13(TIPPER_BODY_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_RPT_00_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = TIPPER_BODY_RPT_00_DLC;
  *_ide = TIPPER_BODY_RPT_00_IDE;
  return TIPPER_BODY_RPT_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_POWER_TAKE_OFF_RPT_pacmod13(POWER_TAKE_OFF_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < POWER_TAKE_OFF_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_POWER_TAKE_OFF_RPT_pacmod13(&_m->mon1, POWER_TAKE_OFF_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return POWER_TAKE_OFF_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_POWER_TAKE_OFF_RPT_pacmod13(POWER_TAKE_OFF_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < POWER_TAKE_OFF_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = POWER_TAKE_OFF_RPT_CANID;
  cframe->DLC = POWER_TAKE_OFF_RPT_DLC;
  cframe->IDE = POWER_TAKE_OFF_RPT_IDE;
  return POWER_TAKE_OFF_RPT_CANID;
}

#else

uint32_t Pack_POWER_TAKE_OFF_RPT_pacmod13(POWER_TAKE_OFF_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < POWER_TAKE_OFF_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = POWER_TAKE_OFF_RPT_DLC;
  *_ide = POWER_TAKE_OFF_RPT_IDE;
  return POWER_TAKE_OFF_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_BRAKE_RPT_pacmod13(TRAILER_BRAKE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD13_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD13_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD13_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_BRAKE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_BRAKE_RPT_pacmod13(&_m->mon1, TRAILER_BRAKE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_BRAKE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_BRAKE_RPT_pacmod13(TRAILER_BRAKE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  cframe->MsgId = TRAILER_BRAKE_RPT_CANID;
  cframe->DLC = TRAILER_BRAKE_RPT_DLC;
  cframe->IDE = TRAILER_BRAKE_RPT_IDE;
  return TRAILER_BRAKE_RPT_CANID;
}

#else

uint32_t Pack_TRAILER_BRAKE_RPT_pacmod13(TRAILER_BRAKE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD13_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD13_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD13_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  *_len = TRAILER_BRAKE_RPT_DLC;
  *_ide = TRAILER_BRAKE_RPT_IDE;
  return TRAILER_BRAKE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_AIR_SUPPLY_RPT_pacmod13(TRAILER_AIR_SUPPLY_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0x01U));
  _m->COMMANDED_VALUE = (_d[2] & (0x01U));
  _m->OUTPUT_VALUE = (_d[3] & (0x01U));
  _m->CONTROL_STATUS = (_d[4] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[4] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[4] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_AIR_SUPPLY_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_AIR_SUPPLY_RPT_pacmod13(&_m->mon1, TRAILER_AIR_SUPPLY_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_AIR_SUPPLY_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_AIR_SUPPLY_RPT_pacmod13(TRAILER_AIR_SUPPLY_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_AIR_SUPPLY_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0x01U));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0x01U));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0x01U));
  cframe->Data[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = TRAILER_AIR_SUPPLY_RPT_CANID;
  cframe->DLC = TRAILER_AIR_SUPPLY_RPT_DLC;
  cframe->IDE = TRAILER_AIR_SUPPLY_RPT_IDE;
  return TRAILER_AIR_SUPPLY_RPT_CANID;
}

#else

uint32_t Pack_TRAILER_AIR_SUPPLY_RPT_pacmod13(TRAILER_AIR_SUPPLY_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_AIR_SUPPLY_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0x01U));
  _d[2] |= (_m->COMMANDED_VALUE & (0x01U));
  _d[3] |= (_m->OUTPUT_VALUE & (0x01U));
  _d[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = TRAILER_AIR_SUPPLY_RPT_DLC;
  *_ide = TRAILER_AIR_SUPPLY_RPT_IDE;
  return TRAILER_AIR_SUPPLY_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_AIR_SUPPLY_RPT_2_pacmod13(TRAILER_AIR_SUPPLY_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0x01U));
  _m->COMMANDED_VALUE = (_d[2] & (0x01U));
  _m->OUTPUT_VALUE = (_d[3] & (0x01U));
  _m->CONTROL_STATUS = (_d[4] & (0x01U));
  _m->CONTROLLING_SYSTEMS = ((_d[4] >> 1) & (0x03U));
  _m->PERFORMANCE_STATUS = ((_d[4] >> 3) & (0x07U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_AIR_SUPPLY_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_AIR_SUPPLY_RPT_2_pacmod13(&_m->mon1, TRAILER_AIR_SUPPLY_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_AIR_SUPPLY_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_AIR_SUPPLY_RPT_2_pacmod13(TRAILER_AIR_SUPPLY_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_AIR_SUPPLY_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0x01U));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0x01U));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0x01U));
  cframe->Data[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  cframe->MsgId = TRAILER_AIR_SUPPLY_RPT_2_CANID;
  cframe->DLC = TRAILER_AIR_SUPPLY_RPT_2_DLC;
  cframe->IDE = TRAILER_AIR_SUPPLY_RPT_2_IDE;
  return TRAILER_AIR_SUPPLY_RPT_2_CANID;
}

#else

uint32_t Pack_TRAILER_AIR_SUPPLY_RPT_2_pacmod13(TRAILER_AIR_SUPPLY_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_AIR_SUPPLY_RPT_2_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0x01U));
  _d[2] |= (_m->COMMANDED_VALUE & (0x01U));
  _d[3] |= (_m->OUTPUT_VALUE & (0x01U));
  _d[4] |= (_m->CONTROL_STATUS & (0x01U)) | ((_m->CONTROLLING_SYSTEMS & (0x03U)) << 1) | ((_m->PERFORMANCE_STATUS & (0x07U)) << 3);

  *_len = TRAILER_AIR_SUPPLY_RPT_2_DLC;
  *_ide = TRAILER_AIR_SUPPLY_RPT_2_IDE;
  return TRAILER_AIR_SUPPLY_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ENGINE_RPT_pacmod13(ENGINE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ENGINE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ENGINE_RPT_pacmod13(&_m->mon1, ENGINE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ENGINE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ENGINE_RPT_pacmod13(ENGINE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ENGINE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = ENGINE_RPT_CANID;
  cframe->DLC = ENGINE_RPT_DLC;
  cframe->IDE = ENGINE_RPT_IDE;
  return ENGINE_RPT_CANID;
}

#else

uint32_t Pack_ENGINE_RPT_pacmod13(ENGINE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ENGINE_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = ENGINE_RPT_DLC;
  *_ide = ENGINE_RPT_IDE;
  return ENGINE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIPPER_BODY_RPT_01_pacmod13(TIPPER_BODY_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIPPER_BODY_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIPPER_BODY_RPT_01_pacmod13(&_m->mon1, TIPPER_BODY_RPT_01_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIPPER_BODY_RPT_01_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIPPER_BODY_RPT_01_pacmod13(TIPPER_BODY_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_RPT_01_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = TIPPER_BODY_RPT_01_CANID;
  cframe->DLC = TIPPER_BODY_RPT_01_DLC;
  cframe->IDE = TIPPER_BODY_RPT_01_IDE;
  return TIPPER_BODY_RPT_01_CANID;
}

#else

uint32_t Pack_TIPPER_BODY_RPT_01_pacmod13(TIPPER_BODY_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_RPT_01_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = TIPPER_BODY_RPT_01_DLC;
  *_ide = TIPPER_BODY_RPT_01_IDE;
  return TIPPER_BODY_RPT_01_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIPPER_BODY_RPT_02_pacmod13(TIPPER_BODY_RPT_02_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MANUAL_INPUT = (_d[1] & (0xFFU));
  _m->COMMANDED_VALUE = (_d[2] & (0xFFU));
  _m->OUTPUT_VALUE = (_d[3] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIPPER_BODY_RPT_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIPPER_BODY_RPT_02_pacmod13(&_m->mon1, TIPPER_BODY_RPT_02_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIPPER_BODY_RPT_02_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIPPER_BODY_RPT_02_pacmod13(TIPPER_BODY_RPT_02_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_RPT_02_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = TIPPER_BODY_RPT_02_CANID;
  cframe->DLC = TIPPER_BODY_RPT_02_DLC;
  cframe->IDE = TIPPER_BODY_RPT_02_IDE;
  return TIPPER_BODY_RPT_02_CANID;
}

#else

uint32_t Pack_TIPPER_BODY_RPT_02_pacmod13(TIPPER_BODY_RPT_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_RPT_02_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = TIPPER_BODY_RPT_02_DLC;
  *_ide = TIPPER_BODY_RPT_02_IDE;
  return TIPPER_BODY_RPT_02_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DIFFERENTIAL_LOCKS_RPT_pacmod13(DIFFERENTIAL_LOCKS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLED = (_d[0] & (0x01U));
  _m->OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->COMMAND_OUTPUT_FAULT = ((_d[0] >> 2) & (0x01U));
  _m->INPUT_OUTPUT_FAULT = ((_d[0] >> 3) & (0x01U));
  _m->OUTPUT_REPORTED_FAULT = ((_d[0] >> 4) & (0x01U));
  _m->PACMOD_FAULT = ((_d[0] >> 5) & (0x01U));
  _m->VEHICLE_FAULT = ((_d[0] >> 6) & (0x01U));
  _m->COMMAND_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->MAN_FRONT_LOCK = (_d[1] & (0x03U));
  _m->MAN_CENTER_LOCK = ((_d[1] >> 2) & (0x03U));
  _m->MAN_REAR_LOCK = ((_d[1] >> 4) & (0x03U));
  _m->CMD_FRONT_LOCK = (_d[2] & (0x03U));
  _m->CMD_CENTER_LOCK = ((_d[2] >> 2) & (0x03U));
  _m->CMD_REAR_LOCK = ((_d[2] >> 4) & (0x03U));
  _m->OUT_FRONT_LOCK = (_d[3] & (0x03U));
  _m->OUT_CENTER_LOCK = ((_d[3] >> 2) & (0x03U));
  _m->OUT_REAR_LOCK = ((_d[3] >> 4) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DIFFERENTIAL_LOCKS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DIFFERENTIAL_LOCKS_RPT_pacmod13(&_m->mon1, DIFFERENTIAL_LOCKS_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DIFFERENTIAL_LOCKS_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DIFFERENTIAL_LOCKS_RPT_pacmod13(DIFFERENTIAL_LOCKS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DIFFERENTIAL_LOCKS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MAN_FRONT_LOCK & (0x03U)) | ((_m->MAN_CENTER_LOCK & (0x03U)) << 2) | ((_m->MAN_REAR_LOCK & (0x03U)) << 4);
  cframe->Data[2] |= (_m->CMD_FRONT_LOCK & (0x03U)) | ((_m->CMD_CENTER_LOCK & (0x03U)) << 2) | ((_m->CMD_REAR_LOCK & (0x03U)) << 4);
  cframe->Data[3] |= (_m->OUT_FRONT_LOCK & (0x03U)) | ((_m->OUT_CENTER_LOCK & (0x03U)) << 2) | ((_m->OUT_REAR_LOCK & (0x03U)) << 4);

  cframe->MsgId = DIFFERENTIAL_LOCKS_RPT_CANID;
  cframe->DLC = DIFFERENTIAL_LOCKS_RPT_DLC;
  cframe->IDE = DIFFERENTIAL_LOCKS_RPT_IDE;
  return DIFFERENTIAL_LOCKS_RPT_CANID;
}

#else

uint32_t Pack_DIFFERENTIAL_LOCKS_RPT_pacmod13(DIFFERENTIAL_LOCKS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DIFFERENTIAL_LOCKS_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MAN_FRONT_LOCK & (0x03U)) | ((_m->MAN_CENTER_LOCK & (0x03U)) << 2) | ((_m->MAN_REAR_LOCK & (0x03U)) << 4);
  _d[2] |= (_m->CMD_FRONT_LOCK & (0x03U)) | ((_m->CMD_CENTER_LOCK & (0x03U)) << 2) | ((_m->CMD_REAR_LOCK & (0x03U)) << 4);
  _d[3] |= (_m->OUT_FRONT_LOCK & (0x03U)) | ((_m->OUT_CENTER_LOCK & (0x03U)) << 2) | ((_m->OUT_REAR_LOCK & (0x03U)) << 4);

  *_len = DIFFERENTIAL_LOCKS_RPT_DLC;
  *_ide = DIFFERENTIAL_LOCKS_RPT_IDE;
  return DIFFERENTIAL_LOCKS_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ACCEL_AUX_RPT_pacmod13(ACCEL_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->OPERATOR_INTERACTION = (_d[4] & (0x01U));
  _m->ACCEL_LIMITING_ACTIVE = ((_d[4] >> 1) & (0x01U));
  _m->PRK_BRK_INTERLOCK_ACTIVE = ((_d[4] >> 2) & (0x01U));
  _m->BRAKE_INTERLOCK_ACTIVE = ((_d[4] >> 3) & (0x01U));
  _m->CALIBRATION_STATUS = ((_d[4] >> 4) & (0x07U));
  _m->OPERATOR_INTERACTION_AVAIL = ((_d[5] >> 2) & (0x01U));
  _m->ACCEL_LIMITING_ACTIVE_AVAIL = ((_d[5] >> 3) & (0x01U));
  _m->PRK_BRK_INTERLOCK_ACTIVE_AVAIL = ((_d[5] >> 4) & (0x01U));
  _m->BRAKE_INTERLOCK_ACTIVE_AVAIL = ((_d[5] >> 5) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ACCEL_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ACCEL_AUX_RPT_pacmod13(&_m->mon1, ACCEL_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ACCEL_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ACCEL_AUX_RPT_pacmod13(ACCEL_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ACCEL_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[4] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->ACCEL_LIMITING_ACTIVE & (0x01U)) << 1) | ((_m->PRK_BRK_INTERLOCK_ACTIVE & (0x01U)) << 2) | ((_m->BRAKE_INTERLOCK_ACTIVE & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4);
  cframe->Data[5] |= ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 2) | ((_m->ACCEL_LIMITING_ACTIVE_AVAIL & (0x01U)) << 3) | ((_m->PRK_BRK_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 4) | ((_m->BRAKE_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 5);

  cframe->MsgId = ACCEL_AUX_RPT_CANID;
  cframe->DLC = ACCEL_AUX_RPT_DLC;
  cframe->IDE = ACCEL_AUX_RPT_IDE;
  return ACCEL_AUX_RPT_CANID;
}

#else

uint32_t Pack_ACCEL_AUX_RPT_pacmod13(ACCEL_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ACCEL_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[4] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->ACCEL_LIMITING_ACTIVE & (0x01U)) << 1) | ((_m->PRK_BRK_INTERLOCK_ACTIVE & (0x01U)) << 2) | ((_m->BRAKE_INTERLOCK_ACTIVE & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4);
  _d[5] |= ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 2) | ((_m->ACCEL_LIMITING_ACTIVE_AVAIL & (0x01U)) << 3) | ((_m->PRK_BRK_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 4) | ((_m->BRAKE_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 5);

  *_len = ACCEL_AUX_RPT_DLC;
  *_ide = ACCEL_AUX_RPT_IDE;
  return ACCEL_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_AUX_RPT_pacmod13(BRAKE_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_PRESSURE_2_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_2_phys = (sigfloat_t)(PACMOD13_BRAKE_PRESSURE_2_ro_fromS(_m->BRAKE_PRESSURE_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_phys = (sigfloat_t)(PACMOD13_BRAKE_PRESSURE_ro_fromS(_m->BRAKE_PRESSURE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OPERATOR_INTERACTION = (_d[6] & (0x01U));
  _m->BRAKE_ON_OFF = ((_d[6] >> 1) & (0x01U));
  _m->BRAKE_LIMITING_ACTIVE = ((_d[6] >> 2) & (0x01U));
  _m->BRAKE_REDUCED_ASSIST = ((_d[6] >> 3) & (0x01U));
  _m->CALIBRATION_STATUS = ((_d[6] >> 4) & (0x07U));
  _m->BRAKE_PRESSURE_2_AVAIL = ((_d[7] >> 1) & (0x01U));
  _m->BRAKE_PRESSURE_AVAIL = ((_d[7] >> 2) & (0x01U));
  _m->OPERATOR_INTERACTION_AVAIL = ((_d[7] >> 3) & (0x01U));
  _m->BRAKE_ON_OFF_AVAIL = ((_d[7] >> 4) & (0x01U));
  _m->BRAKE_LIMITING_ACTIVE_AVAIL = ((_d[7] >> 5) & (0x01U));
  _m->BRAKE_REDUCED_ASSIST_AVAIL = ((_d[7] >> 6) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_AUX_RPT_pacmod13(&_m->mon1, BRAKE_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_AUX_RPT_pacmod13(BRAKE_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_2_ro = PACMOD13_BRAKE_PRESSURE_2_ro_toS(_m->BRAKE_PRESSURE_2_phys);
  _m->BRAKE_PRESSURE_ro = PACMOD13_BRAKE_PRESSURE_ro_toS(_m->BRAKE_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[2] |= ((_m->BRAKE_PRESSURE_2_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->BRAKE_PRESSURE_2_ro & (0xFFU));
  cframe->Data[4] |= ((_m->BRAKE_PRESSURE_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->BRAKE_PRESSURE_ro & (0xFFU));
  cframe->Data[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->BRAKE_ON_OFF & (0x01U)) << 1) | ((_m->BRAKE_LIMITING_ACTIVE & (0x01U)) << 2) | ((_m->BRAKE_REDUCED_ASSIST & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4);
  cframe->Data[7] |= ((_m->BRAKE_PRESSURE_2_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_PRESSURE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->BRAKE_ON_OFF_AVAIL & (0x01U)) << 4) | ((_m->BRAKE_LIMITING_ACTIVE_AVAIL & (0x01U)) << 5) | ((_m->BRAKE_REDUCED_ASSIST_AVAIL & (0x01U)) << 6);

  cframe->MsgId = BRAKE_AUX_RPT_CANID;
  cframe->DLC = BRAKE_AUX_RPT_DLC;
  cframe->IDE = BRAKE_AUX_RPT_IDE;
  return BRAKE_AUX_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_AUX_RPT_pacmod13(BRAKE_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_2_ro = PACMOD13_BRAKE_PRESSURE_2_ro_toS(_m->BRAKE_PRESSURE_2_phys);
  _m->BRAKE_PRESSURE_ro = PACMOD13_BRAKE_PRESSURE_ro_toS(_m->BRAKE_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[2] |= ((_m->BRAKE_PRESSURE_2_ro >> 8) & (0xFFU));
  _d[3] |= (_m->BRAKE_PRESSURE_2_ro & (0xFFU));
  _d[4] |= ((_m->BRAKE_PRESSURE_ro >> 8) & (0xFFU));
  _d[5] |= (_m->BRAKE_PRESSURE_ro & (0xFFU));
  _d[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->BRAKE_ON_OFF & (0x01U)) << 1) | ((_m->BRAKE_LIMITING_ACTIVE & (0x01U)) << 2) | ((_m->BRAKE_REDUCED_ASSIST & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4);
  _d[7] |= ((_m->BRAKE_PRESSURE_2_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_PRESSURE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->BRAKE_ON_OFF_AVAIL & (0x01U)) << 4) | ((_m->BRAKE_LIMITING_ACTIVE_AVAIL & (0x01U)) << 5) | ((_m->BRAKE_REDUCED_ASSIST_AVAIL & (0x01U)) << 6);

  *_len = BRAKE_AUX_RPT_DLC;
  *_ide = BRAKE_AUX_RPT_IDE;
  return BRAKE_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_AUX_RPT_2_pacmod13(BRAKE_AUX_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_PRESSURE_2_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_2_phys = (sigfloat_t)(PACMOD13_BRAKE_PRESSURE_2_ro_fromS(_m->BRAKE_PRESSURE_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_phys = (sigfloat_t)(PACMOD13_BRAKE_PRESSURE_ro_fromS(_m->BRAKE_PRESSURE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OPERATOR_INTERACTION = (_d[6] & (0x01U));
  _m->BRAKE_ON_OFF = ((_d[6] >> 1) & (0x01U));
  _m->BRAKE_LIMITING_ACTIVE = ((_d[6] >> 2) & (0x01U));
  _m->BRAKE_REDUCED_ASSIST = ((_d[6] >> 3) & (0x01U));
  _m->CALIBRATION_STATUS = ((_d[6] >> 4) & (0x07U));
  _m->BRAKE_PRESSURE_2_AVAIL = ((_d[7] >> 1) & (0x01U));
  _m->BRAKE_PRESSURE_AVAIL = ((_d[7] >> 2) & (0x01U));
  _m->OPERATOR_INTERACTION_AVAIL = ((_d[7] >> 3) & (0x01U));
  _m->BRAKE_ON_OFF_AVAIL = ((_d[7] >> 4) & (0x01U));
  _m->BRAKE_LIMITING_ACTIVE_AVAIL = ((_d[7] >> 5) & (0x01U));
  _m->BRAKE_REDUCED_ASSIST_AVAIL = ((_d[7] >> 6) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_AUX_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_AUX_RPT_2_pacmod13(&_m->mon1, BRAKE_AUX_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_AUX_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_AUX_RPT_2_pacmod13(BRAKE_AUX_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_AUX_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_2_ro = PACMOD13_BRAKE_PRESSURE_2_ro_toS(_m->BRAKE_PRESSURE_2_phys);
  _m->BRAKE_PRESSURE_ro = PACMOD13_BRAKE_PRESSURE_ro_toS(_m->BRAKE_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[2] |= ((_m->BRAKE_PRESSURE_2_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->BRAKE_PRESSURE_2_ro & (0xFFU));
  cframe->Data[4] |= ((_m->BRAKE_PRESSURE_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->BRAKE_PRESSURE_ro & (0xFFU));
  cframe->Data[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->BRAKE_ON_OFF & (0x01U)) << 1) | ((_m->BRAKE_LIMITING_ACTIVE & (0x01U)) << 2) | ((_m->BRAKE_REDUCED_ASSIST & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4);
  cframe->Data[7] |= ((_m->BRAKE_PRESSURE_2_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_PRESSURE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->BRAKE_ON_OFF_AVAIL & (0x01U)) << 4) | ((_m->BRAKE_LIMITING_ACTIVE_AVAIL & (0x01U)) << 5) | ((_m->BRAKE_REDUCED_ASSIST_AVAIL & (0x01U)) << 6);

  cframe->MsgId = BRAKE_AUX_RPT_2_CANID;
  cframe->DLC = BRAKE_AUX_RPT_2_DLC;
  cframe->IDE = BRAKE_AUX_RPT_2_IDE;
  return BRAKE_AUX_RPT_2_CANID;
}

#else

uint32_t Pack_BRAKE_AUX_RPT_2_pacmod13(BRAKE_AUX_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_AUX_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_2_ro = PACMOD13_BRAKE_PRESSURE_2_ro_toS(_m->BRAKE_PRESSURE_2_phys);
  _m->BRAKE_PRESSURE_ro = PACMOD13_BRAKE_PRESSURE_ro_toS(_m->BRAKE_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[2] |= ((_m->BRAKE_PRESSURE_2_ro >> 8) & (0xFFU));
  _d[3] |= (_m->BRAKE_PRESSURE_2_ro & (0xFFU));
  _d[4] |= ((_m->BRAKE_PRESSURE_ro >> 8) & (0xFFU));
  _d[5] |= (_m->BRAKE_PRESSURE_ro & (0xFFU));
  _d[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->BRAKE_ON_OFF & (0x01U)) << 1) | ((_m->BRAKE_LIMITING_ACTIVE & (0x01U)) << 2) | ((_m->BRAKE_REDUCED_ASSIST & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4);
  _d[7] |= ((_m->BRAKE_PRESSURE_2_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_PRESSURE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->BRAKE_ON_OFF_AVAIL & (0x01U)) << 4) | ((_m->BRAKE_LIMITING_ACTIVE_AVAIL & (0x01U)) << 5) | ((_m->BRAKE_REDUCED_ASSIST_AVAIL & (0x01U)) << 6);

  *_len = BRAKE_AUX_RPT_2_DLC;
  *_ide = BRAKE_AUX_RPT_2_IDE;
  return BRAKE_AUX_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_HEADLIGHT_AUX_RPT_pacmod13(HEADLIGHT_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->HEADLIGHTS_ON = (_d[0] & (0x01U));
  _m->HEADLIGHTS_ON_BRIGHT = ((_d[0] >> 1) & (0x01U));
  _m->FOG_LIGHTS_ON = ((_d[0] >> 2) & (0x01U));
  _m->HEADLIGHTS_MODE = (_d[1] & (0xFFU));
  _m->HEADLIGHTS_ON_AVAIL = (_d[2] & (0x01U));
  _m->HEADLIGHTS_ON_BRIGHT_AVAIL = ((_d[2] >> 1) & (0x01U));
  _m->FOG_LIGHTS_ON_AVAIL = ((_d[2] >> 2) & (0x01U));
  _m->HEADLIGHTS_MODE_AVAIL = ((_d[2] >> 3) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HEADLIGHT_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HEADLIGHT_AUX_RPT_pacmod13(&_m->mon1, HEADLIGHT_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return HEADLIGHT_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_HEADLIGHT_AUX_RPT_pacmod13(HEADLIGHT_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < HEADLIGHT_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->HEADLIGHTS_ON & (0x01U)) | ((_m->HEADLIGHTS_ON_BRIGHT & (0x01U)) << 1) | ((_m->FOG_LIGHTS_ON & (0x01U)) << 2);
  cframe->Data[1] |= (_m->HEADLIGHTS_MODE & (0xFFU));
  cframe->Data[2] |= (_m->HEADLIGHTS_ON_AVAIL & (0x01U)) | ((_m->HEADLIGHTS_ON_BRIGHT_AVAIL & (0x01U)) << 1) | ((_m->FOG_LIGHTS_ON_AVAIL & (0x01U)) << 2) | ((_m->HEADLIGHTS_MODE_AVAIL & (0x01U)) << 3);

  cframe->MsgId = HEADLIGHT_AUX_RPT_CANID;
  cframe->DLC = HEADLIGHT_AUX_RPT_DLC;
  cframe->IDE = HEADLIGHT_AUX_RPT_IDE;
  return HEADLIGHT_AUX_RPT_CANID;
}

#else

uint32_t Pack_HEADLIGHT_AUX_RPT_pacmod13(HEADLIGHT_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HEADLIGHT_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->HEADLIGHTS_ON & (0x01U)) | ((_m->HEADLIGHTS_ON_BRIGHT & (0x01U)) << 1) | ((_m->FOG_LIGHTS_ON & (0x01U)) << 2);
  _d[1] |= (_m->HEADLIGHTS_MODE & (0xFFU));
  _d[2] |= (_m->HEADLIGHTS_ON_AVAIL & (0x01U)) | ((_m->HEADLIGHTS_ON_BRIGHT_AVAIL & (0x01U)) << 1) | ((_m->FOG_LIGHTS_ON_AVAIL & (0x01U)) << 2) | ((_m->HEADLIGHTS_MODE_AVAIL & (0x01U)) << 3);

  *_len = HEADLIGHT_AUX_RPT_DLC;
  *_ide = HEADLIGHT_AUX_RPT_IDE;
  return HEADLIGHT_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_PARKING_BRAKE_AUX_RPT_pacmod13(PARKING_BRAKE_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PARKING_BRAKE_STATUS = (_d[0] & (0x03U));
  _m->PARKING_BRAKE_STATUS_AVAIL = (_d[1] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < PARKING_BRAKE_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_PARKING_BRAKE_AUX_RPT_pacmod13(&_m->mon1, PARKING_BRAKE_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return PARKING_BRAKE_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_PARKING_BRAKE_AUX_RPT_pacmod13(PARKING_BRAKE_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->PARKING_BRAKE_STATUS & (0x03U));
  cframe->Data[1] |= (_m->PARKING_BRAKE_STATUS_AVAIL & (0x01U));

  cframe->MsgId = PARKING_BRAKE_AUX_RPT_CANID;
  cframe->DLC = PARKING_BRAKE_AUX_RPT_DLC;
  cframe->IDE = PARKING_BRAKE_AUX_RPT_IDE;
  return PARKING_BRAKE_AUX_RPT_CANID;
}

#else

uint32_t Pack_PARKING_BRAKE_AUX_RPT_pacmod13(PARKING_BRAKE_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->PARKING_BRAKE_STATUS & (0x03U));
  _d[1] |= (_m->PARKING_BRAKE_STATUS_AVAIL & (0x01U));

  *_len = PARKING_BRAKE_AUX_RPT_DLC;
  *_ide = PARKING_BRAKE_AUX_RPT_IDE;
  return PARKING_BRAKE_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SHIFT_AUX_RPT_pacmod13(SHIFT_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BETWEEN_GEARS = (_d[0] & (0x01U));
  _m->STAY_IN_NEUTRAL_MODE = ((_d[0] >> 1) & (0x01U));
  _m->BRAKE_INTERLOCK_ACTIVE = ((_d[0] >> 2) & (0x01U));
  _m->SPEED_INTERLOCK_ACTIVE = ((_d[0] >> 3) & (0x01U));
  _m->WRITE_TO_CONFIG = ((_d[0] >> 4) & (0x01U));
  _m->CALIBRATION_STATUS = ((_d[0] >> 5) & (0x07U));
  _m->BETWEEN_GEARS_AVAIL = (_d[1] & (0x01U));
  _m->STAY_IN_NEUTRAL_MODE_AVAIL = ((_d[1] >> 1) & (0x01U));
  _m->BRAKE_INTERLOCK_ACTIVE_AVAIL = ((_d[1] >> 2) & (0x01U));
  _m->SPEED_INTERLOCK_ACTIVE_AVAIL = ((_d[1] >> 3) & (0x01U));
  _m->WRITE_TO_CONFIG_IS_VALID = ((_d[1] >> 4) & (0x01U));
  _m->GEAR_NUMBER_AVAIL = ((_d[1] >> 5) & (0x01U));
  _m->SHIFT_MODE_AVAIL = ((_d[1] >> 6) & (0x01U));
  _m->SHIFT_IN_PROGRESS_AVAIL = ((_d[1] >> 7) & (0x01U));
  _m->GEAR_NUMBER = __ext_sig__(( (_d[2] & (0x3FU)) ), 6);
  _m->SHIFT_MODE = ((_d[2] >> 6) & (0x03U));
  _m->SHIFT_IN_PROGRESS = (_d[3] & (0x03U));
  _m->DRIVELINE_ENGAGED = ((_d[3] >> 2) & (0x03U));
  _m->ACTUAL_GEAR_RATIO_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACTUAL_GEAR_RATIO_phys = (sigfloat_t)(PACMOD13_ACTUAL_GEAR_RATIO_ro_fromS(_m->ACTUAL_GEAR_RATIO_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->DRIVELINE_ENGAGED_AVAIL = (_d[6] & (0x01U));
  _m->ACTUAL_GEAR_RATIO_AVAIL = ((_d[6] >> 1) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SHIFT_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SHIFT_AUX_RPT_pacmod13(&_m->mon1, SHIFT_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SHIFT_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SHIFT_AUX_RPT_pacmod13(SHIFT_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SHIFT_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACTUAL_GEAR_RATIO_ro = PACMOD13_ACTUAL_GEAR_RATIO_ro_toS(_m->ACTUAL_GEAR_RATIO_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->BETWEEN_GEARS & (0x01U)) | ((_m->STAY_IN_NEUTRAL_MODE & (0x01U)) << 1) | ((_m->BRAKE_INTERLOCK_ACTIVE & (0x01U)) << 2) | ((_m->SPEED_INTERLOCK_ACTIVE & (0x01U)) << 3) | ((_m->WRITE_TO_CONFIG & (0x01U)) << 4) | ((_m->CALIBRATION_STATUS & (0x07U)) << 5);
  cframe->Data[1] |= (_m->BETWEEN_GEARS_AVAIL & (0x01U)) | ((_m->STAY_IN_NEUTRAL_MODE_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 2) | ((_m->SPEED_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 3) | ((_m->WRITE_TO_CONFIG_IS_VALID & (0x01U)) << 4) | ((_m->GEAR_NUMBER_AVAIL & (0x01U)) << 5) | ((_m->SHIFT_MODE_AVAIL & (0x01U)) << 6) | ((_m->SHIFT_IN_PROGRESS_AVAIL & (0x01U)) << 7);
  cframe->Data[2] |= (_m->GEAR_NUMBER & (0x3FU)) | ((_m->SHIFT_MODE & (0x03U)) << 6);
  cframe->Data[3] |= (_m->SHIFT_IN_PROGRESS & (0x03U)) | ((_m->DRIVELINE_ENGAGED & (0x03U)) << 2);
  cframe->Data[4] |= ((_m->ACTUAL_GEAR_RATIO_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->ACTUAL_GEAR_RATIO_ro & (0xFFU));
  cframe->Data[6] |= (_m->DRIVELINE_ENGAGED_AVAIL & (0x01U)) | ((_m->ACTUAL_GEAR_RATIO_AVAIL & (0x01U)) << 1);

  cframe->MsgId = SHIFT_AUX_RPT_CANID;
  cframe->DLC = SHIFT_AUX_RPT_DLC;
  cframe->IDE = SHIFT_AUX_RPT_IDE;
  return SHIFT_AUX_RPT_CANID;
}

#else

uint32_t Pack_SHIFT_AUX_RPT_pacmod13(SHIFT_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SHIFT_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACTUAL_GEAR_RATIO_ro = PACMOD13_ACTUAL_GEAR_RATIO_ro_toS(_m->ACTUAL_GEAR_RATIO_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->BETWEEN_GEARS & (0x01U)) | ((_m->STAY_IN_NEUTRAL_MODE & (0x01U)) << 1) | ((_m->BRAKE_INTERLOCK_ACTIVE & (0x01U)) << 2) | ((_m->SPEED_INTERLOCK_ACTIVE & (0x01U)) << 3) | ((_m->WRITE_TO_CONFIG & (0x01U)) << 4) | ((_m->CALIBRATION_STATUS & (0x07U)) << 5);
  _d[1] |= (_m->BETWEEN_GEARS_AVAIL & (0x01U)) | ((_m->STAY_IN_NEUTRAL_MODE_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 2) | ((_m->SPEED_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 3) | ((_m->WRITE_TO_CONFIG_IS_VALID & (0x01U)) << 4) | ((_m->GEAR_NUMBER_AVAIL & (0x01U)) << 5) | ((_m->SHIFT_MODE_AVAIL & (0x01U)) << 6) | ((_m->SHIFT_IN_PROGRESS_AVAIL & (0x01U)) << 7);
  _d[2] |= (_m->GEAR_NUMBER & (0x3FU)) | ((_m->SHIFT_MODE & (0x03U)) << 6);
  _d[3] |= (_m->SHIFT_IN_PROGRESS & (0x03U)) | ((_m->DRIVELINE_ENGAGED & (0x03U)) << 2);
  _d[4] |= ((_m->ACTUAL_GEAR_RATIO_ro >> 8) & (0xFFU));
  _d[5] |= (_m->ACTUAL_GEAR_RATIO_ro & (0xFFU));
  _d[6] |= (_m->DRIVELINE_ENGAGED_AVAIL & (0x01U)) | ((_m->ACTUAL_GEAR_RATIO_AVAIL & (0x01U)) << 1);

  *_len = SHIFT_AUX_RPT_DLC;
  *_ide = SHIFT_AUX_RPT_IDE;
  return SHIFT_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_AUX_RPT_pacmod13(STEERING_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->STEERING_FLUID_PRESSURE_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->STEERING_FLUID_PRESSURE_phys = (sigfloat_t)(PACMOD13_STEERING_FLUID_PRESSURE_ro_fromS(_m->STEERING_FLUID_PRESSURE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->STEERING_TORQUE_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->STEERING_TORQUE_phys = (sigfloat_t)(PACMOD13_STEERING_TORQUE_ro_fromS(_m->STEERING_TORQUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->ROTATION_RATE_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROTATION_RATE_phys = (sigfloat_t)(PACMOD13_ROTATION_RATE_ro_fromS(_m->ROTATION_RATE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OPERATOR_INTERACTION = (_d[6] & (0x01U));
  _m->ROTATION_RATE_SIGN = ((_d[6] >> 1) & (0x01U));
  _m->VEHICLE_ANGLE_CALIB_STATUS = ((_d[6] >> 2) & (0x01U));
  _m->STEERING_LIMITING_ACTIVE = ((_d[6] >> 3) & (0x01U));
  _m->CALIBRATION_STATUS = ((_d[6] >> 4) & (0x07U));
  _m->STEERING_CONTROLLER_TYPE = ((_d[6] >> 7) & (0x01U));
  _m->STEERING_TORQUE_AVAIL = ((_d[7] >> 1) & (0x01U));
  _m->ROTATION_RATE_AVAIL = ((_d[7] >> 2) & (0x01U));
  _m->OPERATOR_INTERACTION_AVAIL = ((_d[7] >> 3) & (0x01U));
  _m->ROTATION_RATE_SIGN_AVAIL = ((_d[7] >> 4) & (0x01U));
  _m->VEHICLE_ANGLE_CALIB_STATUS_AVAIL = ((_d[7] >> 5) & (0x01U));
  _m->STEERING_LIMITING_ACTIVE_AVAIL = ((_d[7] >> 6) & (0x01U));
  _m->STEERING_CONTROLLER_TYPE_AVAIL = ((_d[7] >> 7) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_AUX_RPT_pacmod13(&_m->mon1, STEERING_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_AUX_RPT_pacmod13(STEERING_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->STEERING_FLUID_PRESSURE_ro = PACMOD13_STEERING_FLUID_PRESSURE_ro_toS(_m->STEERING_FLUID_PRESSURE_phys);
  _m->STEERING_TORQUE_ro = PACMOD13_STEERING_TORQUE_ro_toS(_m->STEERING_TORQUE_phys);
  _m->ROTATION_RATE_ro = PACMOD13_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->STEERING_FLUID_PRESSURE_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->STEERING_FLUID_PRESSURE_ro & (0xFFU));
  cframe->Data[2] |= ((_m->STEERING_TORQUE_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->STEERING_TORQUE_ro & (0xFFU));
  cframe->Data[4] |= ((_m->ROTATION_RATE_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->ROTATION_RATE_ro & (0xFFU));
  cframe->Data[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->ROTATION_RATE_SIGN & (0x01U)) << 1) | ((_m->VEHICLE_ANGLE_CALIB_STATUS & (0x01U)) << 2) | ((_m->STEERING_LIMITING_ACTIVE & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4) | ((_m->STEERING_CONTROLLER_TYPE & (0x01U)) << 7);
  cframe->Data[7] |= ((_m->STEERING_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ROTATION_RATE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->ROTATION_RATE_SIGN_AVAIL & (0x01U)) << 4) | ((_m->VEHICLE_ANGLE_CALIB_STATUS_AVAIL & (0x01U)) << 5) | ((_m->STEERING_LIMITING_ACTIVE_AVAIL & (0x01U)) << 6) | ((_m->STEERING_CONTROLLER_TYPE_AVAIL & (0x01U)) << 7);

  cframe->MsgId = STEERING_AUX_RPT_CANID;
  cframe->DLC = STEERING_AUX_RPT_DLC;
  cframe->IDE = STEERING_AUX_RPT_IDE;
  return STEERING_AUX_RPT_CANID;
}

#else

uint32_t Pack_STEERING_AUX_RPT_pacmod13(STEERING_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->STEERING_FLUID_PRESSURE_ro = PACMOD13_STEERING_FLUID_PRESSURE_ro_toS(_m->STEERING_FLUID_PRESSURE_phys);
  _m->STEERING_TORQUE_ro = PACMOD13_STEERING_TORQUE_ro_toS(_m->STEERING_TORQUE_phys);
  _m->ROTATION_RATE_ro = PACMOD13_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->STEERING_FLUID_PRESSURE_ro >> 8) & (0xFFU));
  _d[1] |= (_m->STEERING_FLUID_PRESSURE_ro & (0xFFU));
  _d[2] |= ((_m->STEERING_TORQUE_ro >> 8) & (0xFFU));
  _d[3] |= (_m->STEERING_TORQUE_ro & (0xFFU));
  _d[4] |= ((_m->ROTATION_RATE_ro >> 8) & (0xFFU));
  _d[5] |= (_m->ROTATION_RATE_ro & (0xFFU));
  _d[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->ROTATION_RATE_SIGN & (0x01U)) << 1) | ((_m->VEHICLE_ANGLE_CALIB_STATUS & (0x01U)) << 2) | ((_m->STEERING_LIMITING_ACTIVE & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4) | ((_m->STEERING_CONTROLLER_TYPE & (0x01U)) << 7);
  _d[7] |= ((_m->STEERING_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ROTATION_RATE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->ROTATION_RATE_SIGN_AVAIL & (0x01U)) << 4) | ((_m->VEHICLE_ANGLE_CALIB_STATUS_AVAIL & (0x01U)) << 5) | ((_m->STEERING_LIMITING_ACTIVE_AVAIL & (0x01U)) << 6) | ((_m->STEERING_CONTROLLER_TYPE_AVAIL & (0x01U)) << 7);

  *_len = STEERING_AUX_RPT_DLC;
  *_ide = STEERING_AUX_RPT_IDE;
  return STEERING_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_AUX_RPT_2_pacmod13(STEERING_AUX_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->STEERING_FLUID_PRESSURE_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->STEERING_FLUID_PRESSURE_phys = (sigfloat_t)(PACMOD13_STEERING_FLUID_PRESSURE_ro_fromS(_m->STEERING_FLUID_PRESSURE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->STEERING_TORQUE_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->STEERING_TORQUE_phys = (sigfloat_t)(PACMOD13_STEERING_TORQUE_ro_fromS(_m->STEERING_TORQUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->ROTATION_RATE_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROTATION_RATE_phys = (sigfloat_t)(PACMOD13_ROTATION_RATE_ro_fromS(_m->ROTATION_RATE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OPERATOR_INTERACTION = (_d[6] & (0x01U));
  _m->ROTATION_RATE_SIGN = ((_d[6] >> 1) & (0x01U));
  _m->VEHICLE_ANGLE_CALIB_STATUS = ((_d[6] >> 2) & (0x01U));
  _m->STEERING_LIMITING_ACTIVE = ((_d[6] >> 3) & (0x01U));
  _m->CALIBRATION_STATUS = ((_d[6] >> 4) & (0x07U));
  _m->STEERING_CONTROLLER_TYPE = ((_d[6] >> 7) & (0x01U));
  _m->STEERING_TORQUE_AVAIL = ((_d[7] >> 1) & (0x01U));
  _m->ROTATION_RATE_AVAIL = ((_d[7] >> 2) & (0x01U));
  _m->OPERATOR_INTERACTION_AVAIL = ((_d[7] >> 3) & (0x01U));
  _m->ROTATION_RATE_SIGN_AVAIL = ((_d[7] >> 4) & (0x01U));
  _m->VEHICLE_ANGLE_CALIB_STATUS_AVAIL = ((_d[7] >> 5) & (0x01U));
  _m->STEERING_LIMITING_ACTIVE_AVAIL = ((_d[7] >> 6) & (0x01U));
  _m->STEERING_CONTROLLER_TYPE_AVAIL = ((_d[7] >> 7) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_AUX_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_AUX_RPT_2_pacmod13(&_m->mon1, STEERING_AUX_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_AUX_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_AUX_RPT_2_pacmod13(STEERING_AUX_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_AUX_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->STEERING_FLUID_PRESSURE_ro = PACMOD13_STEERING_FLUID_PRESSURE_ro_toS(_m->STEERING_FLUID_PRESSURE_phys);
  _m->STEERING_TORQUE_ro = PACMOD13_STEERING_TORQUE_ro_toS(_m->STEERING_TORQUE_phys);
  _m->ROTATION_RATE_ro = PACMOD13_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->STEERING_FLUID_PRESSURE_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->STEERING_FLUID_PRESSURE_ro & (0xFFU));
  cframe->Data[2] |= ((_m->STEERING_TORQUE_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->STEERING_TORQUE_ro & (0xFFU));
  cframe->Data[4] |= ((_m->ROTATION_RATE_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->ROTATION_RATE_ro & (0xFFU));
  cframe->Data[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->ROTATION_RATE_SIGN & (0x01U)) << 1) | ((_m->VEHICLE_ANGLE_CALIB_STATUS & (0x01U)) << 2) | ((_m->STEERING_LIMITING_ACTIVE & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4) | ((_m->STEERING_CONTROLLER_TYPE & (0x01U)) << 7);
  cframe->Data[7] |= ((_m->STEERING_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ROTATION_RATE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->ROTATION_RATE_SIGN_AVAIL & (0x01U)) << 4) | ((_m->VEHICLE_ANGLE_CALIB_STATUS_AVAIL & (0x01U)) << 5) | ((_m->STEERING_LIMITING_ACTIVE_AVAIL & (0x01U)) << 6) | ((_m->STEERING_CONTROLLER_TYPE_AVAIL & (0x01U)) << 7);

  cframe->MsgId = STEERING_AUX_RPT_2_CANID;
  cframe->DLC = STEERING_AUX_RPT_2_DLC;
  cframe->IDE = STEERING_AUX_RPT_2_IDE;
  return STEERING_AUX_RPT_2_CANID;
}

#else

uint32_t Pack_STEERING_AUX_RPT_2_pacmod13(STEERING_AUX_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_AUX_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->STEERING_FLUID_PRESSURE_ro = PACMOD13_STEERING_FLUID_PRESSURE_ro_toS(_m->STEERING_FLUID_PRESSURE_phys);
  _m->STEERING_TORQUE_ro = PACMOD13_STEERING_TORQUE_ro_toS(_m->STEERING_TORQUE_phys);
  _m->ROTATION_RATE_ro = PACMOD13_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->STEERING_FLUID_PRESSURE_ro >> 8) & (0xFFU));
  _d[1] |= (_m->STEERING_FLUID_PRESSURE_ro & (0xFFU));
  _d[2] |= ((_m->STEERING_TORQUE_ro >> 8) & (0xFFU));
  _d[3] |= (_m->STEERING_TORQUE_ro & (0xFFU));
  _d[4] |= ((_m->ROTATION_RATE_ro >> 8) & (0xFFU));
  _d[5] |= (_m->ROTATION_RATE_ro & (0xFFU));
  _d[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->ROTATION_RATE_SIGN & (0x01U)) << 1) | ((_m->VEHICLE_ANGLE_CALIB_STATUS & (0x01U)) << 2) | ((_m->STEERING_LIMITING_ACTIVE & (0x01U)) << 3) | ((_m->CALIBRATION_STATUS & (0x07U)) << 4) | ((_m->STEERING_CONTROLLER_TYPE & (0x01U)) << 7);
  _d[7] |= ((_m->STEERING_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ROTATION_RATE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->ROTATION_RATE_SIGN_AVAIL & (0x01U)) << 4) | ((_m->VEHICLE_ANGLE_CALIB_STATUS_AVAIL & (0x01U)) << 5) | ((_m->STEERING_LIMITING_ACTIVE_AVAIL & (0x01U)) << 6) | ((_m->STEERING_CONTROLLER_TYPE_AVAIL & (0x01U)) << 7);

  *_len = STEERING_AUX_RPT_2_DLC;
  *_ide = STEERING_AUX_RPT_2_IDE;
  return STEERING_AUX_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TURN_AUX_RPT_pacmod13(TURN_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DRIVER_BLINKER_BULB_ON = (_d[0] & (0x01U));
  _m->PASS_BLINKER_BULB_ON = ((_d[0] >> 1) & (0x01U));
  _m->DRIVER_BLINKER_BULB_ON_AVAIL = (_d[1] & (0x01U));
  _m->PASS_BLINKER_BULB_ON_AVAIL = ((_d[1] >> 1) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TURN_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TURN_AUX_RPT_pacmod13(&_m->mon1, TURN_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TURN_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TURN_AUX_RPT_pacmod13(TURN_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TURN_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->DRIVER_BLINKER_BULB_ON & (0x01U)) | ((_m->PASS_BLINKER_BULB_ON & (0x01U)) << 1);
  cframe->Data[1] |= (_m->DRIVER_BLINKER_BULB_ON_AVAIL & (0x01U)) | ((_m->PASS_BLINKER_BULB_ON_AVAIL & (0x01U)) << 1);

  cframe->MsgId = TURN_AUX_RPT_CANID;
  cframe->DLC = TURN_AUX_RPT_DLC;
  cframe->IDE = TURN_AUX_RPT_IDE;
  return TURN_AUX_RPT_CANID;
}

#else

uint32_t Pack_TURN_AUX_RPT_pacmod13(TURN_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TURN_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->DRIVER_BLINKER_BULB_ON & (0x01U)) | ((_m->PASS_BLINKER_BULB_ON & (0x01U)) << 1);
  _d[1] |= (_m->DRIVER_BLINKER_BULB_ON_AVAIL & (0x01U)) | ((_m->PASS_BLINKER_BULB_ON_AVAIL & (0x01U)) << 1);

  *_len = TURN_AUX_RPT_DLC;
  *_ide = TURN_AUX_RPT_IDE;
  return TURN_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_WIPER_AUX_RPT_pacmod13(WIPER_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->FRONT_WIPING = (_d[0] & (0x01U));
  _m->FRONT_SPRAYING = ((_d[0] >> 1) & (0x01U));
  _m->REAR_WIPING = ((_d[0] >> 2) & (0x01U));
  _m->REAR_SPRAYING = ((_d[0] >> 3) & (0x01U));
  _m->SPRAY_NEAR_EMPTY = ((_d[0] >> 4) & (0x01U));
  _m->SPRAY_EMPTY = ((_d[0] >> 5) & (0x01U));
  _m->FRONT_WIPING_AVAIL = (_d[1] & (0x01U));
  _m->FRONT_SPRAYING_AVAIL = ((_d[1] >> 1) & (0x01U));
  _m->REAR_WIPING_AVAIL = ((_d[1] >> 2) & (0x01U));
  _m->REAR_SPRAYING_AVAIL = ((_d[1] >> 3) & (0x01U));
  _m->SPRAY_NEAR_EMPTY_AVAIL = ((_d[1] >> 4) & (0x01U));
  _m->SPRAY_EMPTY_AVAIL = ((_d[1] >> 5) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WIPER_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WIPER_AUX_RPT_pacmod13(&_m->mon1, WIPER_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return WIPER_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_WIPER_AUX_RPT_pacmod13(WIPER_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < WIPER_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->FRONT_WIPING & (0x01U)) | ((_m->FRONT_SPRAYING & (0x01U)) << 1) | ((_m->REAR_WIPING & (0x01U)) << 2) | ((_m->REAR_SPRAYING & (0x01U)) << 3) | ((_m->SPRAY_NEAR_EMPTY & (0x01U)) << 4) | ((_m->SPRAY_EMPTY & (0x01U)) << 5);
  cframe->Data[1] |= (_m->FRONT_WIPING_AVAIL & (0x01U)) | ((_m->FRONT_SPRAYING_AVAIL & (0x01U)) << 1) | ((_m->REAR_WIPING_AVAIL & (0x01U)) << 2) | ((_m->REAR_SPRAYING_AVAIL & (0x01U)) << 3) | ((_m->SPRAY_NEAR_EMPTY_AVAIL & (0x01U)) << 4) | ((_m->SPRAY_EMPTY_AVAIL & (0x01U)) << 5);

  cframe->MsgId = WIPER_AUX_RPT_CANID;
  cframe->DLC = WIPER_AUX_RPT_DLC;
  cframe->IDE = WIPER_AUX_RPT_IDE;
  return WIPER_AUX_RPT_CANID;
}

#else

uint32_t Pack_WIPER_AUX_RPT_pacmod13(WIPER_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WIPER_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->FRONT_WIPING & (0x01U)) | ((_m->FRONT_SPRAYING & (0x01U)) << 1) | ((_m->REAR_WIPING & (0x01U)) << 2) | ((_m->REAR_SPRAYING & (0x01U)) << 3) | ((_m->SPRAY_NEAR_EMPTY & (0x01U)) << 4) | ((_m->SPRAY_EMPTY & (0x01U)) << 5);
  _d[1] |= (_m->FRONT_WIPING_AVAIL & (0x01U)) | ((_m->FRONT_SPRAYING_AVAIL & (0x01U)) << 1) | ((_m->REAR_WIPING_AVAIL & (0x01U)) << 2) | ((_m->REAR_SPRAYING_AVAIL & (0x01U)) << 3) | ((_m->SPRAY_NEAR_EMPTY_AVAIL & (0x01U)) << 4) | ((_m->SPRAY_EMPTY_AVAIL & (0x01U)) << 5);

  *_len = WIPER_AUX_RPT_DLC;
  *_ide = WIPER_AUX_RPT_IDE;
  return WIPER_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_DECEL_AUX_RPT_pacmod13(BRAKE_DECEL_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->XBR_ACTIVE_CONTROL_MODE = (_d[0] & (0x0FU));
  _m->XBR_SYSTEM_STATE = ((_d[0] >> 4) & (0x03U));
  _m->FOUNDATION_BRAKE_USE = ((_d[0] >> 6) & (0x03U));
  _m->HILL_HOLDER_MODE = (_d[1] & (0x07U));
  _m->XBR_ACTIVE_CONTROL_MODE_AVAIL = (_d[2] & (0x01U));
  _m->XBR_SYSTEM_STATE_AVAIL = ((_d[2] >> 1) & (0x01U));
  _m->FOUNDATION_BRAKE_USE_AVAIL = ((_d[2] >> 2) & (0x01U));
  _m->HILL_HOLDER_MODE_AVAIL = ((_d[2] >> 3) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_DECEL_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_DECEL_AUX_RPT_pacmod13(&_m->mon1, BRAKE_DECEL_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_DECEL_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_DECEL_AUX_RPT_pacmod13(BRAKE_DECEL_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECEL_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->XBR_ACTIVE_CONTROL_MODE & (0x0FU)) | ((_m->XBR_SYSTEM_STATE & (0x03U)) << 4) | ((_m->FOUNDATION_BRAKE_USE & (0x03U)) << 6);
  cframe->Data[1] |= (_m->HILL_HOLDER_MODE & (0x07U));
  cframe->Data[2] |= (_m->XBR_ACTIVE_CONTROL_MODE_AVAIL & (0x01U)) | ((_m->XBR_SYSTEM_STATE_AVAIL & (0x01U)) << 1) | ((_m->FOUNDATION_BRAKE_USE_AVAIL & (0x01U)) << 2) | ((_m->HILL_HOLDER_MODE_AVAIL & (0x01U)) << 3);

  cframe->MsgId = BRAKE_DECEL_AUX_RPT_CANID;
  cframe->DLC = BRAKE_DECEL_AUX_RPT_DLC;
  cframe->IDE = BRAKE_DECEL_AUX_RPT_IDE;
  return BRAKE_DECEL_AUX_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_DECEL_AUX_RPT_pacmod13(BRAKE_DECEL_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECEL_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->XBR_ACTIVE_CONTROL_MODE & (0x0FU)) | ((_m->XBR_SYSTEM_STATE & (0x03U)) << 4) | ((_m->FOUNDATION_BRAKE_USE & (0x03U)) << 6);
  _d[1] |= (_m->HILL_HOLDER_MODE & (0x07U));
  _d[2] |= (_m->XBR_ACTIVE_CONTROL_MODE_AVAIL & (0x01U)) | ((_m->XBR_SYSTEM_STATE_AVAIL & (0x01U)) << 1) | ((_m->FOUNDATION_BRAKE_USE_AVAIL & (0x01U)) << 2) | ((_m->HILL_HOLDER_MODE_AVAIL & (0x01U)) << 3);

  *_len = BRAKE_DECEL_AUX_RPT_DLC;
  *_ide = BRAKE_DECEL_AUX_RPT_IDE;
  return BRAKE_DECEL_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ENGINE_BRAKE_AUX_RPT_pacmod13(ENGINE_BRAKE_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENGINE_BRAKE_STATUS = (_d[0] & (0x03U));
  _m->ACTUAL_ENGINE_BRK_TORQUE_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACTUAL_ENGINE_BRK_TORQUE_phys = PACMOD13_ACTUAL_ENGINE_BRK_TORQUE_ro_fromS(_m->ACTUAL_ENGINE_BRK_TORQUE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->INTENDED_ENGINE_BRK_TORQUE_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->INTENDED_ENGINE_BRK_TORQUE_phys = PACMOD13_INTENDED_ENGINE_BRK_TORQUE_ro_fromS(_m->INTENDED_ENGINE_BRK_TORQUE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->ENGINE_BRAKE_STATUS_AVAIL = (_d[3] & (0x01U));
  _m->ACTUAL_ENGINE_BRK_TORQUE_AVAIL = ((_d[3] >> 1) & (0x01U));
  _m->INTENDED_ENGINE_BRK_TORQUE_AVAIL = ((_d[3] >> 2) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ENGINE_BRAKE_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ENGINE_BRAKE_AUX_RPT_pacmod13(&_m->mon1, ENGINE_BRAKE_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ENGINE_BRAKE_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ENGINE_BRAKE_AUX_RPT_pacmod13(ENGINE_BRAKE_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ENGINE_BRAKE_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACTUAL_ENGINE_BRK_TORQUE_ro = PACMOD13_ACTUAL_ENGINE_BRK_TORQUE_ro_toS(_m->ACTUAL_ENGINE_BRK_TORQUE_phys);
  _m->INTENDED_ENGINE_BRK_TORQUE_ro = PACMOD13_INTENDED_ENGINE_BRK_TORQUE_ro_toS(_m->INTENDED_ENGINE_BRK_TORQUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENGINE_BRAKE_STATUS & (0x03U));
  cframe->Data[1] |= (_m->ACTUAL_ENGINE_BRK_TORQUE_ro & (0xFFU));
  cframe->Data[2] |= (_m->INTENDED_ENGINE_BRK_TORQUE_ro & (0xFFU));
  cframe->Data[3] |= (_m->ENGINE_BRAKE_STATUS_AVAIL & (0x01U)) | ((_m->ACTUAL_ENGINE_BRK_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->INTENDED_ENGINE_BRK_TORQUE_AVAIL & (0x01U)) << 2);

  cframe->MsgId = ENGINE_BRAKE_AUX_RPT_CANID;
  cframe->DLC = ENGINE_BRAKE_AUX_RPT_DLC;
  cframe->IDE = ENGINE_BRAKE_AUX_RPT_IDE;
  return ENGINE_BRAKE_AUX_RPT_CANID;
}

#else

uint32_t Pack_ENGINE_BRAKE_AUX_RPT_pacmod13(ENGINE_BRAKE_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ENGINE_BRAKE_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACTUAL_ENGINE_BRK_TORQUE_ro = PACMOD13_ACTUAL_ENGINE_BRK_TORQUE_ro_toS(_m->ACTUAL_ENGINE_BRK_TORQUE_phys);
  _m->INTENDED_ENGINE_BRK_TORQUE_ro = PACMOD13_INTENDED_ENGINE_BRK_TORQUE_ro_toS(_m->INTENDED_ENGINE_BRK_TORQUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->ENGINE_BRAKE_STATUS & (0x03U));
  _d[1] |= (_m->ACTUAL_ENGINE_BRK_TORQUE_ro & (0xFFU));
  _d[2] |= (_m->INTENDED_ENGINE_BRK_TORQUE_ro & (0xFFU));
  _d[3] |= (_m->ENGINE_BRAKE_STATUS_AVAIL & (0x01U)) | ((_m->ACTUAL_ENGINE_BRK_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->INTENDED_ENGINE_BRK_TORQUE_AVAIL & (0x01U)) << 2);

  *_len = ENGINE_BRAKE_AUX_RPT_DLC;
  *_ide = ENGINE_BRAKE_AUX_RPT_IDE;
  return ENGINE_BRAKE_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIPPER_BODY_AUX_RPT_00_pacmod13(TIPPER_BODY_AUX_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ROLL_ANGLE_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_ANGLE_phys = (sigfloat_t)(PACMOD13_ROLL_ANGLE_ro_fromS(_m->ROLL_ANGLE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PITCH_ANGLE_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PITCH_ANGLE_phys = (sigfloat_t)(PACMOD13_PITCH_ANGLE_ro_fromS(_m->PITCH_ANGLE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->DOOR_FULLY_OPEN = (_d[4] & (0x03U));
  _m->DOOR_FULLY_CLOSED = ((_d[4] >> 2) & (0x03U));
  _m->BODY_FULLY_LOWERED = ((_d[4] >> 4) & (0x03U));
  _m->BODY_FULLY_RAISED = ((_d[4] >> 6) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIPPER_BODY_AUX_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIPPER_BODY_AUX_RPT_00_pacmod13(&_m->mon1, TIPPER_BODY_AUX_RPT_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIPPER_BODY_AUX_RPT_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIPPER_BODY_AUX_RPT_00_pacmod13(TIPPER_BODY_AUX_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_AUX_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_ANGLE_ro = PACMOD13_ROLL_ANGLE_ro_toS(_m->ROLL_ANGLE_phys);
  _m->PITCH_ANGLE_ro = PACMOD13_PITCH_ANGLE_ro_toS(_m->PITCH_ANGLE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->ROLL_ANGLE_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->ROLL_ANGLE_ro & (0xFFU));
  cframe->Data[2] |= ((_m->PITCH_ANGLE_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->PITCH_ANGLE_ro & (0xFFU));
  cframe->Data[4] |= (_m->DOOR_FULLY_OPEN & (0x03U)) | ((_m->DOOR_FULLY_CLOSED & (0x03U)) << 2) | ((_m->BODY_FULLY_LOWERED & (0x03U)) << 4) | ((_m->BODY_FULLY_RAISED & (0x03U)) << 6);

  cframe->MsgId = TIPPER_BODY_AUX_RPT_00_CANID;
  cframe->DLC = TIPPER_BODY_AUX_RPT_00_DLC;
  cframe->IDE = TIPPER_BODY_AUX_RPT_00_IDE;
  return TIPPER_BODY_AUX_RPT_00_CANID;
}

#else

uint32_t Pack_TIPPER_BODY_AUX_RPT_00_pacmod13(TIPPER_BODY_AUX_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_AUX_RPT_00_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_ANGLE_ro = PACMOD13_ROLL_ANGLE_ro_toS(_m->ROLL_ANGLE_phys);
  _m->PITCH_ANGLE_ro = PACMOD13_PITCH_ANGLE_ro_toS(_m->PITCH_ANGLE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->ROLL_ANGLE_ro >> 8) & (0xFFU));
  _d[1] |= (_m->ROLL_ANGLE_ro & (0xFFU));
  _d[2] |= ((_m->PITCH_ANGLE_ro >> 8) & (0xFFU));
  _d[3] |= (_m->PITCH_ANGLE_ro & (0xFFU));
  _d[4] |= (_m->DOOR_FULLY_OPEN & (0x03U)) | ((_m->DOOR_FULLY_CLOSED & (0x03U)) << 2) | ((_m->BODY_FULLY_LOWERED & (0x03U)) << 4) | ((_m->BODY_FULLY_RAISED & (0x03U)) << 6);

  *_len = TIPPER_BODY_AUX_RPT_00_DLC;
  *_ide = TIPPER_BODY_AUX_RPT_00_IDE;
  return TIPPER_BODY_AUX_RPT_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIPPER_BODY_AUX_RPT_01_pacmod13(TIPPER_BODY_AUX_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ROLL_ANGLE_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_ANGLE_phys = (sigfloat_t)(PACMOD13_ROLL_ANGLE_ro_fromS(_m->ROLL_ANGLE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PITCH_ANGLE_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PITCH_ANGLE_phys = (sigfloat_t)(PACMOD13_PITCH_ANGLE_ro_fromS(_m->PITCH_ANGLE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->DOOR_FULLY_OPEN = (_d[4] & (0x03U));
  _m->DOOR_FULLY_CLOSED = ((_d[4] >> 2) & (0x03U));
  _m->BODY_FULLY_LOWERED = ((_d[4] >> 4) & (0x03U));
  _m->BODY_FULLY_RAISED = ((_d[4] >> 6) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIPPER_BODY_AUX_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIPPER_BODY_AUX_RPT_01_pacmod13(&_m->mon1, TIPPER_BODY_AUX_RPT_01_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIPPER_BODY_AUX_RPT_01_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIPPER_BODY_AUX_RPT_01_pacmod13(TIPPER_BODY_AUX_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_AUX_RPT_01_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_ANGLE_ro = PACMOD13_ROLL_ANGLE_ro_toS(_m->ROLL_ANGLE_phys);
  _m->PITCH_ANGLE_ro = PACMOD13_PITCH_ANGLE_ro_toS(_m->PITCH_ANGLE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->ROLL_ANGLE_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->ROLL_ANGLE_ro & (0xFFU));
  cframe->Data[2] |= ((_m->PITCH_ANGLE_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->PITCH_ANGLE_ro & (0xFFU));
  cframe->Data[4] |= (_m->DOOR_FULLY_OPEN & (0x03U)) | ((_m->DOOR_FULLY_CLOSED & (0x03U)) << 2) | ((_m->BODY_FULLY_LOWERED & (0x03U)) << 4) | ((_m->BODY_FULLY_RAISED & (0x03U)) << 6);

  cframe->MsgId = TIPPER_BODY_AUX_RPT_01_CANID;
  cframe->DLC = TIPPER_BODY_AUX_RPT_01_DLC;
  cframe->IDE = TIPPER_BODY_AUX_RPT_01_IDE;
  return TIPPER_BODY_AUX_RPT_01_CANID;
}

#else

uint32_t Pack_TIPPER_BODY_AUX_RPT_01_pacmod13(TIPPER_BODY_AUX_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_AUX_RPT_01_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_ANGLE_ro = PACMOD13_ROLL_ANGLE_ro_toS(_m->ROLL_ANGLE_phys);
  _m->PITCH_ANGLE_ro = PACMOD13_PITCH_ANGLE_ro_toS(_m->PITCH_ANGLE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->ROLL_ANGLE_ro >> 8) & (0xFFU));
  _d[1] |= (_m->ROLL_ANGLE_ro & (0xFFU));
  _d[2] |= ((_m->PITCH_ANGLE_ro >> 8) & (0xFFU));
  _d[3] |= (_m->PITCH_ANGLE_ro & (0xFFU));
  _d[4] |= (_m->DOOR_FULLY_OPEN & (0x03U)) | ((_m->DOOR_FULLY_CLOSED & (0x03U)) << 2) | ((_m->BODY_FULLY_LOWERED & (0x03U)) << 4) | ((_m->BODY_FULLY_RAISED & (0x03U)) << 6);

  *_len = TIPPER_BODY_AUX_RPT_01_DLC;
  *_ide = TIPPER_BODY_AUX_RPT_01_IDE;
  return TIPPER_BODY_AUX_RPT_01_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIPPER_BODY_AUX_RPT_02_pacmod13(TIPPER_BODY_AUX_RPT_02_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ROLL_ANGLE_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_ANGLE_phys = (sigfloat_t)(PACMOD13_ROLL_ANGLE_ro_fromS(_m->ROLL_ANGLE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PITCH_ANGLE_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PITCH_ANGLE_phys = (sigfloat_t)(PACMOD13_PITCH_ANGLE_ro_fromS(_m->PITCH_ANGLE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->DOOR_FULLY_OPEN = (_d[4] & (0x03U));
  _m->DOOR_FULLY_CLOSED = ((_d[4] >> 2) & (0x03U));
  _m->BODY_FULLY_LOWERED = ((_d[4] >> 4) & (0x03U));
  _m->BODY_FULLY_RAISED = ((_d[4] >> 6) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIPPER_BODY_AUX_RPT_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIPPER_BODY_AUX_RPT_02_pacmod13(&_m->mon1, TIPPER_BODY_AUX_RPT_02_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIPPER_BODY_AUX_RPT_02_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIPPER_BODY_AUX_RPT_02_pacmod13(TIPPER_BODY_AUX_RPT_02_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_AUX_RPT_02_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_ANGLE_ro = PACMOD13_ROLL_ANGLE_ro_toS(_m->ROLL_ANGLE_phys);
  _m->PITCH_ANGLE_ro = PACMOD13_PITCH_ANGLE_ro_toS(_m->PITCH_ANGLE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->ROLL_ANGLE_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->ROLL_ANGLE_ro & (0xFFU));
  cframe->Data[2] |= ((_m->PITCH_ANGLE_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->PITCH_ANGLE_ro & (0xFFU));
  cframe->Data[4] |= (_m->DOOR_FULLY_OPEN & (0x03U)) | ((_m->DOOR_FULLY_CLOSED & (0x03U)) << 2) | ((_m->BODY_FULLY_LOWERED & (0x03U)) << 4) | ((_m->BODY_FULLY_RAISED & (0x03U)) << 6);

  cframe->MsgId = TIPPER_BODY_AUX_RPT_02_CANID;
  cframe->DLC = TIPPER_BODY_AUX_RPT_02_DLC;
  cframe->IDE = TIPPER_BODY_AUX_RPT_02_IDE;
  return TIPPER_BODY_AUX_RPT_02_CANID;
}

#else

uint32_t Pack_TIPPER_BODY_AUX_RPT_02_pacmod13(TIPPER_BODY_AUX_RPT_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIPPER_BODY_AUX_RPT_02_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_ANGLE_ro = PACMOD13_ROLL_ANGLE_ro_toS(_m->ROLL_ANGLE_phys);
  _m->PITCH_ANGLE_ro = PACMOD13_PITCH_ANGLE_ro_toS(_m->PITCH_ANGLE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->ROLL_ANGLE_ro >> 8) & (0xFFU));
  _d[1] |= (_m->ROLL_ANGLE_ro & (0xFFU));
  _d[2] |= ((_m->PITCH_ANGLE_ro >> 8) & (0xFFU));
  _d[3] |= (_m->PITCH_ANGLE_ro & (0xFFU));
  _d[4] |= (_m->DOOR_FULLY_OPEN & (0x03U)) | ((_m->DOOR_FULLY_CLOSED & (0x03U)) << 2) | ((_m->BODY_FULLY_LOWERED & (0x03U)) << 4) | ((_m->BODY_FULLY_RAISED & (0x03U)) << 6);

  *_len = TIPPER_BODY_AUX_RPT_02_DLC;
  *_ide = TIPPER_BODY_AUX_RPT_02_IDE;
  return TIPPER_BODY_AUX_RPT_02_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_SPEED_RPT_pacmod13(VEHICLE_SPEED_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->VEHICLE_SPEED_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->VEHICLE_SPEED_phys = (sigfloat_t)(PACMOD13_VEHICLE_SPEED_ro_fromS(_m->VEHICLE_SPEED_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->VEHICLE_SPEED_VALID = (_d[2] & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_SPEED_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_SPEED_RPT_pacmod13(&_m->mon1, VEHICLE_SPEED_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return VEHICLE_SPEED_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_VEHICLE_SPEED_RPT_pacmod13(VEHICLE_SPEED_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < VEHICLE_SPEED_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->VEHICLE_SPEED_ro = PACMOD13_VEHICLE_SPEED_ro_toS(_m->VEHICLE_SPEED_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->VEHICLE_SPEED_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->VEHICLE_SPEED_ro & (0xFFU));
  cframe->Data[2] |= (_m->VEHICLE_SPEED_VALID & (0x01U));

  cframe->MsgId = VEHICLE_SPEED_RPT_CANID;
  cframe->DLC = VEHICLE_SPEED_RPT_DLC;
  cframe->IDE = VEHICLE_SPEED_RPT_IDE;
  return VEHICLE_SPEED_RPT_CANID;
}

#else

uint32_t Pack_VEHICLE_SPEED_RPT_pacmod13(VEHICLE_SPEED_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < VEHICLE_SPEED_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->VEHICLE_SPEED_ro = PACMOD13_VEHICLE_SPEED_ro_toS(_m->VEHICLE_SPEED_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->VEHICLE_SPEED_ro >> 8) & (0xFFU));
  _d[1] |= (_m->VEHICLE_SPEED_ro & (0xFFU));
  _d[2] |= (_m->VEHICLE_SPEED_VALID & (0x01U));

  *_len = VEHICLE_SPEED_RPT_DLC;
  *_ide = VEHICLE_SPEED_RPT_IDE;
  return VEHICLE_SPEED_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_MOTOR_RPT_1_pacmod13(BRAKE_MOTOR_RPT_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MOTOR_CURRENT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 24) | ((_d[1] & (0xFFU)) << 16) | ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MOTOR_CURRENT_phys = (sigfloat_t)(PACMOD13_MOTOR_CURRENT_ro_fromS(_m->MOTOR_CURRENT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->SHAFT_POSITION_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->SHAFT_POSITION_phys = (sigfloat_t)(PACMOD13_SHAFT_POSITION_ro_fromS(_m->SHAFT_POSITION_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_MOTOR_RPT_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_MOTOR_RPT_1_pacmod13(&_m->mon1, BRAKE_MOTOR_RPT_1_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_MOTOR_RPT_1_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_MOTOR_RPT_1_pacmod13(BRAKE_MOTOR_RPT_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_1_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MOTOR_CURRENT_ro = PACMOD13_MOTOR_CURRENT_ro_toS(_m->MOTOR_CURRENT_phys);
  _m->SHAFT_POSITION_ro = PACMOD13_SHAFT_POSITION_ro_toS(_m->SHAFT_POSITION_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->MOTOR_CURRENT_ro >> 24) & (0xFFU));
  cframe->Data[1] |= ((_m->MOTOR_CURRENT_ro >> 16) & (0xFFU));
  cframe->Data[2] |= ((_m->MOTOR_CURRENT_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->MOTOR_CURRENT_ro & (0xFFU));
  cframe->Data[4] |= ((_m->SHAFT_POSITION_ro >> 24) & (0xFFU));
  cframe->Data[5] |= ((_m->SHAFT_POSITION_ro >> 16) & (0xFFU));
  cframe->Data[6] |= ((_m->SHAFT_POSITION_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->SHAFT_POSITION_ro & (0xFFU));

  cframe->MsgId = BRAKE_MOTOR_RPT_1_CANID;
  cframe->DLC = BRAKE_MOTOR_RPT_1_DLC;
  cframe->IDE = BRAKE_MOTOR_RPT_1_IDE;
  return BRAKE_MOTOR_RPT_1_CANID;
}

#else

uint32_t Pack_BRAKE_MOTOR_RPT_1_pacmod13(BRAKE_MOTOR_RPT_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_1_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MOTOR_CURRENT_ro = PACMOD13_MOTOR_CURRENT_ro_toS(_m->MOTOR_CURRENT_phys);
  _m->SHAFT_POSITION_ro = PACMOD13_SHAFT_POSITION_ro_toS(_m->SHAFT_POSITION_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->MOTOR_CURRENT_ro >> 24) & (0xFFU));
  _d[1] |= ((_m->MOTOR_CURRENT_ro >> 16) & (0xFFU));
  _d[2] |= ((_m->MOTOR_CURRENT_ro >> 8) & (0xFFU));
  _d[3] |= (_m->MOTOR_CURRENT_ro & (0xFFU));
  _d[4] |= ((_m->SHAFT_POSITION_ro >> 24) & (0xFFU));
  _d[5] |= ((_m->SHAFT_POSITION_ro >> 16) & (0xFFU));
  _d[6] |= ((_m->SHAFT_POSITION_ro >> 8) & (0xFFU));
  _d[7] |= (_m->SHAFT_POSITION_ro & (0xFFU));

  *_len = BRAKE_MOTOR_RPT_1_DLC;
  *_ide = BRAKE_MOTOR_RPT_1_IDE;
  return BRAKE_MOTOR_RPT_1_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_MOTOR_RPT_2_pacmod13(BRAKE_MOTOR_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENCODER_TEMPERATURE = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
  _m->MOTOR_TEMPERATURE = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
  _m->ANGULAR_SPEED_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ANGULAR_SPEED_phys = (sigfloat_t)(PACMOD13_ANGULAR_SPEED_ro_fromS(_m->ANGULAR_SPEED_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_MOTOR_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_MOTOR_RPT_2_pacmod13(&_m->mon1, BRAKE_MOTOR_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_MOTOR_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_MOTOR_RPT_2_pacmod13(BRAKE_MOTOR_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ANGULAR_SPEED_ro = PACMOD13_ANGULAR_SPEED_ro_toS(_m->ANGULAR_SPEED_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->ENCODER_TEMPERATURE >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->ENCODER_TEMPERATURE & (0xFFU));
  cframe->Data[2] |= ((_m->MOTOR_TEMPERATURE >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->MOTOR_TEMPERATURE & (0xFFU));
  cframe->Data[4] |= ((_m->ANGULAR_SPEED_ro >> 24) & (0xFFU));
  cframe->Data[5] |= ((_m->ANGULAR_SPEED_ro >> 16) & (0xFFU));
  cframe->Data[6] |= ((_m->ANGULAR_SPEED_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->ANGULAR_SPEED_ro & (0xFFU));

  cframe->MsgId = BRAKE_MOTOR_RPT_2_CANID;
  cframe->DLC = BRAKE_MOTOR_RPT_2_DLC;
  cframe->IDE = BRAKE_MOTOR_RPT_2_IDE;
  return BRAKE_MOTOR_RPT_2_CANID;
}

#else

uint32_t Pack_BRAKE_MOTOR_RPT_2_pacmod13(BRAKE_MOTOR_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ANGULAR_SPEED_ro = PACMOD13_ANGULAR_SPEED_ro_toS(_m->ANGULAR_SPEED_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->ENCODER_TEMPERATURE >> 8) & (0xFFU));
  _d[1] |= (_m->ENCODER_TEMPERATURE & (0xFFU));
  _d[2] |= ((_m->MOTOR_TEMPERATURE >> 8) & (0xFFU));
  _d[3] |= (_m->MOTOR_TEMPERATURE & (0xFFU));
  _d[4] |= ((_m->ANGULAR_SPEED_ro >> 24) & (0xFFU));
  _d[5] |= ((_m->ANGULAR_SPEED_ro >> 16) & (0xFFU));
  _d[6] |= ((_m->ANGULAR_SPEED_ro >> 8) & (0xFFU));
  _d[7] |= (_m->ANGULAR_SPEED_ro & (0xFFU));

  *_len = BRAKE_MOTOR_RPT_2_DLC;
  *_ide = BRAKE_MOTOR_RPT_2_IDE;
  return BRAKE_MOTOR_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_MOTOR_RPT_3_pacmod13(BRAKE_MOTOR_RPT_3_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TORQUE_OUTPUT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 24) | ((_d[1] & (0xFFU)) << 16) | ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_phys = (sigfloat_t)(PACMOD13_TORQUE_OUTPUT_ro_fromS(_m->TORQUE_OUTPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->TORQUE_INPUT_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TORQUE_INPUT_phys = (sigfloat_t)(PACMOD13_TORQUE_INPUT_ro_fromS(_m->TORQUE_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_MOTOR_RPT_3_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_MOTOR_RPT_3_pacmod13(&_m->mon1, BRAKE_MOTOR_RPT_3_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_MOTOR_RPT_3_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_MOTOR_RPT_3_pacmod13(BRAKE_MOTOR_RPT_3_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_3_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_ro = PACMOD13_TORQUE_OUTPUT_ro_toS(_m->TORQUE_OUTPUT_phys);
  _m->TORQUE_INPUT_ro = PACMOD13_TORQUE_INPUT_ro_toS(_m->TORQUE_INPUT_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->TORQUE_OUTPUT_ro >> 24) & (0xFFU));
  cframe->Data[1] |= ((_m->TORQUE_OUTPUT_ro >> 16) & (0xFFU));
  cframe->Data[2] |= ((_m->TORQUE_OUTPUT_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->TORQUE_OUTPUT_ro & (0xFFU));
  cframe->Data[4] |= ((_m->TORQUE_INPUT_ro >> 24) & (0xFFU));
  cframe->Data[5] |= ((_m->TORQUE_INPUT_ro >> 16) & (0xFFU));
  cframe->Data[6] |= ((_m->TORQUE_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->TORQUE_INPUT_ro & (0xFFU));

  cframe->MsgId = BRAKE_MOTOR_RPT_3_CANID;
  cframe->DLC = BRAKE_MOTOR_RPT_3_DLC;
  cframe->IDE = BRAKE_MOTOR_RPT_3_IDE;
  return BRAKE_MOTOR_RPT_3_CANID;
}

#else

uint32_t Pack_BRAKE_MOTOR_RPT_3_pacmod13(BRAKE_MOTOR_RPT_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_3_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_ro = PACMOD13_TORQUE_OUTPUT_ro_toS(_m->TORQUE_OUTPUT_phys);
  _m->TORQUE_INPUT_ro = PACMOD13_TORQUE_INPUT_ro_toS(_m->TORQUE_INPUT_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->TORQUE_OUTPUT_ro >> 24) & (0xFFU));
  _d[1] |= ((_m->TORQUE_OUTPUT_ro >> 16) & (0xFFU));
  _d[2] |= ((_m->TORQUE_OUTPUT_ro >> 8) & (0xFFU));
  _d[3] |= (_m->TORQUE_OUTPUT_ro & (0xFFU));
  _d[4] |= ((_m->TORQUE_INPUT_ro >> 24) & (0xFFU));
  _d[5] |= ((_m->TORQUE_INPUT_ro >> 16) & (0xFFU));
  _d[6] |= ((_m->TORQUE_INPUT_ro >> 8) & (0xFFU));
  _d[7] |= (_m->TORQUE_INPUT_ro & (0xFFU));

  *_len = BRAKE_MOTOR_RPT_3_DLC;
  *_ide = BRAKE_MOTOR_RPT_3_IDE;
  return BRAKE_MOTOR_RPT_3_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_MOTOR_RPT_1_pacmod13(STEERING_MOTOR_RPT_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MOTOR_CURRENT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 24) | ((_d[1] & (0xFFU)) << 16) | ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->MOTOR_CURRENT_phys = (sigfloat_t)(PACMOD13_MOTOR_CURRENT_ro_fromS(_m->MOTOR_CURRENT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->SHAFT_POSITION_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->SHAFT_POSITION_phys = (sigfloat_t)(PACMOD13_SHAFT_POSITION_ro_fromS(_m->SHAFT_POSITION_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_MOTOR_RPT_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_MOTOR_RPT_1_pacmod13(&_m->mon1, STEERING_MOTOR_RPT_1_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_MOTOR_RPT_1_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_MOTOR_RPT_1_pacmod13(STEERING_MOTOR_RPT_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_1_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MOTOR_CURRENT_ro = PACMOD13_MOTOR_CURRENT_ro_toS(_m->MOTOR_CURRENT_phys);
  _m->SHAFT_POSITION_ro = PACMOD13_SHAFT_POSITION_ro_toS(_m->SHAFT_POSITION_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->MOTOR_CURRENT_ro >> 24) & (0xFFU));
  cframe->Data[1] |= ((_m->MOTOR_CURRENT_ro >> 16) & (0xFFU));
  cframe->Data[2] |= ((_m->MOTOR_CURRENT_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->MOTOR_CURRENT_ro & (0xFFU));
  cframe->Data[4] |= ((_m->SHAFT_POSITION_ro >> 24) & (0xFFU));
  cframe->Data[5] |= ((_m->SHAFT_POSITION_ro >> 16) & (0xFFU));
  cframe->Data[6] |= ((_m->SHAFT_POSITION_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->SHAFT_POSITION_ro & (0xFFU));

  cframe->MsgId = STEERING_MOTOR_RPT_1_CANID;
  cframe->DLC = STEERING_MOTOR_RPT_1_DLC;
  cframe->IDE = STEERING_MOTOR_RPT_1_IDE;
  return STEERING_MOTOR_RPT_1_CANID;
}

#else

uint32_t Pack_STEERING_MOTOR_RPT_1_pacmod13(STEERING_MOTOR_RPT_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_1_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->MOTOR_CURRENT_ro = PACMOD13_MOTOR_CURRENT_ro_toS(_m->MOTOR_CURRENT_phys);
  _m->SHAFT_POSITION_ro = PACMOD13_SHAFT_POSITION_ro_toS(_m->SHAFT_POSITION_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->MOTOR_CURRENT_ro >> 24) & (0xFFU));
  _d[1] |= ((_m->MOTOR_CURRENT_ro >> 16) & (0xFFU));
  _d[2] |= ((_m->MOTOR_CURRENT_ro >> 8) & (0xFFU));
  _d[3] |= (_m->MOTOR_CURRENT_ro & (0xFFU));
  _d[4] |= ((_m->SHAFT_POSITION_ro >> 24) & (0xFFU));
  _d[5] |= ((_m->SHAFT_POSITION_ro >> 16) & (0xFFU));
  _d[6] |= ((_m->SHAFT_POSITION_ro >> 8) & (0xFFU));
  _d[7] |= (_m->SHAFT_POSITION_ro & (0xFFU));

  *_len = STEERING_MOTOR_RPT_1_DLC;
  *_ide = STEERING_MOTOR_RPT_1_IDE;
  return STEERING_MOTOR_RPT_1_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_MOTOR_RPT_2_pacmod13(STEERING_MOTOR_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENCODER_TEMPERATURE = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
  _m->MOTOR_TEMPERATURE = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
  _m->ANGULAR_SPEED_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ANGULAR_SPEED_phys = (sigfloat_t)(PACMOD13_ANGULAR_SPEED_ro_fromS(_m->ANGULAR_SPEED_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_MOTOR_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_MOTOR_RPT_2_pacmod13(&_m->mon1, STEERING_MOTOR_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_MOTOR_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_MOTOR_RPT_2_pacmod13(STEERING_MOTOR_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ANGULAR_SPEED_ro = PACMOD13_ANGULAR_SPEED_ro_toS(_m->ANGULAR_SPEED_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->ENCODER_TEMPERATURE >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->ENCODER_TEMPERATURE & (0xFFU));
  cframe->Data[2] |= ((_m->MOTOR_TEMPERATURE >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->MOTOR_TEMPERATURE & (0xFFU));
  cframe->Data[4] |= ((_m->ANGULAR_SPEED_ro >> 24) & (0xFFU));
  cframe->Data[5] |= ((_m->ANGULAR_SPEED_ro >> 16) & (0xFFU));
  cframe->Data[6] |= ((_m->ANGULAR_SPEED_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->ANGULAR_SPEED_ro & (0xFFU));

  cframe->MsgId = STEERING_MOTOR_RPT_2_CANID;
  cframe->DLC = STEERING_MOTOR_RPT_2_DLC;
  cframe->IDE = STEERING_MOTOR_RPT_2_IDE;
  return STEERING_MOTOR_RPT_2_CANID;
}

#else

uint32_t Pack_STEERING_MOTOR_RPT_2_pacmod13(STEERING_MOTOR_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ANGULAR_SPEED_ro = PACMOD13_ANGULAR_SPEED_ro_toS(_m->ANGULAR_SPEED_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->ENCODER_TEMPERATURE >> 8) & (0xFFU));
  _d[1] |= (_m->ENCODER_TEMPERATURE & (0xFFU));
  _d[2] |= ((_m->MOTOR_TEMPERATURE >> 8) & (0xFFU));
  _d[3] |= (_m->MOTOR_TEMPERATURE & (0xFFU));
  _d[4] |= ((_m->ANGULAR_SPEED_ro >> 24) & (0xFFU));
  _d[5] |= ((_m->ANGULAR_SPEED_ro >> 16) & (0xFFU));
  _d[6] |= ((_m->ANGULAR_SPEED_ro >> 8) & (0xFFU));
  _d[7] |= (_m->ANGULAR_SPEED_ro & (0xFFU));

  *_len = STEERING_MOTOR_RPT_2_DLC;
  *_ide = STEERING_MOTOR_RPT_2_IDE;
  return STEERING_MOTOR_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_MOTOR_RPT_3_pacmod13(STEERING_MOTOR_RPT_3_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TORQUE_OUTPUT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 24) | ((_d[1] & (0xFFU)) << 16) | ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_phys = (sigfloat_t)(PACMOD13_TORQUE_OUTPUT_ro_fromS(_m->TORQUE_OUTPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->TORQUE_INPUT_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TORQUE_INPUT_phys = (sigfloat_t)(PACMOD13_TORQUE_INPUT_ro_fromS(_m->TORQUE_INPUT_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_MOTOR_RPT_3_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_MOTOR_RPT_3_pacmod13(&_m->mon1, STEERING_MOTOR_RPT_3_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_MOTOR_RPT_3_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_MOTOR_RPT_3_pacmod13(STEERING_MOTOR_RPT_3_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_3_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_ro = PACMOD13_TORQUE_OUTPUT_ro_toS(_m->TORQUE_OUTPUT_phys);
  _m->TORQUE_INPUT_ro = PACMOD13_TORQUE_INPUT_ro_toS(_m->TORQUE_INPUT_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->TORQUE_OUTPUT_ro >> 24) & (0xFFU));
  cframe->Data[1] |= ((_m->TORQUE_OUTPUT_ro >> 16) & (0xFFU));
  cframe->Data[2] |= ((_m->TORQUE_OUTPUT_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->TORQUE_OUTPUT_ro & (0xFFU));
  cframe->Data[4] |= ((_m->TORQUE_INPUT_ro >> 24) & (0xFFU));
  cframe->Data[5] |= ((_m->TORQUE_INPUT_ro >> 16) & (0xFFU));
  cframe->Data[6] |= ((_m->TORQUE_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->TORQUE_INPUT_ro & (0xFFU));

  cframe->MsgId = STEERING_MOTOR_RPT_3_CANID;
  cframe->DLC = STEERING_MOTOR_RPT_3_DLC;
  cframe->IDE = STEERING_MOTOR_RPT_3_IDE;
  return STEERING_MOTOR_RPT_3_CANID;
}

#else

uint32_t Pack_STEERING_MOTOR_RPT_3_pacmod13(STEERING_MOTOR_RPT_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_3_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_ro = PACMOD13_TORQUE_OUTPUT_ro_toS(_m->TORQUE_OUTPUT_phys);
  _m->TORQUE_INPUT_ro = PACMOD13_TORQUE_INPUT_ro_toS(_m->TORQUE_INPUT_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->TORQUE_OUTPUT_ro >> 24) & (0xFFU));
  _d[1] |= ((_m->TORQUE_OUTPUT_ro >> 16) & (0xFFU));
  _d[2] |= ((_m->TORQUE_OUTPUT_ro >> 8) & (0xFFU));
  _d[3] |= (_m->TORQUE_OUTPUT_ro & (0xFFU));
  _d[4] |= ((_m->TORQUE_INPUT_ro >> 24) & (0xFFU));
  _d[5] |= ((_m->TORQUE_INPUT_ro >> 16) & (0xFFU));
  _d[6] |= ((_m->TORQUE_INPUT_ro >> 8) & (0xFFU));
  _d[7] |= (_m->TORQUE_INPUT_ro & (0xFFU));

  *_len = STEERING_MOTOR_RPT_3_DLC;
  *_ide = STEERING_MOTOR_RPT_3_IDE;
  return STEERING_MOTOR_RPT_3_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_WHEEL_SPEED_RPT_pacmod13(WHEEL_SPEED_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->WHEEL_SPD_AXLE_1_LEFT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_1_LEFT_phys = (sigfloat_t)(PACMOD13_WHEEL_SPD_AXLE_1_LEFT_ro_fromS(_m->WHEEL_SPD_AXLE_1_LEFT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->WHEEL_SPD_AXLE_1_RIGHT_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_1_RIGHT_phys = (sigfloat_t)(PACMOD13_WHEEL_SPD_AXLE_1_RIGHT_ro_fromS(_m->WHEEL_SPD_AXLE_1_RIGHT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->WHEEL_SPD_AXLE_2_LEFT_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_2_LEFT_phys = (sigfloat_t)(PACMOD13_WHEEL_SPD_AXLE_2_LEFT_ro_fromS(_m->WHEEL_SPD_AXLE_2_LEFT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->WHEEL_SPD_AXLE_2_RIGHT_ro = __ext_sig__(( ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_2_RIGHT_phys = (sigfloat_t)(PACMOD13_WHEEL_SPD_AXLE_2_RIGHT_ro_fromS(_m->WHEEL_SPD_AXLE_2_RIGHT_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WHEEL_SPEED_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WHEEL_SPEED_RPT_pacmod13(&_m->mon1, WHEEL_SPEED_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return WHEEL_SPEED_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_WHEEL_SPEED_RPT_pacmod13(WHEEL_SPEED_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < WHEEL_SPEED_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_1_LEFT_ro = PACMOD13_WHEEL_SPD_AXLE_1_LEFT_ro_toS(_m->WHEEL_SPD_AXLE_1_LEFT_phys);
  _m->WHEEL_SPD_AXLE_1_RIGHT_ro = PACMOD13_WHEEL_SPD_AXLE_1_RIGHT_ro_toS(_m->WHEEL_SPD_AXLE_1_RIGHT_phys);
  _m->WHEEL_SPD_AXLE_2_LEFT_ro = PACMOD13_WHEEL_SPD_AXLE_2_LEFT_ro_toS(_m->WHEEL_SPD_AXLE_2_LEFT_phys);
  _m->WHEEL_SPD_AXLE_2_RIGHT_ro = PACMOD13_WHEEL_SPD_AXLE_2_RIGHT_ro_toS(_m->WHEEL_SPD_AXLE_2_RIGHT_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->WHEEL_SPD_AXLE_1_LEFT_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->WHEEL_SPD_AXLE_1_LEFT_ro & (0xFFU));
  cframe->Data[2] |= ((_m->WHEEL_SPD_AXLE_1_RIGHT_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->WHEEL_SPD_AXLE_1_RIGHT_ro & (0xFFU));
  cframe->Data[4] |= ((_m->WHEEL_SPD_AXLE_2_LEFT_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->WHEEL_SPD_AXLE_2_LEFT_ro & (0xFFU));
  cframe->Data[6] |= ((_m->WHEEL_SPD_AXLE_2_RIGHT_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->WHEEL_SPD_AXLE_2_RIGHT_ro & (0xFFU));

  cframe->MsgId = WHEEL_SPEED_RPT_CANID;
  cframe->DLC = WHEEL_SPEED_RPT_DLC;
  cframe->IDE = WHEEL_SPEED_RPT_IDE;
  return WHEEL_SPEED_RPT_CANID;
}

#else

uint32_t Pack_WHEEL_SPEED_RPT_pacmod13(WHEEL_SPEED_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WHEEL_SPEED_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_1_LEFT_ro = PACMOD13_WHEEL_SPD_AXLE_1_LEFT_ro_toS(_m->WHEEL_SPD_AXLE_1_LEFT_phys);
  _m->WHEEL_SPD_AXLE_1_RIGHT_ro = PACMOD13_WHEEL_SPD_AXLE_1_RIGHT_ro_toS(_m->WHEEL_SPD_AXLE_1_RIGHT_phys);
  _m->WHEEL_SPD_AXLE_2_LEFT_ro = PACMOD13_WHEEL_SPD_AXLE_2_LEFT_ro_toS(_m->WHEEL_SPD_AXLE_2_LEFT_phys);
  _m->WHEEL_SPD_AXLE_2_RIGHT_ro = PACMOD13_WHEEL_SPD_AXLE_2_RIGHT_ro_toS(_m->WHEEL_SPD_AXLE_2_RIGHT_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->WHEEL_SPD_AXLE_1_LEFT_ro >> 8) & (0xFFU));
  _d[1] |= (_m->WHEEL_SPD_AXLE_1_LEFT_ro & (0xFFU));
  _d[2] |= ((_m->WHEEL_SPD_AXLE_1_RIGHT_ro >> 8) & (0xFFU));
  _d[3] |= (_m->WHEEL_SPD_AXLE_1_RIGHT_ro & (0xFFU));
  _d[4] |= ((_m->WHEEL_SPD_AXLE_2_LEFT_ro >> 8) & (0xFFU));
  _d[5] |= (_m->WHEEL_SPD_AXLE_2_LEFT_ro & (0xFFU));
  _d[6] |= ((_m->WHEEL_SPD_AXLE_2_RIGHT_ro >> 8) & (0xFFU));
  _d[7] |= (_m->WHEEL_SPD_AXLE_2_RIGHT_ro & (0xFFU));

  *_len = WHEEL_SPEED_RPT_DLC;
  *_ide = WHEEL_SPEED_RPT_IDE;
  return WHEEL_SPEED_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_00_pacmod13(SOFTWARE_VERSION_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_00_pacmod13(&_m->mon1, SOFTWARE_VERSION_RPT_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_00_pacmod13(SOFTWARE_VERSION_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->MAJOR & (0xFFU));
  cframe->Data[1] |= (_m->MINOR & (0xFFU));
  cframe->Data[2] |= (_m->PATCH & (0xFFU));
  cframe->Data[3] |= (_m->BUILD0 & (0xFFU));
  cframe->Data[4] |= (_m->BUILD1 & (0xFFU));
  cframe->Data[5] |= (_m->BUILD2 & (0xFFU));
  cframe->Data[6] |= (_m->BUILD3 & (0xFFU));

  cframe->MsgId = SOFTWARE_VERSION_RPT_00_CANID;
  cframe->DLC = SOFTWARE_VERSION_RPT_00_DLC;
  cframe->IDE = SOFTWARE_VERSION_RPT_00_IDE;
  return SOFTWARE_VERSION_RPT_00_CANID;
}

#else

uint32_t Pack_SOFTWARE_VERSION_RPT_00_pacmod13(SOFTWARE_VERSION_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_00_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->MAJOR & (0xFFU));
  _d[1] |= (_m->MINOR & (0xFFU));
  _d[2] |= (_m->PATCH & (0xFFU));
  _d[3] |= (_m->BUILD0 & (0xFFU));
  _d[4] |= (_m->BUILD1 & (0xFFU));
  _d[5] |= (_m->BUILD2 & (0xFFU));
  _d[6] |= (_m->BUILD3 & (0xFFU));

  *_len = SOFTWARE_VERSION_RPT_00_DLC;
  *_ide = SOFTWARE_VERSION_RPT_00_IDE;
  return SOFTWARE_VERSION_RPT_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_01_pacmod13(SOFTWARE_VERSION_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_01_pacmod13(&_m->mon1, SOFTWARE_VERSION_RPT_01_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_01_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_01_pacmod13(SOFTWARE_VERSION_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_01_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->MAJOR & (0xFFU));
  cframe->Data[1] |= (_m->MINOR & (0xFFU));
  cframe->Data[2] |= (_m->PATCH & (0xFFU));
  cframe->Data[3] |= (_m->BUILD0 & (0xFFU));
  cframe->Data[4] |= (_m->BUILD1 & (0xFFU));
  cframe->Data[5] |= (_m->BUILD2 & (0xFFU));
  cframe->Data[6] |= (_m->BUILD3 & (0xFFU));

  cframe->MsgId = SOFTWARE_VERSION_RPT_01_CANID;
  cframe->DLC = SOFTWARE_VERSION_RPT_01_DLC;
  cframe->IDE = SOFTWARE_VERSION_RPT_01_IDE;
  return SOFTWARE_VERSION_RPT_01_CANID;
}

#else

uint32_t Pack_SOFTWARE_VERSION_RPT_01_pacmod13(SOFTWARE_VERSION_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_01_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->MAJOR & (0xFFU));
  _d[1] |= (_m->MINOR & (0xFFU));
  _d[2] |= (_m->PATCH & (0xFFU));
  _d[3] |= (_m->BUILD0 & (0xFFU));
  _d[4] |= (_m->BUILD1 & (0xFFU));
  _d[5] |= (_m->BUILD2 & (0xFFU));
  _d[6] |= (_m->BUILD3 & (0xFFU));

  *_len = SOFTWARE_VERSION_RPT_01_DLC;
  *_ide = SOFTWARE_VERSION_RPT_01_IDE;
  return SOFTWARE_VERSION_RPT_01_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_02_pacmod13(SOFTWARE_VERSION_RPT_02_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_02_pacmod13(&_m->mon1, SOFTWARE_VERSION_RPT_02_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_02_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_02_pacmod13(SOFTWARE_VERSION_RPT_02_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_02_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->MAJOR & (0xFFU));
  cframe->Data[1] |= (_m->MINOR & (0xFFU));
  cframe->Data[2] |= (_m->PATCH & (0xFFU));
  cframe->Data[3] |= (_m->BUILD0 & (0xFFU));
  cframe->Data[4] |= (_m->BUILD1 & (0xFFU));
  cframe->Data[5] |= (_m->BUILD2 & (0xFFU));
  cframe->Data[6] |= (_m->BUILD3 & (0xFFU));

  cframe->MsgId = SOFTWARE_VERSION_RPT_02_CANID;
  cframe->DLC = SOFTWARE_VERSION_RPT_02_DLC;
  cframe->IDE = SOFTWARE_VERSION_RPT_02_IDE;
  return SOFTWARE_VERSION_RPT_02_CANID;
}

#else

uint32_t Pack_SOFTWARE_VERSION_RPT_02_pacmod13(SOFTWARE_VERSION_RPT_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_02_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->MAJOR & (0xFFU));
  _d[1] |= (_m->MINOR & (0xFFU));
  _d[2] |= (_m->PATCH & (0xFFU));
  _d[3] |= (_m->BUILD0 & (0xFFU));
  _d[4] |= (_m->BUILD1 & (0xFFU));
  _d[5] |= (_m->BUILD2 & (0xFFU));
  _d[6] |= (_m->BUILD3 & (0xFFU));

  *_len = SOFTWARE_VERSION_RPT_02_DLC;
  *_ide = SOFTWARE_VERSION_RPT_02_IDE;
  return SOFTWARE_VERSION_RPT_02_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_03_pacmod13(SOFTWARE_VERSION_RPT_03_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_03_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_03_pacmod13(&_m->mon1, SOFTWARE_VERSION_RPT_03_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_03_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_03_pacmod13(SOFTWARE_VERSION_RPT_03_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_03_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->MAJOR & (0xFFU));
  cframe->Data[1] |= (_m->MINOR & (0xFFU));
  cframe->Data[2] |= (_m->PATCH & (0xFFU));
  cframe->Data[3] |= (_m->BUILD0 & (0xFFU));
  cframe->Data[4] |= (_m->BUILD1 & (0xFFU));
  cframe->Data[5] |= (_m->BUILD2 & (0xFFU));
  cframe->Data[6] |= (_m->BUILD3 & (0xFFU));

  cframe->MsgId = SOFTWARE_VERSION_RPT_03_CANID;
  cframe->DLC = SOFTWARE_VERSION_RPT_03_DLC;
  cframe->IDE = SOFTWARE_VERSION_RPT_03_IDE;
  return SOFTWARE_VERSION_RPT_03_CANID;
}

#else

uint32_t Pack_SOFTWARE_VERSION_RPT_03_pacmod13(SOFTWARE_VERSION_RPT_03_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_03_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->MAJOR & (0xFFU));
  _d[1] |= (_m->MINOR & (0xFFU));
  _d[2] |= (_m->PATCH & (0xFFU));
  _d[3] |= (_m->BUILD0 & (0xFFU));
  _d[4] |= (_m->BUILD1 & (0xFFU));
  _d[5] |= (_m->BUILD2 & (0xFFU));
  _d[6] |= (_m->BUILD3 & (0xFFU));

  *_len = SOFTWARE_VERSION_RPT_03_DLC;
  *_ide = SOFTWARE_VERSION_RPT_03_IDE;
  return SOFTWARE_VERSION_RPT_03_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_04_pacmod13(SOFTWARE_VERSION_RPT_04_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_04_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_04_pacmod13(&_m->mon1, SOFTWARE_VERSION_RPT_04_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_04_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_04_pacmod13(SOFTWARE_VERSION_RPT_04_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_04_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->MAJOR & (0xFFU));
  cframe->Data[1] |= (_m->MINOR & (0xFFU));
  cframe->Data[2] |= (_m->PATCH & (0xFFU));
  cframe->Data[3] |= (_m->BUILD0 & (0xFFU));
  cframe->Data[4] |= (_m->BUILD1 & (0xFFU));
  cframe->Data[5] |= (_m->BUILD2 & (0xFFU));
  cframe->Data[6] |= (_m->BUILD3 & (0xFFU));

  cframe->MsgId = SOFTWARE_VERSION_RPT_04_CANID;
  cframe->DLC = SOFTWARE_VERSION_RPT_04_DLC;
  cframe->IDE = SOFTWARE_VERSION_RPT_04_IDE;
  return SOFTWARE_VERSION_RPT_04_CANID;
}

#else

uint32_t Pack_SOFTWARE_VERSION_RPT_04_pacmod13(SOFTWARE_VERSION_RPT_04_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_04_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->MAJOR & (0xFFU));
  _d[1] |= (_m->MINOR & (0xFFU));
  _d[2] |= (_m->PATCH & (0xFFU));
  _d[3] |= (_m->BUILD0 & (0xFFU));
  _d[4] |= (_m->BUILD1 & (0xFFU));
  _d[5] |= (_m->BUILD2 & (0xFFU));
  _d[6] |= (_m->BUILD3 & (0xFFU));

  *_len = SOFTWARE_VERSION_RPT_04_DLC;
  *_ide = SOFTWARE_VERSION_RPT_04_IDE;
  return SOFTWARE_VERSION_RPT_04_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_YAW_RATE_RPT_pacmod13(YAW_RATE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->YAW_RATE_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->YAW_RATE_phys = (sigfloat_t)(PACMOD13_YAW_RATE_ro_fromS(_m->YAW_RATE_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < YAW_RATE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_YAW_RATE_RPT_pacmod13(&_m->mon1, YAW_RATE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return YAW_RATE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_YAW_RATE_RPT_pacmod13(YAW_RATE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < YAW_RATE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->YAW_RATE_ro = PACMOD13_YAW_RATE_ro_toS(_m->YAW_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->YAW_RATE_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->YAW_RATE_ro & (0xFFU));

  cframe->MsgId = YAW_RATE_RPT_CANID;
  cframe->DLC = YAW_RATE_RPT_DLC;
  cframe->IDE = YAW_RATE_RPT_IDE;
  return YAW_RATE_RPT_CANID;
}

#else

uint32_t Pack_YAW_RATE_RPT_pacmod13(YAW_RATE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < YAW_RATE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->YAW_RATE_ro = PACMOD13_YAW_RATE_ro_toS(_m->YAW_RATE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->YAW_RATE_ro >> 8) & (0xFFU));
  _d[1] |= (_m->YAW_RATE_ro & (0xFFU));

  *_len = YAW_RATE_RPT_DLC;
  *_ide = YAW_RATE_RPT_IDE;
  return YAW_RATE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_LAT_LON_HEADING_RPT_pacmod13(LAT_LON_HEADING_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->LATITUDE_DEGREES = __ext_sig__(( (_d[0] & (0xFFU)) ), 8);
  _m->LATITUDE_MINUTES = __ext_sig__(( (_d[1] & (0xFFU)) ), 8);
  _m->LATITUDE_SECONDS = __ext_sig__(( (_d[2] & (0xFFU)) ), 8);
  _m->LONGITUDE_DEGREES = __ext_sig__(( (_d[3] & (0xFFU)) ), 8);
  _m->LONGITUDE_MINUTES = __ext_sig__(( (_d[4] & (0xFFU)) ), 8);
  _m->LONGITUDE_SECONDS = __ext_sig__(( (_d[5] & (0xFFU)) ), 8);
  _m->HEADING_ro = __ext_sig__(( ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->HEADING_phys = (sigfloat_t)(PACMOD13_HEADING_ro_fromS(_m->HEADING_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < LAT_LON_HEADING_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_LAT_LON_HEADING_RPT_pacmod13(&_m->mon1, LAT_LON_HEADING_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return LAT_LON_HEADING_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_LAT_LON_HEADING_RPT_pacmod13(LAT_LON_HEADING_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < LAT_LON_HEADING_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->HEADING_ro = PACMOD13_HEADING_ro_toS(_m->HEADING_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->LATITUDE_DEGREES & (0xFFU));
  cframe->Data[1] |= (_m->LATITUDE_MINUTES & (0xFFU));
  cframe->Data[2] |= (_m->LATITUDE_SECONDS & (0xFFU));
  cframe->Data[3] |= (_m->LONGITUDE_DEGREES & (0xFFU));
  cframe->Data[4] |= (_m->LONGITUDE_MINUTES & (0xFFU));
  cframe->Data[5] |= (_m->LONGITUDE_SECONDS & (0xFFU));
  cframe->Data[6] |= ((_m->HEADING_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->HEADING_ro & (0xFFU));

  cframe->MsgId = LAT_LON_HEADING_RPT_CANID;
  cframe->DLC = LAT_LON_HEADING_RPT_DLC;
  cframe->IDE = LAT_LON_HEADING_RPT_IDE;
  return LAT_LON_HEADING_RPT_CANID;
}

#else

uint32_t Pack_LAT_LON_HEADING_RPT_pacmod13(LAT_LON_HEADING_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < LAT_LON_HEADING_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->HEADING_ro = PACMOD13_HEADING_ro_toS(_m->HEADING_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->LATITUDE_DEGREES & (0xFFU));
  _d[1] |= (_m->LATITUDE_MINUTES & (0xFFU));
  _d[2] |= (_m->LATITUDE_SECONDS & (0xFFU));
  _d[3] |= (_m->LONGITUDE_DEGREES & (0xFFU));
  _d[4] |= (_m->LONGITUDE_MINUTES & (0xFFU));
  _d[5] |= (_m->LONGITUDE_SECONDS & (0xFFU));
  _d[6] |= ((_m->HEADING_ro >> 8) & (0xFFU));
  _d[7] |= (_m->HEADING_ro & (0xFFU));

  *_len = LAT_LON_HEADING_RPT_DLC;
  *_ide = LAT_LON_HEADING_RPT_IDE;
  return LAT_LON_HEADING_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DATE_TIME_RPT_pacmod13(DATE_TIME_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DATE_YEAR_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->DATE_YEAR_phys = PACMOD13_DATE_YEAR_ro_fromS(_m->DATE_YEAR_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->DATE_MONTH_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->DATE_MONTH_phys = PACMOD13_DATE_MONTH_ro_fromS(_m->DATE_MONTH_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->DATE_DAY_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->DATE_DAY_phys = PACMOD13_DATE_DAY_ro_fromS(_m->DATE_DAY_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TIME_HOUR = (_d[3] & (0xFFU));
  _m->TIME_MINUTE = (_d[4] & (0xFFU));
  _m->TIME_SECOND = (_d[5] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DATE_TIME_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DATE_TIME_RPT_pacmod13(&_m->mon1, DATE_TIME_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DATE_TIME_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DATE_TIME_RPT_pacmod13(DATE_TIME_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DATE_TIME_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->DATE_YEAR_ro = PACMOD13_DATE_YEAR_ro_toS(_m->DATE_YEAR_phys);
  _m->DATE_MONTH_ro = PACMOD13_DATE_MONTH_ro_toS(_m->DATE_MONTH_phys);
  _m->DATE_DAY_ro = PACMOD13_DATE_DAY_ro_toS(_m->DATE_DAY_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->DATE_YEAR_ro & (0xFFU));
  cframe->Data[1] |= (_m->DATE_MONTH_ro & (0xFFU));
  cframe->Data[2] |= (_m->DATE_DAY_ro & (0xFFU));
  cframe->Data[3] |= (_m->TIME_HOUR & (0xFFU));
  cframe->Data[4] |= (_m->TIME_MINUTE & (0xFFU));
  cframe->Data[5] |= (_m->TIME_SECOND & (0xFFU));

  cframe->MsgId = DATE_TIME_RPT_CANID;
  cframe->DLC = DATE_TIME_RPT_DLC;
  cframe->IDE = DATE_TIME_RPT_IDE;
  return DATE_TIME_RPT_CANID;
}

#else

uint32_t Pack_DATE_TIME_RPT_pacmod13(DATE_TIME_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DATE_TIME_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->DATE_YEAR_ro = PACMOD13_DATE_YEAR_ro_toS(_m->DATE_YEAR_phys);
  _m->DATE_MONTH_ro = PACMOD13_DATE_MONTH_ro_toS(_m->DATE_MONTH_phys);
  _m->DATE_DAY_ro = PACMOD13_DATE_DAY_ro_toS(_m->DATE_DAY_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->DATE_YEAR_ro & (0xFFU));
  _d[1] |= (_m->DATE_MONTH_ro & (0xFFU));
  _d[2] |= (_m->DATE_DAY_ro & (0xFFU));
  _d[3] |= (_m->TIME_HOUR & (0xFFU));
  _d[4] |= (_m->TIME_MINUTE & (0xFFU));
  _d[5] |= (_m->TIME_SECOND & (0xFFU));

  *_len = DATE_TIME_RPT_DLC;
  *_ide = DATE_TIME_RPT_IDE;
  return DATE_TIME_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ENGINE_AUX_RPT_pacmod13(ENGINE_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENGINE_SPEED_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ENGINE_SPEED_phys = (sigfloat_t)(PACMOD13_ENGINE_SPEED_ro_fromS(_m->ENGINE_SPEED_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->ENGINE_TORQUE_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ENGINE_TORQUE_phys = (sigfloat_t)(PACMOD13_ENGINE_TORQUE_ro_fromS(_m->ENGINE_TORQUE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->ENGINE_COOLANT_TEMP_ro = (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ENGINE_COOLANT_TEMP_phys = PACMOD13_ENGINE_COOLANT_TEMP_ro_fromS(_m->ENGINE_COOLANT_TEMP_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->ENGINE_SPEED_AVAIL = (_d[5] & (0x01U));
  _m->ENGINE_TORQUE_AVAIL = ((_d[5] >> 1) & (0x01U));
  _m->ENGINE_COOLANT_TEMP_AVAIL = ((_d[5] >> 2) & (0x01U));
  _m->FUEL_LEVEL_AVAIL = ((_d[5] >> 3) & (0x01U));
  _m->DIESEL_EXHAUST_FLUID_LEVEL_AVAIL = ((_d[5] >> 4) & (0x01U));
  _m->FUEL_LEVEL_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->FUEL_LEVEL_phys = (sigfloat_t)(PACMOD13_FUEL_LEVEL_ro_fromS(_m->FUEL_LEVEL_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->DIESEL_EXHAUST_FLUID_LEVEL_ro = (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->DIESEL_EXHAUST_FLUID_LEVEL_phys = (sigfloat_t)(PACMOD13_DIESEL_EXHAUST_FLUID_LEVEL_ro_fromS(_m->DIESEL_EXHAUST_FLUID_LEVEL_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ENGINE_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ENGINE_AUX_RPT_pacmod13(&_m->mon1, ENGINE_AUX_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ENGINE_AUX_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ENGINE_AUX_RPT_pacmod13(ENGINE_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ENGINE_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ENGINE_SPEED_ro = PACMOD13_ENGINE_SPEED_ro_toS(_m->ENGINE_SPEED_phys);
  _m->ENGINE_TORQUE_ro = PACMOD13_ENGINE_TORQUE_ro_toS(_m->ENGINE_TORQUE_phys);
  _m->ENGINE_COOLANT_TEMP_ro = PACMOD13_ENGINE_COOLANT_TEMP_ro_toS(_m->ENGINE_COOLANT_TEMP_phys);
  _m->FUEL_LEVEL_ro = PACMOD13_FUEL_LEVEL_ro_toS(_m->FUEL_LEVEL_phys);
  _m->DIESEL_EXHAUST_FLUID_LEVEL_ro = PACMOD13_DIESEL_EXHAUST_FLUID_LEVEL_ro_toS(_m->DIESEL_EXHAUST_FLUID_LEVEL_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->ENGINE_SPEED_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->ENGINE_SPEED_ro & (0xFFU));
  cframe->Data[2] |= ((_m->ENGINE_TORQUE_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->ENGINE_TORQUE_ro & (0xFFU));
  cframe->Data[4] |= (_m->ENGINE_COOLANT_TEMP_ro & (0xFFU));
  cframe->Data[5] |= (_m->ENGINE_SPEED_AVAIL & (0x01U)) | ((_m->ENGINE_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ENGINE_COOLANT_TEMP_AVAIL & (0x01U)) << 2) | ((_m->FUEL_LEVEL_AVAIL & (0x01U)) << 3) | ((_m->DIESEL_EXHAUST_FLUID_LEVEL_AVAIL & (0x01U)) << 4);
  cframe->Data[6] |= (_m->FUEL_LEVEL_ro & (0xFFU));
  cframe->Data[7] |= (_m->DIESEL_EXHAUST_FLUID_LEVEL_ro & (0xFFU));

  cframe->MsgId = ENGINE_AUX_RPT_CANID;
  cframe->DLC = ENGINE_AUX_RPT_DLC;
  cframe->IDE = ENGINE_AUX_RPT_IDE;
  return ENGINE_AUX_RPT_CANID;
}

#else

uint32_t Pack_ENGINE_AUX_RPT_pacmod13(ENGINE_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ENGINE_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->ENGINE_SPEED_ro = PACMOD13_ENGINE_SPEED_ro_toS(_m->ENGINE_SPEED_phys);
  _m->ENGINE_TORQUE_ro = PACMOD13_ENGINE_TORQUE_ro_toS(_m->ENGINE_TORQUE_phys);
  _m->ENGINE_COOLANT_TEMP_ro = PACMOD13_ENGINE_COOLANT_TEMP_ro_toS(_m->ENGINE_COOLANT_TEMP_phys);
  _m->FUEL_LEVEL_ro = PACMOD13_FUEL_LEVEL_ro_toS(_m->FUEL_LEVEL_phys);
  _m->DIESEL_EXHAUST_FLUID_LEVEL_ro = PACMOD13_DIESEL_EXHAUST_FLUID_LEVEL_ro_toS(_m->DIESEL_EXHAUST_FLUID_LEVEL_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->ENGINE_SPEED_ro >> 8) & (0xFFU));
  _d[1] |= (_m->ENGINE_SPEED_ro & (0xFFU));
  _d[2] |= ((_m->ENGINE_TORQUE_ro >> 8) & (0xFFU));
  _d[3] |= (_m->ENGINE_TORQUE_ro & (0xFFU));
  _d[4] |= (_m->ENGINE_COOLANT_TEMP_ro & (0xFFU));
  _d[5] |= (_m->ENGINE_SPEED_AVAIL & (0x01U)) | ((_m->ENGINE_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ENGINE_COOLANT_TEMP_AVAIL & (0x01U)) << 2) | ((_m->FUEL_LEVEL_AVAIL & (0x01U)) << 3) | ((_m->DIESEL_EXHAUST_FLUID_LEVEL_AVAIL & (0x01U)) << 4);
  _d[6] |= (_m->FUEL_LEVEL_ro & (0xFFU));
  _d[7] |= (_m->DIESEL_EXHAUST_FLUID_LEVEL_ro & (0xFFU));

  *_len = ENGINE_AUX_RPT_DLC;
  *_ide = ENGINE_AUX_RPT_IDE;
  return ENGINE_AUX_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DETECTED_OBJECT_RPT_pacmod13(DETECTED_OBJECT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->FRONT_OBJECT_DISTANCE_LOW_RES_ro = ((_d[0] & (0xFFU)) << 16) | ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->FRONT_OBJECT_DISTANCE_LOW_RES_phys = (sigfloat_t)(PACMOD13_FRONT_OBJECT_DISTANCE_LOW_RES_ro_fromS(_m->FRONT_OBJECT_DISTANCE_LOW_RES_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro = ((_d[3] & (0xFFU)) << 16) | ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->FRONT_OBJECT_DISTANCE_HIGH_RES_phys = (sigfloat_t)(PACMOD13_FRONT_OBJECT_DISTANCE_HIGH_RES_ro_fromS(_m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DETECTED_OBJECT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DETECTED_OBJECT_RPT_pacmod13(&_m->mon1, DETECTED_OBJECT_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DETECTED_OBJECT_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DETECTED_OBJECT_RPT_pacmod13(DETECTED_OBJECT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DETECTED_OBJECT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->FRONT_OBJECT_DISTANCE_LOW_RES_ro = PACMOD13_FRONT_OBJECT_DISTANCE_LOW_RES_ro_toS(_m->FRONT_OBJECT_DISTANCE_LOW_RES_phys);
  _m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro = PACMOD13_FRONT_OBJECT_DISTANCE_HIGH_RES_ro_toS(_m->FRONT_OBJECT_DISTANCE_HIGH_RES_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->FRONT_OBJECT_DISTANCE_LOW_RES_ro >> 16) & (0xFFU));
  cframe->Data[1] |= ((_m->FRONT_OBJECT_DISTANCE_LOW_RES_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->FRONT_OBJECT_DISTANCE_LOW_RES_ro & (0xFFU));
  cframe->Data[3] |= ((_m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro >> 16) & (0xFFU));
  cframe->Data[4] |= ((_m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro & (0xFFU));

  cframe->MsgId = DETECTED_OBJECT_RPT_CANID;
  cframe->DLC = DETECTED_OBJECT_RPT_DLC;
  cframe->IDE = DETECTED_OBJECT_RPT_IDE;
  return DETECTED_OBJECT_RPT_CANID;
}

#else

uint32_t Pack_DETECTED_OBJECT_RPT_pacmod13(DETECTED_OBJECT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DETECTED_OBJECT_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->FRONT_OBJECT_DISTANCE_LOW_RES_ro = PACMOD13_FRONT_OBJECT_DISTANCE_LOW_RES_ro_toS(_m->FRONT_OBJECT_DISTANCE_LOW_RES_phys);
  _m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro = PACMOD13_FRONT_OBJECT_DISTANCE_HIGH_RES_ro_toS(_m->FRONT_OBJECT_DISTANCE_HIGH_RES_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->FRONT_OBJECT_DISTANCE_LOW_RES_ro >> 16) & (0xFFU));
  _d[1] |= ((_m->FRONT_OBJECT_DISTANCE_LOW_RES_ro >> 8) & (0xFFU));
  _d[2] |= (_m->FRONT_OBJECT_DISTANCE_LOW_RES_ro & (0xFFU));
  _d[3] |= ((_m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro >> 16) & (0xFFU));
  _d[4] |= ((_m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro >> 8) & (0xFFU));
  _d[5] |= (_m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro & (0xFFU));

  *_len = DETECTED_OBJECT_RPT_DLC;
  *_ide = DETECTED_OBJECT_RPT_IDE;
  return DETECTED_OBJECT_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_FIRE_SUPPRESSION_RPT_pacmod13(FIRE_SUPPRESSION_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->FIRE_SUPPRESSION_ALARM_STATUS = (_d[0] & (0x0FU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < FIRE_SUPPRESSION_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_FIRE_SUPPRESSION_RPT_pacmod13(&_m->mon1, FIRE_SUPPRESSION_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return FIRE_SUPPRESSION_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_FIRE_SUPPRESSION_RPT_pacmod13(FIRE_SUPPRESSION_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < FIRE_SUPPRESSION_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->FIRE_SUPPRESSION_ALARM_STATUS & (0x0FU));

  cframe->MsgId = FIRE_SUPPRESSION_RPT_CANID;
  cframe->DLC = FIRE_SUPPRESSION_RPT_DLC;
  cframe->IDE = FIRE_SUPPRESSION_RPT_IDE;
  return FIRE_SUPPRESSION_RPT_CANID;
}

#else

uint32_t Pack_FIRE_SUPPRESSION_RPT_pacmod13(FIRE_SUPPRESSION_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < FIRE_SUPPRESSION_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->FIRE_SUPPRESSION_ALARM_STATUS & (0x0FU));

  *_len = FIRE_SUPPRESSION_RPT_DLC;
  *_ide = FIRE_SUPPRESSION_RPT_IDE;
  return FIRE_SUPPRESSION_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_VEH_DYNAMICS_RPT_pacmod13(VEH_DYNAMICS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->VEH_G_FORCES_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->VEH_G_FORCES_phys = (sigfloat_t)(PACMOD13_VEH_G_FORCES_ro_fromS(_m->VEH_G_FORCES_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_DYNAMICS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_DYNAMICS_RPT_pacmod13(&_m->mon1, VEH_DYNAMICS_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return VEH_DYNAMICS_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_VEH_DYNAMICS_RPT_pacmod13(VEH_DYNAMICS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < VEH_DYNAMICS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->VEH_G_FORCES_ro = PACMOD13_VEH_G_FORCES_ro_toS(_m->VEH_G_FORCES_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->VEH_G_FORCES_ro & (0xFFU));

  cframe->MsgId = VEH_DYNAMICS_RPT_CANID;
  cframe->DLC = VEH_DYNAMICS_RPT_DLC;
  cframe->IDE = VEH_DYNAMICS_RPT_IDE;
  return VEH_DYNAMICS_RPT_CANID;
}

#else

uint32_t Pack_VEH_DYNAMICS_RPT_pacmod13(VEH_DYNAMICS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < VEH_DYNAMICS_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->VEH_G_FORCES_ro = PACMOD13_VEH_G_FORCES_ro_toS(_m->VEH_G_FORCES_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->VEH_G_FORCES_ro & (0xFFU));

  *_len = VEH_DYNAMICS_RPT_DLC;
  *_ide = VEH_DYNAMICS_RPT_IDE;
  return VEH_DYNAMICS_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_VIN_RPT_pacmod13(VIN_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->VEH_MFG_CODE = ((_d[0] & (0xFFU)) << 16) | ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->VEH_MY_CODE = (_d[3] & (0xFFU));
  _m->VEH_SERIAL = ((_d[4] & (0xFFU)) << 16) | ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VIN_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VIN_RPT_pacmod13(&_m->mon1, VIN_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return VIN_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_VIN_RPT_pacmod13(VIN_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < VIN_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= ((_m->VEH_MFG_CODE >> 16) & (0xFFU));
  cframe->Data[1] |= ((_m->VEH_MFG_CODE >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->VEH_MFG_CODE & (0xFFU));
  cframe->Data[3] |= (_m->VEH_MY_CODE & (0xFFU));
  cframe->Data[4] |= ((_m->VEH_SERIAL >> 16) & (0xFFU));
  cframe->Data[5] |= ((_m->VEH_SERIAL >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->VEH_SERIAL & (0xFFU));

  cframe->MsgId = VIN_RPT_CANID;
  cframe->DLC = VIN_RPT_DLC;
  cframe->IDE = VIN_RPT_IDE;
  return VIN_RPT_CANID;
}

#else

uint32_t Pack_VIN_RPT_pacmod13(VIN_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < VIN_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= ((_m->VEH_MFG_CODE >> 16) & (0xFFU));
  _d[1] |= ((_m->VEH_MFG_CODE >> 8) & (0xFFU));
  _d[2] |= (_m->VEH_MFG_CODE & (0xFFU));
  _d[3] |= (_m->VEH_MY_CODE & (0xFFU));
  _d[4] |= ((_m->VEH_SERIAL >> 16) & (0xFFU));
  _d[5] |= ((_m->VEH_SERIAL >> 8) & (0xFFU));
  _d[6] |= (_m->VEH_SERIAL & (0xFFU));

  *_len = VIN_RPT_DLC;
  *_ide = VIN_RPT_IDE;
  return VIN_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_OCCUPANCY_RPT_pacmod13(OCCUPANCY_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DRIVER_SEAT_OCCUPIED = (_d[0] & (0x01U));
  _m->PASS_SEAT_OCCUPIED = ((_d[0] >> 1) & (0x01U));
  _m->REAR_SEAT_OCCUPIED = ((_d[0] >> 2) & (0x01U));
  _m->DRIVER_SEATBELT_BUCKLED = ((_d[0] >> 3) & (0x01U));
  _m->PASS_SEATBELT_BUCKLED = ((_d[0] >> 4) & (0x01U));
  _m->DRVR_REAR_SEATBELT_BUCKLED = ((_d[0] >> 5) & (0x01U));
  _m->PASS_REAR_SEATBELT_BUCKLED = ((_d[0] >> 6) & (0x01U));
  _m->CTR_REAR_SEATBELT_BUCKLED = ((_d[0] >> 7) & (0x01U));
  _m->DRIVER_SEAT_OCCUPIED_AVAIL = (_d[1] & (0x01U));
  _m->PASS_SEAT_OCCUPIED_AVAIL = ((_d[1] >> 1) & (0x01U));
  _m->REAR_SEAT_OCCUPIED_AVAIL = ((_d[1] >> 2) & (0x01U));
  _m->DRIVER_SEATBELT_BUCKLED_AVAIL = ((_d[1] >> 3) & (0x01U));
  _m->PASS_SEATBELT_BUCKLED_AVAIL = ((_d[1] >> 4) & (0x01U));
  _m->DRVR_REAR_SEATBELT_BUCKLED_AVAIL = ((_d[1] >> 5) & (0x01U));
  _m->PASS_REAR_SEATBELT_BUCKLED_AVAIL = ((_d[1] >> 6) & (0x01U));
  _m->CTR_REAR_SEATBELT_BUCKLED_AVAIL = ((_d[1] >> 7) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < OCCUPANCY_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_OCCUPANCY_RPT_pacmod13(&_m->mon1, OCCUPANCY_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return OCCUPANCY_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_OCCUPANCY_RPT_pacmod13(OCCUPANCY_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < OCCUPANCY_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->DRIVER_SEAT_OCCUPIED & (0x01U)) | ((_m->PASS_SEAT_OCCUPIED & (0x01U)) << 1) | ((_m->REAR_SEAT_OCCUPIED & (0x01U)) << 2) | ((_m->DRIVER_SEATBELT_BUCKLED & (0x01U)) << 3) | ((_m->PASS_SEATBELT_BUCKLED & (0x01U)) << 4) | ((_m->DRVR_REAR_SEATBELT_BUCKLED & (0x01U)) << 5) | ((_m->PASS_REAR_SEATBELT_BUCKLED & (0x01U)) << 6) | ((_m->CTR_REAR_SEATBELT_BUCKLED & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DRIVER_SEAT_OCCUPIED_AVAIL & (0x01U)) | ((_m->PASS_SEAT_OCCUPIED_AVAIL & (0x01U)) << 1) | ((_m->REAR_SEAT_OCCUPIED_AVAIL & (0x01U)) << 2) | ((_m->DRIVER_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 3) | ((_m->PASS_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 4) | ((_m->DRVR_REAR_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 5) | ((_m->PASS_REAR_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 6) | ((_m->CTR_REAR_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 7);

  cframe->MsgId = OCCUPANCY_RPT_CANID;
  cframe->DLC = OCCUPANCY_RPT_DLC;
  cframe->IDE = OCCUPANCY_RPT_IDE;
  return OCCUPANCY_RPT_CANID;
}

#else

uint32_t Pack_OCCUPANCY_RPT_pacmod13(OCCUPANCY_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < OCCUPANCY_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->DRIVER_SEAT_OCCUPIED & (0x01U)) | ((_m->PASS_SEAT_OCCUPIED & (0x01U)) << 1) | ((_m->REAR_SEAT_OCCUPIED & (0x01U)) << 2) | ((_m->DRIVER_SEATBELT_BUCKLED & (0x01U)) << 3) | ((_m->PASS_SEATBELT_BUCKLED & (0x01U)) << 4) | ((_m->DRVR_REAR_SEATBELT_BUCKLED & (0x01U)) << 5) | ((_m->PASS_REAR_SEATBELT_BUCKLED & (0x01U)) << 6) | ((_m->CTR_REAR_SEATBELT_BUCKLED & (0x01U)) << 7);
  _d[1] |= (_m->DRIVER_SEAT_OCCUPIED_AVAIL & (0x01U)) | ((_m->PASS_SEAT_OCCUPIED_AVAIL & (0x01U)) << 1) | ((_m->REAR_SEAT_OCCUPIED_AVAIL & (0x01U)) << 2) | ((_m->DRIVER_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 3) | ((_m->PASS_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 4) | ((_m->DRVR_REAR_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 5) | ((_m->PASS_REAR_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 6) | ((_m->CTR_REAR_SEATBELT_BUCKLED_AVAIL & (0x01U)) << 7);

  *_len = OCCUPANCY_RPT_DLC;
  *_ide = OCCUPANCY_RPT_IDE;
  return OCCUPANCY_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_INTERIOR_LIGHTS_RPT_pacmod13(INTERIOR_LIGHTS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->FRONT_DOME_LIGHTS_ON = (_d[0] & (0x01U));
  _m->REAR_DOME_LIGHTS_ON = ((_d[0] >> 1) & (0x01U));
  _m->MOOD_LIGHTS_ON = ((_d[0] >> 2) & (0x01U));
  _m->AMBIENT_LIGHT_SENSOR = ((_d[0] >> 3) & (0x01U));
  _m->DIM_LEVEL = (_d[1] & (0xFFU));
  _m->FRONT_DOME_LIGHTS_ON_AVAIL = (_d[2] & (0x01U));
  _m->REAR_DOME_LIGHTS_ON_AVAIL = ((_d[2] >> 1) & (0x01U));
  _m->MOOD_LIGHTS_ON_AVAIL = ((_d[2] >> 2) & (0x01U));
  _m->DIM_LEVEL_AVAIL = ((_d[2] >> 3) & (0x01U));
  _m->AMBIENT_LIGHT_SENSOR_AVAIL = ((_d[2] >> 4) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < INTERIOR_LIGHTS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_INTERIOR_LIGHTS_RPT_pacmod13(&_m->mon1, INTERIOR_LIGHTS_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return INTERIOR_LIGHTS_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_INTERIOR_LIGHTS_RPT_pacmod13(INTERIOR_LIGHTS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < INTERIOR_LIGHTS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->FRONT_DOME_LIGHTS_ON & (0x01U)) | ((_m->REAR_DOME_LIGHTS_ON & (0x01U)) << 1) | ((_m->MOOD_LIGHTS_ON & (0x01U)) << 2) | ((_m->AMBIENT_LIGHT_SENSOR & (0x01U)) << 3);
  cframe->Data[1] |= (_m->DIM_LEVEL & (0xFFU));
  cframe->Data[2] |= (_m->FRONT_DOME_LIGHTS_ON_AVAIL & (0x01U)) | ((_m->REAR_DOME_LIGHTS_ON_AVAIL & (0x01U)) << 1) | ((_m->MOOD_LIGHTS_ON_AVAIL & (0x01U)) << 2) | ((_m->DIM_LEVEL_AVAIL & (0x01U)) << 3) | ((_m->AMBIENT_LIGHT_SENSOR_AVAIL & (0x01U)) << 4);

  cframe->MsgId = INTERIOR_LIGHTS_RPT_CANID;
  cframe->DLC = INTERIOR_LIGHTS_RPT_DLC;
  cframe->IDE = INTERIOR_LIGHTS_RPT_IDE;
  return INTERIOR_LIGHTS_RPT_CANID;
}

#else

uint32_t Pack_INTERIOR_LIGHTS_RPT_pacmod13(INTERIOR_LIGHTS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < INTERIOR_LIGHTS_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->FRONT_DOME_LIGHTS_ON & (0x01U)) | ((_m->REAR_DOME_LIGHTS_ON & (0x01U)) << 1) | ((_m->MOOD_LIGHTS_ON & (0x01U)) << 2) | ((_m->AMBIENT_LIGHT_SENSOR & (0x01U)) << 3);
  _d[1] |= (_m->DIM_LEVEL & (0xFFU));
  _d[2] |= (_m->FRONT_DOME_LIGHTS_ON_AVAIL & (0x01U)) | ((_m->REAR_DOME_LIGHTS_ON_AVAIL & (0x01U)) << 1) | ((_m->MOOD_LIGHTS_ON_AVAIL & (0x01U)) << 2) | ((_m->DIM_LEVEL_AVAIL & (0x01U)) << 3) | ((_m->AMBIENT_LIGHT_SENSOR_AVAIL & (0x01U)) << 4);

  *_len = INTERIOR_LIGHTS_RPT_DLC;
  *_ide = INTERIOR_LIGHTS_RPT_IDE;
  return INTERIOR_LIGHTS_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DOOR_RPT_pacmod13(DOOR_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DRIVER_DOOR_OPEN = (_d[0] & (0x01U));
  _m->PASS_DOOR_OPEN = ((_d[0] >> 1) & (0x01U));
  _m->REAR_DRIVER_DOOR_OPEN = ((_d[0] >> 2) & (0x01U));
  _m->REAR_PASS_DOOR_OPEN = ((_d[0] >> 3) & (0x01U));
  _m->HOOD_OPEN = ((_d[0] >> 4) & (0x01U));
  _m->TRUNK_OPEN = ((_d[0] >> 5) & (0x01U));
  _m->FUEL_DOOR_OPEN = ((_d[0] >> 6) & (0x01U));
  _m->CARGO_DOOR_OPEN = ((_d[0] >> 7) & (0x01U));
  _m->DRIVER_DOOR_OPEN_AVAIL = (_d[1] & (0x01U));
  _m->PASS_DOOR_OPEN_AVAIL = ((_d[1] >> 1) & (0x01U));
  _m->REAR_DRIVER_DOOR_OPEN_AVAIL = ((_d[1] >> 2) & (0x01U));
  _m->REAR_PASS_DOOR_OPEN_AVAIL = ((_d[1] >> 3) & (0x01U));
  _m->HOOD_OPEN_AVAIL = ((_d[1] >> 4) & (0x01U));
  _m->TRUNK_OPEN_AVAIL = ((_d[1] >> 5) & (0x01U));
  _m->FUEL_DOOR_OPEN_AVAIL = ((_d[1] >> 6) & (0x01U));
  _m->CARGO_DOOR_OPEN_AVAIL = ((_d[1] >> 7) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DOOR_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DOOR_RPT_pacmod13(&_m->mon1, DOOR_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DOOR_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DOOR_RPT_pacmod13(DOOR_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DOOR_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->DRIVER_DOOR_OPEN & (0x01U)) | ((_m->PASS_DOOR_OPEN & (0x01U)) << 1) | ((_m->REAR_DRIVER_DOOR_OPEN & (0x01U)) << 2) | ((_m->REAR_PASS_DOOR_OPEN & (0x01U)) << 3) | ((_m->HOOD_OPEN & (0x01U)) << 4) | ((_m->TRUNK_OPEN & (0x01U)) << 5) | ((_m->FUEL_DOOR_OPEN & (0x01U)) << 6) | ((_m->CARGO_DOOR_OPEN & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DRIVER_DOOR_OPEN_AVAIL & (0x01U)) | ((_m->PASS_DOOR_OPEN_AVAIL & (0x01U)) << 1) | ((_m->REAR_DRIVER_DOOR_OPEN_AVAIL & (0x01U)) << 2) | ((_m->REAR_PASS_DOOR_OPEN_AVAIL & (0x01U)) << 3) | ((_m->HOOD_OPEN_AVAIL & (0x01U)) << 4) | ((_m->TRUNK_OPEN_AVAIL & (0x01U)) << 5) | ((_m->FUEL_DOOR_OPEN_AVAIL & (0x01U)) << 6) | ((_m->CARGO_DOOR_OPEN_AVAIL & (0x01U)) << 7);

  cframe->MsgId = DOOR_RPT_CANID;
  cframe->DLC = DOOR_RPT_DLC;
  cframe->IDE = DOOR_RPT_IDE;
  return DOOR_RPT_CANID;
}

#else

uint32_t Pack_DOOR_RPT_pacmod13(DOOR_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DOOR_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->DRIVER_DOOR_OPEN & (0x01U)) | ((_m->PASS_DOOR_OPEN & (0x01U)) << 1) | ((_m->REAR_DRIVER_DOOR_OPEN & (0x01U)) << 2) | ((_m->REAR_PASS_DOOR_OPEN & (0x01U)) << 3) | ((_m->HOOD_OPEN & (0x01U)) << 4) | ((_m->TRUNK_OPEN & (0x01U)) << 5) | ((_m->FUEL_DOOR_OPEN & (0x01U)) << 6) | ((_m->CARGO_DOOR_OPEN & (0x01U)) << 7);
  _d[1] |= (_m->DRIVER_DOOR_OPEN_AVAIL & (0x01U)) | ((_m->PASS_DOOR_OPEN_AVAIL & (0x01U)) << 1) | ((_m->REAR_DRIVER_DOOR_OPEN_AVAIL & (0x01U)) << 2) | ((_m->REAR_PASS_DOOR_OPEN_AVAIL & (0x01U)) << 3) | ((_m->HOOD_OPEN_AVAIL & (0x01U)) << 4) | ((_m->TRUNK_OPEN_AVAIL & (0x01U)) << 5) | ((_m->FUEL_DOOR_OPEN_AVAIL & (0x01U)) << 6) | ((_m->CARGO_DOOR_OPEN_AVAIL & (0x01U)) << 7);

  *_len = DOOR_RPT_DLC;
  *_ide = DOOR_RPT_IDE;
  return DOOR_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_REAR_LIGHTS_RPT_pacmod13(REAR_LIGHTS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_LIGHTS_ON = (_d[0] & (0x01U));
  _m->REVERSE_LIGHTS_ON = ((_d[0] >> 1) & (0x01U));
  _m->BRAKE_LIGHTS_ON_AVAIL = (_d[1] & (0x01U));
  _m->REVERSE_LIGHTS_ON_AVAIL = ((_d[1] >> 1) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < REAR_LIGHTS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_REAR_LIGHTS_RPT_pacmod13(&_m->mon1, REAR_LIGHTS_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return REAR_LIGHTS_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_REAR_LIGHTS_RPT_pacmod13(REAR_LIGHTS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < REAR_LIGHTS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BRAKE_LIGHTS_ON & (0x01U)) | ((_m->REVERSE_LIGHTS_ON & (0x01U)) << 1);
  cframe->Data[1] |= (_m->BRAKE_LIGHTS_ON_AVAIL & (0x01U)) | ((_m->REVERSE_LIGHTS_ON_AVAIL & (0x01U)) << 1);

  cframe->MsgId = REAR_LIGHTS_RPT_CANID;
  cframe->DLC = REAR_LIGHTS_RPT_DLC;
  cframe->IDE = REAR_LIGHTS_RPT_IDE;
  return REAR_LIGHTS_RPT_CANID;
}

#else

uint32_t Pack_REAR_LIGHTS_RPT_pacmod13(REAR_LIGHTS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < REAR_LIGHTS_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BRAKE_LIGHTS_ON & (0x01U)) | ((_m->REVERSE_LIGHTS_ON & (0x01U)) << 1);
  _d[1] |= (_m->BRAKE_LIGHTS_ON_AVAIL & (0x01U)) | ((_m->REVERSE_LIGHTS_ON_AVAIL & (0x01U)) << 1);

  *_len = REAR_LIGHTS_RPT_DLC;
  *_ide = REAR_LIGHTS_RPT_IDE;
  return REAR_LIGHTS_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_LINEAR_ACCEL_RPT_pacmod13(LINEAR_ACCEL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->LATERAL_NEW_DATA_RX = (_d[0] & (0x01U));
  _m->LONGITUDINAL_NEW_DATA_RX = ((_d[0] >> 1) & (0x01U));
  _m->VERTICAL_NEW_DATA_RX = ((_d[0] >> 2) & (0x01U));
  _m->LATERAL_VALID = ((_d[0] >> 3) & (0x01U));
  _m->LONGITUDINAL_VALID = ((_d[0] >> 4) & (0x01U));
  _m->VERTICAL_VALID = ((_d[0] >> 5) & (0x01U));
  _m->LATERAL_ACCEL_ro = __ext_sig__(( ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->LATERAL_ACCEL_phys = (sigfloat_t)(PACMOD13_LATERAL_ACCEL_ro_fromS(_m->LATERAL_ACCEL_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->LONGITUDINAL_ACCEL_ro = __ext_sig__(( ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->LONGITUDINAL_ACCEL_phys = (sigfloat_t)(PACMOD13_LONGITUDINAL_ACCEL_ro_fromS(_m->LONGITUDINAL_ACCEL_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->VERTICAL_ACCEL_ro = __ext_sig__(( ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->VERTICAL_ACCEL_phys = (sigfloat_t)(PACMOD13_VERTICAL_ACCEL_ro_fromS(_m->VERTICAL_ACCEL_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < LINEAR_ACCEL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_LINEAR_ACCEL_RPT_pacmod13(&_m->mon1, LINEAR_ACCEL_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return LINEAR_ACCEL_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_LINEAR_ACCEL_RPT_pacmod13(LINEAR_ACCEL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < LINEAR_ACCEL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->LATERAL_ACCEL_ro = PACMOD13_LATERAL_ACCEL_ro_toS(_m->LATERAL_ACCEL_phys);
  _m->LONGITUDINAL_ACCEL_ro = PACMOD13_LONGITUDINAL_ACCEL_ro_toS(_m->LONGITUDINAL_ACCEL_phys);
  _m->VERTICAL_ACCEL_ro = PACMOD13_VERTICAL_ACCEL_ro_toS(_m->VERTICAL_ACCEL_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->LATERAL_NEW_DATA_RX & (0x01U)) | ((_m->LONGITUDINAL_NEW_DATA_RX & (0x01U)) << 1) | ((_m->VERTICAL_NEW_DATA_RX & (0x01U)) << 2) | ((_m->LATERAL_VALID & (0x01U)) << 3) | ((_m->LONGITUDINAL_VALID & (0x01U)) << 4) | ((_m->VERTICAL_VALID & (0x01U)) << 5);
  cframe->Data[1] |= ((_m->LATERAL_ACCEL_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->LATERAL_ACCEL_ro & (0xFFU));
  cframe->Data[3] |= ((_m->LONGITUDINAL_ACCEL_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->LONGITUDINAL_ACCEL_ro & (0xFFU));
  cframe->Data[5] |= ((_m->VERTICAL_ACCEL_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->VERTICAL_ACCEL_ro & (0xFFU));

  cframe->MsgId = LINEAR_ACCEL_RPT_CANID;
  cframe->DLC = LINEAR_ACCEL_RPT_DLC;
  cframe->IDE = LINEAR_ACCEL_RPT_IDE;
  return LINEAR_ACCEL_RPT_CANID;
}

#else

uint32_t Pack_LINEAR_ACCEL_RPT_pacmod13(LINEAR_ACCEL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < LINEAR_ACCEL_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->LATERAL_ACCEL_ro = PACMOD13_LATERAL_ACCEL_ro_toS(_m->LATERAL_ACCEL_phys);
  _m->LONGITUDINAL_ACCEL_ro = PACMOD13_LONGITUDINAL_ACCEL_ro_toS(_m->LONGITUDINAL_ACCEL_phys);
  _m->VERTICAL_ACCEL_ro = PACMOD13_VERTICAL_ACCEL_ro_toS(_m->VERTICAL_ACCEL_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->LATERAL_NEW_DATA_RX & (0x01U)) | ((_m->LONGITUDINAL_NEW_DATA_RX & (0x01U)) << 1) | ((_m->VERTICAL_NEW_DATA_RX & (0x01U)) << 2) | ((_m->LATERAL_VALID & (0x01U)) << 3) | ((_m->LONGITUDINAL_VALID & (0x01U)) << 4) | ((_m->VERTICAL_VALID & (0x01U)) << 5);
  _d[1] |= ((_m->LATERAL_ACCEL_ro >> 8) & (0xFFU));
  _d[2] |= (_m->LATERAL_ACCEL_ro & (0xFFU));
  _d[3] |= ((_m->LONGITUDINAL_ACCEL_ro >> 8) & (0xFFU));
  _d[4] |= (_m->LONGITUDINAL_ACCEL_ro & (0xFFU));
  _d[5] |= ((_m->VERTICAL_ACCEL_ro >> 8) & (0xFFU));
  _d[6] |= (_m->VERTICAL_ACCEL_ro & (0xFFU));

  *_len = LINEAR_ACCEL_RPT_DLC;
  *_ide = LINEAR_ACCEL_RPT_IDE;
  return LINEAR_ACCEL_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ANG_VEL_RPT_pacmod13(ANG_VEL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PITCH_NEW_DATA_RX = (_d[0] & (0x01U));
  _m->ROLL_NEW_DATA_RX = ((_d[0] >> 1) & (0x01U));
  _m->YAW_NEW_DATA_RX = ((_d[0] >> 2) & (0x01U));
  _m->PITCH_VALID = ((_d[0] >> 3) & (0x01U));
  _m->ROLL_VALID = ((_d[0] >> 4) & (0x01U));
  _m->YAW_VALID = ((_d[0] >> 5) & (0x01U));
  _m->PITCH_VEL_ro = __ext_sig__(( ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PITCH_VEL_phys = (sigfloat_t)(PACMOD13_PITCH_VEL_ro_fromS(_m->PITCH_VEL_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->ROLL_VEL_ro = __ext_sig__(( ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ROLL_VEL_phys = (sigfloat_t)(PACMOD13_ROLL_VEL_ro_fromS(_m->ROLL_VEL_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->YAW_VEL_ro = __ext_sig__(( ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->YAW_VEL_phys = (sigfloat_t)(PACMOD13_YAW_VEL_ro_fromS(_m->YAW_VEL_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ANG_VEL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ANG_VEL_RPT_pacmod13(&_m->mon1, ANG_VEL_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ANG_VEL_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ANG_VEL_RPT_pacmod13(ANG_VEL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ANG_VEL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PITCH_VEL_ro = PACMOD13_PITCH_VEL_ro_toS(_m->PITCH_VEL_phys);
  _m->ROLL_VEL_ro = PACMOD13_ROLL_VEL_ro_toS(_m->ROLL_VEL_phys);
  _m->YAW_VEL_ro = PACMOD13_YAW_VEL_ro_toS(_m->YAW_VEL_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->PITCH_NEW_DATA_RX & (0x01U)) | ((_m->ROLL_NEW_DATA_RX & (0x01U)) << 1) | ((_m->YAW_NEW_DATA_RX & (0x01U)) << 2) | ((_m->PITCH_VALID & (0x01U)) << 3) | ((_m->ROLL_VALID & (0x01U)) << 4) | ((_m->YAW_VALID & (0x01U)) << 5);
  cframe->Data[1] |= ((_m->PITCH_VEL_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->PITCH_VEL_ro & (0xFFU));
  cframe->Data[3] |= ((_m->ROLL_VEL_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->ROLL_VEL_ro & (0xFFU));
  cframe->Data[5] |= ((_m->YAW_VEL_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->YAW_VEL_ro & (0xFFU));

  cframe->MsgId = ANG_VEL_RPT_CANID;
  cframe->DLC = ANG_VEL_RPT_DLC;
  cframe->IDE = ANG_VEL_RPT_IDE;
  return ANG_VEL_RPT_CANID;
}

#else

uint32_t Pack_ANG_VEL_RPT_pacmod13(ANG_VEL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ANG_VEL_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PITCH_VEL_ro = PACMOD13_PITCH_VEL_ro_toS(_m->PITCH_VEL_phys);
  _m->ROLL_VEL_ro = PACMOD13_ROLL_VEL_ro_toS(_m->ROLL_VEL_phys);
  _m->YAW_VEL_ro = PACMOD13_YAW_VEL_ro_toS(_m->YAW_VEL_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->PITCH_NEW_DATA_RX & (0x01U)) | ((_m->ROLL_NEW_DATA_RX & (0x01U)) << 1) | ((_m->YAW_NEW_DATA_RX & (0x01U)) << 2) | ((_m->PITCH_VALID & (0x01U)) << 3) | ((_m->ROLL_VALID & (0x01U)) << 4) | ((_m->YAW_VALID & (0x01U)) << 5);
  _d[1] |= ((_m->PITCH_VEL_ro >> 8) & (0xFFU));
  _d[2] |= (_m->PITCH_VEL_ro & (0xFFU));
  _d[3] |= ((_m->ROLL_VEL_ro >> 8) & (0xFFU));
  _d[4] |= (_m->ROLL_VEL_ro & (0xFFU));
  _d[5] |= ((_m->YAW_VEL_ro >> 8) & (0xFFU));
  _d[6] |= (_m->YAW_VEL_ro & (0xFFU));

  *_len = ANG_VEL_RPT_DLC;
  *_ide = ANG_VEL_RPT_IDE;
  return ANG_VEL_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_NOTIFICATION_CMD_pacmod13(NOTIFICATION_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BUZZER_MUTE = (_d[0] & (0x01U));
  _m->UNDERDASH_LIGHTS_WHITE = ((_d[0] >> 1) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < NOTIFICATION_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_NOTIFICATION_CMD_pacmod13(&_m->mon1, NOTIFICATION_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return NOTIFICATION_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_NOTIFICATION_CMD_pacmod13(NOTIFICATION_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < NOTIFICATION_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BUZZER_MUTE & (0x01U)) | ((_m->UNDERDASH_LIGHTS_WHITE & (0x01U)) << 1);

  cframe->MsgId = NOTIFICATION_CMD_CANID;
  cframe->DLC = NOTIFICATION_CMD_DLC;
  cframe->IDE = NOTIFICATION_CMD_IDE;
  return NOTIFICATION_CMD_CANID;
}

#else

uint32_t Pack_NOTIFICATION_CMD_pacmod13(NOTIFICATION_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < NOTIFICATION_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BUZZER_MUTE & (0x01U)) | ((_m->UNDERDASH_LIGHTS_WHITE & (0x01U)) << 1);

  *_len = NOTIFICATION_CMD_DLC;
  *_ide = NOTIFICATION_CMD_IDE;
  return NOTIFICATION_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ESTOP_RPT_pacmod13(ESTOP_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ESTOP = (_d[0] & (0x01U));
  _m->ESTOP_FAULT = ((_d[0] >> 1) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ESTOP_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ESTOP_RPT_pacmod13(&_m->mon1, ESTOP_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ESTOP_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ESTOP_RPT_pacmod13(ESTOP_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ESTOP_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ESTOP & (0x01U)) | ((_m->ESTOP_FAULT & (0x01U)) << 1);

  cframe->MsgId = ESTOP_RPT_CANID;
  cframe->DLC = ESTOP_RPT_DLC;
  cframe->IDE = ESTOP_RPT_IDE;
  return ESTOP_RPT_CANID;
}

#else

uint32_t Pack_ESTOP_RPT_pacmod13(ESTOP_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ESTOP_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ESTOP & (0x01U)) | ((_m->ESTOP_FAULT & (0x01U)) << 1);

  *_len = ESTOP_RPT_DLC;
  *_ide = ESTOP_RPT_IDE;
  return ESTOP_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_USER_NOTIFICATION_CMD_pacmod13(USER_NOTIFICATION_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BUZZER_MUTE = (_d[0] & (0x01U));
  _m->LIGHT_COMMAND = ((_d[0] >> 1) & (0x0FU));
  _m->BUZZER_ON = ((_d[0] >> 5) & (0x01U));
  _m->BUZZER_MUTE_INDICATOR = ((_d[0] >> 6) & (0x03U));
  _m->LED_BRIGHTNESS = (_d[1] & (0x0FU));
  _m->LIGHT_STATUS_COMMAND = ((_d[1] >> 4) & (0x03U));
  _m->LIGHT_COMMAND_ALTERNATE = (_d[2] & (0x0FU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < USER_NOTIFICATION_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_USER_NOTIFICATION_CMD_pacmod13(&_m->mon1, USER_NOTIFICATION_CMD_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return USER_NOTIFICATION_CMD_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_USER_NOTIFICATION_CMD_pacmod13(USER_NOTIFICATION_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < USER_NOTIFICATION_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BUZZER_MUTE & (0x01U)) | ((_m->LIGHT_COMMAND & (0x0FU)) << 1) | ((_m->BUZZER_ON & (0x01U)) << 5) | ((_m->BUZZER_MUTE_INDICATOR & (0x03U)) << 6);
  cframe->Data[1] |= (_m->LED_BRIGHTNESS & (0x0FU)) | ((_m->LIGHT_STATUS_COMMAND & (0x03U)) << 4);
  cframe->Data[2] |= (_m->LIGHT_COMMAND_ALTERNATE & (0x0FU));

  cframe->MsgId = USER_NOTIFICATION_CMD_CANID;
  cframe->DLC = USER_NOTIFICATION_CMD_DLC;
  cframe->IDE = USER_NOTIFICATION_CMD_IDE;
  return USER_NOTIFICATION_CMD_CANID;
}

#else

uint32_t Pack_USER_NOTIFICATION_CMD_pacmod13(USER_NOTIFICATION_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < USER_NOTIFICATION_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BUZZER_MUTE & (0x01U)) | ((_m->LIGHT_COMMAND & (0x0FU)) << 1) | ((_m->BUZZER_ON & (0x01U)) << 5) | ((_m->BUZZER_MUTE_INDICATOR & (0x03U)) << 6);
  _d[1] |= (_m->LED_BRIGHTNESS & (0x0FU)) | ((_m->LIGHT_STATUS_COMMAND & (0x03U)) << 4);
  _d[2] |= (_m->LIGHT_COMMAND_ALTERNATE & (0x0FU));

  *_len = USER_NOTIFICATION_CMD_DLC;
  *_ide = USER_NOTIFICATION_CMD_IDE;
  return USER_NOTIFICATION_CMD_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIRE_PRESSURE_RPT_pacmod13(TIRE_PRESSURE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->FRONT_LEFT_TIRE_PRESSURE_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->FRONT_LEFT_TIRE_PRESSURE_phys = PACMOD13_FRONT_LEFT_TIRE_PRESSURE_ro_fromS(_m->FRONT_LEFT_TIRE_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->FRONT_RIGHT_TIRE_PRESSURE_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->FRONT_RIGHT_TIRE_PRESSURE_phys = PACMOD13_FRONT_RIGHT_TIRE_PRESSURE_ro_fromS(_m->FRONT_RIGHT_TIRE_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->REAR_LEFT_TIRE_PRESSURE_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->REAR_LEFT_TIRE_PRESSURE_phys = PACMOD13_REAR_LEFT_TIRE_PRESSURE_ro_fromS(_m->REAR_LEFT_TIRE_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->REAR_RIGHT_TIRE_PRESSURE_ro = (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->REAR_RIGHT_TIRE_PRESSURE_phys = PACMOD13_REAR_RIGHT_TIRE_PRESSURE_ro_fromS(_m->REAR_RIGHT_TIRE_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIRE_PRESSURE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIRE_PRESSURE_RPT_pacmod13(&_m->mon1, TIRE_PRESSURE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIRE_PRESSURE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIRE_PRESSURE_RPT_pacmod13(TIRE_PRESSURE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIRE_PRESSURE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->FRONT_LEFT_TIRE_PRESSURE_ro = PACMOD13_FRONT_LEFT_TIRE_PRESSURE_ro_toS(_m->FRONT_LEFT_TIRE_PRESSURE_phys);
  _m->FRONT_RIGHT_TIRE_PRESSURE_ro = PACMOD13_FRONT_RIGHT_TIRE_PRESSURE_ro_toS(_m->FRONT_RIGHT_TIRE_PRESSURE_phys);
  _m->REAR_LEFT_TIRE_PRESSURE_ro = PACMOD13_REAR_LEFT_TIRE_PRESSURE_ro_toS(_m->REAR_LEFT_TIRE_PRESSURE_phys);
  _m->REAR_RIGHT_TIRE_PRESSURE_ro = PACMOD13_REAR_RIGHT_TIRE_PRESSURE_ro_toS(_m->REAR_RIGHT_TIRE_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->FRONT_LEFT_TIRE_PRESSURE_ro & (0xFFU));
  cframe->Data[1] |= (_m->FRONT_RIGHT_TIRE_PRESSURE_ro & (0xFFU));
  cframe->Data[2] |= (_m->REAR_LEFT_TIRE_PRESSURE_ro & (0xFFU));
  cframe->Data[3] |= (_m->REAR_RIGHT_TIRE_PRESSURE_ro & (0xFFU));

  cframe->MsgId = TIRE_PRESSURE_RPT_CANID;
  cframe->DLC = TIRE_PRESSURE_RPT_DLC;
  cframe->IDE = TIRE_PRESSURE_RPT_IDE;
  return TIRE_PRESSURE_RPT_CANID;
}

#else

uint32_t Pack_TIRE_PRESSURE_RPT_pacmod13(TIRE_PRESSURE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIRE_PRESSURE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->FRONT_LEFT_TIRE_PRESSURE_ro = PACMOD13_FRONT_LEFT_TIRE_PRESSURE_ro_toS(_m->FRONT_LEFT_TIRE_PRESSURE_phys);
  _m->FRONT_RIGHT_TIRE_PRESSURE_ro = PACMOD13_FRONT_RIGHT_TIRE_PRESSURE_ro_toS(_m->FRONT_RIGHT_TIRE_PRESSURE_phys);
  _m->REAR_LEFT_TIRE_PRESSURE_ro = PACMOD13_REAR_LEFT_TIRE_PRESSURE_ro_toS(_m->REAR_LEFT_TIRE_PRESSURE_phys);
  _m->REAR_RIGHT_TIRE_PRESSURE_ro = PACMOD13_REAR_RIGHT_TIRE_PRESSURE_ro_toS(_m->REAR_RIGHT_TIRE_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->FRONT_LEFT_TIRE_PRESSURE_ro & (0xFFU));
  _d[1] |= (_m->FRONT_RIGHT_TIRE_PRESSURE_ro & (0xFFU));
  _d[2] |= (_m->REAR_LEFT_TIRE_PRESSURE_ro & (0xFFU));
  _d[3] |= (_m->REAR_RIGHT_TIRE_PRESSURE_ro & (0xFFU));

  *_len = TIRE_PRESSURE_RPT_DLC;
  *_ide = TIRE_PRESSURE_RPT_IDE;
  return TIRE_PRESSURE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_DRIVE_TRAIN_FEATURE_RPT_pacmod13(DRIVE_TRAIN_FEATURE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ANTILOCK_BRAKE_ACTIVE = (_d[0] & (0x01U));
  _m->TRACTION_CONTROL_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->FOUR_WHEEL_DRIVE_ACTIVE = ((_d[0] >> 2) & (0x01U));
  _m->ANTILOCK_BRAKE_DISABLED = ((_d[0] >> 3) & (0x01U));
  _m->ANTILOCK_BRAKE_ACTIVE_AVAIL = ((_d[0] >> 4) & (0x01U));
  _m->TRACTION_CONTROL_ACTIVE_AVAIL = ((_d[0] >> 5) & (0x01U));
  _m->FOUR_WHEEL_DRIVE_ACTIVE_AVAIL = ((_d[0] >> 6) & (0x01U));
  _m->ANTILOCK_BRAKE_DISABLED_AVAIL = ((_d[0] >> 7) & (0x01U));
  _m->DRIVE_MODE = (_d[1] & (0x0FU));
  _m->DRIVE_MODE_AVAIL = ((_d[1] >> 4) & (0x01U));
  _m->TRACTION_CONTROL_DISABLED = ((_d[1] >> 5) & (0x01U));
  _m->TRACTION_CONTROL_DISABLED_AVAIL = ((_d[1] >> 6) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DRIVE_TRAIN_FEATURE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DRIVE_TRAIN_FEATURE_RPT_pacmod13(&_m->mon1, DRIVE_TRAIN_FEATURE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return DRIVE_TRAIN_FEATURE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_DRIVE_TRAIN_FEATURE_RPT_pacmod13(DRIVE_TRAIN_FEATURE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DRIVE_TRAIN_FEATURE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ANTILOCK_BRAKE_ACTIVE & (0x01U)) | ((_m->TRACTION_CONTROL_ACTIVE & (0x01U)) << 1) | ((_m->FOUR_WHEEL_DRIVE_ACTIVE & (0x01U)) << 2) | ((_m->ANTILOCK_BRAKE_DISABLED & (0x01U)) << 3) | ((_m->ANTILOCK_BRAKE_ACTIVE_AVAIL & (0x01U)) << 4) | ((_m->TRACTION_CONTROL_ACTIVE_AVAIL & (0x01U)) << 5) | ((_m->FOUR_WHEEL_DRIVE_ACTIVE_AVAIL & (0x01U)) << 6) | ((_m->ANTILOCK_BRAKE_DISABLED_AVAIL & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DRIVE_MODE & (0x0FU)) | ((_m->DRIVE_MODE_AVAIL & (0x01U)) << 4) | ((_m->TRACTION_CONTROL_DISABLED & (0x01U)) << 5) | ((_m->TRACTION_CONTROL_DISABLED_AVAIL & (0x01U)) << 6);

  cframe->MsgId = DRIVE_TRAIN_FEATURE_RPT_CANID;
  cframe->DLC = DRIVE_TRAIN_FEATURE_RPT_DLC;
  cframe->IDE = DRIVE_TRAIN_FEATURE_RPT_IDE;
  return DRIVE_TRAIN_FEATURE_RPT_CANID;
}

#else

uint32_t Pack_DRIVE_TRAIN_FEATURE_RPT_pacmod13(DRIVE_TRAIN_FEATURE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DRIVE_TRAIN_FEATURE_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ANTILOCK_BRAKE_ACTIVE & (0x01U)) | ((_m->TRACTION_CONTROL_ACTIVE & (0x01U)) << 1) | ((_m->FOUR_WHEEL_DRIVE_ACTIVE & (0x01U)) << 2) | ((_m->ANTILOCK_BRAKE_DISABLED & (0x01U)) << 3) | ((_m->ANTILOCK_BRAKE_ACTIVE_AVAIL & (0x01U)) << 4) | ((_m->TRACTION_CONTROL_ACTIVE_AVAIL & (0x01U)) << 5) | ((_m->FOUR_WHEEL_DRIVE_ACTIVE_AVAIL & (0x01U)) << 6) | ((_m->ANTILOCK_BRAKE_DISABLED_AVAIL & (0x01U)) << 7);
  _d[1] |= (_m->DRIVE_MODE & (0x0FU)) | ((_m->DRIVE_MODE_AVAIL & (0x01U)) << 4) | ((_m->TRACTION_CONTROL_DISABLED & (0x01U)) << 5) | ((_m->TRACTION_CONTROL_DISABLED_AVAIL & (0x01U)) << 6);

  *_len = DRIVE_TRAIN_FEATURE_RPT_DLC;
  *_ide = DRIVE_TRAIN_FEATURE_RPT_IDE;
  return DRIVE_TRAIN_FEATURE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SAFETY_FUNC_CRITICAL_STOP_RPT_pacmod13(SAFETY_FUNC_CRITICAL_STOP_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->AUTOMS_MAN_OPCTRL_FAULT = (_d[0] & (0x01U));
  _m->REMOTE_STOP_FAULT = ((_d[0] >> 1) & (0x01U));
  _m->SAFETY_BRAKE_OPCTRL_OFF = ((_d[0] >> 2) & (0x01U));
  _m->SAFETY_BRAKE_CMD_TIMEOUT = ((_d[0] >> 3) & (0x01U));
  _m->SAFETY_FUNC_CMD_TIMEOUT = ((_d[0] >> 4) & (0x01U));
  _m->SAFETY_FUNC_CRITICAL_STOP_1_CMD = ((_d[0] >> 5) & (0x01U));
  _m->SAFETY_FUNC_CRITICAL_STOP_2_CMD = ((_d[0] >> 6) & (0x01U));
  _m->SAFETY_FUNC_NONE_CMD = ((_d[0] >> 7) & (0x01U));
  _m->PACMOD_SYSTEM_TIMEOUT = (_d[1] & (0x01U));
  _m->PACMOD_SYSTEM_FAULT = ((_d[1] >> 1) & (0x01U));
  _m->PACMOD_SYSTEM_NOT_ACTIVE = ((_d[1] >> 2) & (0x01U));
  _m->VEHICLE_REPORT_TIMEOUT = ((_d[1] >> 3) & (0x01U));
  _m->VEHICLE_REPORT_FAULT = ((_d[1] >> 4) & (0x01U));
  _m->LOW_ENGINE_RPM = ((_d[1] >> 5) & (0x01U));
  _m->PRI_SAFETY_BRAKE_SIGNAL_1_FAULT = ((_d[1] >> 6) & (0x01U));
  _m->PRI_SAFETY_BRAKE_SIGNAL_2_FAULT = ((_d[1] >> 7) & (0x01U));
  _m->SEC_SAFETY_BRAKE_SIGNAL_1_FAULT = (_d[2] & (0x01U));
  _m->SEC_SAFETY_BRAKE_SIGNAL_2_FAULT = ((_d[2] >> 1) & (0x01U));
  _m->PRIMARY_PROCESSOR_FAULT = ((_d[2] >> 2) & (0x01U));
  _m->SECONDARY_PROCESSOR_FAULT = ((_d[2] >> 3) & (0x01U));
  _m->REMOTE_STOP_CMD = ((_d[2] >> 4) & (0x01U));
  _m->PRI_SAFETY_BRAKE_PRESSURE_FAULT = ((_d[2] >> 5) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SAFETY_FUNC_CRITICAL_STOP_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SAFETY_FUNC_CRITICAL_STOP_RPT_pacmod13(&_m->mon1, SAFETY_FUNC_CRITICAL_STOP_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SAFETY_FUNC_CRITICAL_STOP_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SAFETY_FUNC_CRITICAL_STOP_RPT_pacmod13(SAFETY_FUNC_CRITICAL_STOP_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SAFETY_FUNC_CRITICAL_STOP_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->AUTOMS_MAN_OPCTRL_FAULT & (0x01U)) | ((_m->REMOTE_STOP_FAULT & (0x01U)) << 1) | ((_m->SAFETY_BRAKE_OPCTRL_OFF & (0x01U)) << 2) | ((_m->SAFETY_BRAKE_CMD_TIMEOUT & (0x01U)) << 3) | ((_m->SAFETY_FUNC_CMD_TIMEOUT & (0x01U)) << 4) | ((_m->SAFETY_FUNC_CRITICAL_STOP_1_CMD & (0x01U)) << 5) | ((_m->SAFETY_FUNC_CRITICAL_STOP_2_CMD & (0x01U)) << 6) | ((_m->SAFETY_FUNC_NONE_CMD & (0x01U)) << 7);
  cframe->Data[1] |= (_m->PACMOD_SYSTEM_TIMEOUT & (0x01U)) | ((_m->PACMOD_SYSTEM_FAULT & (0x01U)) << 1) | ((_m->PACMOD_SYSTEM_NOT_ACTIVE & (0x01U)) << 2) | ((_m->VEHICLE_REPORT_TIMEOUT & (0x01U)) << 3) | ((_m->VEHICLE_REPORT_FAULT & (0x01U)) << 4) | ((_m->LOW_ENGINE_RPM & (0x01U)) << 5) | ((_m->PRI_SAFETY_BRAKE_SIGNAL_1_FAULT & (0x01U)) << 6) | ((_m->PRI_SAFETY_BRAKE_SIGNAL_2_FAULT & (0x01U)) << 7);
  cframe->Data[2] |= (_m->SEC_SAFETY_BRAKE_SIGNAL_1_FAULT & (0x01U)) | ((_m->SEC_SAFETY_BRAKE_SIGNAL_2_FAULT & (0x01U)) << 1) | ((_m->PRIMARY_PROCESSOR_FAULT & (0x01U)) << 2) | ((_m->SECONDARY_PROCESSOR_FAULT & (0x01U)) << 3) | ((_m->REMOTE_STOP_CMD & (0x01U)) << 4) | ((_m->PRI_SAFETY_BRAKE_PRESSURE_FAULT & (0x01U)) << 5);

  cframe->MsgId = SAFETY_FUNC_CRITICAL_STOP_RPT_CANID;
  cframe->DLC = SAFETY_FUNC_CRITICAL_STOP_RPT_DLC;
  cframe->IDE = SAFETY_FUNC_CRITICAL_STOP_RPT_IDE;
  return SAFETY_FUNC_CRITICAL_STOP_RPT_CANID;
}

#else

uint32_t Pack_SAFETY_FUNC_CRITICAL_STOP_RPT_pacmod13(SAFETY_FUNC_CRITICAL_STOP_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SAFETY_FUNC_CRITICAL_STOP_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->AUTOMS_MAN_OPCTRL_FAULT & (0x01U)) | ((_m->REMOTE_STOP_FAULT & (0x01U)) << 1) | ((_m->SAFETY_BRAKE_OPCTRL_OFF & (0x01U)) << 2) | ((_m->SAFETY_BRAKE_CMD_TIMEOUT & (0x01U)) << 3) | ((_m->SAFETY_FUNC_CMD_TIMEOUT & (0x01U)) << 4) | ((_m->SAFETY_FUNC_CRITICAL_STOP_1_CMD & (0x01U)) << 5) | ((_m->SAFETY_FUNC_CRITICAL_STOP_2_CMD & (0x01U)) << 6) | ((_m->SAFETY_FUNC_NONE_CMD & (0x01U)) << 7);
  _d[1] |= (_m->PACMOD_SYSTEM_TIMEOUT & (0x01U)) | ((_m->PACMOD_SYSTEM_FAULT & (0x01U)) << 1) | ((_m->PACMOD_SYSTEM_NOT_ACTIVE & (0x01U)) << 2) | ((_m->VEHICLE_REPORT_TIMEOUT & (0x01U)) << 3) | ((_m->VEHICLE_REPORT_FAULT & (0x01U)) << 4) | ((_m->LOW_ENGINE_RPM & (0x01U)) << 5) | ((_m->PRI_SAFETY_BRAKE_SIGNAL_1_FAULT & (0x01U)) << 6) | ((_m->PRI_SAFETY_BRAKE_SIGNAL_2_FAULT & (0x01U)) << 7);
  _d[2] |= (_m->SEC_SAFETY_BRAKE_SIGNAL_1_FAULT & (0x01U)) | ((_m->SEC_SAFETY_BRAKE_SIGNAL_2_FAULT & (0x01U)) << 1) | ((_m->PRIMARY_PROCESSOR_FAULT & (0x01U)) << 2) | ((_m->SECONDARY_PROCESSOR_FAULT & (0x01U)) << 3) | ((_m->REMOTE_STOP_CMD & (0x01U)) << 4) | ((_m->PRI_SAFETY_BRAKE_PRESSURE_FAULT & (0x01U)) << 5);

  *_len = SAFETY_FUNC_CRITICAL_STOP_RPT_DLC;
  *_ide = SAFETY_FUNC_CRITICAL_STOP_RPT_IDE;
  return SAFETY_FUNC_CRITICAL_STOP_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_WATCHDOG_RPT_2_pacmod13(WATCHDOG_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ACCEL_RPT_TIMEOUT = (_d[0] & (0x01U));
  _m->BRAKE_RPT_TIMEOUT = ((_d[0] >> 1) & (0x01U));
  _m->BRAKE_DECEL_RPT_TIMEOUT = ((_d[0] >> 2) & (0x01U));
  _m->CABIN_CLIMATE_RPT_TIMEOUT = ((_d[0] >> 3) & (0x01U));
  _m->CABIN_FAN_SPEED_RPT_TIMEOUT = ((_d[0] >> 4) & (0x01U));
  _m->CABIN_TEMP_RPT_TIMEOUT = ((_d[0] >> 5) & (0x01U));
  _m->CRUISE_CONTROL_RPT_TIMEOUT = ((_d[0] >> 6) & (0x01U));
  _m->DASH_LEFT_RPT_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->DASH_RIGHT_RPT_TIMEOUT = (_d[1] & (0x01U));
  _m->ENGINE_BRAKE_RPT_TIMEOUT = ((_d[1] >> 1) & (0x01U));
  _m->HAZARD_LIGHTS_RPT_TIMEOUT = ((_d[1] >> 2) & (0x01U));
  _m->HEADLIGHT_RPT_TIMEOUT = ((_d[1] >> 3) & (0x01U));
  _m->HORN_RPT_TIMEOUT = ((_d[1] >> 4) & (0x01U));
  _m->MARKER_LAMP_RPT_TIMEOUT = ((_d[1] >> 5) & (0x01U));
  _m->MEDIA_CONTROLS_RPT_TIMEOUT = ((_d[1] >> 6) & (0x01U));
  _m->PARKING_BRAKE_RPT_TIMEOUT = ((_d[1] >> 7) & (0x01U));
  _m->REAR_PASS_DOOR_RPT_TIMEOUT = (_d[2] & (0x01U));
  _m->SHIFT_RPT_TIMEOUT = ((_d[2] >> 1) & (0x01U));
  _m->SPRAYER_RPT_TIMEOUT = ((_d[2] >> 2) & (0x01U));
  _m->STEERING_RPT_TIMEOUT = ((_d[2] >> 3) & (0x01U));
  _m->TURN_RPT_TIMEOUT = ((_d[2] >> 4) & (0x01U));
  _m->WIPER_RPT_TIMEOUT = ((_d[2] >> 5) & (0x01U));
  _m->PACMOD1_SANITY_FAULT = ((_d[2] >> 6) & (0x01U));
  _m->PACMOD2_SANITY_FAULT = ((_d[2] >> 7) & (0x01U));
  _m->PACMOD3_SANITY_FAULT = (_d[3] & (0x01U));
  _m->PACMINI1_SANITY_FAULT = ((_d[3] >> 1) & (0x01U));
  _m->PACMINI2_SANITY_FAULT = ((_d[3] >> 2) & (0x01U));
  _m->PACMINI3_SANITY_FAULT = ((_d[3] >> 3) & (0x01U));
  _m->PACMOD1_COMPONENT_RPT_TIMEOUT = ((_d[3] >> 4) & (0x01U));
  _m->PACMOD2_COMPONENT_RPT_TIMEOUT = ((_d[3] >> 5) & (0x01U));
  _m->PACMOD3_COMPONENT_RPT_TIMEOUT = ((_d[3] >> 6) & (0x01U));
  _m->PACMINI1_COMPONENT_RPT_TIMEOUT = ((_d[3] >> 7) & (0x01U));
  _m->PACMINI2_COMPONENT_RPT_TIMEOUT = (_d[4] & (0x01U));
  _m->PACMINI3_COMPONENT_RPT_TIMEOUT = ((_d[4] >> 1) & (0x01U));
  _m->PACMOD1_SYSTEM_PRESENT_FAULT = ((_d[4] >> 2) & (0x01U));
  _m->PACMOD2_SYSTEM_PRESENT_FAULT = ((_d[4] >> 3) & (0x01U));
  _m->PACMOD3_SYSTEM_PRESENT_FAULT = ((_d[4] >> 4) & (0x01U));
  _m->PACMINI1_SYSTEM_PRESENT_FAULT = ((_d[4] >> 5) & (0x01U));
  _m->PACMINI2_SYSTEM_PRESENT_FAULT = ((_d[4] >> 6) & (0x01U));
  _m->PACMINI3_SYSTEM_PRESENT_FAULT = ((_d[4] >> 7) & (0x01U));
  _m->DRIVE_MODE_INVALID = (_d[5] & (0x01U));
  _m->GLOBAL_CMD_SANITY_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->GLOBAL_CMD_TIMEOUT = ((_d[5] >> 2) & (0x01U));
  _m->EXHAUST_BRAKE_RPT_TIMEOUT = ((_d[5] >> 3) & (0x01U));
  _m->POWER_TAKE_OFF_RPT_TIMEOUT = ((_d[5] >> 4) & (0x01U));
  _m->TIPPER_BODY_00_RPT_TIMEOUT = ((_d[5] >> 5) & (0x01U));
  _m->TRAILER_AIR_SUPPLY_RPT_TIMEOUT = ((_d[5] >> 6) & (0x01U));
  _m->TRAILER_BRAKE_RPT_TIMEOUT = ((_d[5] >> 7) & (0x01U));
  _m->ENGINE_RPT_TIMEOUT = (_d[6] & (0x01U));
  _m->TIPPER_BODY_01_RPT_TIMEOUT = ((_d[6] >> 1) & (0x01U));
  _m->TIPPER_BODY_02_RPT_TIMEOUT = ((_d[6] >> 2) & (0x01U));
  _m->DIFFERENTIAL_LOCKS_RPT_TIMEOUT = ((_d[6] >> 3) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WATCHDOG_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WATCHDOG_RPT_2_pacmod13(&_m->mon1, WATCHDOG_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return WATCHDOG_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_WATCHDOG_RPT_2_pacmod13(WATCHDOG_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < WATCHDOG_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ACCEL_RPT_TIMEOUT & (0x01U)) | ((_m->BRAKE_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->BRAKE_DECEL_RPT_TIMEOUT & (0x01U)) << 2) | ((_m->CABIN_CLIMATE_RPT_TIMEOUT & (0x01U)) << 3) | ((_m->CABIN_FAN_SPEED_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->CABIN_TEMP_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_RPT_TIMEOUT & (0x01U)) << 6) | ((_m->DASH_LEFT_RPT_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_RIGHT_RPT_TIMEOUT & (0x01U)) | ((_m->ENGINE_BRAKE_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->HAZARD_LIGHTS_RPT_TIMEOUT & (0x01U)) << 2) | ((_m->HEADLIGHT_RPT_TIMEOUT & (0x01U)) << 3) | ((_m->HORN_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->MARKER_LAMP_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->MEDIA_CONTROLS_RPT_TIMEOUT & (0x01U)) << 6) | ((_m->PARKING_BRAKE_RPT_TIMEOUT & (0x01U)) << 7);
  cframe->Data[2] |= (_m->REAR_PASS_DOOR_RPT_TIMEOUT & (0x01U)) | ((_m->SHIFT_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->SPRAYER_RPT_TIMEOUT & (0x01U)) << 2) | ((_m->STEERING_RPT_TIMEOUT & (0x01U)) << 3) | ((_m->TURN_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->WIPER_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->PACMOD1_SANITY_FAULT & (0x01U)) << 6) | ((_m->PACMOD2_SANITY_FAULT & (0x01U)) << 7);
  cframe->Data[3] |= (_m->PACMOD3_SANITY_FAULT & (0x01U)) | ((_m->PACMINI1_SANITY_FAULT & (0x01U)) << 1) | ((_m->PACMINI2_SANITY_FAULT & (0x01U)) << 2) | ((_m->PACMINI3_SANITY_FAULT & (0x01U)) << 3) | ((_m->PACMOD1_COMPONENT_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->PACMOD2_COMPONENT_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->PACMOD3_COMPONENT_RPT_TIMEOUT & (0x01U)) << 6) | ((_m->PACMINI1_COMPONENT_RPT_TIMEOUT & (0x01U)) << 7);
  cframe->Data[4] |= (_m->PACMINI2_COMPONENT_RPT_TIMEOUT & (0x01U)) | ((_m->PACMINI3_COMPONENT_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->PACMOD1_SYSTEM_PRESENT_FAULT & (0x01U)) << 2) | ((_m->PACMOD2_SYSTEM_PRESENT_FAULT & (0x01U)) << 3) | ((_m->PACMOD3_SYSTEM_PRESENT_FAULT & (0x01U)) << 4) | ((_m->PACMINI1_SYSTEM_PRESENT_FAULT & (0x01U)) << 5) | ((_m->PACMINI2_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->PACMINI3_SYSTEM_PRESENT_FAULT & (0x01U)) << 7);
  cframe->Data[5] |= (_m->DRIVE_MODE_INVALID & (0x01U)) | ((_m->GLOBAL_CMD_SANITY_FAULT & (0x01U)) << 1) | ((_m->GLOBAL_CMD_TIMEOUT & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE_RPT_TIMEOUT & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->TIPPER_BODY_00_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY_RPT_TIMEOUT & (0x01U)) << 6) | ((_m->TRAILER_BRAKE_RPT_TIMEOUT & (0x01U)) << 7);
  cframe->Data[6] |= (_m->ENGINE_RPT_TIMEOUT & (0x01U)) | ((_m->TIPPER_BODY_01_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->TIPPER_BODY_02_RPT_TIMEOUT & (0x01U)) << 2) | ((_m->DIFFERENTIAL_LOCKS_RPT_TIMEOUT & (0x01U)) << 3);

  cframe->MsgId = WATCHDOG_RPT_2_CANID;
  cframe->DLC = WATCHDOG_RPT_2_DLC;
  cframe->IDE = WATCHDOG_RPT_2_IDE;
  return WATCHDOG_RPT_2_CANID;
}

#else

uint32_t Pack_WATCHDOG_RPT_2_pacmod13(WATCHDOG_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WATCHDOG_RPT_2_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ACCEL_RPT_TIMEOUT & (0x01U)) | ((_m->BRAKE_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->BRAKE_DECEL_RPT_TIMEOUT & (0x01U)) << 2) | ((_m->CABIN_CLIMATE_RPT_TIMEOUT & (0x01U)) << 3) | ((_m->CABIN_FAN_SPEED_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->CABIN_TEMP_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_RPT_TIMEOUT & (0x01U)) << 6) | ((_m->DASH_LEFT_RPT_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_RIGHT_RPT_TIMEOUT & (0x01U)) | ((_m->ENGINE_BRAKE_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->HAZARD_LIGHTS_RPT_TIMEOUT & (0x01U)) << 2) | ((_m->HEADLIGHT_RPT_TIMEOUT & (0x01U)) << 3) | ((_m->HORN_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->MARKER_LAMP_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->MEDIA_CONTROLS_RPT_TIMEOUT & (0x01U)) << 6) | ((_m->PARKING_BRAKE_RPT_TIMEOUT & (0x01U)) << 7);
  _d[2] |= (_m->REAR_PASS_DOOR_RPT_TIMEOUT & (0x01U)) | ((_m->SHIFT_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->SPRAYER_RPT_TIMEOUT & (0x01U)) << 2) | ((_m->STEERING_RPT_TIMEOUT & (0x01U)) << 3) | ((_m->TURN_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->WIPER_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->PACMOD1_SANITY_FAULT & (0x01U)) << 6) | ((_m->PACMOD2_SANITY_FAULT & (0x01U)) << 7);
  _d[3] |= (_m->PACMOD3_SANITY_FAULT & (0x01U)) | ((_m->PACMINI1_SANITY_FAULT & (0x01U)) << 1) | ((_m->PACMINI2_SANITY_FAULT & (0x01U)) << 2) | ((_m->PACMINI3_SANITY_FAULT & (0x01U)) << 3) | ((_m->PACMOD1_COMPONENT_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->PACMOD2_COMPONENT_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->PACMOD3_COMPONENT_RPT_TIMEOUT & (0x01U)) << 6) | ((_m->PACMINI1_COMPONENT_RPT_TIMEOUT & (0x01U)) << 7);
  _d[4] |= (_m->PACMINI2_COMPONENT_RPT_TIMEOUT & (0x01U)) | ((_m->PACMINI3_COMPONENT_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->PACMOD1_SYSTEM_PRESENT_FAULT & (0x01U)) << 2) | ((_m->PACMOD2_SYSTEM_PRESENT_FAULT & (0x01U)) << 3) | ((_m->PACMOD3_SYSTEM_PRESENT_FAULT & (0x01U)) << 4) | ((_m->PACMINI1_SYSTEM_PRESENT_FAULT & (0x01U)) << 5) | ((_m->PACMINI2_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->PACMINI3_SYSTEM_PRESENT_FAULT & (0x01U)) << 7);
  _d[5] |= (_m->DRIVE_MODE_INVALID & (0x01U)) | ((_m->GLOBAL_CMD_SANITY_FAULT & (0x01U)) << 1) | ((_m->GLOBAL_CMD_TIMEOUT & (0x01U)) << 2) | ((_m->EXHAUST_BRAKE_RPT_TIMEOUT & (0x01U)) << 3) | ((_m->POWER_TAKE_OFF_RPT_TIMEOUT & (0x01U)) << 4) | ((_m->TIPPER_BODY_00_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->TRAILER_AIR_SUPPLY_RPT_TIMEOUT & (0x01U)) << 6) | ((_m->TRAILER_BRAKE_RPT_TIMEOUT & (0x01U)) << 7);
  _d[6] |= (_m->ENGINE_RPT_TIMEOUT & (0x01U)) | ((_m->TIPPER_BODY_01_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->TIPPER_BODY_02_RPT_TIMEOUT & (0x01U)) << 2) | ((_m->DIFFERENTIAL_LOCKS_RPT_TIMEOUT & (0x01U)) << 3);

  *_len = WATCHDOG_RPT_2_DLC;
  *_ide = WATCHDOG_RPT_2_IDE;
  return WATCHDOG_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_VIN_RPT_2_pacmod13(VIN_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->VEHICLE_IDENTIFIER_SECTION_10 = (_d[0] & (0xFFU));
  _m->VEHICLE_IDENTIFIER_SECTION_11 = (_d[1] & (0xFFU));
  _m->VEHICLE_IDENTIFIER_SECTION_12 = (_d[2] & (0xFFU));
  _m->VEHICLE_IDENTIFIER_SECTION_13 = (_d[3] & (0xFFU));
  _m->VEHICLE_IDENTIFIER_SECTION_14 = (_d[4] & (0xFFU));
  _m->VEHICLE_IDENTIFIER_SECTION_15 = (_d[5] & (0xFFU));
  _m->VEHICLE_IDENTIFIER_SECTION_16 = (_d[6] & (0xFFU));
  _m->VEHICLE_IDENTIFIER_SECTION_17 = (_d[7] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VIN_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VIN_RPT_2_pacmod13(&_m->mon1, VIN_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return VIN_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_VIN_RPT_2_pacmod13(VIN_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < VIN_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->VEHICLE_IDENTIFIER_SECTION_10 & (0xFFU));
  cframe->Data[1] |= (_m->VEHICLE_IDENTIFIER_SECTION_11 & (0xFFU));
  cframe->Data[2] |= (_m->VEHICLE_IDENTIFIER_SECTION_12 & (0xFFU));
  cframe->Data[3] |= (_m->VEHICLE_IDENTIFIER_SECTION_13 & (0xFFU));
  cframe->Data[4] |= (_m->VEHICLE_IDENTIFIER_SECTION_14 & (0xFFU));
  cframe->Data[5] |= (_m->VEHICLE_IDENTIFIER_SECTION_15 & (0xFFU));
  cframe->Data[6] |= (_m->VEHICLE_IDENTIFIER_SECTION_16 & (0xFFU));
  cframe->Data[7] |= (_m->VEHICLE_IDENTIFIER_SECTION_17 & (0xFFU));

  cframe->MsgId = VIN_RPT_2_CANID;
  cframe->DLC = VIN_RPT_2_DLC;
  cframe->IDE = VIN_RPT_2_IDE;
  return VIN_RPT_2_CANID;
}

#else

uint32_t Pack_VIN_RPT_2_pacmod13(VIN_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < VIN_RPT_2_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->VEHICLE_IDENTIFIER_SECTION_10 & (0xFFU));
  _d[1] |= (_m->VEHICLE_IDENTIFIER_SECTION_11 & (0xFFU));
  _d[2] |= (_m->VEHICLE_IDENTIFIER_SECTION_12 & (0xFFU));
  _d[3] |= (_m->VEHICLE_IDENTIFIER_SECTION_13 & (0xFFU));
  _d[4] |= (_m->VEHICLE_IDENTIFIER_SECTION_14 & (0xFFU));
  _d[5] |= (_m->VEHICLE_IDENTIFIER_SECTION_15 & (0xFFU));
  _d[6] |= (_m->VEHICLE_IDENTIFIER_SECTION_16 & (0xFFU));
  _d[7] |= (_m->VEHICLE_IDENTIFIER_SECTION_17 & (0xFFU));

  *_len = VIN_RPT_2_DLC;
  *_ide = VIN_RPT_2_IDE;
  return VIN_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_NOTIFICATION_RPT_pacmod13(NOTIFICATION_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BUZZER_STATUS = (_d[0] & (0x03U));
  _m->LIGHT_STATUS = ((_d[0] >> 2) & (0x03U));
  _m->LIGHT_COLOR = ((_d[0] >> 4) & (0x0FU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < NOTIFICATION_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_NOTIFICATION_RPT_pacmod13(&_m->mon1, NOTIFICATION_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return NOTIFICATION_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_NOTIFICATION_RPT_pacmod13(NOTIFICATION_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < NOTIFICATION_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BUZZER_STATUS & (0x03U)) | ((_m->LIGHT_STATUS & (0x03U)) << 2) | ((_m->LIGHT_COLOR & (0x0FU)) << 4);

  cframe->MsgId = NOTIFICATION_RPT_CANID;
  cframe->DLC = NOTIFICATION_RPT_DLC;
  cframe->IDE = NOTIFICATION_RPT_IDE;
  return NOTIFICATION_RPT_CANID;
}

#else

uint32_t Pack_NOTIFICATION_RPT_pacmod13(NOTIFICATION_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < NOTIFICATION_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BUZZER_STATUS & (0x03U)) | ((_m->LIGHT_STATUS & (0x03U)) << 2) | ((_m->LIGHT_COLOR & (0x0FU)) << 4);

  *_len = NOTIFICATION_RPT_DLC;
  *_ide = NOTIFICATION_RPT_IDE;
  return NOTIFICATION_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_AIR_PRESSURE_RPT_pacmod13(AIR_PRESSURE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PNEUMATIC_SUPPLY_PRESSURE_phys = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_fromS(_m->PNEUMATIC_SUPPLY_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_CIRCUIT_1_PRESSURE_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_CIRCUIT_1_PRESSURE_phys = PACMOD13_BRAKE_CIRCUIT_1_PRESSURE_ro_fromS(_m->BRAKE_CIRCUIT_1_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_CIRCUIT_2_PRESSURE_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_CIRCUIT_2_PRESSURE_phys = PACMOD13_BRAKE_CIRCUIT_2_PRESSURE_ro_fromS(_m->BRAKE_CIRCUIT_2_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->PARK_TRAILER_AIR_PRESSURE_ro = (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PARK_TRAILER_AIR_PRESSURE_phys = PACMOD13_PARK_TRAILER_AIR_PRESSURE_ro_fromS(_m->PARK_TRAILER_AIR_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->POWERTRAIN_AIR_PRESSURE_ro = (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->POWERTRAIN_AIR_PRESSURE_phys = PACMOD13_POWERTRAIN_AIR_PRESSURE_ro_fromS(_m->POWERTRAIN_AIR_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->AIR_COMPRESSOR_STATUS = (_d[5] & (0x03U));
  _m->PNEUMATIC_SUPPLY_PRESSURE_AVAIL = (_d[6] & (0x01U));
  _m->BRAKE_CIRCUIT_1_PRESSURE_AVAIL = ((_d[6] >> 1) & (0x01U));
  _m->BRAKE_CIRCUIT_2_PRESSURE_AVAIL = ((_d[6] >> 2) & (0x01U));
  _m->PARK_TRAILER_AIR_PRESSURE_AVAIL = ((_d[6] >> 3) & (0x01U));
  _m->POWERTRAIN_AIR_PRESSURE_AVAIL = ((_d[6] >> 4) & (0x01U));
  _m->AIR_COMPRESSOR_STATUS_AVAIL = ((_d[6] >> 5) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < AIR_PRESSURE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_AIR_PRESSURE_RPT_pacmod13(&_m->mon1, AIR_PRESSURE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return AIR_PRESSURE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_AIR_PRESSURE_RPT_pacmod13(AIR_PRESSURE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < AIR_PRESSURE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
  _m->BRAKE_CIRCUIT_1_PRESSURE_ro = PACMOD13_BRAKE_CIRCUIT_1_PRESSURE_ro_toS(_m->BRAKE_CIRCUIT_1_PRESSURE_phys);
  _m->BRAKE_CIRCUIT_2_PRESSURE_ro = PACMOD13_BRAKE_CIRCUIT_2_PRESSURE_ro_toS(_m->BRAKE_CIRCUIT_2_PRESSURE_phys);
  _m->PARK_TRAILER_AIR_PRESSURE_ro = PACMOD13_PARK_TRAILER_AIR_PRESSURE_ro_toS(_m->PARK_TRAILER_AIR_PRESSURE_phys);
  _m->POWERTRAIN_AIR_PRESSURE_ro = PACMOD13_POWERTRAIN_AIR_PRESSURE_ro_toS(_m->POWERTRAIN_AIR_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));
  cframe->Data[1] |= (_m->BRAKE_CIRCUIT_1_PRESSURE_ro & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_CIRCUIT_2_PRESSURE_ro & (0xFFU));
  cframe->Data[3] |= (_m->PARK_TRAILER_AIR_PRESSURE_ro & (0xFFU));
  cframe->Data[4] |= (_m->POWERTRAIN_AIR_PRESSURE_ro & (0xFFU));
  cframe->Data[5] |= (_m->AIR_COMPRESSOR_STATUS & (0x03U));
  cframe->Data[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_AVAIL & (0x01U)) | ((_m->BRAKE_CIRCUIT_1_PRESSURE_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_CIRCUIT_2_PRESSURE_AVAIL & (0x01U)) << 2) | ((_m->PARK_TRAILER_AIR_PRESSURE_AVAIL & (0x01U)) << 3) | ((_m->POWERTRAIN_AIR_PRESSURE_AVAIL & (0x01U)) << 4) | ((_m->AIR_COMPRESSOR_STATUS_AVAIL & (0x01U)) << 5);

  cframe->MsgId = AIR_PRESSURE_RPT_CANID;
  cframe->DLC = AIR_PRESSURE_RPT_DLC;
  cframe->IDE = AIR_PRESSURE_RPT_IDE;
  return AIR_PRESSURE_RPT_CANID;
}

#else

uint32_t Pack_AIR_PRESSURE_RPT_pacmod13(AIR_PRESSURE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < AIR_PRESSURE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
  _m->BRAKE_CIRCUIT_1_PRESSURE_ro = PACMOD13_BRAKE_CIRCUIT_1_PRESSURE_ro_toS(_m->BRAKE_CIRCUIT_1_PRESSURE_phys);
  _m->BRAKE_CIRCUIT_2_PRESSURE_ro = PACMOD13_BRAKE_CIRCUIT_2_PRESSURE_ro_toS(_m->BRAKE_CIRCUIT_2_PRESSURE_phys);
  _m->PARK_TRAILER_AIR_PRESSURE_ro = PACMOD13_PARK_TRAILER_AIR_PRESSURE_ro_toS(_m->PARK_TRAILER_AIR_PRESSURE_phys);
  _m->POWERTRAIN_AIR_PRESSURE_ro = PACMOD13_POWERTRAIN_AIR_PRESSURE_ro_toS(_m->POWERTRAIN_AIR_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));
  _d[1] |= (_m->BRAKE_CIRCUIT_1_PRESSURE_ro & (0xFFU));
  _d[2] |= (_m->BRAKE_CIRCUIT_2_PRESSURE_ro & (0xFFU));
  _d[3] |= (_m->PARK_TRAILER_AIR_PRESSURE_ro & (0xFFU));
  _d[4] |= (_m->POWERTRAIN_AIR_PRESSURE_ro & (0xFFU));
  _d[5] |= (_m->AIR_COMPRESSOR_STATUS & (0x03U));
  _d[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_AVAIL & (0x01U)) | ((_m->BRAKE_CIRCUIT_1_PRESSURE_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_CIRCUIT_2_PRESSURE_AVAIL & (0x01U)) << 2) | ((_m->PARK_TRAILER_AIR_PRESSURE_AVAIL & (0x01U)) << 3) | ((_m->POWERTRAIN_AIR_PRESSURE_AVAIL & (0x01U)) << 4) | ((_m->AIR_COMPRESSOR_STATUS_AVAIL & (0x01U)) << 5);

  *_len = AIR_PRESSURE_RPT_DLC;
  *_ide = AIR_PRESSURE_RPT_IDE;
  return AIR_PRESSURE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ENGINE_AUX_RPT_2_pacmod13(ENGINE_AUX_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->FUEL_RATE_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->FUEL_RATE_phys = (sigfloat_t)(PACMOD13_FUEL_RATE_ro_fromS(_m->FUEL_RATE_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->FUEL_RATE_AVAIL = (_d[2] & (0x01U));
  _m->OIL_LEVEL_AVAIL = ((_d[2] >> 1) & (0x01U));
  _m->OIL_PRESSURE_AVAIL = ((_d[2] >> 2) & (0x01U));
  _m->OIL_LEVEL_ro = (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OIL_LEVEL_phys = (sigfloat_t)(PACMOD13_OIL_LEVEL_ro_fromS(_m->OIL_LEVEL_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->OIL_PRESSURE_ro = (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->OIL_PRESSURE_phys = PACMOD13_OIL_PRESSURE_ro_fromS(_m->OIL_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ENGINE_AUX_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ENGINE_AUX_RPT_2_pacmod13(&_m->mon1, ENGINE_AUX_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ENGINE_AUX_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ENGINE_AUX_RPT_2_pacmod13(ENGINE_AUX_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ENGINE_AUX_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->FUEL_RATE_ro = PACMOD13_FUEL_RATE_ro_toS(_m->FUEL_RATE_phys);
  _m->OIL_LEVEL_ro = PACMOD13_OIL_LEVEL_ro_toS(_m->OIL_LEVEL_phys);
  _m->OIL_PRESSURE_ro = PACMOD13_OIL_PRESSURE_ro_toS(_m->OIL_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->FUEL_RATE_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->FUEL_RATE_ro & (0xFFU));
  cframe->Data[2] |= (_m->FUEL_RATE_AVAIL & (0x01U)) | ((_m->OIL_LEVEL_AVAIL & (0x01U)) << 1) | ((_m->OIL_PRESSURE_AVAIL & (0x01U)) << 2);
  cframe->Data[3] |= (_m->OIL_LEVEL_ro & (0xFFU));
  cframe->Data[4] |= (_m->OIL_PRESSURE_ro & (0xFFU));

  cframe->MsgId = ENGINE_AUX_RPT_2_CANID;
  cframe->DLC = ENGINE_AUX_RPT_2_DLC;
  cframe->IDE = ENGINE_AUX_RPT_2_IDE;
  return ENGINE_AUX_RPT_2_CANID;
}

#else

uint32_t Pack_ENGINE_AUX_RPT_2_pacmod13(ENGINE_AUX_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ENGINE_AUX_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->FUEL_RATE_ro = PACMOD13_FUEL_RATE_ro_toS(_m->FUEL_RATE_phys);
  _m->OIL_LEVEL_ro = PACMOD13_OIL_LEVEL_ro_toS(_m->OIL_LEVEL_phys);
  _m->OIL_PRESSURE_ro = PACMOD13_OIL_PRESSURE_ro_toS(_m->OIL_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->FUEL_RATE_ro >> 8) & (0xFFU));
  _d[1] |= (_m->FUEL_RATE_ro & (0xFFU));
  _d[2] |= (_m->FUEL_RATE_AVAIL & (0x01U)) | ((_m->OIL_LEVEL_AVAIL & (0x01U)) << 1) | ((_m->OIL_PRESSURE_AVAIL & (0x01U)) << 2);
  _d[3] |= (_m->OIL_LEVEL_ro & (0xFFU));
  _d[4] |= (_m->OIL_PRESSURE_ro & (0xFFU));

  *_len = ENGINE_AUX_RPT_2_DLC;
  *_ide = ENGINE_AUX_RPT_2_IDE;
  return ENGINE_AUX_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_WHEEL_SPEED_RPT_2_pacmod13(WHEEL_SPEED_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->WHEEL_SPD_AXLE_3_LEFT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_3_LEFT_phys = (sigfloat_t)(PACMOD13_WHEEL_SPD_AXLE_3_LEFT_ro_fromS(_m->WHEEL_SPD_AXLE_3_LEFT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->WHEEL_SPD_AXLE_3_RIGHT_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_3_RIGHT_phys = (sigfloat_t)(PACMOD13_WHEEL_SPD_AXLE_3_RIGHT_ro_fromS(_m->WHEEL_SPD_AXLE_3_RIGHT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->WHEEL_SPD_AXLE_4_LEFT_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_4_LEFT_phys = (sigfloat_t)(PACMOD13_WHEEL_SPD_AXLE_4_LEFT_ro_fromS(_m->WHEEL_SPD_AXLE_4_LEFT_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->WHEEL_SPD_AXLE_4_RIGHT_ro = __ext_sig__(( ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_4_RIGHT_phys = (sigfloat_t)(PACMOD13_WHEEL_SPD_AXLE_4_RIGHT_ro_fromS(_m->WHEEL_SPD_AXLE_4_RIGHT_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WHEEL_SPEED_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WHEEL_SPEED_RPT_2_pacmod13(&_m->mon1, WHEEL_SPEED_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return WHEEL_SPEED_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_WHEEL_SPEED_RPT_2_pacmod13(WHEEL_SPEED_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < WHEEL_SPEED_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_3_LEFT_ro = PACMOD13_WHEEL_SPD_AXLE_3_LEFT_ro_toS(_m->WHEEL_SPD_AXLE_3_LEFT_phys);
  _m->WHEEL_SPD_AXLE_3_RIGHT_ro = PACMOD13_WHEEL_SPD_AXLE_3_RIGHT_ro_toS(_m->WHEEL_SPD_AXLE_3_RIGHT_phys);
  _m->WHEEL_SPD_AXLE_4_LEFT_ro = PACMOD13_WHEEL_SPD_AXLE_4_LEFT_ro_toS(_m->WHEEL_SPD_AXLE_4_LEFT_phys);
  _m->WHEEL_SPD_AXLE_4_RIGHT_ro = PACMOD13_WHEEL_SPD_AXLE_4_RIGHT_ro_toS(_m->WHEEL_SPD_AXLE_4_RIGHT_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->WHEEL_SPD_AXLE_3_LEFT_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->WHEEL_SPD_AXLE_3_LEFT_ro & (0xFFU));
  cframe->Data[2] |= ((_m->WHEEL_SPD_AXLE_3_RIGHT_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->WHEEL_SPD_AXLE_3_RIGHT_ro & (0xFFU));
  cframe->Data[4] |= ((_m->WHEEL_SPD_AXLE_4_LEFT_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->WHEEL_SPD_AXLE_4_LEFT_ro & (0xFFU));
  cframe->Data[6] |= ((_m->WHEEL_SPD_AXLE_4_RIGHT_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->WHEEL_SPD_AXLE_4_RIGHT_ro & (0xFFU));

  cframe->MsgId = WHEEL_SPEED_RPT_2_CANID;
  cframe->DLC = WHEEL_SPEED_RPT_2_DLC;
  cframe->IDE = WHEEL_SPEED_RPT_2_IDE;
  return WHEEL_SPEED_RPT_2_CANID;
}

#else

uint32_t Pack_WHEEL_SPEED_RPT_2_pacmod13(WHEEL_SPEED_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WHEEL_SPEED_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPD_AXLE_3_LEFT_ro = PACMOD13_WHEEL_SPD_AXLE_3_LEFT_ro_toS(_m->WHEEL_SPD_AXLE_3_LEFT_phys);
  _m->WHEEL_SPD_AXLE_3_RIGHT_ro = PACMOD13_WHEEL_SPD_AXLE_3_RIGHT_ro_toS(_m->WHEEL_SPD_AXLE_3_RIGHT_phys);
  _m->WHEEL_SPD_AXLE_4_LEFT_ro = PACMOD13_WHEEL_SPD_AXLE_4_LEFT_ro_toS(_m->WHEEL_SPD_AXLE_4_LEFT_phys);
  _m->WHEEL_SPD_AXLE_4_RIGHT_ro = PACMOD13_WHEEL_SPD_AXLE_4_RIGHT_ro_toS(_m->WHEEL_SPD_AXLE_4_RIGHT_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->WHEEL_SPD_AXLE_3_LEFT_ro >> 8) & (0xFFU));
  _d[1] |= (_m->WHEEL_SPD_AXLE_3_LEFT_ro & (0xFFU));
  _d[2] |= ((_m->WHEEL_SPD_AXLE_3_RIGHT_ro >> 8) & (0xFFU));
  _d[3] |= (_m->WHEEL_SPD_AXLE_3_RIGHT_ro & (0xFFU));
  _d[4] |= ((_m->WHEEL_SPD_AXLE_4_LEFT_ro >> 8) & (0xFFU));
  _d[5] |= (_m->WHEEL_SPD_AXLE_4_LEFT_ro & (0xFFU));
  _d[6] |= ((_m->WHEEL_SPD_AXLE_4_RIGHT_ro >> 8) & (0xFFU));
  _d[7] |= (_m->WHEEL_SPD_AXLE_4_RIGHT_ro & (0xFFU));

  *_len = WHEEL_SPEED_RPT_2_DLC;
  *_ide = WHEEL_SPEED_RPT_2_IDE;
  return WHEEL_SPEED_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ENGINE_LOAD_FACTOR_RPT_pacmod13(ENGINE_LOAD_FACTOR_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DRVR_DEMANDED_ENG_TORQUE_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->DRVR_DEMANDED_ENG_TORQUE_phys = PACMOD13_DRVR_DEMANDED_ENG_TORQUE_ro_fromS(_m->DRVR_DEMANDED_ENG_TORQUE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->ACTUAL_ENGINE_TORQUE_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->ACTUAL_ENGINE_TORQUE_phys = PACMOD13_ACTUAL_ENGINE_TORQUE_ro_fromS(_m->ACTUAL_ENGINE_TORQUE_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->ENG_LOAD_AT_CURRENT_SPEED = (_d[2] & (0xFFU));
  _m->REFERENCE_ENGINE_TORQUE = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
  _m->DRVR_DEMANDED_ENG_TORQUE_AVAIL = (_d[5] & (0x01U));
  _m->ACTUAL_ENGINE_TORQUE_AVAIL = ((_d[5] >> 1) & (0x01U));
  _m->ENG_LOAD_AT_CURRENT_SPEED_AVAIL = ((_d[5] >> 2) & (0x01U));
  _m->REFERENCE_ENGINE_TORQUE_AVAIL = ((_d[5] >> 3) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ENGINE_LOAD_FACTOR_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ENGINE_LOAD_FACTOR_RPT_pacmod13(&_m->mon1, ENGINE_LOAD_FACTOR_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ENGINE_LOAD_FACTOR_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ENGINE_LOAD_FACTOR_RPT_pacmod13(ENGINE_LOAD_FACTOR_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ENGINE_LOAD_FACTOR_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->DRVR_DEMANDED_ENG_TORQUE_ro = PACMOD13_DRVR_DEMANDED_ENG_TORQUE_ro_toS(_m->DRVR_DEMANDED_ENG_TORQUE_phys);
  _m->ACTUAL_ENGINE_TORQUE_ro = PACMOD13_ACTUAL_ENGINE_TORQUE_ro_toS(_m->ACTUAL_ENGINE_TORQUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->DRVR_DEMANDED_ENG_TORQUE_ro & (0xFFU));
  cframe->Data[1] |= (_m->ACTUAL_ENGINE_TORQUE_ro & (0xFFU));
  cframe->Data[2] |= (_m->ENG_LOAD_AT_CURRENT_SPEED & (0xFFU));
  cframe->Data[3] |= ((_m->REFERENCE_ENGINE_TORQUE >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->REFERENCE_ENGINE_TORQUE & (0xFFU));
  cframe->Data[5] |= (_m->DRVR_DEMANDED_ENG_TORQUE_AVAIL & (0x01U)) | ((_m->ACTUAL_ENGINE_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ENG_LOAD_AT_CURRENT_SPEED_AVAIL & (0x01U)) << 2) | ((_m->REFERENCE_ENGINE_TORQUE_AVAIL & (0x01U)) << 3);

  cframe->MsgId = ENGINE_LOAD_FACTOR_RPT_CANID;
  cframe->DLC = ENGINE_LOAD_FACTOR_RPT_DLC;
  cframe->IDE = ENGINE_LOAD_FACTOR_RPT_IDE;
  return ENGINE_LOAD_FACTOR_RPT_CANID;
}

#else

uint32_t Pack_ENGINE_LOAD_FACTOR_RPT_pacmod13(ENGINE_LOAD_FACTOR_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ENGINE_LOAD_FACTOR_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->DRVR_DEMANDED_ENG_TORQUE_ro = PACMOD13_DRVR_DEMANDED_ENG_TORQUE_ro_toS(_m->DRVR_DEMANDED_ENG_TORQUE_phys);
  _m->ACTUAL_ENGINE_TORQUE_ro = PACMOD13_ACTUAL_ENGINE_TORQUE_ro_toS(_m->ACTUAL_ENGINE_TORQUE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->DRVR_DEMANDED_ENG_TORQUE_ro & (0xFFU));
  _d[1] |= (_m->ACTUAL_ENGINE_TORQUE_ro & (0xFFU));
  _d[2] |= (_m->ENG_LOAD_AT_CURRENT_SPEED & (0xFFU));
  _d[3] |= ((_m->REFERENCE_ENGINE_TORQUE >> 8) & (0xFFU));
  _d[4] |= (_m->REFERENCE_ENGINE_TORQUE & (0xFFU));
  _d[5] |= (_m->DRVR_DEMANDED_ENG_TORQUE_AVAIL & (0x01U)) | ((_m->ACTUAL_ENGINE_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ENG_LOAD_AT_CURRENT_SPEED_AVAIL & (0x01U)) << 2) | ((_m->REFERENCE_ENGINE_TORQUE_AVAIL & (0x01U)) << 3);

  *_len = ENGINE_LOAD_FACTOR_RPT_DLC;
  *_ide = ENGINE_LOAD_FACTOR_RPT_IDE;
  return ENGINE_LOAD_FACTOR_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_BRAKE_PRESSURE_RPT_00_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PNEUMATIC_SUPPLY_PRESSURE_phys = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_fromS(_m->PNEUMATIC_SUPPLY_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_BRAKE_PRESSURE_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_BRAKE_PRESSURE_RPT_00_pacmod13(&_m->mon1, TRAILER_BRAKE_PRESSURE_RPT_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_BRAKE_PRESSURE_RPT_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_00_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  cframe->Data[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  cframe->Data[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  cframe->Data[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  cframe->Data[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  cframe->Data[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  cframe->MsgId = TRAILER_BRAKE_PRESSURE_RPT_00_CANID;
  cframe->DLC = TRAILER_BRAKE_PRESSURE_RPT_00_DLC;
  cframe->IDE = TRAILER_BRAKE_PRESSURE_RPT_00_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_00_CANID;
}

#else

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_00_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_00_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  _d[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  _d[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  _d[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  _d[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  _d[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  _d[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  *_len = TRAILER_BRAKE_PRESSURE_RPT_00_DLC;
  *_ide = TRAILER_BRAKE_PRESSURE_RPT_00_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_BRAKE_PRESSURE_RPT_01_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PNEUMATIC_SUPPLY_PRESSURE_phys = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_fromS(_m->PNEUMATIC_SUPPLY_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_BRAKE_PRESSURE_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_BRAKE_PRESSURE_RPT_01_pacmod13(&_m->mon1, TRAILER_BRAKE_PRESSURE_RPT_01_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_BRAKE_PRESSURE_RPT_01_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_01_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_01_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  cframe->Data[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  cframe->Data[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  cframe->Data[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  cframe->Data[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  cframe->Data[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  cframe->MsgId = TRAILER_BRAKE_PRESSURE_RPT_01_CANID;
  cframe->DLC = TRAILER_BRAKE_PRESSURE_RPT_01_DLC;
  cframe->IDE = TRAILER_BRAKE_PRESSURE_RPT_01_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_01_CANID;
}

#else

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_01_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_01_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  _d[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  _d[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  _d[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  _d[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  _d[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  _d[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  *_len = TRAILER_BRAKE_PRESSURE_RPT_01_DLC;
  *_ide = TRAILER_BRAKE_PRESSURE_RPT_01_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_01_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_BRAKE_PRESSURE_RPT_02_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_02_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PNEUMATIC_SUPPLY_PRESSURE_phys = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_fromS(_m->PNEUMATIC_SUPPLY_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_BRAKE_PRESSURE_RPT_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_BRAKE_PRESSURE_RPT_02_pacmod13(&_m->mon1, TRAILER_BRAKE_PRESSURE_RPT_02_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_BRAKE_PRESSURE_RPT_02_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_02_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_02_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_02_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  cframe->Data[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  cframe->Data[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  cframe->Data[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  cframe->Data[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  cframe->Data[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  cframe->MsgId = TRAILER_BRAKE_PRESSURE_RPT_02_CANID;
  cframe->DLC = TRAILER_BRAKE_PRESSURE_RPT_02_DLC;
  cframe->IDE = TRAILER_BRAKE_PRESSURE_RPT_02_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_02_CANID;
}

#else

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_02_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_02_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  _d[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  _d[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  _d[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  _d[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  _d[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  _d[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  *_len = TRAILER_BRAKE_PRESSURE_RPT_02_DLC;
  *_ide = TRAILER_BRAKE_PRESSURE_RPT_02_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_02_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_BRAKE_PRESSURE_RPT_03_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_03_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PNEUMATIC_SUPPLY_PRESSURE_phys = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_fromS(_m->PNEUMATIC_SUPPLY_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_BRAKE_PRESSURE_RPT_03_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_BRAKE_PRESSURE_RPT_03_pacmod13(&_m->mon1, TRAILER_BRAKE_PRESSURE_RPT_03_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_BRAKE_PRESSURE_RPT_03_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_03_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_03_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_03_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  cframe->Data[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  cframe->Data[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  cframe->Data[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  cframe->Data[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  cframe->Data[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  cframe->MsgId = TRAILER_BRAKE_PRESSURE_RPT_03_CANID;
  cframe->DLC = TRAILER_BRAKE_PRESSURE_RPT_03_DLC;
  cframe->IDE = TRAILER_BRAKE_PRESSURE_RPT_03_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_03_CANID;
}

#else

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_03_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_03_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_03_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  _d[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  _d[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  _d[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  _d[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  _d[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  _d[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  *_len = TRAILER_BRAKE_PRESSURE_RPT_03_DLC;
  *_ide = TRAILER_BRAKE_PRESSURE_RPT_03_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_03_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_BRAKE_PRESSURE_RPT_04_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_04_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = (_d[2] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = (_d[4] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_fromS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PNEUMATIC_SUPPLY_PRESSURE_phys = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_fromS(_m->PNEUMATIC_SUPPLY_PRESSURE_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_BRAKE_PRESSURE_RPT_04_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_BRAKE_PRESSURE_RPT_04_pacmod13(&_m->mon1, TRAILER_BRAKE_PRESSURE_RPT_04_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_BRAKE_PRESSURE_RPT_04_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_04_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_04_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_04_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  cframe->Data[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  cframe->Data[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  cframe->Data[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  cframe->Data[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  cframe->Data[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  cframe->MsgId = TRAILER_BRAKE_PRESSURE_RPT_04_CANID;
  cframe->DLC = TRAILER_BRAKE_PRESSURE_RPT_04_DLC;
  cframe->IDE = TRAILER_BRAKE_PRESSURE_RPT_04_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_04_CANID;
}

#else

uint32_t Pack_TRAILER_BRAKE_PRESSURE_RPT_04_pacmod13(TRAILER_BRAKE_PRESSURE_RPT_04_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_BRAKE_PRESSURE_RPT_04_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BRAKE_PRESSURE_AXLE_1_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_1_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_1_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_2_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_2_RIGHT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_LEFT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_LEFT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_LEFT_phys);
  _m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro = PACMOD13_BRAKE_PRESSURE_AXLE_3_RIGHT_ro_toS(_m->BRAKE_PRESSURE_AXLE_3_RIGHT_phys);
  _m->PNEUMATIC_SUPPLY_PRESSURE_ro = PACMOD13_PNEUMATIC_SUPPLY_PRESSURE_ro_toS(_m->PNEUMATIC_SUPPLY_PRESSURE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->BRAKE_PRESSURE_AXLE_1_LEFT_ro & (0xFFU));
  _d[1] |= (_m->BRAKE_PRESSURE_AXLE_1_RIGHT_ro & (0xFFU));
  _d[2] |= (_m->BRAKE_PRESSURE_AXLE_2_LEFT_ro & (0xFFU));
  _d[3] |= (_m->BRAKE_PRESSURE_AXLE_2_RIGHT_ro & (0xFFU));
  _d[4] |= (_m->BRAKE_PRESSURE_AXLE_3_LEFT_ro & (0xFFU));
  _d[5] |= (_m->BRAKE_PRESSURE_AXLE_3_RIGHT_ro & (0xFFU));
  _d[6] |= (_m->PNEUMATIC_SUPPLY_PRESSURE_ro & (0xFFU));

  *_len = TRAILER_BRAKE_PRESSURE_RPT_04_DLC;
  *_ide = TRAILER_BRAKE_PRESSURE_RPT_04_IDE;
  return TRAILER_BRAKE_PRESSURE_RPT_04_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_WHEEL_SPEED_RPT_00_pacmod13(TRAILER_WHEEL_SPEED_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->WHEEL_BASED_VEHICLE_SPEED_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_BASED_VEHICLE_SPEED_phys = (sigfloat_t)(PACMOD13_WHEEL_BASED_VEHICLE_SPEED_ro_fromS(_m->WHEEL_BASED_VEHICLE_SPEED_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_phys = (sigfloat_t)(PACMOD13_WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro_fromS(_m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_WHEEL_SPEED_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_WHEEL_SPEED_RPT_00_pacmod13(&_m->mon1, TRAILER_WHEEL_SPEED_RPT_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_WHEEL_SPEED_RPT_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_WHEEL_SPEED_RPT_00_pacmod13(TRAILER_WHEEL_SPEED_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_WHEEL_SPEED_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_BASED_VEHICLE_SPEED_ro = PACMOD13_WHEEL_BASED_VEHICLE_SPEED_ro_toS(_m->WHEEL_BASED_VEHICLE_SPEED_phys);
  _m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro = PACMOD13_WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro_toS(_m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->WHEEL_BASED_VEHICLE_SPEED_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->WHEEL_BASED_VEHICLE_SPEED_ro & (0xFFU));
  cframe->Data[2] |= ((_m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro & (0xFFU));

  cframe->MsgId = TRAILER_WHEEL_SPEED_RPT_00_CANID;
  cframe->DLC = TRAILER_WHEEL_SPEED_RPT_00_DLC;
  cframe->IDE = TRAILER_WHEEL_SPEED_RPT_00_IDE;
  return TRAILER_WHEEL_SPEED_RPT_00_CANID;
}

#else

uint32_t Pack_TRAILER_WHEEL_SPEED_RPT_00_pacmod13(TRAILER_WHEEL_SPEED_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_WHEEL_SPEED_RPT_00_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->WHEEL_BASED_VEHICLE_SPEED_ro = PACMOD13_WHEEL_BASED_VEHICLE_SPEED_ro_toS(_m->WHEEL_BASED_VEHICLE_SPEED_phys);
  _m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro = PACMOD13_WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro_toS(_m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->WHEEL_BASED_VEHICLE_SPEED_ro >> 8) & (0xFFU));
  _d[1] |= (_m->WHEEL_BASED_VEHICLE_SPEED_ro & (0xFFU));
  _d[2] |= ((_m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro >> 8) & (0xFFU));
  _d[3] |= (_m->WHEEL_SPEED_DIFFERENCE_MAIN_AXLE_ro & (0xFFU));

  *_len = TRAILER_WHEEL_SPEED_RPT_00_DLC;
  *_ide = TRAILER_WHEEL_SPEED_RPT_00_IDE;
  return TRAILER_WHEEL_SPEED_RPT_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BATTERY_VOLTAGE_LEVEL_RPT_1_pacmod13(BATTERY_VOLTAGE_LEVEL_RPT_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BATTERY_VOLTAGE_1_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BATTERY_VOLTAGE_1_phys = (sigfloat_t)(PACMOD13_BATTERY_VOLTAGE_1_ro_fromS(_m->BATTERY_VOLTAGE_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->BATTERY_VOLTAGE_2_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BATTERY_VOLTAGE_2_phys = (sigfloat_t)(PACMOD13_BATTERY_VOLTAGE_2_ro_fromS(_m->BATTERY_VOLTAGE_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BATTERY_VOLTAGE_LEVEL_RPT_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BATTERY_VOLTAGE_LEVEL_RPT_1_pacmod13(&_m->mon1, BATTERY_VOLTAGE_LEVEL_RPT_1_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BATTERY_VOLTAGE_LEVEL_RPT_1_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BATTERY_VOLTAGE_LEVEL_RPT_1_pacmod13(BATTERY_VOLTAGE_LEVEL_RPT_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BATTERY_VOLTAGE_LEVEL_RPT_1_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BATTERY_VOLTAGE_1_ro = PACMOD13_BATTERY_VOLTAGE_1_ro_toS(_m->BATTERY_VOLTAGE_1_phys);
  _m->BATTERY_VOLTAGE_2_ro = PACMOD13_BATTERY_VOLTAGE_2_ro_toS(_m->BATTERY_VOLTAGE_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->BATTERY_VOLTAGE_1_ro & (0xFFU));
  cframe->Data[1] |= (_m->BATTERY_VOLTAGE_2_ro & (0xFFU));

  cframe->MsgId = BATTERY_VOLTAGE_LEVEL_RPT_1_CANID;
  cframe->DLC = BATTERY_VOLTAGE_LEVEL_RPT_1_DLC;
  cframe->IDE = BATTERY_VOLTAGE_LEVEL_RPT_1_IDE;
  return BATTERY_VOLTAGE_LEVEL_RPT_1_CANID;
}

#else

uint32_t Pack_BATTERY_VOLTAGE_LEVEL_RPT_1_pacmod13(BATTERY_VOLTAGE_LEVEL_RPT_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BATTERY_VOLTAGE_LEVEL_RPT_1_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BATTERY_VOLTAGE_1_ro = PACMOD13_BATTERY_VOLTAGE_1_ro_toS(_m->BATTERY_VOLTAGE_1_phys);
  _m->BATTERY_VOLTAGE_2_ro = PACMOD13_BATTERY_VOLTAGE_2_ro_toS(_m->BATTERY_VOLTAGE_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->BATTERY_VOLTAGE_1_ro & (0xFFU));
  _d[1] |= (_m->BATTERY_VOLTAGE_2_ro & (0xFFU));

  *_len = BATTERY_VOLTAGE_LEVEL_RPT_1_DLC;
  *_ide = BATTERY_VOLTAGE_LEVEL_RPT_1_IDE;
  return BATTERY_VOLTAGE_LEVEL_RPT_1_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIRE_PRESSURE_EXTENDED_RPT_pacmod13(TIRE_PRESSURE_EXTENDED_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TIRE_CHASSIS_INDEX_1 = (_d[0] & (0x0FU));
  _m->TIRE_CHASSIS_INDEX_2 = ((_d[0] >> 4) & (0x0FU));
  _m->TIRE_CHASSIS_INDEX_3 = ((_d[1] >> 4) & (0x0FU));
  _m->TIRE_AXLE_1 = ((_d[2] >> 2) & (0x07U));
  _m->TIRE_AXLE_2 = ((_d[2] >> 5) & (0x07U));
  _m->TIRE_AXLE_3 = ((_d[3] >> 2) & (0x07U));
  _m->TIRE_POSITION_1 = ((_d[3] >> 5) & (0x07U));
  _m->TIRE_POSITION_2 = ((_d[4] >> 2) & (0x07U));
  _m->TIRE_POSITION_3 = ((_d[4] >> 5) & (0x07U));
  _m->TIRE_PRESSURE_1_ro = (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_1_phys = PACMOD13_TIRE_PRESSURE_1_ro_fromS(_m->TIRE_PRESSURE_1_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TIRE_PRESSURE_2_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_2_phys = PACMOD13_TIRE_PRESSURE_2_ro_fromS(_m->TIRE_PRESSURE_2_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TIRE_PRESSURE_3_ro = (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_3_phys = PACMOD13_TIRE_PRESSURE_3_ro_fromS(_m->TIRE_PRESSURE_3_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIRE_PRESSURE_EXTENDED_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIRE_PRESSURE_EXTENDED_RPT_pacmod13(&_m->mon1, TIRE_PRESSURE_EXTENDED_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIRE_PRESSURE_EXTENDED_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIRE_PRESSURE_EXTENDED_RPT_pacmod13(TIRE_PRESSURE_EXTENDED_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIRE_PRESSURE_EXTENDED_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_1_ro = PACMOD13_TIRE_PRESSURE_1_ro_toS(_m->TIRE_PRESSURE_1_phys);
  _m->TIRE_PRESSURE_2_ro = PACMOD13_TIRE_PRESSURE_2_ro_toS(_m->TIRE_PRESSURE_2_phys);
  _m->TIRE_PRESSURE_3_ro = PACMOD13_TIRE_PRESSURE_3_ro_toS(_m->TIRE_PRESSURE_3_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->TIRE_CHASSIS_INDEX_1 & (0x0FU)) | ((_m->TIRE_CHASSIS_INDEX_2 & (0x0FU)) << 4);
  cframe->Data[1] |= ((_m->TIRE_CHASSIS_INDEX_3 & (0x0FU)) << 4);
  cframe->Data[2] |= ((_m->TIRE_AXLE_1 & (0x07U)) << 2) | ((_m->TIRE_AXLE_2 & (0x07U)) << 5);
  cframe->Data[3] |= ((_m->TIRE_AXLE_3 & (0x07U)) << 2) | ((_m->TIRE_POSITION_1 & (0x07U)) << 5);
  cframe->Data[4] |= ((_m->TIRE_POSITION_2 & (0x07U)) << 2) | ((_m->TIRE_POSITION_3 & (0x07U)) << 5);
  cframe->Data[5] |= (_m->TIRE_PRESSURE_1_ro & (0xFFU));
  cframe->Data[6] |= (_m->TIRE_PRESSURE_2_ro & (0xFFU));
  cframe->Data[7] |= (_m->TIRE_PRESSURE_3_ro & (0xFFU));

  cframe->MsgId = TIRE_PRESSURE_EXTENDED_RPT_CANID;
  cframe->DLC = TIRE_PRESSURE_EXTENDED_RPT_DLC;
  cframe->IDE = TIRE_PRESSURE_EXTENDED_RPT_IDE;
  return TIRE_PRESSURE_EXTENDED_RPT_CANID;
}

#else

uint32_t Pack_TIRE_PRESSURE_EXTENDED_RPT_pacmod13(TIRE_PRESSURE_EXTENDED_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIRE_PRESSURE_EXTENDED_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_1_ro = PACMOD13_TIRE_PRESSURE_1_ro_toS(_m->TIRE_PRESSURE_1_phys);
  _m->TIRE_PRESSURE_2_ro = PACMOD13_TIRE_PRESSURE_2_ro_toS(_m->TIRE_PRESSURE_2_phys);
  _m->TIRE_PRESSURE_3_ro = PACMOD13_TIRE_PRESSURE_3_ro_toS(_m->TIRE_PRESSURE_3_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->TIRE_CHASSIS_INDEX_1 & (0x0FU)) | ((_m->TIRE_CHASSIS_INDEX_2 & (0x0FU)) << 4);
  _d[1] |= ((_m->TIRE_CHASSIS_INDEX_3 & (0x0FU)) << 4);
  _d[2] |= ((_m->TIRE_AXLE_1 & (0x07U)) << 2) | ((_m->TIRE_AXLE_2 & (0x07U)) << 5);
  _d[3] |= ((_m->TIRE_AXLE_3 & (0x07U)) << 2) | ((_m->TIRE_POSITION_1 & (0x07U)) << 5);
  _d[4] |= ((_m->TIRE_POSITION_2 & (0x07U)) << 2) | ((_m->TIRE_POSITION_3 & (0x07U)) << 5);
  _d[5] |= (_m->TIRE_PRESSURE_1_ro & (0xFFU));
  _d[6] |= (_m->TIRE_PRESSURE_2_ro & (0xFFU));
  _d[7] |= (_m->TIRE_PRESSURE_3_ro & (0xFFU));

  *_len = TIRE_PRESSURE_EXTENDED_RPT_DLC;
  *_ide = TIRE_PRESSURE_EXTENDED_RPT_IDE;
  return TIRE_PRESSURE_EXTENDED_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIRE_PRESSURE_EXTENDED_RPT_2_pacmod13(TIRE_PRESSURE_EXTENDED_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TIRE_CHASSIS_INDEX_1 = (_d[0] & (0x0FU));
  _m->TIRE_CHASSIS_INDEX_2 = ((_d[0] >> 4) & (0x0FU));
  _m->TIRE_CHASSIS_INDEX_3 = ((_d[1] >> 4) & (0x0FU));
  _m->TIRE_AXLE_1 = ((_d[2] >> 2) & (0x07U));
  _m->TIRE_AXLE_2 = ((_d[2] >> 5) & (0x07U));
  _m->TIRE_AXLE_3 = ((_d[3] >> 2) & (0x07U));
  _m->TIRE_POSITION_1 = ((_d[3] >> 5) & (0x07U));
  _m->TIRE_POSITION_2 = ((_d[4] >> 2) & (0x07U));
  _m->TIRE_POSITION_3 = ((_d[4] >> 5) & (0x07U));
  _m->TIRE_PRESSURE_1_ro = (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_1_phys = PACMOD13_TIRE_PRESSURE_1_ro_fromS(_m->TIRE_PRESSURE_1_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TIRE_PRESSURE_2_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_2_phys = PACMOD13_TIRE_PRESSURE_2_ro_fromS(_m->TIRE_PRESSURE_2_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TIRE_PRESSURE_3_ro = (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_3_phys = PACMOD13_TIRE_PRESSURE_3_ro_fromS(_m->TIRE_PRESSURE_3_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIRE_PRESSURE_EXTENDED_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIRE_PRESSURE_EXTENDED_RPT_2_pacmod13(&_m->mon1, TIRE_PRESSURE_EXTENDED_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIRE_PRESSURE_EXTENDED_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIRE_PRESSURE_EXTENDED_RPT_2_pacmod13(TIRE_PRESSURE_EXTENDED_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIRE_PRESSURE_EXTENDED_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_1_ro = PACMOD13_TIRE_PRESSURE_1_ro_toS(_m->TIRE_PRESSURE_1_phys);
  _m->TIRE_PRESSURE_2_ro = PACMOD13_TIRE_PRESSURE_2_ro_toS(_m->TIRE_PRESSURE_2_phys);
  _m->TIRE_PRESSURE_3_ro = PACMOD13_TIRE_PRESSURE_3_ro_toS(_m->TIRE_PRESSURE_3_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->TIRE_CHASSIS_INDEX_1 & (0x0FU)) | ((_m->TIRE_CHASSIS_INDEX_2 & (0x0FU)) << 4);
  cframe->Data[1] |= ((_m->TIRE_CHASSIS_INDEX_3 & (0x0FU)) << 4);
  cframe->Data[2] |= ((_m->TIRE_AXLE_1 & (0x07U)) << 2) | ((_m->TIRE_AXLE_2 & (0x07U)) << 5);
  cframe->Data[3] |= ((_m->TIRE_AXLE_3 & (0x07U)) << 2) | ((_m->TIRE_POSITION_1 & (0x07U)) << 5);
  cframe->Data[4] |= ((_m->TIRE_POSITION_2 & (0x07U)) << 2) | ((_m->TIRE_POSITION_3 & (0x07U)) << 5);
  cframe->Data[5] |= (_m->TIRE_PRESSURE_1_ro & (0xFFU));
  cframe->Data[6] |= (_m->TIRE_PRESSURE_2_ro & (0xFFU));
  cframe->Data[7] |= (_m->TIRE_PRESSURE_3_ro & (0xFFU));

  cframe->MsgId = TIRE_PRESSURE_EXTENDED_RPT_2_CANID;
  cframe->DLC = TIRE_PRESSURE_EXTENDED_RPT_2_DLC;
  cframe->IDE = TIRE_PRESSURE_EXTENDED_RPT_2_IDE;
  return TIRE_PRESSURE_EXTENDED_RPT_2_CANID;
}

#else

uint32_t Pack_TIRE_PRESSURE_EXTENDED_RPT_2_pacmod13(TIRE_PRESSURE_EXTENDED_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIRE_PRESSURE_EXTENDED_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_PRESSURE_1_ro = PACMOD13_TIRE_PRESSURE_1_ro_toS(_m->TIRE_PRESSURE_1_phys);
  _m->TIRE_PRESSURE_2_ro = PACMOD13_TIRE_PRESSURE_2_ro_toS(_m->TIRE_PRESSURE_2_phys);
  _m->TIRE_PRESSURE_3_ro = PACMOD13_TIRE_PRESSURE_3_ro_toS(_m->TIRE_PRESSURE_3_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->TIRE_CHASSIS_INDEX_1 & (0x0FU)) | ((_m->TIRE_CHASSIS_INDEX_2 & (0x0FU)) << 4);
  _d[1] |= ((_m->TIRE_CHASSIS_INDEX_3 & (0x0FU)) << 4);
  _d[2] |= ((_m->TIRE_AXLE_1 & (0x07U)) << 2) | ((_m->TIRE_AXLE_2 & (0x07U)) << 5);
  _d[3] |= ((_m->TIRE_AXLE_3 & (0x07U)) << 2) | ((_m->TIRE_POSITION_1 & (0x07U)) << 5);
  _d[4] |= ((_m->TIRE_POSITION_2 & (0x07U)) << 2) | ((_m->TIRE_POSITION_3 & (0x07U)) << 5);
  _d[5] |= (_m->TIRE_PRESSURE_1_ro & (0xFFU));
  _d[6] |= (_m->TIRE_PRESSURE_2_ro & (0xFFU));
  _d[7] |= (_m->TIRE_PRESSURE_3_ro & (0xFFU));

  *_len = TIRE_PRESSURE_EXTENDED_RPT_2_DLC;
  *_ide = TIRE_PRESSURE_EXTENDED_RPT_2_IDE;
  return TIRE_PRESSURE_EXTENDED_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIRE_TEMPERATURE_EXTENDED_RPT_pacmod13(TIRE_TEMPERATURE_EXTENDED_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TIRE_CHASSIS_INDEX_1 = (_d[0] & (0x0FU));
  _m->TIRE_CHASSIS_INDEX_2 = ((_d[0] >> 4) & (0x0FU));
  _m->TIRE_CHASSIS_INDEX_3 = ((_d[1] >> 4) & (0x0FU));
  _m->TIRE_AXLE_1 = ((_d[2] >> 2) & (0x07U));
  _m->TIRE_AXLE_2 = ((_d[2] >> 5) & (0x07U));
  _m->TIRE_AXLE_3 = ((_d[3] >> 2) & (0x07U));
  _m->TIRE_POSITION_1 = ((_d[3] >> 5) & (0x07U));
  _m->TIRE_POSITION_2 = ((_d[4] >> 2) & (0x07U));
  _m->TIRE_POSITION_3 = ((_d[4] >> 5) & (0x07U));
  _m->TIRE_TEMPERATURE_1_ro = (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_1_phys = PACMOD13_TIRE_TEMPERATURE_1_ro_fromS(_m->TIRE_TEMPERATURE_1_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TIRE_TEMPERATURE_2_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_2_phys = PACMOD13_TIRE_TEMPERATURE_2_ro_fromS(_m->TIRE_TEMPERATURE_2_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TIRE_TEMPERATURE_3_ro = (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_3_phys = PACMOD13_TIRE_TEMPERATURE_3_ro_fromS(_m->TIRE_TEMPERATURE_3_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIRE_TEMPERATURE_EXTENDED_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIRE_TEMPERATURE_EXTENDED_RPT_pacmod13(&_m->mon1, TIRE_TEMPERATURE_EXTENDED_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIRE_TEMPERATURE_EXTENDED_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIRE_TEMPERATURE_EXTENDED_RPT_pacmod13(TIRE_TEMPERATURE_EXTENDED_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIRE_TEMPERATURE_EXTENDED_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_1_ro = PACMOD13_TIRE_TEMPERATURE_1_ro_toS(_m->TIRE_TEMPERATURE_1_phys);
  _m->TIRE_TEMPERATURE_2_ro = PACMOD13_TIRE_TEMPERATURE_2_ro_toS(_m->TIRE_TEMPERATURE_2_phys);
  _m->TIRE_TEMPERATURE_3_ro = PACMOD13_TIRE_TEMPERATURE_3_ro_toS(_m->TIRE_TEMPERATURE_3_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->TIRE_CHASSIS_INDEX_1 & (0x0FU)) | ((_m->TIRE_CHASSIS_INDEX_2 & (0x0FU)) << 4);
  cframe->Data[1] |= ((_m->TIRE_CHASSIS_INDEX_3 & (0x0FU)) << 4);
  cframe->Data[2] |= ((_m->TIRE_AXLE_1 & (0x07U)) << 2) | ((_m->TIRE_AXLE_2 & (0x07U)) << 5);
  cframe->Data[3] |= ((_m->TIRE_AXLE_3 & (0x07U)) << 2) | ((_m->TIRE_POSITION_1 & (0x07U)) << 5);
  cframe->Data[4] |= ((_m->TIRE_POSITION_2 & (0x07U)) << 2) | ((_m->TIRE_POSITION_3 & (0x07U)) << 5);
  cframe->Data[5] |= (_m->TIRE_TEMPERATURE_1_ro & (0xFFU));
  cframe->Data[6] |= (_m->TIRE_TEMPERATURE_2_ro & (0xFFU));
  cframe->Data[7] |= (_m->TIRE_TEMPERATURE_3_ro & (0xFFU));

  cframe->MsgId = TIRE_TEMPERATURE_EXTENDED_RPT_CANID;
  cframe->DLC = TIRE_TEMPERATURE_EXTENDED_RPT_DLC;
  cframe->IDE = TIRE_TEMPERATURE_EXTENDED_RPT_IDE;
  return TIRE_TEMPERATURE_EXTENDED_RPT_CANID;
}

#else

uint32_t Pack_TIRE_TEMPERATURE_EXTENDED_RPT_pacmod13(TIRE_TEMPERATURE_EXTENDED_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIRE_TEMPERATURE_EXTENDED_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_1_ro = PACMOD13_TIRE_TEMPERATURE_1_ro_toS(_m->TIRE_TEMPERATURE_1_phys);
  _m->TIRE_TEMPERATURE_2_ro = PACMOD13_TIRE_TEMPERATURE_2_ro_toS(_m->TIRE_TEMPERATURE_2_phys);
  _m->TIRE_TEMPERATURE_3_ro = PACMOD13_TIRE_TEMPERATURE_3_ro_toS(_m->TIRE_TEMPERATURE_3_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->TIRE_CHASSIS_INDEX_1 & (0x0FU)) | ((_m->TIRE_CHASSIS_INDEX_2 & (0x0FU)) << 4);
  _d[1] |= ((_m->TIRE_CHASSIS_INDEX_3 & (0x0FU)) << 4);
  _d[2] |= ((_m->TIRE_AXLE_1 & (0x07U)) << 2) | ((_m->TIRE_AXLE_2 & (0x07U)) << 5);
  _d[3] |= ((_m->TIRE_AXLE_3 & (0x07U)) << 2) | ((_m->TIRE_POSITION_1 & (0x07U)) << 5);
  _d[4] |= ((_m->TIRE_POSITION_2 & (0x07U)) << 2) | ((_m->TIRE_POSITION_3 & (0x07U)) << 5);
  _d[5] |= (_m->TIRE_TEMPERATURE_1_ro & (0xFFU));
  _d[6] |= (_m->TIRE_TEMPERATURE_2_ro & (0xFFU));
  _d[7] |= (_m->TIRE_TEMPERATURE_3_ro & (0xFFU));

  *_len = TIRE_TEMPERATURE_EXTENDED_RPT_DLC;
  *_ide = TIRE_TEMPERATURE_EXTENDED_RPT_IDE;
  return TIRE_TEMPERATURE_EXTENDED_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TIRE_TEMPERATURE_EXTENDED_RPT_2_pacmod13(TIRE_TEMPERATURE_EXTENDED_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TIRE_CHASSIS_INDEX_1 = (_d[0] & (0x0FU));
  _m->TIRE_CHASSIS_INDEX_2 = ((_d[0] >> 4) & (0x0FU));
  _m->TIRE_CHASSIS_INDEX_3 = ((_d[1] >> 4) & (0x0FU));
  _m->TIRE_AXLE_1 = ((_d[2] >> 2) & (0x07U));
  _m->TIRE_AXLE_2 = ((_d[2] >> 5) & (0x07U));
  _m->TIRE_AXLE_3 = ((_d[3] >> 2) & (0x07U));
  _m->TIRE_POSITION_1 = ((_d[3] >> 5) & (0x07U));
  _m->TIRE_POSITION_2 = ((_d[4] >> 2) & (0x07U));
  _m->TIRE_POSITION_3 = ((_d[4] >> 5) & (0x07U));
  _m->TIRE_TEMPERATURE_1_ro = (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_1_phys = PACMOD13_TIRE_TEMPERATURE_1_ro_fromS(_m->TIRE_TEMPERATURE_1_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TIRE_TEMPERATURE_2_ro = (_d[6] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_2_phys = PACMOD13_TIRE_TEMPERATURE_2_ro_fromS(_m->TIRE_TEMPERATURE_2_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TIRE_TEMPERATURE_3_ro = (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_3_phys = PACMOD13_TIRE_TEMPERATURE_3_ro_fromS(_m->TIRE_TEMPERATURE_3_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TIRE_TEMPERATURE_EXTENDED_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TIRE_TEMPERATURE_EXTENDED_RPT_2_pacmod13(&_m->mon1, TIRE_TEMPERATURE_EXTENDED_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TIRE_TEMPERATURE_EXTENDED_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TIRE_TEMPERATURE_EXTENDED_RPT_2_pacmod13(TIRE_TEMPERATURE_EXTENDED_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TIRE_TEMPERATURE_EXTENDED_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_1_ro = PACMOD13_TIRE_TEMPERATURE_1_ro_toS(_m->TIRE_TEMPERATURE_1_phys);
  _m->TIRE_TEMPERATURE_2_ro = PACMOD13_TIRE_TEMPERATURE_2_ro_toS(_m->TIRE_TEMPERATURE_2_phys);
  _m->TIRE_TEMPERATURE_3_ro = PACMOD13_TIRE_TEMPERATURE_3_ro_toS(_m->TIRE_TEMPERATURE_3_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->TIRE_CHASSIS_INDEX_1 & (0x0FU)) | ((_m->TIRE_CHASSIS_INDEX_2 & (0x0FU)) << 4);
  cframe->Data[1] |= ((_m->TIRE_CHASSIS_INDEX_3 & (0x0FU)) << 4);
  cframe->Data[2] |= ((_m->TIRE_AXLE_1 & (0x07U)) << 2) | ((_m->TIRE_AXLE_2 & (0x07U)) << 5);
  cframe->Data[3] |= ((_m->TIRE_AXLE_3 & (0x07U)) << 2) | ((_m->TIRE_POSITION_1 & (0x07U)) << 5);
  cframe->Data[4] |= ((_m->TIRE_POSITION_2 & (0x07U)) << 2) | ((_m->TIRE_POSITION_3 & (0x07U)) << 5);
  cframe->Data[5] |= (_m->TIRE_TEMPERATURE_1_ro & (0xFFU));
  cframe->Data[6] |= (_m->TIRE_TEMPERATURE_2_ro & (0xFFU));
  cframe->Data[7] |= (_m->TIRE_TEMPERATURE_3_ro & (0xFFU));

  cframe->MsgId = TIRE_TEMPERATURE_EXTENDED_RPT_2_CANID;
  cframe->DLC = TIRE_TEMPERATURE_EXTENDED_RPT_2_DLC;
  cframe->IDE = TIRE_TEMPERATURE_EXTENDED_RPT_2_IDE;
  return TIRE_TEMPERATURE_EXTENDED_RPT_2_CANID;
}

#else

uint32_t Pack_TIRE_TEMPERATURE_EXTENDED_RPT_2_pacmod13(TIRE_TEMPERATURE_EXTENDED_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TIRE_TEMPERATURE_EXTENDED_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->TIRE_TEMPERATURE_1_ro = PACMOD13_TIRE_TEMPERATURE_1_ro_toS(_m->TIRE_TEMPERATURE_1_phys);
  _m->TIRE_TEMPERATURE_2_ro = PACMOD13_TIRE_TEMPERATURE_2_ro_toS(_m->TIRE_TEMPERATURE_2_phys);
  _m->TIRE_TEMPERATURE_3_ro = PACMOD13_TIRE_TEMPERATURE_3_ro_toS(_m->TIRE_TEMPERATURE_3_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->TIRE_CHASSIS_INDEX_1 & (0x0FU)) | ((_m->TIRE_CHASSIS_INDEX_2 & (0x0FU)) << 4);
  _d[1] |= ((_m->TIRE_CHASSIS_INDEX_3 & (0x0FU)) << 4);
  _d[2] |= ((_m->TIRE_AXLE_1 & (0x07U)) << 2) | ((_m->TIRE_AXLE_2 & (0x07U)) << 5);
  _d[3] |= ((_m->TIRE_AXLE_3 & (0x07U)) << 2) | ((_m->TIRE_POSITION_1 & (0x07U)) << 5);
  _d[4] |= ((_m->TIRE_POSITION_2 & (0x07U)) << 2) | ((_m->TIRE_POSITION_3 & (0x07U)) << 5);
  _d[5] |= (_m->TIRE_TEMPERATURE_1_ro & (0xFFU));
  _d[6] |= (_m->TIRE_TEMPERATURE_2_ro & (0xFFU));
  _d[7] |= (_m->TIRE_TEMPERATURE_3_ro & (0xFFU));

  *_len = TIRE_TEMPERATURE_EXTENDED_RPT_2_DLC;
  *_ide = TIRE_TEMPERATURE_EXTENDED_RPT_2_IDE;
  return TIRE_TEMPERATURE_EXTENDED_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_REMOTE_STOP_RPT_pacmod13(REMOTE_STOP_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->REMOTE_STOP_COMMAND = (_d[0] & (0xFFU));
  _m->REMOTE_STOP_SENDER_ID = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->REMOTE_STOP_TIMEOUT = (_d[3] & (0x01U));
  _m->REMOTE_STOP_FAULT = ((_d[3] >> 1) & (0x01U));
  _m->REMOTE_STOP_MODE_CHANGE_ALLOWED = ((_d[3] >> 2) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < REMOTE_STOP_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_REMOTE_STOP_RPT_pacmod13(&_m->mon1, REMOTE_STOP_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return REMOTE_STOP_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_REMOTE_STOP_RPT_pacmod13(REMOTE_STOP_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < REMOTE_STOP_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->REMOTE_STOP_COMMAND & (0xFFU));
  cframe->Data[1] |= ((_m->REMOTE_STOP_SENDER_ID >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->REMOTE_STOP_SENDER_ID & (0xFFU));
  cframe->Data[3] |= (_m->REMOTE_STOP_TIMEOUT & (0x01U)) | ((_m->REMOTE_STOP_FAULT & (0x01U)) << 1) | ((_m->REMOTE_STOP_MODE_CHANGE_ALLOWED & (0x01U)) << 2);

  cframe->MsgId = REMOTE_STOP_RPT_CANID;
  cframe->DLC = REMOTE_STOP_RPT_DLC;
  cframe->IDE = REMOTE_STOP_RPT_IDE;
  return REMOTE_STOP_RPT_CANID;
}

#else

uint32_t Pack_REMOTE_STOP_RPT_pacmod13(REMOTE_STOP_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < REMOTE_STOP_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->REMOTE_STOP_COMMAND & (0xFFU));
  _d[1] |= ((_m->REMOTE_STOP_SENDER_ID >> 8) & (0xFFU));
  _d[2] |= (_m->REMOTE_STOP_SENDER_ID & (0xFFU));
  _d[3] |= (_m->REMOTE_STOP_TIMEOUT & (0x01U)) | ((_m->REMOTE_STOP_FAULT & (0x01U)) << 1) | ((_m->REMOTE_STOP_MODE_CHANGE_ALLOWED & (0x01U)) << 2);

  *_len = REMOTE_STOP_RPT_DLC;
  *_ide = REMOTE_STOP_RPT_IDE;
  return REMOTE_STOP_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_AUTOMS_MAN_SWITCH_RPT_pacmod13(AUTOMS_MAN_SWITCH_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->AUTOMS_MAN_OPCTRL = (_d[0] & (0x03U));
  _m->AUTOMS_MAN_EXTCTRL = ((_d[0] >> 2) & (0x03U));
  _m->AUTOMS_MAN_OPCTRL_AVAIL = ((_d[0] >> 4) & (0x01U));
  _m->AUTOMS_MAN_EXTCTRL_AVAIL = ((_d[0] >> 5) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < AUTOMS_MAN_SWITCH_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_AUTOMS_MAN_SWITCH_RPT_pacmod13(&_m->mon1, AUTOMS_MAN_SWITCH_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return AUTOMS_MAN_SWITCH_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_AUTOMS_MAN_SWITCH_RPT_pacmod13(AUTOMS_MAN_SWITCH_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < AUTOMS_MAN_SWITCH_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->AUTOMS_MAN_OPCTRL & (0x03U)) | ((_m->AUTOMS_MAN_EXTCTRL & (0x03U)) << 2) | ((_m->AUTOMS_MAN_OPCTRL_AVAIL & (0x01U)) << 4) | ((_m->AUTOMS_MAN_EXTCTRL_AVAIL & (0x01U)) << 5);

  cframe->MsgId = AUTOMS_MAN_SWITCH_RPT_CANID;
  cframe->DLC = AUTOMS_MAN_SWITCH_RPT_DLC;
  cframe->IDE = AUTOMS_MAN_SWITCH_RPT_IDE;
  return AUTOMS_MAN_SWITCH_RPT_CANID;
}

#else

uint32_t Pack_AUTOMS_MAN_SWITCH_RPT_pacmod13(AUTOMS_MAN_SWITCH_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < AUTOMS_MAN_SWITCH_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->AUTOMS_MAN_OPCTRL & (0x03U)) | ((_m->AUTOMS_MAN_EXTCTRL & (0x03U)) << 2) | ((_m->AUTOMS_MAN_OPCTRL_AVAIL & (0x01U)) << 4) | ((_m->AUTOMS_MAN_EXTCTRL_AVAIL & (0x01U)) << 5);

  *_len = AUTOMS_MAN_SWITCH_RPT_DLC;
  *_ide = AUTOMS_MAN_SWITCH_RPT_IDE;
  return AUTOMS_MAN_SWITCH_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_PAYLOAD_RPT_00_pacmod13(TRAILER_PAYLOAD_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PAYLOAD_00_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_00_phys = PACMOD13_PAYLOAD_00_ro_fromS(_m->PAYLOAD_00_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TARE_00_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TARE_00_phys = PACMOD13_TARE_00_ro_fromS(_m->TARE_00_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->PAYLOAD_01_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_01_phys = PACMOD13_PAYLOAD_01_ro_fromS(_m->PAYLOAD_01_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TARE_01_ro = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TARE_01_phys = PACMOD13_TARE_01_ro_fromS(_m->TARE_01_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_PAYLOAD_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_PAYLOAD_RPT_00_pacmod13(&_m->mon1, TRAILER_PAYLOAD_RPT_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_PAYLOAD_RPT_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_PAYLOAD_RPT_00_pacmod13(TRAILER_PAYLOAD_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_PAYLOAD_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_00_ro = PACMOD13_PAYLOAD_00_ro_toS(_m->PAYLOAD_00_phys);
  _m->TARE_00_ro = PACMOD13_TARE_00_ro_toS(_m->TARE_00_phys);
  _m->PAYLOAD_01_ro = PACMOD13_PAYLOAD_01_ro_toS(_m->PAYLOAD_01_phys);
  _m->TARE_01_ro = PACMOD13_TARE_01_ro_toS(_m->TARE_01_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->PAYLOAD_00_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->PAYLOAD_00_ro & (0xFFU));
  cframe->Data[2] |= ((_m->TARE_00_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->TARE_00_ro & (0xFFU));
  cframe->Data[4] |= ((_m->PAYLOAD_01_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->PAYLOAD_01_ro & (0xFFU));
  cframe->Data[6] |= ((_m->TARE_01_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->TARE_01_ro & (0xFFU));

  cframe->MsgId = TRAILER_PAYLOAD_RPT_00_CANID;
  cframe->DLC = TRAILER_PAYLOAD_RPT_00_DLC;
  cframe->IDE = TRAILER_PAYLOAD_RPT_00_IDE;
  return TRAILER_PAYLOAD_RPT_00_CANID;
}

#else

uint32_t Pack_TRAILER_PAYLOAD_RPT_00_pacmod13(TRAILER_PAYLOAD_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_PAYLOAD_RPT_00_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_00_ro = PACMOD13_PAYLOAD_00_ro_toS(_m->PAYLOAD_00_phys);
  _m->TARE_00_ro = PACMOD13_TARE_00_ro_toS(_m->TARE_00_phys);
  _m->PAYLOAD_01_ro = PACMOD13_PAYLOAD_01_ro_toS(_m->PAYLOAD_01_phys);
  _m->TARE_01_ro = PACMOD13_TARE_01_ro_toS(_m->TARE_01_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->PAYLOAD_00_ro >> 8) & (0xFFU));
  _d[1] |= (_m->PAYLOAD_00_ro & (0xFFU));
  _d[2] |= ((_m->TARE_00_ro >> 8) & (0xFFU));
  _d[3] |= (_m->TARE_00_ro & (0xFFU));
  _d[4] |= ((_m->PAYLOAD_01_ro >> 8) & (0xFFU));
  _d[5] |= (_m->PAYLOAD_01_ro & (0xFFU));
  _d[6] |= ((_m->TARE_01_ro >> 8) & (0xFFU));
  _d[7] |= (_m->TARE_01_ro & (0xFFU));

  *_len = TRAILER_PAYLOAD_RPT_00_DLC;
  *_ide = TRAILER_PAYLOAD_RPT_00_IDE;
  return TRAILER_PAYLOAD_RPT_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_PAYLOAD_RPT_01_pacmod13(TRAILER_PAYLOAD_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PAYLOAD_00_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_00_phys = PACMOD13_PAYLOAD_00_ro_fromS(_m->PAYLOAD_00_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TARE_00_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TARE_00_phys = PACMOD13_TARE_00_ro_fromS(_m->TARE_00_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->PAYLOAD_01_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_01_phys = PACMOD13_PAYLOAD_01_ro_fromS(_m->PAYLOAD_01_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TARE_01_ro = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TARE_01_phys = PACMOD13_TARE_01_ro_fromS(_m->TARE_01_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_PAYLOAD_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_PAYLOAD_RPT_01_pacmod13(&_m->mon1, TRAILER_PAYLOAD_RPT_01_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_PAYLOAD_RPT_01_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_PAYLOAD_RPT_01_pacmod13(TRAILER_PAYLOAD_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_PAYLOAD_RPT_01_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_00_ro = PACMOD13_PAYLOAD_00_ro_toS(_m->PAYLOAD_00_phys);
  _m->TARE_00_ro = PACMOD13_TARE_00_ro_toS(_m->TARE_00_phys);
  _m->PAYLOAD_01_ro = PACMOD13_PAYLOAD_01_ro_toS(_m->PAYLOAD_01_phys);
  _m->TARE_01_ro = PACMOD13_TARE_01_ro_toS(_m->TARE_01_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->PAYLOAD_00_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->PAYLOAD_00_ro & (0xFFU));
  cframe->Data[2] |= ((_m->TARE_00_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->TARE_00_ro & (0xFFU));
  cframe->Data[4] |= ((_m->PAYLOAD_01_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->PAYLOAD_01_ro & (0xFFU));
  cframe->Data[6] |= ((_m->TARE_01_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->TARE_01_ro & (0xFFU));

  cframe->MsgId = TRAILER_PAYLOAD_RPT_01_CANID;
  cframe->DLC = TRAILER_PAYLOAD_RPT_01_DLC;
  cframe->IDE = TRAILER_PAYLOAD_RPT_01_IDE;
  return TRAILER_PAYLOAD_RPT_01_CANID;
}

#else

uint32_t Pack_TRAILER_PAYLOAD_RPT_01_pacmod13(TRAILER_PAYLOAD_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_PAYLOAD_RPT_01_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_00_ro = PACMOD13_PAYLOAD_00_ro_toS(_m->PAYLOAD_00_phys);
  _m->TARE_00_ro = PACMOD13_TARE_00_ro_toS(_m->TARE_00_phys);
  _m->PAYLOAD_01_ro = PACMOD13_PAYLOAD_01_ro_toS(_m->PAYLOAD_01_phys);
  _m->TARE_01_ro = PACMOD13_TARE_01_ro_toS(_m->TARE_01_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->PAYLOAD_00_ro >> 8) & (0xFFU));
  _d[1] |= (_m->PAYLOAD_00_ro & (0xFFU));
  _d[2] |= ((_m->TARE_00_ro >> 8) & (0xFFU));
  _d[3] |= (_m->TARE_00_ro & (0xFFU));
  _d[4] |= ((_m->PAYLOAD_01_ro >> 8) & (0xFFU));
  _d[5] |= (_m->PAYLOAD_01_ro & (0xFFU));
  _d[6] |= ((_m->TARE_01_ro >> 8) & (0xFFU));
  _d[7] |= (_m->TARE_01_ro & (0xFFU));

  *_len = TRAILER_PAYLOAD_RPT_01_DLC;
  *_ide = TRAILER_PAYLOAD_RPT_01_IDE;
  return TRAILER_PAYLOAD_RPT_01_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_PAYLOAD_RPT_02_pacmod13(TRAILER_PAYLOAD_RPT_02_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PAYLOAD_00_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_00_phys = PACMOD13_PAYLOAD_00_ro_fromS(_m->PAYLOAD_00_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TARE_00_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TARE_00_phys = PACMOD13_TARE_00_ro_fromS(_m->TARE_00_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->PAYLOAD_01_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU)) ), 16);
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_01_phys = PACMOD13_PAYLOAD_01_ro_fromS(_m->PAYLOAD_01_ro);
#endif // PACMOD13_USE_SIGFLOAT

  _m->TARE_01_ro = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->TARE_01_phys = PACMOD13_TARE_01_ro_fromS(_m->TARE_01_ro);
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_PAYLOAD_RPT_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_PAYLOAD_RPT_02_pacmod13(&_m->mon1, TRAILER_PAYLOAD_RPT_02_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_PAYLOAD_RPT_02_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_PAYLOAD_RPT_02_pacmod13(TRAILER_PAYLOAD_RPT_02_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_PAYLOAD_RPT_02_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_00_ro = PACMOD13_PAYLOAD_00_ro_toS(_m->PAYLOAD_00_phys);
  _m->TARE_00_ro = PACMOD13_TARE_00_ro_toS(_m->TARE_00_phys);
  _m->PAYLOAD_01_ro = PACMOD13_PAYLOAD_01_ro_toS(_m->PAYLOAD_01_phys);
  _m->TARE_01_ro = PACMOD13_TARE_01_ro_toS(_m->TARE_01_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->PAYLOAD_00_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->PAYLOAD_00_ro & (0xFFU));
  cframe->Data[2] |= ((_m->TARE_00_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->TARE_00_ro & (0xFFU));
  cframe->Data[4] |= ((_m->PAYLOAD_01_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->PAYLOAD_01_ro & (0xFFU));
  cframe->Data[6] |= ((_m->TARE_01_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->TARE_01_ro & (0xFFU));

  cframe->MsgId = TRAILER_PAYLOAD_RPT_02_CANID;
  cframe->DLC = TRAILER_PAYLOAD_RPT_02_DLC;
  cframe->IDE = TRAILER_PAYLOAD_RPT_02_IDE;
  return TRAILER_PAYLOAD_RPT_02_CANID;
}

#else

uint32_t Pack_TRAILER_PAYLOAD_RPT_02_pacmod13(TRAILER_PAYLOAD_RPT_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_PAYLOAD_RPT_02_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PAYLOAD_00_ro = PACMOD13_PAYLOAD_00_ro_toS(_m->PAYLOAD_00_phys);
  _m->TARE_00_ro = PACMOD13_TARE_00_ro_toS(_m->TARE_00_phys);
  _m->PAYLOAD_01_ro = PACMOD13_PAYLOAD_01_ro_toS(_m->PAYLOAD_01_phys);
  _m->TARE_01_ro = PACMOD13_TARE_01_ro_toS(_m->TARE_01_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->PAYLOAD_00_ro >> 8) & (0xFFU));
  _d[1] |= (_m->PAYLOAD_00_ro & (0xFFU));
  _d[2] |= ((_m->TARE_00_ro >> 8) & (0xFFU));
  _d[3] |= (_m->TARE_00_ro & (0xFFU));
  _d[4] |= ((_m->PAYLOAD_01_ro >> 8) & (0xFFU));
  _d[5] |= (_m->PAYLOAD_01_ro & (0xFFU));
  _d[6] |= ((_m->TARE_01_ro >> 8) & (0xFFU));
  _d[7] |= (_m->TARE_01_ro & (0xFFU));

  *_len = TRAILER_PAYLOAD_RPT_02_DLC;
  *_ide = TRAILER_PAYLOAD_RPT_02_IDE;
  return TRAILER_PAYLOAD_RPT_02_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BATTERY_VOLTAGE_LEVEL_RPT_2_pacmod13(BATTERY_VOLTAGE_LEVEL_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BATTERY_VOLTAGE_1_ro = (_d[0] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BATTERY_VOLTAGE_1_phys = (sigfloat_t)(PACMOD13_BATTERY_VOLTAGE_1_ro_fromS(_m->BATTERY_VOLTAGE_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->BATTERY_VOLTAGE_2_ro = (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->BATTERY_VOLTAGE_2_phys = (sigfloat_t)(PACMOD13_BATTERY_VOLTAGE_2_ro_fromS(_m->BATTERY_VOLTAGE_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BATTERY_VOLTAGE_LEVEL_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BATTERY_VOLTAGE_LEVEL_RPT_2_pacmod13(&_m->mon1, BATTERY_VOLTAGE_LEVEL_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BATTERY_VOLTAGE_LEVEL_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BATTERY_VOLTAGE_LEVEL_RPT_2_pacmod13(BATTERY_VOLTAGE_LEVEL_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BATTERY_VOLTAGE_LEVEL_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BATTERY_VOLTAGE_1_ro = PACMOD13_BATTERY_VOLTAGE_1_ro_toS(_m->BATTERY_VOLTAGE_1_phys);
  _m->BATTERY_VOLTAGE_2_ro = PACMOD13_BATTERY_VOLTAGE_2_ro_toS(_m->BATTERY_VOLTAGE_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= (_m->BATTERY_VOLTAGE_1_ro & (0xFFU));
  cframe->Data[1] |= (_m->BATTERY_VOLTAGE_2_ro & (0xFFU));

  cframe->MsgId = BATTERY_VOLTAGE_LEVEL_RPT_2_CANID;
  cframe->DLC = BATTERY_VOLTAGE_LEVEL_RPT_2_DLC;
  cframe->IDE = BATTERY_VOLTAGE_LEVEL_RPT_2_IDE;
  return BATTERY_VOLTAGE_LEVEL_RPT_2_CANID;
}

#else

uint32_t Pack_BATTERY_VOLTAGE_LEVEL_RPT_2_pacmod13(BATTERY_VOLTAGE_LEVEL_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BATTERY_VOLTAGE_LEVEL_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->BATTERY_VOLTAGE_1_ro = PACMOD13_BATTERY_VOLTAGE_1_ro_toS(_m->BATTERY_VOLTAGE_1_phys);
  _m->BATTERY_VOLTAGE_2_ro = PACMOD13_BATTERY_VOLTAGE_2_ro_toS(_m->BATTERY_VOLTAGE_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= (_m->BATTERY_VOLTAGE_1_ro & (0xFFU));
  _d[1] |= (_m->BATTERY_VOLTAGE_2_ro & (0xFFU));

  *_len = BATTERY_VOLTAGE_LEVEL_RPT_2_DLC;
  *_ide = BATTERY_VOLTAGE_LEVEL_RPT_2_IDE;
  return BATTERY_VOLTAGE_LEVEL_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_GNSS_TIME_pacmod13(GNSS_TIME_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->GNSS_TIMESTAMP = ((uint64_t)(_d[0] & (0xFFU)) << 40) | ((uint64_t)(_d[1] & (0xFFU)) << 32) | ((_d[2] & (0xFFU)) << 24) | ((_d[3] & (0xFFU)) << 16) | ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < GNSS_TIME_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_GNSS_TIME_pacmod13(&_m->mon1, GNSS_TIME_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return GNSS_TIME_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_GNSS_TIME_pacmod13(GNSS_TIME_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < GNSS_TIME_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= ((_m->GNSS_TIMESTAMP >> 40) & (0xFFU));
  cframe->Data[1] |= ((_m->GNSS_TIMESTAMP >> 32) & (0xFFU));
  cframe->Data[2] |= ((_m->GNSS_TIMESTAMP >> 24) & (0xFFU));
  cframe->Data[3] |= ((_m->GNSS_TIMESTAMP >> 16) & (0xFFU));
  cframe->Data[4] |= ((_m->GNSS_TIMESTAMP >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->GNSS_TIMESTAMP & (0xFFU));

  cframe->MsgId = GNSS_TIME_CANID;
  cframe->DLC = GNSS_TIME_DLC;
  cframe->IDE = GNSS_TIME_IDE;
  return GNSS_TIME_CANID;
}

#else

uint32_t Pack_GNSS_TIME_pacmod13(GNSS_TIME_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < GNSS_TIME_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= ((_m->GNSS_TIMESTAMP >> 40) & (0xFFU));
  _d[1] |= ((_m->GNSS_TIMESTAMP >> 32) & (0xFFU));
  _d[2] |= ((_m->GNSS_TIMESTAMP >> 24) & (0xFFU));
  _d[3] |= ((_m->GNSS_TIMESTAMP >> 16) & (0xFFU));
  _d[4] |= ((_m->GNSS_TIMESTAMP >> 8) & (0xFFU));
  _d[5] |= (_m->GNSS_TIMESTAMP & (0xFFU));

  *_len = GNSS_TIME_DLC;
  *_ide = GNSS_TIME_IDE;
  return GNSS_TIME_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_FAULT_RPT_2_pacmod13(VEHICLE_FAULT_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKES_AMBER_LAMP = (_d[0] & (0x03U));
  _m->BRAKES_RED_LAMP = ((_d[0] >> 2) & (0x03U));
  _m->CHASSIS_AMBER_LAMP = ((_d[0] >> 4) & (0x03U));
  _m->CHASSIS_RED_LAMP = ((_d[0] >> 6) & (0x03U));
  _m->ELECTRONIC_BRAKES_AMBER_LAMP = (_d[1] & (0x03U));
  _m->ELECTRONIC_BRAKES_RED_LAMP = ((_d[1] >> 2) & (0x03U));
  _m->ENGINE_AMBER_LAMP = ((_d[1] >> 4) & (0x03U));
  _m->ENGINE_RED_LAMP = ((_d[1] >> 6) & (0x03U));
  _m->ENGINE_BRAKE_AMBER_LAMP = (_d[2] & (0x03U));
  _m->ENGINE_BRAKE_RED_LAMP = ((_d[2] >> 2) & (0x03U));
  _m->MANAGEMENT_ECU_AMBER_LAMP = ((_d[2] >> 4) & (0x03U));
  _m->MANAGEMENT_ECU_RED_LAMP = ((_d[2] >> 6) & (0x03U));
  _m->PNEUMATIC_AMBER_LAMP = (_d[3] & (0x03U));
  _m->PNEUMATIC_RED_LAMP = ((_d[3] >> 2) & (0x03U));
  _m->RESTRAINTS_AMBER_LAMP = ((_d[3] >> 4) & (0x03U));
  _m->RESTRAINTS_RED_LAMP = ((_d[3] >> 6) & (0x03U));
  _m->TRAILER_ABS_AMBER_LAMP = (_d[4] & (0x03U));
  _m->TRAILER_ABS_RED_LAMP = ((_d[4] >> 2) & (0x03U));
  _m->TRANSMISSION_AMBER_LAMP = ((_d[4] >> 4) & (0x03U));
  _m->TRANSMISSION_RED_LAMP = ((_d[4] >> 6) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_FAULT_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_FAULT_RPT_2_pacmod13(&_m->mon1, VEHICLE_FAULT_RPT_2_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return VEHICLE_FAULT_RPT_2_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_VEHICLE_FAULT_RPT_2_pacmod13(VEHICLE_FAULT_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < VEHICLE_FAULT_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BRAKES_AMBER_LAMP & (0x03U)) | ((_m->BRAKES_RED_LAMP & (0x03U)) << 2) | ((_m->CHASSIS_AMBER_LAMP & (0x03U)) << 4) | ((_m->CHASSIS_RED_LAMP & (0x03U)) << 6);
  cframe->Data[1] |= (_m->ELECTRONIC_BRAKES_AMBER_LAMP & (0x03U)) | ((_m->ELECTRONIC_BRAKES_RED_LAMP & (0x03U)) << 2) | ((_m->ENGINE_AMBER_LAMP & (0x03U)) << 4) | ((_m->ENGINE_RED_LAMP & (0x03U)) << 6);
  cframe->Data[2] |= (_m->ENGINE_BRAKE_AMBER_LAMP & (0x03U)) | ((_m->ENGINE_BRAKE_RED_LAMP & (0x03U)) << 2) | ((_m->MANAGEMENT_ECU_AMBER_LAMP & (0x03U)) << 4) | ((_m->MANAGEMENT_ECU_RED_LAMP & (0x03U)) << 6);
  cframe->Data[3] |= (_m->PNEUMATIC_AMBER_LAMP & (0x03U)) | ((_m->PNEUMATIC_RED_LAMP & (0x03U)) << 2) | ((_m->RESTRAINTS_AMBER_LAMP & (0x03U)) << 4) | ((_m->RESTRAINTS_RED_LAMP & (0x03U)) << 6);
  cframe->Data[4] |= (_m->TRAILER_ABS_AMBER_LAMP & (0x03U)) | ((_m->TRAILER_ABS_RED_LAMP & (0x03U)) << 2) | ((_m->TRANSMISSION_AMBER_LAMP & (0x03U)) << 4) | ((_m->TRANSMISSION_RED_LAMP & (0x03U)) << 6);

  cframe->MsgId = VEHICLE_FAULT_RPT_2_CANID;
  cframe->DLC = VEHICLE_FAULT_RPT_2_DLC;
  cframe->IDE = VEHICLE_FAULT_RPT_2_IDE;
  return VEHICLE_FAULT_RPT_2_CANID;
}

#else

uint32_t Pack_VEHICLE_FAULT_RPT_2_pacmod13(VEHICLE_FAULT_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < VEHICLE_FAULT_RPT_2_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BRAKES_AMBER_LAMP & (0x03U)) | ((_m->BRAKES_RED_LAMP & (0x03U)) << 2) | ((_m->CHASSIS_AMBER_LAMP & (0x03U)) << 4) | ((_m->CHASSIS_RED_LAMP & (0x03U)) << 6);
  _d[1] |= (_m->ELECTRONIC_BRAKES_AMBER_LAMP & (0x03U)) | ((_m->ELECTRONIC_BRAKES_RED_LAMP & (0x03U)) << 2) | ((_m->ENGINE_AMBER_LAMP & (0x03U)) << 4) | ((_m->ENGINE_RED_LAMP & (0x03U)) << 6);
  _d[2] |= (_m->ENGINE_BRAKE_AMBER_LAMP & (0x03U)) | ((_m->ENGINE_BRAKE_RED_LAMP & (0x03U)) << 2) | ((_m->MANAGEMENT_ECU_AMBER_LAMP & (0x03U)) << 4) | ((_m->MANAGEMENT_ECU_RED_LAMP & (0x03U)) << 6);
  _d[3] |= (_m->PNEUMATIC_AMBER_LAMP & (0x03U)) | ((_m->PNEUMATIC_RED_LAMP & (0x03U)) << 2) | ((_m->RESTRAINTS_AMBER_LAMP & (0x03U)) << 4) | ((_m->RESTRAINTS_RED_LAMP & (0x03U)) << 6);
  _d[4] |= (_m->TRAILER_ABS_AMBER_LAMP & (0x03U)) | ((_m->TRAILER_ABS_RED_LAMP & (0x03U)) << 2) | ((_m->TRANSMISSION_AMBER_LAMP & (0x03U)) << 4) | ((_m->TRANSMISSION_RED_LAMP & (0x03U)) << 6);

  *_len = VEHICLE_FAULT_RPT_2_DLC;
  *_ide = VEHICLE_FAULT_RPT_2_IDE;
  return VEHICLE_FAULT_RPT_2_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_FAULT_RPT_00_pacmod13(TRAILER_FAULT_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SERVICE_BRAKE_STATUS = (_d[0] & (0x03U));
  _m->ABS_STATUS = ((_d[0] >> 2) & (0x03U));
  _m->ELECTRICAL_SUPPLY_STATUS = ((_d[0] >> 4) & (0x03U));
  _m->PNEUMATIC_SUPPLY_STATUS = ((_d[0] >> 6) & (0x03U));
  _m->AMBER_WARNING_LAMP_REQUEST = (_d[1] & (0x03U));
  _m->RED_WARNING_LAMP_REQUEST = ((_d[1] >> 2) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_FAULT_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_FAULT_RPT_00_pacmod13(&_m->mon1, TRAILER_FAULT_RPT_00_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_FAULT_RPT_00_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_FAULT_RPT_00_pacmod13(TRAILER_FAULT_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  cframe->Data[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  cframe->MsgId = TRAILER_FAULT_RPT_00_CANID;
  cframe->DLC = TRAILER_FAULT_RPT_00_DLC;
  cframe->IDE = TRAILER_FAULT_RPT_00_IDE;
  return TRAILER_FAULT_RPT_00_CANID;
}

#else

uint32_t Pack_TRAILER_FAULT_RPT_00_pacmod13(TRAILER_FAULT_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_00_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  _d[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  *_len = TRAILER_FAULT_RPT_00_DLC;
  *_ide = TRAILER_FAULT_RPT_00_IDE;
  return TRAILER_FAULT_RPT_00_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_FAULT_RPT_01_pacmod13(TRAILER_FAULT_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SERVICE_BRAKE_STATUS = (_d[0] & (0x03U));
  _m->ABS_STATUS = ((_d[0] >> 2) & (0x03U));
  _m->ELECTRICAL_SUPPLY_STATUS = ((_d[0] >> 4) & (0x03U));
  _m->PNEUMATIC_SUPPLY_STATUS = ((_d[0] >> 6) & (0x03U));
  _m->AMBER_WARNING_LAMP_REQUEST = (_d[1] & (0x03U));
  _m->RED_WARNING_LAMP_REQUEST = ((_d[1] >> 2) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_FAULT_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_FAULT_RPT_01_pacmod13(&_m->mon1, TRAILER_FAULT_RPT_01_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_FAULT_RPT_01_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_FAULT_RPT_01_pacmod13(TRAILER_FAULT_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_01_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  cframe->Data[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  cframe->MsgId = TRAILER_FAULT_RPT_01_CANID;
  cframe->DLC = TRAILER_FAULT_RPT_01_DLC;
  cframe->IDE = TRAILER_FAULT_RPT_01_IDE;
  return TRAILER_FAULT_RPT_01_CANID;
}

#else

uint32_t Pack_TRAILER_FAULT_RPT_01_pacmod13(TRAILER_FAULT_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_01_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  _d[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  *_len = TRAILER_FAULT_RPT_01_DLC;
  *_ide = TRAILER_FAULT_RPT_01_IDE;
  return TRAILER_FAULT_RPT_01_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_FAULT_RPT_02_pacmod13(TRAILER_FAULT_RPT_02_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SERVICE_BRAKE_STATUS = (_d[0] & (0x03U));
  _m->ABS_STATUS = ((_d[0] >> 2) & (0x03U));
  _m->ELECTRICAL_SUPPLY_STATUS = ((_d[0] >> 4) & (0x03U));
  _m->PNEUMATIC_SUPPLY_STATUS = ((_d[0] >> 6) & (0x03U));
  _m->AMBER_WARNING_LAMP_REQUEST = (_d[1] & (0x03U));
  _m->RED_WARNING_LAMP_REQUEST = ((_d[1] >> 2) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_FAULT_RPT_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_FAULT_RPT_02_pacmod13(&_m->mon1, TRAILER_FAULT_RPT_02_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_FAULT_RPT_02_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_FAULT_RPT_02_pacmod13(TRAILER_FAULT_RPT_02_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_02_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  cframe->Data[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  cframe->MsgId = TRAILER_FAULT_RPT_02_CANID;
  cframe->DLC = TRAILER_FAULT_RPT_02_DLC;
  cframe->IDE = TRAILER_FAULT_RPT_02_IDE;
  return TRAILER_FAULT_RPT_02_CANID;
}

#else

uint32_t Pack_TRAILER_FAULT_RPT_02_pacmod13(TRAILER_FAULT_RPT_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_02_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  _d[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  *_len = TRAILER_FAULT_RPT_02_DLC;
  *_ide = TRAILER_FAULT_RPT_02_IDE;
  return TRAILER_FAULT_RPT_02_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_FAULT_RPT_03_pacmod13(TRAILER_FAULT_RPT_03_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SERVICE_BRAKE_STATUS = (_d[0] & (0x03U));
  _m->ABS_STATUS = ((_d[0] >> 2) & (0x03U));
  _m->ELECTRICAL_SUPPLY_STATUS = ((_d[0] >> 4) & (0x03U));
  _m->PNEUMATIC_SUPPLY_STATUS = ((_d[0] >> 6) & (0x03U));
  _m->AMBER_WARNING_LAMP_REQUEST = (_d[1] & (0x03U));
  _m->RED_WARNING_LAMP_REQUEST = ((_d[1] >> 2) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_FAULT_RPT_03_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_FAULT_RPT_03_pacmod13(&_m->mon1, TRAILER_FAULT_RPT_03_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_FAULT_RPT_03_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_FAULT_RPT_03_pacmod13(TRAILER_FAULT_RPT_03_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_03_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  cframe->Data[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  cframe->MsgId = TRAILER_FAULT_RPT_03_CANID;
  cframe->DLC = TRAILER_FAULT_RPT_03_DLC;
  cframe->IDE = TRAILER_FAULT_RPT_03_IDE;
  return TRAILER_FAULT_RPT_03_CANID;
}

#else

uint32_t Pack_TRAILER_FAULT_RPT_03_pacmod13(TRAILER_FAULT_RPT_03_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_03_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  _d[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  *_len = TRAILER_FAULT_RPT_03_DLC;
  *_ide = TRAILER_FAULT_RPT_03_IDE;
  return TRAILER_FAULT_RPT_03_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_TRAILER_FAULT_RPT_04_pacmod13(TRAILER_FAULT_RPT_04_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SERVICE_BRAKE_STATUS = (_d[0] & (0x03U));
  _m->ABS_STATUS = ((_d[0] >> 2) & (0x03U));
  _m->ELECTRICAL_SUPPLY_STATUS = ((_d[0] >> 4) & (0x03U));
  _m->PNEUMATIC_SUPPLY_STATUS = ((_d[0] >> 6) & (0x03U));
  _m->AMBER_WARNING_LAMP_REQUEST = (_d[1] & (0x03U));
  _m->RED_WARNING_LAMP_REQUEST = ((_d[1] >> 2) & (0x03U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TRAILER_FAULT_RPT_04_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TRAILER_FAULT_RPT_04_pacmod13(&_m->mon1, TRAILER_FAULT_RPT_04_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return TRAILER_FAULT_RPT_04_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_TRAILER_FAULT_RPT_04_pacmod13(TRAILER_FAULT_RPT_04_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_04_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  cframe->Data[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  cframe->MsgId = TRAILER_FAULT_RPT_04_CANID;
  cframe->DLC = TRAILER_FAULT_RPT_04_DLC;
  cframe->IDE = TRAILER_FAULT_RPT_04_IDE;
  return TRAILER_FAULT_RPT_04_CANID;
}

#else

uint32_t Pack_TRAILER_FAULT_RPT_04_pacmod13(TRAILER_FAULT_RPT_04_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TRAILER_FAULT_RPT_04_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SERVICE_BRAKE_STATUS & (0x03U)) | ((_m->ABS_STATUS & (0x03U)) << 2) | ((_m->ELECTRICAL_SUPPLY_STATUS & (0x03U)) << 4) | ((_m->PNEUMATIC_SUPPLY_STATUS & (0x03U)) << 6);
  _d[1] |= (_m->AMBER_WARNING_LAMP_REQUEST & (0x03U)) | ((_m->RED_WARNING_LAMP_REQUEST & (0x03U)) << 2);

  *_len = TRAILER_FAULT_RPT_04_DLC;
  *_ide = TRAILER_FAULT_RPT_04_IDE;
  return TRAILER_FAULT_RPT_04_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_05_pacmod13(SOFTWARE_VERSION_RPT_05_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_05_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_05_pacmod13(&_m->mon1, SOFTWARE_VERSION_RPT_05_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_05_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_05_pacmod13(SOFTWARE_VERSION_RPT_05_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_05_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->MAJOR & (0xFFU));
  cframe->Data[1] |= (_m->MINOR & (0xFFU));
  cframe->Data[2] |= (_m->PATCH & (0xFFU));
  cframe->Data[3] |= (_m->BUILD0 & (0xFFU));
  cframe->Data[4] |= (_m->BUILD1 & (0xFFU));
  cframe->Data[5] |= (_m->BUILD2 & (0xFFU));
  cframe->Data[6] |= (_m->BUILD3 & (0xFFU));

  cframe->MsgId = SOFTWARE_VERSION_RPT_05_CANID;
  cframe->DLC = SOFTWARE_VERSION_RPT_05_DLC;
  cframe->IDE = SOFTWARE_VERSION_RPT_05_IDE;
  return SOFTWARE_VERSION_RPT_05_CANID;
}

#else

uint32_t Pack_SOFTWARE_VERSION_RPT_05_pacmod13(SOFTWARE_VERSION_RPT_05_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SOFTWARE_VERSION_RPT_05_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->MAJOR & (0xFFU));
  _d[1] |= (_m->MINOR & (0xFFU));
  _d[2] |= (_m->PATCH & (0xFFU));
  _d[3] |= (_m->BUILD0 & (0xFFU));
  _d[4] |= (_m->BUILD1 & (0xFFU));
  _d[5] |= (_m->BUILD2 & (0xFFU));
  _d[6] |= (_m->BUILD3 & (0xFFU));

  *_len = SOFTWARE_VERSION_RPT_05_DLC;
  *_ide = SOFTWARE_VERSION_RPT_05_IDE;
  return SOFTWARE_VERSION_RPT_05_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_ACCEL_PEDAL_POSITION_VOLTAGE_RPT_pacmod13(ACCEL_PEDAL_POSITION_VOLTAGE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PACMOD_VOLTAGE_IN_1_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_IN_1_ro_fromS(_m->PACMOD_VOLTAGE_IN_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_IN_2_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_2_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_IN_2_ro_fromS(_m->PACMOD_VOLTAGE_IN_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_OUT_1_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_OUT_1_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_fromS(_m->PACMOD_VOLTAGE_OUT_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_OUT_2_ro = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_OUT_2_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_fromS(_m->PACMOD_VOLTAGE_OUT_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ACCEL_PEDAL_POSITION_VOLTAGE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ACCEL_PEDAL_POSITION_VOLTAGE_RPT_pacmod13(&_m->mon1, ACCEL_PEDAL_POSITION_VOLTAGE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return ACCEL_PEDAL_POSITION_VOLTAGE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_ACCEL_PEDAL_POSITION_VOLTAGE_RPT_pacmod13(ACCEL_PEDAL_POSITION_VOLTAGE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ACCEL_PEDAL_POSITION_VOLTAGE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_ro = PACMOD13_PACMOD_VOLTAGE_IN_1_ro_toS(_m->PACMOD_VOLTAGE_IN_1_phys);
  _m->PACMOD_VOLTAGE_IN_2_ro = PACMOD13_PACMOD_VOLTAGE_IN_2_ro_toS(_m->PACMOD_VOLTAGE_IN_2_phys);
  _m->PACMOD_VOLTAGE_OUT_1_ro = PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_toS(_m->PACMOD_VOLTAGE_OUT_1_phys);
  _m->PACMOD_VOLTAGE_OUT_2_ro = PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_toS(_m->PACMOD_VOLTAGE_OUT_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->PACMOD_VOLTAGE_IN_1_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->PACMOD_VOLTAGE_IN_1_ro & (0xFFU));
  cframe->Data[2] |= ((_m->PACMOD_VOLTAGE_IN_2_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->PACMOD_VOLTAGE_IN_2_ro & (0xFFU));
  cframe->Data[4] |= ((_m->PACMOD_VOLTAGE_OUT_1_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->PACMOD_VOLTAGE_OUT_1_ro & (0xFFU));
  cframe->Data[6] |= ((_m->PACMOD_VOLTAGE_OUT_2_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->PACMOD_VOLTAGE_OUT_2_ro & (0xFFU));

  cframe->MsgId = ACCEL_PEDAL_POSITION_VOLTAGE_RPT_CANID;
  cframe->DLC = ACCEL_PEDAL_POSITION_VOLTAGE_RPT_DLC;
  cframe->IDE = ACCEL_PEDAL_POSITION_VOLTAGE_RPT_IDE;
  return ACCEL_PEDAL_POSITION_VOLTAGE_RPT_CANID;
}

#else

uint32_t Pack_ACCEL_PEDAL_POSITION_VOLTAGE_RPT_pacmod13(ACCEL_PEDAL_POSITION_VOLTAGE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ACCEL_PEDAL_POSITION_VOLTAGE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_ro = PACMOD13_PACMOD_VOLTAGE_IN_1_ro_toS(_m->PACMOD_VOLTAGE_IN_1_phys);
  _m->PACMOD_VOLTAGE_IN_2_ro = PACMOD13_PACMOD_VOLTAGE_IN_2_ro_toS(_m->PACMOD_VOLTAGE_IN_2_phys);
  _m->PACMOD_VOLTAGE_OUT_1_ro = PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_toS(_m->PACMOD_VOLTAGE_OUT_1_phys);
  _m->PACMOD_VOLTAGE_OUT_2_ro = PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_toS(_m->PACMOD_VOLTAGE_OUT_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->PACMOD_VOLTAGE_IN_1_ro >> 8) & (0xFFU));
  _d[1] |= (_m->PACMOD_VOLTAGE_IN_1_ro & (0xFFU));
  _d[2] |= ((_m->PACMOD_VOLTAGE_IN_2_ro >> 8) & (0xFFU));
  _d[3] |= (_m->PACMOD_VOLTAGE_IN_2_ro & (0xFFU));
  _d[4] |= ((_m->PACMOD_VOLTAGE_OUT_1_ro >> 8) & (0xFFU));
  _d[5] |= (_m->PACMOD_VOLTAGE_OUT_1_ro & (0xFFU));
  _d[6] |= ((_m->PACMOD_VOLTAGE_OUT_2_ro >> 8) & (0xFFU));
  _d[7] |= (_m->PACMOD_VOLTAGE_OUT_2_ro & (0xFFU));

  *_len = ACCEL_PEDAL_POSITION_VOLTAGE_RPT_DLC;
  *_ide = ACCEL_PEDAL_POSITION_VOLTAGE_RPT_IDE;
  return ACCEL_PEDAL_POSITION_VOLTAGE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_MC_VOLTAGE_RPT_pacmod13(BRAKE_MC_VOLTAGE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PACMOD_VOLTAGE_IN_1_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_IN_1_ro_fromS(_m->PACMOD_VOLTAGE_IN_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_IN_2_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_2_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_IN_2_ro_fromS(_m->PACMOD_VOLTAGE_IN_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_OUT_1_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_OUT_1_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_fromS(_m->PACMOD_VOLTAGE_OUT_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_OUT_2_ro = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_OUT_2_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_fromS(_m->PACMOD_VOLTAGE_OUT_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_MC_VOLTAGE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_MC_VOLTAGE_RPT_pacmod13(&_m->mon1, BRAKE_MC_VOLTAGE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_MC_VOLTAGE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_MC_VOLTAGE_RPT_pacmod13(BRAKE_MC_VOLTAGE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_MC_VOLTAGE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_ro = PACMOD13_PACMOD_VOLTAGE_IN_1_ro_toS(_m->PACMOD_VOLTAGE_IN_1_phys);
  _m->PACMOD_VOLTAGE_IN_2_ro = PACMOD13_PACMOD_VOLTAGE_IN_2_ro_toS(_m->PACMOD_VOLTAGE_IN_2_phys);
  _m->PACMOD_VOLTAGE_OUT_1_ro = PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_toS(_m->PACMOD_VOLTAGE_OUT_1_phys);
  _m->PACMOD_VOLTAGE_OUT_2_ro = PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_toS(_m->PACMOD_VOLTAGE_OUT_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->PACMOD_VOLTAGE_IN_1_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->PACMOD_VOLTAGE_IN_1_ro & (0xFFU));
  cframe->Data[2] |= ((_m->PACMOD_VOLTAGE_IN_2_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->PACMOD_VOLTAGE_IN_2_ro & (0xFFU));
  cframe->Data[4] |= ((_m->PACMOD_VOLTAGE_OUT_1_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->PACMOD_VOLTAGE_OUT_1_ro & (0xFFU));
  cframe->Data[6] |= ((_m->PACMOD_VOLTAGE_OUT_2_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->PACMOD_VOLTAGE_OUT_2_ro & (0xFFU));

  cframe->MsgId = BRAKE_MC_VOLTAGE_RPT_CANID;
  cframe->DLC = BRAKE_MC_VOLTAGE_RPT_DLC;
  cframe->IDE = BRAKE_MC_VOLTAGE_RPT_IDE;
  return BRAKE_MC_VOLTAGE_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_MC_VOLTAGE_RPT_pacmod13(BRAKE_MC_VOLTAGE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_MC_VOLTAGE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_ro = PACMOD13_PACMOD_VOLTAGE_IN_1_ro_toS(_m->PACMOD_VOLTAGE_IN_1_phys);
  _m->PACMOD_VOLTAGE_IN_2_ro = PACMOD13_PACMOD_VOLTAGE_IN_2_ro_toS(_m->PACMOD_VOLTAGE_IN_2_phys);
  _m->PACMOD_VOLTAGE_OUT_1_ro = PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_toS(_m->PACMOD_VOLTAGE_OUT_1_phys);
  _m->PACMOD_VOLTAGE_OUT_2_ro = PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_toS(_m->PACMOD_VOLTAGE_OUT_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->PACMOD_VOLTAGE_IN_1_ro >> 8) & (0xFFU));
  _d[1] |= (_m->PACMOD_VOLTAGE_IN_1_ro & (0xFFU));
  _d[2] |= ((_m->PACMOD_VOLTAGE_IN_2_ro >> 8) & (0xFFU));
  _d[3] |= (_m->PACMOD_VOLTAGE_IN_2_ro & (0xFFU));
  _d[4] |= ((_m->PACMOD_VOLTAGE_OUT_1_ro >> 8) & (0xFFU));
  _d[5] |= (_m->PACMOD_VOLTAGE_OUT_1_ro & (0xFFU));
  _d[6] |= ((_m->PACMOD_VOLTAGE_OUT_2_ro >> 8) & (0xFFU));
  _d[7] |= (_m->PACMOD_VOLTAGE_OUT_2_ro & (0xFFU));

  *_len = BRAKE_MC_VOLTAGE_RPT_DLC;
  *_ide = BRAKE_MC_VOLTAGE_RPT_IDE;
  return BRAKE_MC_VOLTAGE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_BRAKE_PEDAL_POSITION_VOLTAGE_RPT_pacmod13(BRAKE_PEDAL_POSITION_VOLTAGE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PACMOD_VOLTAGE_IN_1_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_IN_1_ro_fromS(_m->PACMOD_VOLTAGE_IN_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_IN_2_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_2_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_IN_2_ro_fromS(_m->PACMOD_VOLTAGE_IN_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_OUT_1_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_OUT_1_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_fromS(_m->PACMOD_VOLTAGE_OUT_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_OUT_2_ro = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_OUT_2_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_fromS(_m->PACMOD_VOLTAGE_OUT_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_PEDAL_POSITION_VOLTAGE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_PEDAL_POSITION_VOLTAGE_RPT_pacmod13(&_m->mon1, BRAKE_PEDAL_POSITION_VOLTAGE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return BRAKE_PEDAL_POSITION_VOLTAGE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_BRAKE_PEDAL_POSITION_VOLTAGE_RPT_pacmod13(BRAKE_PEDAL_POSITION_VOLTAGE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_PEDAL_POSITION_VOLTAGE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_ro = PACMOD13_PACMOD_VOLTAGE_IN_1_ro_toS(_m->PACMOD_VOLTAGE_IN_1_phys);
  _m->PACMOD_VOLTAGE_IN_2_ro = PACMOD13_PACMOD_VOLTAGE_IN_2_ro_toS(_m->PACMOD_VOLTAGE_IN_2_phys);
  _m->PACMOD_VOLTAGE_OUT_1_ro = PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_toS(_m->PACMOD_VOLTAGE_OUT_1_phys);
  _m->PACMOD_VOLTAGE_OUT_2_ro = PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_toS(_m->PACMOD_VOLTAGE_OUT_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->PACMOD_VOLTAGE_IN_1_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->PACMOD_VOLTAGE_IN_1_ro & (0xFFU));
  cframe->Data[2] |= ((_m->PACMOD_VOLTAGE_IN_2_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->PACMOD_VOLTAGE_IN_2_ro & (0xFFU));
  cframe->Data[4] |= ((_m->PACMOD_VOLTAGE_OUT_1_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->PACMOD_VOLTAGE_OUT_1_ro & (0xFFU));
  cframe->Data[6] |= ((_m->PACMOD_VOLTAGE_OUT_2_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->PACMOD_VOLTAGE_OUT_2_ro & (0xFFU));

  cframe->MsgId = BRAKE_PEDAL_POSITION_VOLTAGE_RPT_CANID;
  cframe->DLC = BRAKE_PEDAL_POSITION_VOLTAGE_RPT_DLC;
  cframe->IDE = BRAKE_PEDAL_POSITION_VOLTAGE_RPT_IDE;
  return BRAKE_PEDAL_POSITION_VOLTAGE_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_PEDAL_POSITION_VOLTAGE_RPT_pacmod13(BRAKE_PEDAL_POSITION_VOLTAGE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_PEDAL_POSITION_VOLTAGE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_ro = PACMOD13_PACMOD_VOLTAGE_IN_1_ro_toS(_m->PACMOD_VOLTAGE_IN_1_phys);
  _m->PACMOD_VOLTAGE_IN_2_ro = PACMOD13_PACMOD_VOLTAGE_IN_2_ro_toS(_m->PACMOD_VOLTAGE_IN_2_phys);
  _m->PACMOD_VOLTAGE_OUT_1_ro = PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_toS(_m->PACMOD_VOLTAGE_OUT_1_phys);
  _m->PACMOD_VOLTAGE_OUT_2_ro = PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_toS(_m->PACMOD_VOLTAGE_OUT_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->PACMOD_VOLTAGE_IN_1_ro >> 8) & (0xFFU));
  _d[1] |= (_m->PACMOD_VOLTAGE_IN_1_ro & (0xFFU));
  _d[2] |= ((_m->PACMOD_VOLTAGE_IN_2_ro >> 8) & (0xFFU));
  _d[3] |= (_m->PACMOD_VOLTAGE_IN_2_ro & (0xFFU));
  _d[4] |= ((_m->PACMOD_VOLTAGE_OUT_1_ro >> 8) & (0xFFU));
  _d[5] |= (_m->PACMOD_VOLTAGE_OUT_1_ro & (0xFFU));
  _d[6] |= ((_m->PACMOD_VOLTAGE_OUT_2_ro >> 8) & (0xFFU));
  _d[7] |= (_m->PACMOD_VOLTAGE_OUT_2_ro & (0xFFU));

  *_len = BRAKE_PEDAL_POSITION_VOLTAGE_RPT_DLC;
  *_ide = BRAKE_PEDAL_POSITION_VOLTAGE_RPT_IDE;
  return BRAKE_PEDAL_POSITION_VOLTAGE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_STEERING_TRQ_SENSOR_VOLTAGE_RPT_pacmod13(STEERING_TRQ_SENSOR_VOLTAGE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PACMOD_VOLTAGE_IN_1_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_IN_1_ro_fromS(_m->PACMOD_VOLTAGE_IN_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_IN_2_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_2_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_IN_2_ro_fromS(_m->PACMOD_VOLTAGE_IN_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_OUT_1_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_OUT_1_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_fromS(_m->PACMOD_VOLTAGE_OUT_1_ro));
#endif // PACMOD13_USE_SIGFLOAT

  _m->PACMOD_VOLTAGE_OUT_2_ro = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));
#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_OUT_2_phys = (sigfloat_t)(PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_fromS(_m->PACMOD_VOLTAGE_OUT_2_ro));
#endif // PACMOD13_USE_SIGFLOAT

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_TRQ_SENSOR_VOLTAGE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_TRQ_SENSOR_VOLTAGE_RPT_pacmod13(&_m->mon1, STEERING_TRQ_SENSOR_VOLTAGE_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return STEERING_TRQ_SENSOR_VOLTAGE_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_STEERING_TRQ_SENSOR_VOLTAGE_RPT_pacmod13(STEERING_TRQ_SENSOR_VOLTAGE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_TRQ_SENSOR_VOLTAGE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_ro = PACMOD13_PACMOD_VOLTAGE_IN_1_ro_toS(_m->PACMOD_VOLTAGE_IN_1_phys);
  _m->PACMOD_VOLTAGE_IN_2_ro = PACMOD13_PACMOD_VOLTAGE_IN_2_ro_toS(_m->PACMOD_VOLTAGE_IN_2_phys);
  _m->PACMOD_VOLTAGE_OUT_1_ro = PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_toS(_m->PACMOD_VOLTAGE_OUT_1_phys);
  _m->PACMOD_VOLTAGE_OUT_2_ro = PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_toS(_m->PACMOD_VOLTAGE_OUT_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->PACMOD_VOLTAGE_IN_1_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->PACMOD_VOLTAGE_IN_1_ro & (0xFFU));
  cframe->Data[2] |= ((_m->PACMOD_VOLTAGE_IN_2_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->PACMOD_VOLTAGE_IN_2_ro & (0xFFU));
  cframe->Data[4] |= ((_m->PACMOD_VOLTAGE_OUT_1_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->PACMOD_VOLTAGE_OUT_1_ro & (0xFFU));
  cframe->Data[6] |= ((_m->PACMOD_VOLTAGE_OUT_2_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->PACMOD_VOLTAGE_OUT_2_ro & (0xFFU));

  cframe->MsgId = STEERING_TRQ_SENSOR_VOLTAGE_RPT_CANID;
  cframe->DLC = STEERING_TRQ_SENSOR_VOLTAGE_RPT_DLC;
  cframe->IDE = STEERING_TRQ_SENSOR_VOLTAGE_RPT_IDE;
  return STEERING_TRQ_SENSOR_VOLTAGE_RPT_CANID;
}

#else

uint32_t Pack_STEERING_TRQ_SENSOR_VOLTAGE_RPT_pacmod13(STEERING_TRQ_SENSOR_VOLTAGE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_TRQ_SENSOR_VOLTAGE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD13_USE_SIGFLOAT
  _m->PACMOD_VOLTAGE_IN_1_ro = PACMOD13_PACMOD_VOLTAGE_IN_1_ro_toS(_m->PACMOD_VOLTAGE_IN_1_phys);
  _m->PACMOD_VOLTAGE_IN_2_ro = PACMOD13_PACMOD_VOLTAGE_IN_2_ro_toS(_m->PACMOD_VOLTAGE_IN_2_phys);
  _m->PACMOD_VOLTAGE_OUT_1_ro = PACMOD13_PACMOD_VOLTAGE_OUT_1_ro_toS(_m->PACMOD_VOLTAGE_OUT_1_phys);
  _m->PACMOD_VOLTAGE_OUT_2_ro = PACMOD13_PACMOD_VOLTAGE_OUT_2_ro_toS(_m->PACMOD_VOLTAGE_OUT_2_phys);
#endif // PACMOD13_USE_SIGFLOAT

  _d[0] |= ((_m->PACMOD_VOLTAGE_IN_1_ro >> 8) & (0xFFU));
  _d[1] |= (_m->PACMOD_VOLTAGE_IN_1_ro & (0xFFU));
  _d[2] |= ((_m->PACMOD_VOLTAGE_IN_2_ro >> 8) & (0xFFU));
  _d[3] |= (_m->PACMOD_VOLTAGE_IN_2_ro & (0xFFU));
  _d[4] |= ((_m->PACMOD_VOLTAGE_OUT_1_ro >> 8) & (0xFFU));
  _d[5] |= (_m->PACMOD_VOLTAGE_OUT_1_ro & (0xFFU));
  _d[6] |= ((_m->PACMOD_VOLTAGE_OUT_2_ro >> 8) & (0xFFU));
  _d[7] |= (_m->PACMOD_VOLTAGE_OUT_2_ro & (0xFFU));

  *_len = STEERING_TRQ_SENSOR_VOLTAGE_RPT_DLC;
  *_ide = STEERING_TRQ_SENSOR_VOLTAGE_RPT_IDE;
  return STEERING_TRQ_SENSOR_VOLTAGE_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

uint32_t Unpack_WATCHDOG_RPT_pacmod13(WATCHDOG_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->GLOBAL_ENABLE_FLAG = (_d[0] & (0x01U));
  _m->GLOBAL_OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->GLOBAL_COMMAND_TIMEOUT_ERROR = ((_d[0] >> 2) & (0x01U));
  _m->GLOBAL_PACMOD_SUBSYSTEM_TIMEOUT = ((_d[0] >> 3) & (0x01U));
  _m->GLOBAL_VEHICLE_CAN_TIMEOUT = ((_d[0] >> 4) & (0x01U));
  _m->GLOBAL_PACMOD_SYS_FAULT_ACTIVE = ((_d[0] >> 5) & (0x01U));
  _m->GLOBAL_CONFIG_FAULT_ACTIVE = ((_d[0] >> 6) & (0x01U));
  _m->GLOBAL_TIMEOUT = ((_d[0] >> 7) & (0x01U));
  _m->ACCEL_ENABLED = (_d[1] & (0x01U));
  _m->ACCEL_OVERRIDE_ACTIVE = ((_d[1] >> 1) & (0x01U));
  _m->ACCEL_COMMAND_OUTPUT_FAULT = ((_d[1] >> 2) & (0x01U));
  _m->ACCEL_INPUT_OUTPUT_FAULT = ((_d[1] >> 3) & (0x01U));
  _m->ACCEL_OUTPUT_REPORTED_FAULT = ((_d[1] >> 4) & (0x01U));
  _m->ACCEL_PACMOD_FAULT = ((_d[1] >> 5) & (0x01U));
  _m->ACCEL_VEHICLE_FAULT = ((_d[1] >> 6) & (0x01U));
  _m->ACCEL_TIMEOUT = ((_d[1] >> 7) & (0x01U));
  _m->BRAKE_ENABLED = (_d[2] & (0x01U));
  _m->BRAKE_OVERRIDE_ACTIVE = ((_d[2] >> 1) & (0x01U));
  _m->BRAKE_COMMAND_OUTPUT_FAULT = ((_d[2] >> 2) & (0x01U));
  _m->BRAKE_INPUT_OUTPUT_FAULT = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_OUTPUT_REPORTED_FAULT = ((_d[2] >> 4) & (0x01U));
  _m->BRAKE_PACMOD_FAULT = ((_d[2] >> 5) & (0x01U));
  _m->BRAKE_VEHICLE_FAULT = ((_d[2] >> 6) & (0x01U));
  _m->BRAKE_TIMEOUT = ((_d[2] >> 7) & (0x01U));
  _m->SHIFT_ENABLED = (_d[3] & (0x01U));
  _m->SHIFT_OVERRIDE_ACTIVE = ((_d[3] >> 1) & (0x01U));
  _m->SHIFT_COMMAND_OUTPUT_FAULT = ((_d[3] >> 2) & (0x01U));
  _m->SHIFT_INPUT_OUTPUT_FAULT = ((_d[3] >> 3) & (0x01U));
  _m->SHIFT_OUTPUT_REPORTED_FAULT = ((_d[3] >> 4) & (0x01U));
  _m->SHIFT_PACMOD_FAULT = ((_d[3] >> 5) & (0x01U));
  _m->SHIFT_VEHICLE_FAULT = ((_d[3] >> 6) & (0x01U));
  _m->SHIFT_TIMEOUT = ((_d[3] >> 7) & (0x01U));
  _m->STEER_ENABLED = (_d[4] & (0x01U));
  _m->STEER_OVERRIDE_ACTIVE = ((_d[4] >> 1) & (0x01U));
  _m->STEER_COMMAND_OUTPUT_FAULT = ((_d[4] >> 2) & (0x01U));
  _m->STEER_INPUT_OUTPUT_FAULT = ((_d[4] >> 3) & (0x01U));
  _m->STEER_OUTPUT_REPORTED_FAULT = ((_d[4] >> 4) & (0x01U));
  _m->STEER_PACMOD_FAULT = ((_d[4] >> 5) & (0x01U));
  _m->STEER_VEHICLE_FAULT = ((_d[4] >> 6) & (0x01U));
  _m->STEER_TIMEOUT = ((_d[4] >> 7) & (0x01U));
  _m->PACMOD1_CONFIG_FAULT = (_d[5] & (0x01U));
  _m->PACMOD1_CAN_TIMEOUT = ((_d[5] >> 1) & (0x01U));
  _m->PACMOD1_COUNTER_FAULT = ((_d[5] >> 2) & (0x01U));
  _m->PACMOD2_CONFIG_FAULT = ((_d[5] >> 3) & (0x01U));
  _m->PACMOD2_CAN_TIMEOUT = ((_d[5] >> 4) & (0x01U));
  _m->PACMOD2_COUNTER_FAULT = ((_d[5] >> 5) & (0x01U));
  _m->PACMOD3_CONFIG_FAULT = ((_d[5] >> 6) & (0x01U));
  _m->PACMOD3_CAN_TIMEOUT = ((_d[5] >> 7) & (0x01U));
  _m->PACMOD3_COUNTER_FAULT = (_d[6] & (0x01U));
  _m->PACMINI1_RPT_TIMEOUT = ((_d[6] >> 1) & (0x01U));
  _m->PACMINI1_CONFIG_FAULT = ((_d[6] >> 2) & (0x01U));
  _m->PACMINI1_CAN_TIMEOUT = ((_d[6] >> 3) & (0x01U));
  _m->PACMINI1_COUNTER_FAULT = ((_d[6] >> 4) & (0x01U));
  _m->PACMINI2_RPT_TIMEOUT = ((_d[6] >> 5) & (0x01U));
  _m->PACMINI2_CONFIG_FAULT = ((_d[6] >> 6) & (0x01U));
  _m->PACMINI2_CAN_TIMEOUT = ((_d[6] >> 7) & (0x01U));
  _m->PACMINI2_COUNTER_FAULT = (_d[7] & (0x01U));
  _m->PACMINI3_RPT_TIMEOUT = ((_d[7] >> 1) & (0x01U));
  _m->PACMINI3_CONFIG_FAULT = ((_d[7] >> 2) & (0x01U));
  _m->PACMINI3_CAN_TIMEOUT = ((_d[7] >> 3) & (0x01U));
  _m->PACMINI3_COUNTER_FAULT = ((_d[7] >> 4) & (0x01U));
  _m->PACMOD_SYSTEM_PRESENT_FAULT = ((_d[7] >> 5) & (0x01U));
  _m->PACMINI_SYSTEM_PRESENT_FAULT = ((_d[7] >> 6) & (0x01U));
  _m->GLOBAL_INT_POWER_SUPPLY_FAULT = ((_d[7] >> 7) & (0x01U));

#ifdef PACMOD13_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WATCHDOG_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WATCHDOG_RPT_pacmod13(&_m->mon1, WATCHDOG_RPT_CANID);
#endif // PACMOD13_USE_DIAG_MONITORS

  return WATCHDOG_RPT_CANID;
}

#ifdef PACMOD13_USE_CANSTRUCT

uint32_t Pack_WATCHDOG_RPT_pacmod13(WATCHDOG_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < WATCHDOG_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->GLOBAL_ENABLE_FLAG & (0x01U)) | ((_m->GLOBAL_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->GLOBAL_COMMAND_TIMEOUT_ERROR & (0x01U)) << 2) | ((_m->GLOBAL_PACMOD_SUBSYSTEM_TIMEOUT & (0x01U)) << 3) | ((_m->GLOBAL_VEHICLE_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->GLOBAL_PACMOD_SYS_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->GLOBAL_CONFIG_FAULT_ACTIVE & (0x01U)) << 6) | ((_m->GLOBAL_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->ACCEL_ENABLED & (0x01U)) | ((_m->ACCEL_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->ACCEL_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->ACCEL_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->ACCEL_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->ACCEL_PACMOD_FAULT & (0x01U)) << 5) | ((_m->ACCEL_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->ACCEL_TIMEOUT & (0x01U)) << 7);
  cframe->Data[2] |= (_m->BRAKE_ENABLED & (0x01U)) | ((_m->BRAKE_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->BRAKE_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->BRAKE_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->BRAKE_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->BRAKE_PACMOD_FAULT & (0x01U)) << 5) | ((_m->BRAKE_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->BRAKE_TIMEOUT & (0x01U)) << 7);
  cframe->Data[3] |= (_m->SHIFT_ENABLED & (0x01U)) | ((_m->SHIFT_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->SHIFT_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->SHIFT_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->SHIFT_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->SHIFT_PACMOD_FAULT & (0x01U)) << 5) | ((_m->SHIFT_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->SHIFT_TIMEOUT & (0x01U)) << 7);
  cframe->Data[4] |= (_m->STEER_ENABLED & (0x01U)) | ((_m->STEER_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->STEER_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->STEER_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->STEER_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->STEER_PACMOD_FAULT & (0x01U)) << 5) | ((_m->STEER_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->STEER_TIMEOUT & (0x01U)) << 7);
  cframe->Data[5] |= (_m->PACMOD1_CONFIG_FAULT & (0x01U)) | ((_m->PACMOD1_CAN_TIMEOUT & (0x01U)) << 1) | ((_m->PACMOD1_COUNTER_FAULT & (0x01U)) << 2) | ((_m->PACMOD2_CONFIG_FAULT & (0x01U)) << 3) | ((_m->PACMOD2_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->PACMOD2_COUNTER_FAULT & (0x01U)) << 5) | ((_m->PACMOD3_CONFIG_FAULT & (0x01U)) << 6) | ((_m->PACMOD3_CAN_TIMEOUT & (0x01U)) << 7);
  cframe->Data[6] |= (_m->PACMOD3_COUNTER_FAULT & (0x01U)) | ((_m->PACMINI1_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->PACMINI1_CONFIG_FAULT & (0x01U)) << 2) | ((_m->PACMINI1_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->PACMINI1_COUNTER_FAULT & (0x01U)) << 4) | ((_m->PACMINI2_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->PACMINI2_CONFIG_FAULT & (0x01U)) << 6) | ((_m->PACMINI2_CAN_TIMEOUT & (0x01U)) << 7);
  cframe->Data[7] |= (_m->PACMINI2_COUNTER_FAULT & (0x01U)) | ((_m->PACMINI3_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->PACMINI3_CONFIG_FAULT & (0x01U)) << 2) | ((_m->PACMINI3_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->PACMINI3_COUNTER_FAULT & (0x01U)) << 4) | ((_m->PACMOD_SYSTEM_PRESENT_FAULT & (0x01U)) << 5) | ((_m->PACMINI_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->GLOBAL_INT_POWER_SUPPLY_FAULT & (0x01U)) << 7);

  cframe->MsgId = WATCHDOG_RPT_CANID;
  cframe->DLC = WATCHDOG_RPT_DLC;
  cframe->IDE = WATCHDOG_RPT_IDE;
  return WATCHDOG_RPT_CANID;
}

#else

uint32_t Pack_WATCHDOG_RPT_pacmod13(WATCHDOG_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WATCHDOG_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->GLOBAL_ENABLE_FLAG & (0x01U)) | ((_m->GLOBAL_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->GLOBAL_COMMAND_TIMEOUT_ERROR & (0x01U)) << 2) | ((_m->GLOBAL_PACMOD_SUBSYSTEM_TIMEOUT & (0x01U)) << 3) | ((_m->GLOBAL_VEHICLE_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->GLOBAL_PACMOD_SYS_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->GLOBAL_CONFIG_FAULT_ACTIVE & (0x01U)) << 6) | ((_m->GLOBAL_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->ACCEL_ENABLED & (0x01U)) | ((_m->ACCEL_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->ACCEL_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->ACCEL_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->ACCEL_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->ACCEL_PACMOD_FAULT & (0x01U)) << 5) | ((_m->ACCEL_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->ACCEL_TIMEOUT & (0x01U)) << 7);
  _d[2] |= (_m->BRAKE_ENABLED & (0x01U)) | ((_m->BRAKE_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->BRAKE_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->BRAKE_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->BRAKE_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->BRAKE_PACMOD_FAULT & (0x01U)) << 5) | ((_m->BRAKE_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->BRAKE_TIMEOUT & (0x01U)) << 7);
  _d[3] |= (_m->SHIFT_ENABLED & (0x01U)) | ((_m->SHIFT_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->SHIFT_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->SHIFT_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->SHIFT_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->SHIFT_PACMOD_FAULT & (0x01U)) << 5) | ((_m->SHIFT_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->SHIFT_TIMEOUT & (0x01U)) << 7);
  _d[4] |= (_m->STEER_ENABLED & (0x01U)) | ((_m->STEER_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->STEER_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->STEER_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->STEER_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->STEER_PACMOD_FAULT & (0x01U)) << 5) | ((_m->STEER_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->STEER_TIMEOUT & (0x01U)) << 7);
  _d[5] |= (_m->PACMOD1_CONFIG_FAULT & (0x01U)) | ((_m->PACMOD1_CAN_TIMEOUT & (0x01U)) << 1) | ((_m->PACMOD1_COUNTER_FAULT & (0x01U)) << 2) | ((_m->PACMOD2_CONFIG_FAULT & (0x01U)) << 3) | ((_m->PACMOD2_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->PACMOD2_COUNTER_FAULT & (0x01U)) << 5) | ((_m->PACMOD3_CONFIG_FAULT & (0x01U)) << 6) | ((_m->PACMOD3_CAN_TIMEOUT & (0x01U)) << 7);
  _d[6] |= (_m->PACMOD3_COUNTER_FAULT & (0x01U)) | ((_m->PACMINI1_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->PACMINI1_CONFIG_FAULT & (0x01U)) << 2) | ((_m->PACMINI1_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->PACMINI1_COUNTER_FAULT & (0x01U)) << 4) | ((_m->PACMINI2_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->PACMINI2_CONFIG_FAULT & (0x01U)) << 6) | ((_m->PACMINI2_CAN_TIMEOUT & (0x01U)) << 7);
  _d[7] |= (_m->PACMINI2_COUNTER_FAULT & (0x01U)) | ((_m->PACMINI3_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->PACMINI3_CONFIG_FAULT & (0x01U)) << 2) | ((_m->PACMINI3_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->PACMINI3_COUNTER_FAULT & (0x01U)) << 4) | ((_m->PACMOD_SYSTEM_PRESENT_FAULT & (0x01U)) << 5) | ((_m->PACMINI_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->GLOBAL_INT_POWER_SUPPLY_FAULT & (0x01U)) << 7);

  *_len = WATCHDOG_RPT_DLC;
  *_ide = WATCHDOG_RPT_IDE;
  return WATCHDOG_RPT_CANID;
}

#endif // PACMOD13_USE_CANSTRUCT

