#include "pacmod6.h"


#ifdef PACMOD6_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "pacmod6-fmon.h"

#endif // PACMOD6_USE_DIAG_MONITORS


// To compile this function you need to typedef 'bitext_t' and 'ubitext_t'
// globally in @dbccodeconf.h or locally in 'dbcdrvname'-config.h
// Type selection may affect common performance. Most useful types are:
// bitext_t : int64_t and ubitext_t : uint64_t
static bitext_t __ext_sig__( ubitext_t val, uint8_t bits )
{
  ubitext_t const m = 1u << (bits - 1);
  return (val ^ m) - m;
}

uint32_t Unpack_GLOBAL_RPT_pacmod6(GLOBAL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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
  _m->CONFIG_FAULT_ACTIVE = ((_d[1] >> 7) & (0x01U));
  _m->USR_CAN_READ_ERRORS = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < GLOBAL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_GLOBAL_RPT_pacmod6(&_m->mon1, GLOBAL_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return GLOBAL_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_GLOBAL_RPT_pacmod6(GLOBAL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < GLOBAL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->PACMOD_SYSTEM_ENABLED & (0x01U)) | ((_m->PACMOD_SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->USR_CAN_TIMEOUT & (0x01U)) << 2) | ((_m->STR_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->BRK_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->PACMOD_SUBSYSTEM_TIMEOUT & (0x01U)) << 5) | ((_m->VEH_CAN_TIMEOUT & (0x01U)) << 6) | ((_m->PACMOD_SYSTEM_FAULT_ACTIVE & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->CONFIG_FAULT_ACTIVE & (0x01U)) << 7);
  cframe->Data[6] |= ((_m->USR_CAN_READ_ERRORS >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->USR_CAN_READ_ERRORS & (0xFFU));

  cframe->MsgId = GLOBAL_RPT_CANID;
  cframe->DLC = GLOBAL_RPT_DLC;
  cframe->IDE = GLOBAL_RPT_IDE;
  return GLOBAL_RPT_CANID;
}

#else

uint32_t Pack_GLOBAL_RPT_pacmod6(GLOBAL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < GLOBAL_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->PACMOD_SYSTEM_ENABLED & (0x01U)) | ((_m->PACMOD_SYSTEM_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->USR_CAN_TIMEOUT & (0x01U)) << 2) | ((_m->STR_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->BRK_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->PACMOD_SUBSYSTEM_TIMEOUT & (0x01U)) << 5) | ((_m->VEH_CAN_TIMEOUT & (0x01U)) << 6) | ((_m->PACMOD_SYSTEM_FAULT_ACTIVE & (0x01U)) << 7);
  _d[1] |= ((_m->CONFIG_FAULT_ACTIVE & (0x01U)) << 7);
  _d[6] |= ((_m->USR_CAN_READ_ERRORS >> 8) & (0xFFU));
  _d[7] |= (_m->USR_CAN_READ_ERRORS & (0xFFU));

  *_len = GLOBAL_RPT_DLC;
  *_ide = GLOBAL_RPT_IDE;
  return GLOBAL_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_00_pacmod6(COMPONENT_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
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
  _m->SPRAY = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECCEL = ((_d[2] >> 4) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_00_pacmod6(&_m->mon1, COMPONENT_RPT_00_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return COMPONENT_RPT_00_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_00_pacmod6(COMPONENT_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_00_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAY & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECCEL & (0x01U)) << 4);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_00_CANID;
  cframe->DLC = COMPONENT_RPT_00_DLC;
  cframe->IDE = COMPONENT_RPT_00_IDE;
  return COMPONENT_RPT_00_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_00_pacmod6(COMPONENT_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_00_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAY & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECCEL & (0x01U)) << 4);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2);

  *_len = COMPONENT_RPT_00_DLC;
  *_ide = COMPONENT_RPT_00_IDE;
  return COMPONENT_RPT_00_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_01_pacmod6(COMPONENT_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
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
  _m->SPRAY = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECCEL = ((_d[2] >> 4) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_01_pacmod6(&_m->mon1, COMPONENT_RPT_01_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return COMPONENT_RPT_01_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_01_pacmod6(COMPONENT_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_01_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAY & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECCEL & (0x01U)) << 4);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_01_CANID;
  cframe->DLC = COMPONENT_RPT_01_DLC;
  cframe->IDE = COMPONENT_RPT_01_IDE;
  return COMPONENT_RPT_01_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_01_pacmod6(COMPONENT_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_01_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAY & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECCEL & (0x01U)) << 4);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2);

  *_len = COMPONENT_RPT_01_DLC;
  *_ide = COMPONENT_RPT_01_IDE;
  return COMPONENT_RPT_01_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_02_pacmod6(COMPONENT_RPT_02_t* _m, const uint8_t* _d, uint8_t dlc_)
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
  _m->SPRAY = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECCEL = ((_d[2] >> 4) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_02_pacmod6(&_m->mon1, COMPONENT_RPT_02_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return COMPONENT_RPT_02_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_02_pacmod6(COMPONENT_RPT_02_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_02_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAY & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECCEL & (0x01U)) << 4);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_02_CANID;
  cframe->DLC = COMPONENT_RPT_02_DLC;
  cframe->IDE = COMPONENT_RPT_02_IDE;
  return COMPONENT_RPT_02_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_02_pacmod6(COMPONENT_RPT_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_02_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAY & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECCEL & (0x01U)) << 4);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2);

  *_len = COMPONENT_RPT_02_DLC;
  *_ide = COMPONENT_RPT_02_IDE;
  return COMPONENT_RPT_02_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_COMPONENT_RPT_03_pacmod6(COMPONENT_RPT_03_t* _m, const uint8_t* _d, uint8_t dlc_)
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
  _m->SPRAY = ((_d[1] >> 7) & (0x01U));
  _m->STEERING = (_d[2] & (0x01U));
  _m->TURN = ((_d[2] >> 1) & (0x01U));
  _m->WIPER = ((_d[2] >> 2) & (0x01U));
  _m->WATCHDOG = ((_d[2] >> 3) & (0x01U));
  _m->BRAKE_DECCEL = ((_d[2] >> 4) & (0x01U));
  _m->COUNTER = (_d[4] & (0x0FU));
  _m->COMPLEMENT = ((_d[4] >> 4) & (0x0FU));
  _m->CONFIG_FAULT = (_d[5] & (0x01U));
  _m->CAN_TIMEOUT_FAULT = ((_d[5] >> 1) & (0x01U));
  _m->INTERNAL_SUPPLY_VOLTAGE_FAULT = ((_d[5] >> 2) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < COMPONENT_RPT_03_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_COMPONENT_RPT_03_pacmod6(&_m->mon1, COMPONENT_RPT_03_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return COMPONENT_RPT_03_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_COMPONENT_RPT_03_pacmod6(COMPONENT_RPT_03_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_03_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAY & (0x01U)) << 7);
  cframe->Data[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECCEL & (0x01U)) << 4);
  cframe->Data[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  cframe->Data[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2);

  cframe->MsgId = COMPONENT_RPT_03_CANID;
  cframe->DLC = COMPONENT_RPT_03_DLC;
  cframe->IDE = COMPONENT_RPT_03_IDE;
  return COMPONENT_RPT_03_CANID;
}

#else

uint32_t Pack_COMPONENT_RPT_03_pacmod6(COMPONENT_RPT_03_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < COMPONENT_RPT_03_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->COMPONENT_TYPE & (0x0FU)) | ((_m->ACCEL & (0x01U)) << 4) | ((_m->BRAKE & (0x01U)) << 5) | ((_m->CRUISE_CONTROL_BUTTONS & (0x01U)) << 6) | ((_m->DASH_CONTROLS_LEFT & (0x01U)) << 7);
  _d[1] |= (_m->DASH_CONTROLS_RIGHT & (0x01U)) | ((_m->HAZARD_LIGHTS & (0x01U)) << 1) | ((_m->HEADLIGHT & (0x01U)) << 2) | ((_m->HORN & (0x01U)) << 3) | ((_m->MEDIA_CONTROLS & (0x01U)) << 4) | ((_m->PARKING_BRAKE & (0x01U)) << 5) | ((_m->SHIFT & (0x01U)) << 6) | ((_m->SPRAY & (0x01U)) << 7);
  _d[2] |= (_m->STEERING & (0x01U)) | ((_m->TURN & (0x01U)) << 1) | ((_m->WIPER & (0x01U)) << 2) | ((_m->WATCHDOG & (0x01U)) << 3) | ((_m->BRAKE_DECCEL & (0x01U)) << 4);
  _d[4] |= (_m->COUNTER & (0x0FU)) | ((_m->COMPLEMENT & (0x0FU)) << 4);
  _d[5] |= (_m->CONFIG_FAULT & (0x01U)) | ((_m->CAN_TIMEOUT_FAULT & (0x01U)) << 1) | ((_m->INTERNAL_SUPPLY_VOLTAGE_FAULT & (0x01U)) << 2);

  *_len = COMPONENT_RPT_03_DLC;
  *_ide = COMPONENT_RPT_03_IDE;
  return COMPONENT_RPT_03_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_GLOBAL_CMD_pacmod6(GLOBAL_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->CLEAR_FAULTS = (_d[0] & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < GLOBAL_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_GLOBAL_CMD_pacmod6(&_m->mon1, GLOBAL_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return GLOBAL_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_GLOBAL_CMD_pacmod6(GLOBAL_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < GLOBAL_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->CLEAR_FAULTS & (0x01U));

  cframe->MsgId = GLOBAL_CMD_CANID;
  cframe->DLC = GLOBAL_CMD_DLC;
  cframe->IDE = GLOBAL_CMD_IDE;
  return GLOBAL_CMD_CANID;
}

#else

uint32_t Pack_GLOBAL_CMD_pacmod6(GLOBAL_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < GLOBAL_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->CLEAR_FAULTS & (0x01U));

  *_len = GLOBAL_CMD_DLC;
  *_ide = GLOBAL_CMD_IDE;
  return GLOBAL_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_ACCEL_CMD_pacmod6(ACCEL_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->ACCEL_CMD_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->ACCEL_CMD_phys = (sigfloat_t)(PACMOD6_ACCEL_CMD_ro_fromS(_m->ACCEL_CMD_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ACCEL_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ACCEL_CMD_pacmod6(&_m->mon1, ACCEL_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return ACCEL_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_ACCEL_CMD_pacmod6(ACCEL_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ACCEL_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->ACCEL_CMD_ro = PACMOD6_ACCEL_CMD_ro_toS(_m->ACCEL_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= ((_m->ACCEL_CMD_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->ACCEL_CMD_ro & (0xFFU));

  cframe->MsgId = ACCEL_CMD_CANID;
  cframe->DLC = ACCEL_CMD_DLC;
  cframe->IDE = ACCEL_CMD_IDE;
  return ACCEL_CMD_CANID;
}

#else

uint32_t Pack_ACCEL_CMD_pacmod6(ACCEL_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ACCEL_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->ACCEL_CMD_ro = PACMOD6_ACCEL_CMD_ro_toS(_m->ACCEL_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= ((_m->ACCEL_CMD_ro >> 8) & (0xFFU));
  _d[2] |= (_m->ACCEL_CMD_ro & (0xFFU));

  *_len = ACCEL_CMD_DLC;
  *_ide = ACCEL_CMD_IDE;
  return ACCEL_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_CMD_pacmod6(BRAKE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->BRAKE_CMD_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->BRAKE_CMD_phys = (sigfloat_t)(PACMOD6_BRAKE_CMD_ro_fromS(_m->BRAKE_CMD_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_CMD_pacmod6(&_m->mon1, BRAKE_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_CMD_pacmod6(BRAKE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->BRAKE_CMD_ro = PACMOD6_BRAKE_CMD_ro_toS(_m->BRAKE_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= ((_m->BRAKE_CMD_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_CMD_ro & (0xFFU));

  cframe->MsgId = BRAKE_CMD_CANID;
  cframe->DLC = BRAKE_CMD_DLC;
  cframe->IDE = BRAKE_CMD_IDE;
  return BRAKE_CMD_CANID;
}

#else

uint32_t Pack_BRAKE_CMD_pacmod6(BRAKE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->BRAKE_CMD_ro = PACMOD6_BRAKE_CMD_ro_toS(_m->BRAKE_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= ((_m->BRAKE_CMD_ro >> 8) & (0xFFU));
  _d[2] |= (_m->BRAKE_CMD_ro & (0xFFU));

  *_len = BRAKE_CMD_DLC;
  *_ide = BRAKE_CMD_IDE;
  return BRAKE_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_CRUISE_CONTROL_BUTTONS_CMD_pacmod6(CRUISE_CONTROL_BUTTONS_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->CRUISE_CONTROL_BUTTON = (_d[1] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CRUISE_CONTROL_BUTTONS_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CRUISE_CONTROL_BUTTONS_CMD_pacmod6(&_m->mon1, CRUISE_CONTROL_BUTTONS_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return CRUISE_CONTROL_BUTTONS_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_CRUISE_CONTROL_BUTTONS_CMD_pacmod6(CRUISE_CONTROL_BUTTONS_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_CRUISE_CONTROL_BUTTONS_CMD_pacmod6(CRUISE_CONTROL_BUTTONS_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < CRUISE_CONTROL_BUTTONS_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->CRUISE_CONTROL_BUTTON & (0xFFU));

  *_len = CRUISE_CONTROL_BUTTONS_CMD_DLC;
  *_ide = CRUISE_CONTROL_BUTTONS_CMD_IDE;
  return CRUISE_CONTROL_BUTTONS_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_DASH_CONTROLS_LEFT_CMD_pacmod6(DASH_CONTROLS_LEFT_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->DASH_CONTROLS_BUTTON = (_d[1] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DASH_CONTROLS_LEFT_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DASH_CONTROLS_LEFT_CMD_pacmod6(&_m->mon1, DASH_CONTROLS_LEFT_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return DASH_CONTROLS_LEFT_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_DASH_CONTROLS_LEFT_CMD_pacmod6(DASH_CONTROLS_LEFT_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_DASH_CONTROLS_LEFT_CMD_pacmod6(DASH_CONTROLS_LEFT_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_LEFT_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->DASH_CONTROLS_BUTTON & (0xFFU));

  *_len = DASH_CONTROLS_LEFT_CMD_DLC;
  *_ide = DASH_CONTROLS_LEFT_CMD_IDE;
  return DASH_CONTROLS_LEFT_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_DASH_CONTROLS_RIGHT_CMD_pacmod6(DASH_CONTROLS_RIGHT_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->DASH_CONTROLS_BUTTON = (_d[1] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DASH_CONTROLS_RIGHT_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DASH_CONTROLS_RIGHT_CMD_pacmod6(&_m->mon1, DASH_CONTROLS_RIGHT_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return DASH_CONTROLS_RIGHT_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_DASH_CONTROLS_RIGHT_CMD_pacmod6(DASH_CONTROLS_RIGHT_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_DASH_CONTROLS_RIGHT_CMD_pacmod6(DASH_CONTROLS_RIGHT_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DASH_CONTROLS_RIGHT_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->DASH_CONTROLS_BUTTON & (0xFFU));

  *_len = DASH_CONTROLS_RIGHT_CMD_DLC;
  *_ide = DASH_CONTROLS_RIGHT_CMD_IDE;
  return DASH_CONTROLS_RIGHT_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_HAZARD_LIGHTS_CMD_pacmod6(HAZARD_LIGHTS_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->HAZARD_LIGHTS_CMD = (_d[1] & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HAZARD_LIGHTS_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HAZARD_LIGHTS_CMD_pacmod6(&_m->mon1, HAZARD_LIGHTS_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return HAZARD_LIGHTS_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_HAZARD_LIGHTS_CMD_pacmod6(HAZARD_LIGHTS_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_HAZARD_LIGHTS_CMD_pacmod6(HAZARD_LIGHTS_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HAZARD_LIGHTS_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->HAZARD_LIGHTS_CMD & (0x01U));

  *_len = HAZARD_LIGHTS_CMD_DLC;
  *_ide = HAZARD_LIGHTS_CMD_IDE;
  return HAZARD_LIGHTS_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_HEADLIGHT_CMD_pacmod6(HEADLIGHT_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->HEADLIGHT_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HEADLIGHT_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HEADLIGHT_CMD_pacmod6(&_m->mon1, HEADLIGHT_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return HEADLIGHT_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_HEADLIGHT_CMD_pacmod6(HEADLIGHT_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_HEADLIGHT_CMD_pacmod6(HEADLIGHT_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HEADLIGHT_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->HEADLIGHT_CMD & (0xFFU));

  *_len = HEADLIGHT_CMD_DLC;
  *_ide = HEADLIGHT_CMD_IDE;
  return HEADLIGHT_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_HORN_CMD_pacmod6(HORN_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->HORN_CMD = (_d[1] & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HORN_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HORN_CMD_pacmod6(&_m->mon1, HORN_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return HORN_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_HORN_CMD_pacmod6(HORN_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_HORN_CMD_pacmod6(HORN_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HORN_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->HORN_CMD & (0x01U));

  *_len = HORN_CMD_DLC;
  *_ide = HORN_CMD_IDE;
  return HORN_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_MEDIA_CONTROLS_CMD_pacmod6(MEDIA_CONTROLS_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->MEDIA_CONTROLS_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < MEDIA_CONTROLS_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_MEDIA_CONTROLS_CMD_pacmod6(&_m->mon1, MEDIA_CONTROLS_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return MEDIA_CONTROLS_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_MEDIA_CONTROLS_CMD_pacmod6(MEDIA_CONTROLS_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_MEDIA_CONTROLS_CMD_pacmod6(MEDIA_CONTROLS_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < MEDIA_CONTROLS_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->MEDIA_CONTROLS_CMD & (0xFFU));

  *_len = MEDIA_CONTROLS_CMD_DLC;
  *_ide = MEDIA_CONTROLS_CMD_IDE;
  return MEDIA_CONTROLS_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_PARKING_BRAKE_CMD_pacmod6(PARKING_BRAKE_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->PARKING_BRAKE_CMD = (_d[1] & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < PARKING_BRAKE_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_PARKING_BRAKE_CMD_pacmod6(&_m->mon1, PARKING_BRAKE_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return PARKING_BRAKE_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_PARKING_BRAKE_CMD_pacmod6(PARKING_BRAKE_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_PARKING_BRAKE_CMD_pacmod6(PARKING_BRAKE_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->PARKING_BRAKE_CMD & (0x01U));

  *_len = PARKING_BRAKE_CMD_DLC;
  *_ide = PARKING_BRAKE_CMD_IDE;
  return PARKING_BRAKE_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_SHIFT_CMD_pacmod6(SHIFT_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->SHIFT_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SHIFT_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SHIFT_CMD_pacmod6(&_m->mon1, SHIFT_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return SHIFT_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_SHIFT_CMD_pacmod6(SHIFT_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_SHIFT_CMD_pacmod6(SHIFT_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SHIFT_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->SHIFT_CMD & (0xFFU));

  *_len = SHIFT_CMD_DLC;
  *_ide = SHIFT_CMD_IDE;
  return SHIFT_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_STEERING_CMD_pacmod6(STEERING_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->POSITION_ro = __ext_sig__(( ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->POSITION_phys = (sigfloat_t)(PACMOD6_POSITION_ro_fromS(_m->POSITION_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->ROTATION_RATE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->ROTATION_RATE_phys = (sigfloat_t)(PACMOD6_ROTATION_RATE_ro_fromS(_m->ROTATION_RATE_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_CMD_pacmod6(&_m->mon1, STEERING_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return STEERING_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_STEERING_CMD_pacmod6(STEERING_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->POSITION_ro = PACMOD6_POSITION_ro_toS(_m->POSITION_phys);
  _m->ROTATION_RATE_ro = PACMOD6_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_STEERING_CMD_pacmod6(STEERING_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->POSITION_ro = PACMOD6_POSITION_ro_toS(_m->POSITION_phys);
  _m->ROTATION_RATE_ro = PACMOD6_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= ((_m->POSITION_ro >> 8) & (0xFFU));
  _d[2] |= (_m->POSITION_ro & (0xFFU));
  _d[3] |= ((_m->ROTATION_RATE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->ROTATION_RATE_ro & (0xFFU));

  *_len = STEERING_CMD_DLC;
  *_ide = STEERING_CMD_IDE;
  return STEERING_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_TURN_CMD_pacmod6(TURN_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->TURN_SIGNAL_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TURN_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TURN_CMD_pacmod6(&_m->mon1, TURN_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return TURN_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_TURN_CMD_pacmod6(TURN_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_TURN_CMD_pacmod6(TURN_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TURN_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->TURN_SIGNAL_CMD & (0xFFU));

  *_len = TURN_CMD_DLC;
  *_ide = TURN_CMD_IDE;
  return TURN_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_WIPER_CMD_pacmod6(WIPER_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->WIPER_CMD = (_d[1] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WIPER_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WIPER_CMD_pacmod6(&_m->mon1, WIPER_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return WIPER_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_WIPER_CMD_pacmod6(WIPER_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_WIPER_CMD_pacmod6(WIPER_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WIPER_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->WIPER_CMD & (0xFFU));

  *_len = WIPER_CMD_DLC;
  *_ide = WIPER_CMD_IDE;
  return WIPER_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_SPRAYER_CMD_pacmod6(SPRAYER_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->SPRAYER_CMD = (_d[1] & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SPRAYER_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SPRAYER_CMD_pacmod6(&_m->mon1, SPRAYER_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return SPRAYER_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_SPRAYER_CMD_pacmod6(SPRAYER_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_SPRAYER_CMD_pacmod6(SPRAYER_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SPRAYER_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= (_m->SPRAYER_CMD & (0x01U));

  *_len = SPRAYER_CMD_DLC;
  *_ide = SPRAYER_CMD_IDE;
  return SPRAYER_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_DECCEL_CMD_pacmod6(BRAKE_DECCEL_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENABLE = (_d[0] & (0x01U));
  _m->IGNORE_OVERRIDES = ((_d[0] >> 1) & (0x01U));
  _m->CLEAR_OVERRIDE = ((_d[0] >> 2) & (0x01U));
  _m->BRAKE_DECCEL_CMD_ro = ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->BRAKE_DECCEL_CMD_phys = (sigfloat_t)(PACMOD6_BRAKE_DECCEL_CMD_ro_fromS(_m->BRAKE_DECCEL_CMD_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->XBR_EBI_MODE = (_d[3] & (0x03U));
  _m->XBR_PRIORITY = ((_d[3] >> 2) & (0x03U));
  _m->XBR_CONTROL_MODE = ((_d[3] >> 4) & (0x03U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_DECCEL_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_DECCEL_CMD_pacmod6(&_m->mon1, BRAKE_DECCEL_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_DECCEL_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_DECCEL_CMD_pacmod6(BRAKE_DECCEL_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECCEL_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->BRAKE_DECCEL_CMD_ro = PACMOD6_BRAKE_DECCEL_CMD_ro_toS(_m->BRAKE_DECCEL_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  cframe->Data[1] |= ((_m->BRAKE_DECCEL_CMD_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->BRAKE_DECCEL_CMD_ro & (0xFFU));
  cframe->Data[3] |= (_m->XBR_EBI_MODE & (0x03U)) | ((_m->XBR_PRIORITY & (0x03U)) << 2) | ((_m->XBR_CONTROL_MODE & (0x03U)) << 4);

  cframe->MsgId = BRAKE_DECCEL_CMD_CANID;
  cframe->DLC = BRAKE_DECCEL_CMD_DLC;
  cframe->IDE = BRAKE_DECCEL_CMD_IDE;
  return BRAKE_DECCEL_CMD_CANID;
}

#else

uint32_t Pack_BRAKE_DECCEL_CMD_pacmod6(BRAKE_DECCEL_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECCEL_CMD_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->BRAKE_DECCEL_CMD_ro = PACMOD6_BRAKE_DECCEL_CMD_ro_toS(_m->BRAKE_DECCEL_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->ENABLE & (0x01U)) | ((_m->IGNORE_OVERRIDES & (0x01U)) << 1) | ((_m->CLEAR_OVERRIDE & (0x01U)) << 2);
  _d[1] |= ((_m->BRAKE_DECCEL_CMD_ro >> 8) & (0xFFU));
  _d[2] |= (_m->BRAKE_DECCEL_CMD_ro & (0xFFU));
  _d[3] |= (_m->XBR_EBI_MODE & (0x03U)) | ((_m->XBR_PRIORITY & (0x03U)) << 2) | ((_m->XBR_CONTROL_MODE & (0x03U)) << 4);

  *_len = BRAKE_DECCEL_CMD_DLC;
  *_ide = BRAKE_DECCEL_CMD_IDE;
  return BRAKE_DECCEL_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_ACCEL_RPT_pacmod6(ACCEL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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
#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD6_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD6_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD6_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ACCEL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ACCEL_RPT_pacmod6(&_m->mon1, ACCEL_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return ACCEL_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_ACCEL_RPT_pacmod6(ACCEL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ACCEL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD6_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD6_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD6_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  cframe->MsgId = ACCEL_RPT_CANID;
  cframe->DLC = ACCEL_RPT_DLC;
  cframe->IDE = ACCEL_RPT_IDE;
  return ACCEL_RPT_CANID;
}

#else

uint32_t Pack_ACCEL_RPT_pacmod6(ACCEL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ACCEL_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD6_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD6_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD6_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  *_len = ACCEL_RPT_DLC;
  *_ide = ACCEL_RPT_IDE;
  return ACCEL_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_ACCEL_CMD_LIMIT_RPT_pacmod6(ACCEL_CMD_LIMIT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ACCEL_CMD_LIMIT_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->ACCEL_CMD_LIMIT_phys = (sigfloat_t)(PACMOD6_ACCEL_CMD_LIMIT_ro_fromS(_m->ACCEL_CMD_LIMIT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->LIMITED_ACCEL_CMD_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->LIMITED_ACCEL_CMD_phys = (sigfloat_t)(PACMOD6_LIMITED_ACCEL_CMD_ro_fromS(_m->LIMITED_ACCEL_CMD_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ACCEL_CMD_LIMIT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ACCEL_CMD_LIMIT_RPT_pacmod6(&_m->mon1, ACCEL_CMD_LIMIT_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return ACCEL_CMD_LIMIT_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_ACCEL_CMD_LIMIT_RPT_pacmod6(ACCEL_CMD_LIMIT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ACCEL_CMD_LIMIT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->ACCEL_CMD_LIMIT_ro = PACMOD6_ACCEL_CMD_LIMIT_ro_toS(_m->ACCEL_CMD_LIMIT_phys);
  _m->LIMITED_ACCEL_CMD_ro = PACMOD6_LIMITED_ACCEL_CMD_ro_toS(_m->LIMITED_ACCEL_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_ACCEL_CMD_LIMIT_RPT_pacmod6(ACCEL_CMD_LIMIT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ACCEL_CMD_LIMIT_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->ACCEL_CMD_LIMIT_ro = PACMOD6_ACCEL_CMD_LIMIT_ro_toS(_m->ACCEL_CMD_LIMIT_phys);
  _m->LIMITED_ACCEL_CMD_ro = PACMOD6_LIMITED_ACCEL_CMD_ro_toS(_m->LIMITED_ACCEL_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= ((_m->ACCEL_CMD_LIMIT_ro >> 8) & (0xFFU));
  _d[1] |= (_m->ACCEL_CMD_LIMIT_ro & (0xFFU));
  _d[2] |= ((_m->LIMITED_ACCEL_CMD_ro >> 8) & (0xFFU));
  _d[3] |= (_m->LIMITED_ACCEL_CMD_ro & (0xFFU));

  *_len = ACCEL_CMD_LIMIT_RPT_DLC;
  *_ide = ACCEL_CMD_LIMIT_RPT_IDE;
  return ACCEL_CMD_LIMIT_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_RPT_pacmod6(BRAKE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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
#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD6_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD6_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD6_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_RPT_pacmod6(&_m->mon1, BRAKE_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_RPT_pacmod6(BRAKE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD6_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD6_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD6_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  cframe->MsgId = BRAKE_RPT_CANID;
  cframe->DLC = BRAKE_RPT_DLC;
  cframe->IDE = BRAKE_RPT_IDE;
  return BRAKE_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_RPT_pacmod6(BRAKE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD6_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD6_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD6_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  *_len = BRAKE_RPT_DLC;
  *_ide = BRAKE_RPT_IDE;
  return BRAKE_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_CMD_LIMIT_RPT_pacmod6(BRAKE_CMD_LIMIT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_CMD_LIMIT_ro = ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->BRAKE_CMD_LIMIT_phys = (sigfloat_t)(PACMOD6_BRAKE_CMD_LIMIT_ro_fromS(_m->BRAKE_CMD_LIMIT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->LIMITED_BRAKE_CMD_ro = ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->LIMITED_BRAKE_CMD_phys = (sigfloat_t)(PACMOD6_LIMITED_BRAKE_CMD_ro_fromS(_m->LIMITED_BRAKE_CMD_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_CMD_LIMIT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_CMD_LIMIT_RPT_pacmod6(&_m->mon1, BRAKE_CMD_LIMIT_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_CMD_LIMIT_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_CMD_LIMIT_RPT_pacmod6(BRAKE_CMD_LIMIT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_CMD_LIMIT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->BRAKE_CMD_LIMIT_ro = PACMOD6_BRAKE_CMD_LIMIT_ro_toS(_m->BRAKE_CMD_LIMIT_phys);
  _m->LIMITED_BRAKE_CMD_ro = PACMOD6_LIMITED_BRAKE_CMD_ro_toS(_m->LIMITED_BRAKE_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_BRAKE_CMD_LIMIT_RPT_pacmod6(BRAKE_CMD_LIMIT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_CMD_LIMIT_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->BRAKE_CMD_LIMIT_ro = PACMOD6_BRAKE_CMD_LIMIT_ro_toS(_m->BRAKE_CMD_LIMIT_phys);
  _m->LIMITED_BRAKE_CMD_ro = PACMOD6_LIMITED_BRAKE_CMD_ro_toS(_m->LIMITED_BRAKE_CMD_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= ((_m->BRAKE_CMD_LIMIT_ro >> 8) & (0xFFU));
  _d[1] |= (_m->BRAKE_CMD_LIMIT_ro & (0xFFU));
  _d[2] |= ((_m->LIMITED_BRAKE_CMD_ro >> 8) & (0xFFU));
  _d[3] |= (_m->LIMITED_BRAKE_CMD_ro & (0xFFU));

  *_len = BRAKE_CMD_LIMIT_RPT_DLC;
  *_ide = BRAKE_CMD_LIMIT_RPT_IDE;
  return BRAKE_CMD_LIMIT_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_CRUISE_CONTROL_BUTTONS_RPT_pacmod6(CRUISE_CONTROL_BUTTONS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < CRUISE_CONTROL_BUTTONS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_CRUISE_CONTROL_BUTTONS_RPT_pacmod6(&_m->mon1, CRUISE_CONTROL_BUTTONS_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return CRUISE_CONTROL_BUTTONS_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_CRUISE_CONTROL_BUTTONS_RPT_pacmod6(CRUISE_CONTROL_BUTTONS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_CRUISE_CONTROL_BUTTONS_RPT_pacmod6(CRUISE_CONTROL_BUTTONS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_DASH_CONTROLS_LEFT_RPT_pacmod6(DASH_CONTROLS_LEFT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DASH_CONTROLS_LEFT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DASH_CONTROLS_LEFT_RPT_pacmod6(&_m->mon1, DASH_CONTROLS_LEFT_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return DASH_CONTROLS_LEFT_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_DASH_CONTROLS_LEFT_RPT_pacmod6(DASH_CONTROLS_LEFT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_DASH_CONTROLS_LEFT_RPT_pacmod6(DASH_CONTROLS_LEFT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_DASH_CONTROLS_RIGHT_RPT_pacmod6(DASH_CONTROLS_RIGHT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DASH_CONTROLS_RIGHT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DASH_CONTROLS_RIGHT_RPT_pacmod6(&_m->mon1, DASH_CONTROLS_RIGHT_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return DASH_CONTROLS_RIGHT_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_DASH_CONTROLS_RIGHT_RPT_pacmod6(DASH_CONTROLS_RIGHT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_DASH_CONTROLS_RIGHT_RPT_pacmod6(DASH_CONTROLS_RIGHT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_HAZARD_LIGHTS_RPT_pacmod6(HAZARD_LIGHTS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HAZARD_LIGHTS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HAZARD_LIGHTS_RPT_pacmod6(&_m->mon1, HAZARD_LIGHTS_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return HAZARD_LIGHTS_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_HAZARD_LIGHTS_RPT_pacmod6(HAZARD_LIGHTS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_HAZARD_LIGHTS_RPT_pacmod6(HAZARD_LIGHTS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_HEADLIGHT_RPT_pacmod6(HEADLIGHT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HEADLIGHT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HEADLIGHT_RPT_pacmod6(&_m->mon1, HEADLIGHT_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return HEADLIGHT_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_HEADLIGHT_RPT_pacmod6(HEADLIGHT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_HEADLIGHT_RPT_pacmod6(HEADLIGHT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_HORN_RPT_pacmod6(HORN_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HORN_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HORN_RPT_pacmod6(&_m->mon1, HORN_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return HORN_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_HORN_RPT_pacmod6(HORN_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_HORN_RPT_pacmod6(HORN_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_MEDIA_CONTROLS_RPT_pacmod6(MEDIA_CONTROLS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < MEDIA_CONTROLS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_MEDIA_CONTROLS_RPT_pacmod6(&_m->mon1, MEDIA_CONTROLS_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return MEDIA_CONTROLS_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_MEDIA_CONTROLS_RPT_pacmod6(MEDIA_CONTROLS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_MEDIA_CONTROLS_RPT_pacmod6(MEDIA_CONTROLS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_PARKING_BRAKE_RPT_pacmod6(PARKING_BRAKE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < PARKING_BRAKE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_PARKING_BRAKE_RPT_pacmod6(&_m->mon1, PARKING_BRAKE_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return PARKING_BRAKE_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_PARKING_BRAKE_RPT_pacmod6(PARKING_BRAKE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0x01U));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0x01U));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0x01U));

  cframe->MsgId = PARKING_BRAKE_RPT_CANID;
  cframe->DLC = PARKING_BRAKE_RPT_DLC;
  cframe->IDE = PARKING_BRAKE_RPT_IDE;
  return PARKING_BRAKE_RPT_CANID;
}

#else

uint32_t Pack_PARKING_BRAKE_RPT_pacmod6(PARKING_BRAKE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < PARKING_BRAKE_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0x01U));
  _d[2] |= (_m->COMMANDED_VALUE & (0x01U));
  _d[3] |= (_m->OUTPUT_VALUE & (0x01U));

  *_len = PARKING_BRAKE_RPT_DLC;
  *_ide = PARKING_BRAKE_RPT_IDE;
  return PARKING_BRAKE_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_SHIFT_RPT_pacmod6(SHIFT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SHIFT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SHIFT_RPT_pacmod6(&_m->mon1, SHIFT_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return SHIFT_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_SHIFT_RPT_pacmod6(SHIFT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SHIFT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->MANUAL_INPUT & (0xFFU));
  cframe->Data[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  cframe->Data[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  cframe->MsgId = SHIFT_RPT_CANID;
  cframe->DLC = SHIFT_RPT_DLC;
  cframe->IDE = SHIFT_RPT_IDE;
  return SHIFT_RPT_CANID;
}

#else

uint32_t Pack_SHIFT_RPT_pacmod6(SHIFT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SHIFT_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->MANUAL_INPUT & (0xFFU));
  _d[2] |= (_m->COMMANDED_VALUE & (0xFFU));
  _d[3] |= (_m->OUTPUT_VALUE & (0xFFU));

  *_len = SHIFT_RPT_DLC;
  *_ide = SHIFT_RPT_IDE;
  return SHIFT_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_STEERING_RPT_pacmod6(STEERING_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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
#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD6_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = __ext_sig__(( ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD6_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = __ext_sig__(( ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD6_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_RPT_pacmod6(&_m->mon1, STEERING_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return STEERING_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_STEERING_RPT_pacmod6(STEERING_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD6_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD6_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD6_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  cframe->MsgId = STEERING_RPT_CANID;
  cframe->DLC = STEERING_RPT_DLC;
  cframe->IDE = STEERING_RPT_IDE;
  return STEERING_RPT_CANID;
}

#else

uint32_t Pack_STEERING_RPT_pacmod6(STEERING_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD6_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD6_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD6_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  *_len = STEERING_RPT_DLC;
  *_ide = STEERING_RPT_IDE;
  return STEERING_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_STEERING_CMD_LIMIT_RPT_pacmod6(STEERING_CMD_LIMIT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->POSITION_CMD_LIMIT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->POSITION_CMD_LIMIT_phys = (sigfloat_t)(PACMOD6_POSITION_CMD_LIMIT_ro_fromS(_m->POSITION_CMD_LIMIT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->LIMITED_POSITION_CMD_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->LIMITED_POSITION_CMD_phys = (sigfloat_t)(PACMOD6_LIMITED_POSITION_CMD_ro_fromS(_m->LIMITED_POSITION_CMD_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->ROTATION_RATE_CMD_LIMIT_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->ROTATION_RATE_CMD_LIMIT_phys = (sigfloat_t)(PACMOD6_ROTATION_RATE_CMD_LIMIT_ro_fromS(_m->ROTATION_RATE_CMD_LIMIT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->LIMITED_ROTATION_RATE_ro = ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->LIMITED_ROTATION_RATE_phys = (sigfloat_t)(PACMOD6_LIMITED_ROTATION_RATE_ro_fromS(_m->LIMITED_ROTATION_RATE_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_CMD_LIMIT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_CMD_LIMIT_RPT_pacmod6(&_m->mon1, STEERING_CMD_LIMIT_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return STEERING_CMD_LIMIT_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_STEERING_CMD_LIMIT_RPT_pacmod6(STEERING_CMD_LIMIT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_CMD_LIMIT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->POSITION_CMD_LIMIT_ro = PACMOD6_POSITION_CMD_LIMIT_ro_toS(_m->POSITION_CMD_LIMIT_phys);
  _m->LIMITED_POSITION_CMD_ro = PACMOD6_LIMITED_POSITION_CMD_ro_toS(_m->LIMITED_POSITION_CMD_phys);
  _m->ROTATION_RATE_CMD_LIMIT_ro = PACMOD6_ROTATION_RATE_CMD_LIMIT_ro_toS(_m->ROTATION_RATE_CMD_LIMIT_phys);
  _m->LIMITED_ROTATION_RATE_ro = PACMOD6_LIMITED_ROTATION_RATE_ro_toS(_m->LIMITED_ROTATION_RATE_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_STEERING_CMD_LIMIT_RPT_pacmod6(STEERING_CMD_LIMIT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_CMD_LIMIT_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->POSITION_CMD_LIMIT_ro = PACMOD6_POSITION_CMD_LIMIT_ro_toS(_m->POSITION_CMD_LIMIT_phys);
  _m->LIMITED_POSITION_CMD_ro = PACMOD6_LIMITED_POSITION_CMD_ro_toS(_m->LIMITED_POSITION_CMD_phys);
  _m->ROTATION_RATE_CMD_LIMIT_ro = PACMOD6_ROTATION_RATE_CMD_LIMIT_ro_toS(_m->ROTATION_RATE_CMD_LIMIT_phys);
  _m->LIMITED_ROTATION_RATE_ro = PACMOD6_LIMITED_ROTATION_RATE_ro_toS(_m->LIMITED_ROTATION_RATE_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_TURN_RPT_pacmod6(TURN_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TURN_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TURN_RPT_pacmod6(&_m->mon1, TURN_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return TURN_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_TURN_RPT_pacmod6(TURN_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_TURN_RPT_pacmod6(TURN_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_WIPER_RPT_pacmod6(WIPER_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WIPER_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WIPER_RPT_pacmod6(&_m->mon1, WIPER_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return WIPER_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_WIPER_RPT_pacmod6(WIPER_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_WIPER_RPT_pacmod6(WIPER_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_SPRAYER_RPT_pacmod6(SPRAYER_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SPRAYER_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SPRAYER_RPT_pacmod6(&_m->mon1, SPRAYER_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return SPRAYER_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_SPRAYER_RPT_pacmod6(SPRAYER_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_SPRAYER_RPT_pacmod6(SPRAYER_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_DECCEL_RPT_pacmod6(BRAKE_DECCEL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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
#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_phys = (sigfloat_t)(PACMOD6_MANUAL_INPUT_ro_fromS(_m->MANUAL_INPUT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->COMMANDED_VALUE_ro = ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->COMMANDED_VALUE_phys = (sigfloat_t)(PACMOD6_COMMANDED_VALUE_ro_fromS(_m->COMMANDED_VALUE_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->OUTPUT_VALUE_ro = ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->OUTPUT_VALUE_phys = (sigfloat_t)(PACMOD6_OUTPUT_VALUE_ro_fromS(_m->OUTPUT_VALUE_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_DECCEL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_DECCEL_RPT_pacmod6(&_m->mon1, BRAKE_DECCEL_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_DECCEL_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_DECCEL_RPT_pacmod6(BRAKE_DECCEL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECCEL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD6_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD6_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD6_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  cframe->Data[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  cframe->Data[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  cframe->MsgId = BRAKE_DECCEL_RPT_CANID;
  cframe->DLC = BRAKE_DECCEL_RPT_DLC;
  cframe->IDE = BRAKE_DECCEL_RPT_IDE;
  return BRAKE_DECCEL_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_DECCEL_RPT_pacmod6(BRAKE_DECCEL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECCEL_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MANUAL_INPUT_ro = PACMOD6_MANUAL_INPUT_ro_toS(_m->MANUAL_INPUT_phys);
  _m->COMMANDED_VALUE_ro = PACMOD6_COMMANDED_VALUE_ro_toS(_m->COMMANDED_VALUE_phys);
  _m->OUTPUT_VALUE_ro = PACMOD6_OUTPUT_VALUE_ro_toS(_m->OUTPUT_VALUE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->ENABLED & (0x01U)) | ((_m->OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->PACMOD_FAULT & (0x01U)) << 5) | ((_m->VEHICLE_FAULT & (0x01U)) << 6) | ((_m->COMMAND_TIMEOUT & (0x01U)) << 7);
  _d[1] |= ((_m->MANUAL_INPUT_ro >> 8) & (0xFFU));
  _d[2] |= (_m->MANUAL_INPUT_ro & (0xFFU));
  _d[3] |= ((_m->COMMANDED_VALUE_ro >> 8) & (0xFFU));
  _d[4] |= (_m->COMMANDED_VALUE_ro & (0xFFU));
  _d[5] |= ((_m->OUTPUT_VALUE_ro >> 8) & (0xFFU));
  _d[6] |= (_m->OUTPUT_VALUE_ro & (0xFFU));

  *_len = BRAKE_DECCEL_RPT_DLC;
  *_ide = BRAKE_DECCEL_RPT_IDE;
  return BRAKE_DECCEL_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_ACCEL_AUX_RPT_pacmod6(ACCEL_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->RAW_PEDAL_POS_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->RAW_PEDAL_POS_phys = (sigfloat_t)(PACMOD6_RAW_PEDAL_POS_ro_fromS(_m->RAW_PEDAL_POS_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->RAW_PEDAL_FORCE_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->RAW_PEDAL_FORCE_phys = (sigfloat_t)(PACMOD6_RAW_PEDAL_FORCE_ro_fromS(_m->RAW_PEDAL_FORCE_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->OPERATOR_INTERACTION = (_d[4] & (0x01U));
  _m->RAW_PEDAL_POS_AVAIL = (_d[5] & (0x01U));
  _m->RAW_PEDAL_FORCE_AVAIL = ((_d[5] >> 1) & (0x01U));
  _m->OPERATOR_INTERACTION_AVAIL = ((_d[5] >> 2) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ACCEL_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ACCEL_AUX_RPT_pacmod6(&_m->mon1, ACCEL_AUX_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return ACCEL_AUX_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_ACCEL_AUX_RPT_pacmod6(ACCEL_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ACCEL_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->RAW_PEDAL_POS_ro = PACMOD6_RAW_PEDAL_POS_ro_toS(_m->RAW_PEDAL_POS_phys);
  _m->RAW_PEDAL_FORCE_ro = PACMOD6_RAW_PEDAL_FORCE_ro_toS(_m->RAW_PEDAL_FORCE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->RAW_PEDAL_POS_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->RAW_PEDAL_POS_ro & (0xFFU));
  cframe->Data[2] |= ((_m->RAW_PEDAL_FORCE_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->RAW_PEDAL_FORCE_ro & (0xFFU));
  cframe->Data[4] |= (_m->OPERATOR_INTERACTION & (0x01U));
  cframe->Data[5] |= (_m->RAW_PEDAL_POS_AVAIL & (0x01U)) | ((_m->RAW_PEDAL_FORCE_AVAIL & (0x01U)) << 1) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 2);

  cframe->MsgId = ACCEL_AUX_RPT_CANID;
  cframe->DLC = ACCEL_AUX_RPT_DLC;
  cframe->IDE = ACCEL_AUX_RPT_IDE;
  return ACCEL_AUX_RPT_CANID;
}

#else

uint32_t Pack_ACCEL_AUX_RPT_pacmod6(ACCEL_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ACCEL_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->RAW_PEDAL_POS_ro = PACMOD6_RAW_PEDAL_POS_ro_toS(_m->RAW_PEDAL_POS_phys);
  _m->RAW_PEDAL_FORCE_ro = PACMOD6_RAW_PEDAL_FORCE_ro_toS(_m->RAW_PEDAL_FORCE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= ((_m->RAW_PEDAL_POS_ro >> 8) & (0xFFU));
  _d[1] |= (_m->RAW_PEDAL_POS_ro & (0xFFU));
  _d[2] |= ((_m->RAW_PEDAL_FORCE_ro >> 8) & (0xFFU));
  _d[3] |= (_m->RAW_PEDAL_FORCE_ro & (0xFFU));
  _d[4] |= (_m->OPERATOR_INTERACTION & (0x01U));
  _d[5] |= (_m->RAW_PEDAL_POS_AVAIL & (0x01U)) | ((_m->RAW_PEDAL_FORCE_AVAIL & (0x01U)) << 1) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 2);

  *_len = ACCEL_AUX_RPT_DLC;
  *_ide = ACCEL_AUX_RPT_IDE;
  return ACCEL_AUX_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_AUX_RPT_pacmod6(BRAKE_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->RAW_PEDAL_POS = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
  _m->RAW_PEDAL_FORCE = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
  _m->RAW_BRAKE_PRESSURE = __ext_sig__(( ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU)) ), 16);
  _m->OPERATOR_INTERACTION = (_d[6] & (0x01U));
  _m->BRAKE_ON_OFF = ((_d[6] >> 1) & (0x01U));
  _m->RAW_PEDAL_POS_AVAIL = (_d[7] & (0x01U));
  _m->RAW_PEDAL_FORCE_AVAIL = ((_d[7] >> 1) & (0x01U));
  _m->RAW_BRAKE_PRESSURE_AVAIL = ((_d[7] >> 2) & (0x01U));
  _m->OPERATOR_INTERACTION_AVAIL = ((_d[7] >> 3) & (0x01U));
  _m->BRAKE_ON_OFF_AVAIL = ((_d[7] >> 4) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_AUX_RPT_pacmod6(&_m->mon1, BRAKE_AUX_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_AUX_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_AUX_RPT_pacmod6(BRAKE_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= ((_m->RAW_PEDAL_POS >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->RAW_PEDAL_POS & (0xFFU));
  cframe->Data[2] |= ((_m->RAW_PEDAL_FORCE >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->RAW_PEDAL_FORCE & (0xFFU));
  cframe->Data[4] |= ((_m->RAW_BRAKE_PRESSURE >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->RAW_BRAKE_PRESSURE & (0xFFU));
  cframe->Data[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->BRAKE_ON_OFF & (0x01U)) << 1);
  cframe->Data[7] |= (_m->RAW_PEDAL_POS_AVAIL & (0x01U)) | ((_m->RAW_PEDAL_FORCE_AVAIL & (0x01U)) << 1) | ((_m->RAW_BRAKE_PRESSURE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->BRAKE_ON_OFF_AVAIL & (0x01U)) << 4);

  cframe->MsgId = BRAKE_AUX_RPT_CANID;
  cframe->DLC = BRAKE_AUX_RPT_DLC;
  cframe->IDE = BRAKE_AUX_RPT_IDE;
  return BRAKE_AUX_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_AUX_RPT_pacmod6(BRAKE_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= ((_m->RAW_PEDAL_POS >> 8) & (0xFFU));
  _d[1] |= (_m->RAW_PEDAL_POS & (0xFFU));
  _d[2] |= ((_m->RAW_PEDAL_FORCE >> 8) & (0xFFU));
  _d[3] |= (_m->RAW_PEDAL_FORCE & (0xFFU));
  _d[4] |= ((_m->RAW_BRAKE_PRESSURE >> 8) & (0xFFU));
  _d[5] |= (_m->RAW_BRAKE_PRESSURE & (0xFFU));
  _d[6] |= (_m->OPERATOR_INTERACTION & (0x01U)) | ((_m->BRAKE_ON_OFF & (0x01U)) << 1);
  _d[7] |= (_m->RAW_PEDAL_POS_AVAIL & (0x01U)) | ((_m->RAW_PEDAL_FORCE_AVAIL & (0x01U)) << 1) | ((_m->RAW_BRAKE_PRESSURE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3) | ((_m->BRAKE_ON_OFF_AVAIL & (0x01U)) << 4);

  *_len = BRAKE_AUX_RPT_DLC;
  *_ide = BRAKE_AUX_RPT_IDE;
  return BRAKE_AUX_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_HEADLIGHT_AUX_RPT_pacmod6(HEADLIGHT_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < HEADLIGHT_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_HEADLIGHT_AUX_RPT_pacmod6(&_m->mon1, HEADLIGHT_AUX_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return HEADLIGHT_AUX_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_HEADLIGHT_AUX_RPT_pacmod6(HEADLIGHT_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_HEADLIGHT_AUX_RPT_pacmod6(HEADLIGHT_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < HEADLIGHT_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->HEADLIGHTS_ON & (0x01U)) | ((_m->HEADLIGHTS_ON_BRIGHT & (0x01U)) << 1) | ((_m->FOG_LIGHTS_ON & (0x01U)) << 2);
  _d[1] |= (_m->HEADLIGHTS_MODE & (0xFFU));
  _d[2] |= (_m->HEADLIGHTS_ON_AVAIL & (0x01U)) | ((_m->HEADLIGHTS_ON_BRIGHT_AVAIL & (0x01U)) << 1) | ((_m->FOG_LIGHTS_ON_AVAIL & (0x01U)) << 2) | ((_m->HEADLIGHTS_MODE_AVAIL & (0x01U)) << 3);

  *_len = HEADLIGHT_AUX_RPT_DLC;
  *_ide = HEADLIGHT_AUX_RPT_IDE;
  return HEADLIGHT_AUX_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_SHIFT_AUX_RPT_pacmod6(SHIFT_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BETWEEN_GEARS = (_d[0] & (0x01U));
  _m->STAY_IN_NEUTRAL_MODE = ((_d[0] >> 1) & (0x01U));
  _m->BRAKE_INTERLOCK_ACTIVE = ((_d[0] >> 2) & (0x01U));
  _m->SPEED_INTERLOCK_ACTIVE = ((_d[0] >> 3) & (0x01U));
  _m->BETWEEN_GEARS_AVAIL = (_d[1] & (0x01U));
  _m->STAY_IN_NEUTRAL_MODE_AVAIL = ((_d[1] >> 1) & (0x01U));
  _m->BRAKE_INTERLOCK_ACTIVE_AVAIL = ((_d[1] >> 2) & (0x01U));
  _m->SPEED_INTERLOCK_ACTIVE_AVAIL = ((_d[1] >> 3) & (0x01U));
  _m->WRITE_TO_CONFIG = (_d[7] & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SHIFT_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SHIFT_AUX_RPT_pacmod6(&_m->mon1, SHIFT_AUX_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return SHIFT_AUX_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_SHIFT_AUX_RPT_pacmod6(SHIFT_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < SHIFT_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BETWEEN_GEARS & (0x01U)) | ((_m->STAY_IN_NEUTRAL_MODE & (0x01U)) << 1) | ((_m->BRAKE_INTERLOCK_ACTIVE & (0x01U)) << 2) | ((_m->SPEED_INTERLOCK_ACTIVE & (0x01U)) << 3);
  cframe->Data[1] |= (_m->BETWEEN_GEARS_AVAIL & (0x01U)) | ((_m->STAY_IN_NEUTRAL_MODE_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 2) | ((_m->SPEED_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 3);
  cframe->Data[7] |= (_m->WRITE_TO_CONFIG & (0x01U));

  cframe->MsgId = SHIFT_AUX_RPT_CANID;
  cframe->DLC = SHIFT_AUX_RPT_DLC;
  cframe->IDE = SHIFT_AUX_RPT_IDE;
  return SHIFT_AUX_RPT_CANID;
}

#else

uint32_t Pack_SHIFT_AUX_RPT_pacmod6(SHIFT_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < SHIFT_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BETWEEN_GEARS & (0x01U)) | ((_m->STAY_IN_NEUTRAL_MODE & (0x01U)) << 1) | ((_m->BRAKE_INTERLOCK_ACTIVE & (0x01U)) << 2) | ((_m->SPEED_INTERLOCK_ACTIVE & (0x01U)) << 3);
  _d[1] |= (_m->BETWEEN_GEARS_AVAIL & (0x01U)) | ((_m->STAY_IN_NEUTRAL_MODE_AVAIL & (0x01U)) << 1) | ((_m->BRAKE_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 2) | ((_m->SPEED_INTERLOCK_ACTIVE_AVAIL & (0x01U)) << 3);
  _d[7] |= (_m->WRITE_TO_CONFIG & (0x01U));

  *_len = SHIFT_AUX_RPT_DLC;
  *_ide = SHIFT_AUX_RPT_IDE;
  return SHIFT_AUX_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_STEERING_AUX_RPT_pacmod6(STEERING_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->RAW_POSITION_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->RAW_POSITION_phys = (sigfloat_t)(PACMOD6_RAW_POSITION_ro_fromS(_m->RAW_POSITION_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->RAW_TORQUE_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->RAW_TORQUE_phys = (sigfloat_t)(PACMOD6_RAW_TORQUE_ro_fromS(_m->RAW_TORQUE_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->ROTATION_RATE_ro = ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->ROTATION_RATE_phys = (sigfloat_t)(PACMOD6_ROTATION_RATE_ro_fromS(_m->ROTATION_RATE_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->OPERATOR_INTERACTION = (_d[6] & (0x01U));
  _m->RAW_POSITION_AVAIL = (_d[7] & (0x01U));
  _m->RAW_TORQUE_AVAIL = ((_d[7] >> 1) & (0x01U));
  _m->ROTATION_RATE_AVAIL = ((_d[7] >> 2) & (0x01U));
  _m->OPERATOR_INTERACTION_AVAIL = ((_d[7] >> 3) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_AUX_RPT_pacmod6(&_m->mon1, STEERING_AUX_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return STEERING_AUX_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_STEERING_AUX_RPT_pacmod6(STEERING_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->RAW_POSITION_ro = PACMOD6_RAW_POSITION_ro_toS(_m->RAW_POSITION_phys);
  _m->RAW_TORQUE_ro = PACMOD6_RAW_TORQUE_ro_toS(_m->RAW_TORQUE_phys);
  _m->ROTATION_RATE_ro = PACMOD6_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->RAW_POSITION_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->RAW_POSITION_ro & (0xFFU));
  cframe->Data[2] |= ((_m->RAW_TORQUE_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->RAW_TORQUE_ro & (0xFFU));
  cframe->Data[4] |= ((_m->ROTATION_RATE_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->ROTATION_RATE_ro & (0xFFU));
  cframe->Data[6] |= (_m->OPERATOR_INTERACTION & (0x01U));
  cframe->Data[7] |= (_m->RAW_POSITION_AVAIL & (0x01U)) | ((_m->RAW_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ROTATION_RATE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3);

  cframe->MsgId = STEERING_AUX_RPT_CANID;
  cframe->DLC = STEERING_AUX_RPT_DLC;
  cframe->IDE = STEERING_AUX_RPT_IDE;
  return STEERING_AUX_RPT_CANID;
}

#else

uint32_t Pack_STEERING_AUX_RPT_pacmod6(STEERING_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->RAW_POSITION_ro = PACMOD6_RAW_POSITION_ro_toS(_m->RAW_POSITION_phys);
  _m->RAW_TORQUE_ro = PACMOD6_RAW_TORQUE_ro_toS(_m->RAW_TORQUE_phys);
  _m->ROTATION_RATE_ro = PACMOD6_ROTATION_RATE_ro_toS(_m->ROTATION_RATE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= ((_m->RAW_POSITION_ro >> 8) & (0xFFU));
  _d[1] |= (_m->RAW_POSITION_ro & (0xFFU));
  _d[2] |= ((_m->RAW_TORQUE_ro >> 8) & (0xFFU));
  _d[3] |= (_m->RAW_TORQUE_ro & (0xFFU));
  _d[4] |= ((_m->ROTATION_RATE_ro >> 8) & (0xFFU));
  _d[5] |= (_m->ROTATION_RATE_ro & (0xFFU));
  _d[6] |= (_m->OPERATOR_INTERACTION & (0x01U));
  _d[7] |= (_m->RAW_POSITION_AVAIL & (0x01U)) | ((_m->RAW_TORQUE_AVAIL & (0x01U)) << 1) | ((_m->ROTATION_RATE_AVAIL & (0x01U)) << 2) | ((_m->OPERATOR_INTERACTION_AVAIL & (0x01U)) << 3);

  *_len = STEERING_AUX_RPT_DLC;
  *_ide = STEERING_AUX_RPT_IDE;
  return STEERING_AUX_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_TURN_AUX_RPT_pacmod6(TURN_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DRIVER_BLINKER_BULB_ON = (_d[0] & (0x01U));
  _m->PASS_BLINKER_BULB_ON = ((_d[0] >> 1) & (0x01U));
  _m->DRIVER_BLINKER_BULB_ON_AVAIL = (_d[1] & (0x01U));
  _m->PASS_BLINKER_BULB_ON_AVAIL = ((_d[1] >> 1) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < TURN_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_TURN_AUX_RPT_pacmod6(&_m->mon1, TURN_AUX_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return TURN_AUX_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_TURN_AUX_RPT_pacmod6(TURN_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_TURN_AUX_RPT_pacmod6(TURN_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < TURN_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->DRIVER_BLINKER_BULB_ON & (0x01U)) | ((_m->PASS_BLINKER_BULB_ON & (0x01U)) << 1);
  _d[1] |= (_m->DRIVER_BLINKER_BULB_ON_AVAIL & (0x01U)) | ((_m->PASS_BLINKER_BULB_ON_AVAIL & (0x01U)) << 1);

  *_len = TURN_AUX_RPT_DLC;
  *_ide = TURN_AUX_RPT_IDE;
  return TURN_AUX_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_WIPER_AUX_RPT_pacmod6(WIPER_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WIPER_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WIPER_AUX_RPT_pacmod6(&_m->mon1, WIPER_AUX_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return WIPER_AUX_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_WIPER_AUX_RPT_pacmod6(WIPER_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_WIPER_AUX_RPT_pacmod6(WIPER_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WIPER_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->FRONT_WIPING & (0x01U)) | ((_m->FRONT_SPRAYING & (0x01U)) << 1) | ((_m->REAR_WIPING & (0x01U)) << 2) | ((_m->REAR_SPRAYING & (0x01U)) << 3) | ((_m->SPRAY_NEAR_EMPTY & (0x01U)) << 4) | ((_m->SPRAY_EMPTY & (0x01U)) << 5);
  _d[1] |= (_m->FRONT_WIPING_AVAIL & (0x01U)) | ((_m->FRONT_SPRAYING_AVAIL & (0x01U)) << 1) | ((_m->REAR_WIPING_AVAIL & (0x01U)) << 2) | ((_m->REAR_SPRAYING_AVAIL & (0x01U)) << 3) | ((_m->SPRAY_NEAR_EMPTY_AVAIL & (0x01U)) << 4) | ((_m->SPRAY_EMPTY_AVAIL & (0x01U)) << 5);

  *_len = WIPER_AUX_RPT_DLC;
  *_ide = WIPER_AUX_RPT_IDE;
  return WIPER_AUX_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_DECCEL_AUX_RPT_pacmod6(BRAKE_DECCEL_AUX_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
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

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_DECCEL_AUX_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_DECCEL_AUX_RPT_pacmod6(&_m->mon1, BRAKE_DECCEL_AUX_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_DECCEL_AUX_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_DECCEL_AUX_RPT_pacmod6(BRAKE_DECCEL_AUX_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECCEL_AUX_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->XBR_ACTIVE_CONTROL_MODE & (0x0FU)) | ((_m->XBR_SYSTEM_STATE & (0x03U)) << 4) | ((_m->FOUNDATION_BRAKE_USE & (0x03U)) << 6);
  cframe->Data[1] |= (_m->HILL_HOLDER_MODE & (0x07U));
  cframe->Data[2] |= (_m->XBR_ACTIVE_CONTROL_MODE_AVAIL & (0x01U)) | ((_m->XBR_SYSTEM_STATE_AVAIL & (0x01U)) << 1) | ((_m->FOUNDATION_BRAKE_USE_AVAIL & (0x01U)) << 2) | ((_m->HILL_HOLDER_MODE_AVAIL & (0x01U)) << 3);

  cframe->MsgId = BRAKE_DECCEL_AUX_RPT_CANID;
  cframe->DLC = BRAKE_DECCEL_AUX_RPT_DLC;
  cframe->IDE = BRAKE_DECCEL_AUX_RPT_IDE;
  return BRAKE_DECCEL_AUX_RPT_CANID;
}

#else

uint32_t Pack_BRAKE_DECCEL_AUX_RPT_pacmod6(BRAKE_DECCEL_AUX_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_DECCEL_AUX_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->XBR_ACTIVE_CONTROL_MODE & (0x0FU)) | ((_m->XBR_SYSTEM_STATE & (0x03U)) << 4) | ((_m->FOUNDATION_BRAKE_USE & (0x03U)) << 6);
  _d[1] |= (_m->HILL_HOLDER_MODE & (0x07U));
  _d[2] |= (_m->XBR_ACTIVE_CONTROL_MODE_AVAIL & (0x01U)) | ((_m->XBR_SYSTEM_STATE_AVAIL & (0x01U)) << 1) | ((_m->FOUNDATION_BRAKE_USE_AVAIL & (0x01U)) << 2) | ((_m->HILL_HOLDER_MODE_AVAIL & (0x01U)) << 3);

  *_len = BRAKE_DECCEL_AUX_RPT_DLC;
  *_ide = BRAKE_DECCEL_AUX_RPT_IDE;
  return BRAKE_DECCEL_AUX_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_VEHICLE_SPEED_RPT_pacmod6(VEHICLE_SPEED_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->VEHICLE_SPEED_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->VEHICLE_SPEED_phys = (sigfloat_t)(PACMOD6_VEHICLE_SPEED_ro_fromS(_m->VEHICLE_SPEED_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->VEHICLE_SPEED_VALID = (_d[2] & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEHICLE_SPEED_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEHICLE_SPEED_RPT_pacmod6(&_m->mon1, VEHICLE_SPEED_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return VEHICLE_SPEED_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_VEHICLE_SPEED_RPT_pacmod6(VEHICLE_SPEED_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < VEHICLE_SPEED_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->VEHICLE_SPEED_ro = PACMOD6_VEHICLE_SPEED_ro_toS(_m->VEHICLE_SPEED_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->VEHICLE_SPEED_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->VEHICLE_SPEED_ro & (0xFFU));
  cframe->Data[2] |= (_m->VEHICLE_SPEED_VALID & (0x01U));

  cframe->MsgId = VEHICLE_SPEED_RPT_CANID;
  cframe->DLC = VEHICLE_SPEED_RPT_DLC;
  cframe->IDE = VEHICLE_SPEED_RPT_IDE;
  return VEHICLE_SPEED_RPT_CANID;
}

#else

uint32_t Pack_VEHICLE_SPEED_RPT_pacmod6(VEHICLE_SPEED_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < VEHICLE_SPEED_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->VEHICLE_SPEED_ro = PACMOD6_VEHICLE_SPEED_ro_toS(_m->VEHICLE_SPEED_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= ((_m->VEHICLE_SPEED_ro >> 8) & (0xFFU));
  _d[1] |= (_m->VEHICLE_SPEED_ro & (0xFFU));
  _d[2] |= (_m->VEHICLE_SPEED_VALID & (0x01U));

  *_len = VEHICLE_SPEED_RPT_DLC;
  *_ide = VEHICLE_SPEED_RPT_IDE;
  return VEHICLE_SPEED_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_MOTOR_RPT_1_pacmod6(BRAKE_MOTOR_RPT_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MOTOR_CURRENT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 24) | ((_d[1] & (0xFFU)) << 16) | ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->MOTOR_CURRENT_phys = (sigfloat_t)(PACMOD6_MOTOR_CURRENT_ro_fromS(_m->MOTOR_CURRENT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->SHAFT_POSITION_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->SHAFT_POSITION_phys = (sigfloat_t)(PACMOD6_SHAFT_POSITION_ro_fromS(_m->SHAFT_POSITION_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_MOTOR_RPT_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_MOTOR_RPT_1_pacmod6(&_m->mon1, BRAKE_MOTOR_RPT_1_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_MOTOR_RPT_1_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_MOTOR_RPT_1_pacmod6(BRAKE_MOTOR_RPT_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_1_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MOTOR_CURRENT_ro = PACMOD6_MOTOR_CURRENT_ro_toS(_m->MOTOR_CURRENT_phys);
  _m->SHAFT_POSITION_ro = PACMOD6_SHAFT_POSITION_ro_toS(_m->SHAFT_POSITION_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_BRAKE_MOTOR_RPT_1_pacmod6(BRAKE_MOTOR_RPT_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_1_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MOTOR_CURRENT_ro = PACMOD6_MOTOR_CURRENT_ro_toS(_m->MOTOR_CURRENT_phys);
  _m->SHAFT_POSITION_ro = PACMOD6_SHAFT_POSITION_ro_toS(_m->SHAFT_POSITION_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_MOTOR_RPT_2_pacmod6(BRAKE_MOTOR_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENCODER_TEMPERATURE = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
  _m->MOTOR_TEMPERATURE = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
  _m->ANGULAR_SPEED_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->ANGULAR_SPEED_phys = (sigfloat_t)(PACMOD6_ANGULAR_SPEED_ro_fromS(_m->ANGULAR_SPEED_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_MOTOR_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_MOTOR_RPT_2_pacmod6(&_m->mon1, BRAKE_MOTOR_RPT_2_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_MOTOR_RPT_2_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_MOTOR_RPT_2_pacmod6(BRAKE_MOTOR_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->ANGULAR_SPEED_ro = PACMOD6_ANGULAR_SPEED_ro_toS(_m->ANGULAR_SPEED_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_BRAKE_MOTOR_RPT_2_pacmod6(BRAKE_MOTOR_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->ANGULAR_SPEED_ro = PACMOD6_ANGULAR_SPEED_ro_toS(_m->ANGULAR_SPEED_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_BRAKE_MOTOR_RPT_3_pacmod6(BRAKE_MOTOR_RPT_3_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TORQUE_OUTPUT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 24) | ((_d[1] & (0xFFU)) << 16) | ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_phys = (sigfloat_t)(PACMOD6_TORQUE_OUTPUT_ro_fromS(_m->TORQUE_OUTPUT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->TORQUE_INPUT_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->TORQUE_INPUT_phys = (sigfloat_t)(PACMOD6_TORQUE_INPUT_ro_fromS(_m->TORQUE_INPUT_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BRAKE_MOTOR_RPT_3_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BRAKE_MOTOR_RPT_3_pacmod6(&_m->mon1, BRAKE_MOTOR_RPT_3_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return BRAKE_MOTOR_RPT_3_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_BRAKE_MOTOR_RPT_3_pacmod6(BRAKE_MOTOR_RPT_3_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_3_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_ro = PACMOD6_TORQUE_OUTPUT_ro_toS(_m->TORQUE_OUTPUT_phys);
  _m->TORQUE_INPUT_ro = PACMOD6_TORQUE_INPUT_ro_toS(_m->TORQUE_INPUT_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_BRAKE_MOTOR_RPT_3_pacmod6(BRAKE_MOTOR_RPT_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BRAKE_MOTOR_RPT_3_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_ro = PACMOD6_TORQUE_OUTPUT_ro_toS(_m->TORQUE_OUTPUT_phys);
  _m->TORQUE_INPUT_ro = PACMOD6_TORQUE_INPUT_ro_toS(_m->TORQUE_INPUT_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_STEERING_MOTOR_RPT_1_pacmod6(STEERING_MOTOR_RPT_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MOTOR_CURRENT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 24) | ((_d[1] & (0xFFU)) << 16) | ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->MOTOR_CURRENT_phys = (sigfloat_t)(PACMOD6_MOTOR_CURRENT_ro_fromS(_m->MOTOR_CURRENT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->SHAFT_POSITION_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->SHAFT_POSITION_phys = (sigfloat_t)(PACMOD6_SHAFT_POSITION_ro_fromS(_m->SHAFT_POSITION_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_MOTOR_RPT_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_MOTOR_RPT_1_pacmod6(&_m->mon1, STEERING_MOTOR_RPT_1_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return STEERING_MOTOR_RPT_1_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_STEERING_MOTOR_RPT_1_pacmod6(STEERING_MOTOR_RPT_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_1_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MOTOR_CURRENT_ro = PACMOD6_MOTOR_CURRENT_ro_toS(_m->MOTOR_CURRENT_phys);
  _m->SHAFT_POSITION_ro = PACMOD6_SHAFT_POSITION_ro_toS(_m->SHAFT_POSITION_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_STEERING_MOTOR_RPT_1_pacmod6(STEERING_MOTOR_RPT_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_1_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->MOTOR_CURRENT_ro = PACMOD6_MOTOR_CURRENT_ro_toS(_m->MOTOR_CURRENT_phys);
  _m->SHAFT_POSITION_ro = PACMOD6_SHAFT_POSITION_ro_toS(_m->SHAFT_POSITION_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_STEERING_MOTOR_RPT_2_pacmod6(STEERING_MOTOR_RPT_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ENCODER_TEMPERATURE = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
  _m->MOTOR_TEMPERATURE = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
  _m->ANGULAR_SPEED_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->ANGULAR_SPEED_phys = (sigfloat_t)(PACMOD6_ANGULAR_SPEED_ro_fromS(_m->ANGULAR_SPEED_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_MOTOR_RPT_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_MOTOR_RPT_2_pacmod6(&_m->mon1, STEERING_MOTOR_RPT_2_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return STEERING_MOTOR_RPT_2_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_STEERING_MOTOR_RPT_2_pacmod6(STEERING_MOTOR_RPT_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->ANGULAR_SPEED_ro = PACMOD6_ANGULAR_SPEED_ro_toS(_m->ANGULAR_SPEED_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_STEERING_MOTOR_RPT_2_pacmod6(STEERING_MOTOR_RPT_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->ANGULAR_SPEED_ro = PACMOD6_ANGULAR_SPEED_ro_toS(_m->ANGULAR_SPEED_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_STEERING_MOTOR_RPT_3_pacmod6(STEERING_MOTOR_RPT_3_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->TORQUE_OUTPUT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 24) | ((_d[1] & (0xFFU)) << 16) | ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_phys = (sigfloat_t)(PACMOD6_TORQUE_OUTPUT_ro_fromS(_m->TORQUE_OUTPUT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->TORQUE_INPUT_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 24) | ((_d[5] & (0xFFU)) << 16) | ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 32);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->TORQUE_INPUT_phys = (sigfloat_t)(PACMOD6_TORQUE_INPUT_ro_fromS(_m->TORQUE_INPUT_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < STEERING_MOTOR_RPT_3_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_STEERING_MOTOR_RPT_3_pacmod6(&_m->mon1, STEERING_MOTOR_RPT_3_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return STEERING_MOTOR_RPT_3_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_STEERING_MOTOR_RPT_3_pacmod6(STEERING_MOTOR_RPT_3_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_3_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_ro = PACMOD6_TORQUE_OUTPUT_ro_toS(_m->TORQUE_OUTPUT_phys);
  _m->TORQUE_INPUT_ro = PACMOD6_TORQUE_INPUT_ro_toS(_m->TORQUE_INPUT_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_STEERING_MOTOR_RPT_3_pacmod6(STEERING_MOTOR_RPT_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < STEERING_MOTOR_RPT_3_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->TORQUE_OUTPUT_ro = PACMOD6_TORQUE_OUTPUT_ro_toS(_m->TORQUE_OUTPUT_phys);
  _m->TORQUE_INPUT_ro = PACMOD6_TORQUE_INPUT_ro_toS(_m->TORQUE_INPUT_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_WHEEL_SPEED_RPT_pacmod6(WHEEL_SPEED_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->WHEEL_SPD_FRONT_LEFT_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->WHEEL_SPD_FRONT_LEFT_phys = (sigfloat_t)(PACMOD6_WHEEL_SPD_FRONT_LEFT_ro_fromS(_m->WHEEL_SPD_FRONT_LEFT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->WHEEL_SPD_FRONT_RIGHT_ro = __ext_sig__(( ((_d[2] & (0xFFU)) << 8) | (_d[3] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->WHEEL_SPD_FRONT_RIGHT_phys = (sigfloat_t)(PACMOD6_WHEEL_SPD_FRONT_RIGHT_ro_fromS(_m->WHEEL_SPD_FRONT_RIGHT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->WHEEL_SPD_REAR_LEFT_ro = __ext_sig__(( ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->WHEEL_SPD_REAR_LEFT_phys = (sigfloat_t)(PACMOD6_WHEEL_SPD_REAR_LEFT_ro_fromS(_m->WHEEL_SPD_REAR_LEFT_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->WHEEL_SPD_REAR_RIGHT_ro = __ext_sig__(( ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->WHEEL_SPD_REAR_RIGHT_phys = (sigfloat_t)(PACMOD6_WHEEL_SPD_REAR_RIGHT_ro_fromS(_m->WHEEL_SPD_REAR_RIGHT_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WHEEL_SPEED_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WHEEL_SPEED_RPT_pacmod6(&_m->mon1, WHEEL_SPEED_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return WHEEL_SPEED_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_WHEEL_SPEED_RPT_pacmod6(WHEEL_SPEED_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < WHEEL_SPEED_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->WHEEL_SPD_FRONT_LEFT_ro = PACMOD6_WHEEL_SPD_FRONT_LEFT_ro_toS(_m->WHEEL_SPD_FRONT_LEFT_phys);
  _m->WHEEL_SPD_FRONT_RIGHT_ro = PACMOD6_WHEEL_SPD_FRONT_RIGHT_ro_toS(_m->WHEEL_SPD_FRONT_RIGHT_phys);
  _m->WHEEL_SPD_REAR_LEFT_ro = PACMOD6_WHEEL_SPD_REAR_LEFT_ro_toS(_m->WHEEL_SPD_REAR_LEFT_phys);
  _m->WHEEL_SPD_REAR_RIGHT_ro = PACMOD6_WHEEL_SPD_REAR_RIGHT_ro_toS(_m->WHEEL_SPD_REAR_RIGHT_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->WHEEL_SPD_FRONT_LEFT_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->WHEEL_SPD_FRONT_LEFT_ro & (0xFFU));
  cframe->Data[2] |= ((_m->WHEEL_SPD_FRONT_RIGHT_ro >> 8) & (0xFFU));
  cframe->Data[3] |= (_m->WHEEL_SPD_FRONT_RIGHT_ro & (0xFFU));
  cframe->Data[4] |= ((_m->WHEEL_SPD_REAR_LEFT_ro >> 8) & (0xFFU));
  cframe->Data[5] |= (_m->WHEEL_SPD_REAR_LEFT_ro & (0xFFU));
  cframe->Data[6] |= ((_m->WHEEL_SPD_REAR_RIGHT_ro >> 8) & (0xFFU));
  cframe->Data[7] |= (_m->WHEEL_SPD_REAR_RIGHT_ro & (0xFFU));

  cframe->MsgId = WHEEL_SPEED_RPT_CANID;
  cframe->DLC = WHEEL_SPEED_RPT_DLC;
  cframe->IDE = WHEEL_SPEED_RPT_IDE;
  return WHEEL_SPEED_RPT_CANID;
}

#else

uint32_t Pack_WHEEL_SPEED_RPT_pacmod6(WHEEL_SPEED_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WHEEL_SPEED_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->WHEEL_SPD_FRONT_LEFT_ro = PACMOD6_WHEEL_SPD_FRONT_LEFT_ro_toS(_m->WHEEL_SPD_FRONT_LEFT_phys);
  _m->WHEEL_SPD_FRONT_RIGHT_ro = PACMOD6_WHEEL_SPD_FRONT_RIGHT_ro_toS(_m->WHEEL_SPD_FRONT_RIGHT_phys);
  _m->WHEEL_SPD_REAR_LEFT_ro = PACMOD6_WHEEL_SPD_REAR_LEFT_ro_toS(_m->WHEEL_SPD_REAR_LEFT_phys);
  _m->WHEEL_SPD_REAR_RIGHT_ro = PACMOD6_WHEEL_SPD_REAR_RIGHT_ro_toS(_m->WHEEL_SPD_REAR_RIGHT_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= ((_m->WHEEL_SPD_FRONT_LEFT_ro >> 8) & (0xFFU));
  _d[1] |= (_m->WHEEL_SPD_FRONT_LEFT_ro & (0xFFU));
  _d[2] |= ((_m->WHEEL_SPD_FRONT_RIGHT_ro >> 8) & (0xFFU));
  _d[3] |= (_m->WHEEL_SPD_FRONT_RIGHT_ro & (0xFFU));
  _d[4] |= ((_m->WHEEL_SPD_REAR_LEFT_ro >> 8) & (0xFFU));
  _d[5] |= (_m->WHEEL_SPD_REAR_LEFT_ro & (0xFFU));
  _d[6] |= ((_m->WHEEL_SPD_REAR_RIGHT_ro >> 8) & (0xFFU));
  _d[7] |= (_m->WHEEL_SPD_REAR_RIGHT_ro & (0xFFU));

  *_len = WHEEL_SPEED_RPT_DLC;
  *_ide = WHEEL_SPEED_RPT_IDE;
  return WHEEL_SPEED_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_00_pacmod6(SOFTWARE_VERSION_RPT_00_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_00_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_00_pacmod6(&_m->mon1, SOFTWARE_VERSION_RPT_00_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_00_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_00_pacmod6(SOFTWARE_VERSION_RPT_00_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_SOFTWARE_VERSION_RPT_00_pacmod6(SOFTWARE_VERSION_RPT_00_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_01_pacmod6(SOFTWARE_VERSION_RPT_01_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_01_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_01_pacmod6(&_m->mon1, SOFTWARE_VERSION_RPT_01_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_01_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_01_pacmod6(SOFTWARE_VERSION_RPT_01_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_SOFTWARE_VERSION_RPT_01_pacmod6(SOFTWARE_VERSION_RPT_01_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_02_pacmod6(SOFTWARE_VERSION_RPT_02_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_02_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_02_pacmod6(&_m->mon1, SOFTWARE_VERSION_RPT_02_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_02_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_02_pacmod6(SOFTWARE_VERSION_RPT_02_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_SOFTWARE_VERSION_RPT_02_pacmod6(SOFTWARE_VERSION_RPT_02_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_SOFTWARE_VERSION_RPT_03_pacmod6(SOFTWARE_VERSION_RPT_03_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->MAJOR = (_d[0] & (0xFFU));
  _m->MINOR = (_d[1] & (0xFFU));
  _m->PATCH = (_d[2] & (0xFFU));
  _m->BUILD0 = (_d[3] & (0xFFU));
  _m->BUILD1 = (_d[4] & (0xFFU));
  _m->BUILD2 = (_d[5] & (0xFFU));
  _m->BUILD3 = (_d[6] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < SOFTWARE_VERSION_RPT_03_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_SOFTWARE_VERSION_RPT_03_pacmod6(&_m->mon1, SOFTWARE_VERSION_RPT_03_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return SOFTWARE_VERSION_RPT_03_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_SOFTWARE_VERSION_RPT_03_pacmod6(SOFTWARE_VERSION_RPT_03_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_SOFTWARE_VERSION_RPT_03_pacmod6(SOFTWARE_VERSION_RPT_03_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_YAW_RATE_RPT_pacmod6(YAW_RATE_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->YAW_RATE_ro = __ext_sig__(( ((_d[0] & (0xFFU)) << 8) | (_d[1] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->YAW_RATE_phys = (sigfloat_t)(PACMOD6_YAW_RATE_ro_fromS(_m->YAW_RATE_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < YAW_RATE_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_YAW_RATE_RPT_pacmod6(&_m->mon1, YAW_RATE_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return YAW_RATE_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_YAW_RATE_RPT_pacmod6(YAW_RATE_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < YAW_RATE_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->YAW_RATE_ro = PACMOD6_YAW_RATE_ro_toS(_m->YAW_RATE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= ((_m->YAW_RATE_ro >> 8) & (0xFFU));
  cframe->Data[1] |= (_m->YAW_RATE_ro & (0xFFU));

  cframe->MsgId = YAW_RATE_RPT_CANID;
  cframe->DLC = YAW_RATE_RPT_DLC;
  cframe->IDE = YAW_RATE_RPT_IDE;
  return YAW_RATE_RPT_CANID;
}

#else

uint32_t Pack_YAW_RATE_RPT_pacmod6(YAW_RATE_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < YAW_RATE_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->YAW_RATE_ro = PACMOD6_YAW_RATE_ro_toS(_m->YAW_RATE_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= ((_m->YAW_RATE_ro >> 8) & (0xFFU));
  _d[1] |= (_m->YAW_RATE_ro & (0xFFU));

  *_len = YAW_RATE_RPT_DLC;
  *_ide = YAW_RATE_RPT_IDE;
  return YAW_RATE_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_LAT_LON_HEADING_RPT_pacmod6(LAT_LON_HEADING_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->LATITUDE_DEGREES = __ext_sig__(( (_d[0] & (0xFFU)) ), 8);
  _m->LATITUDE_MINUTES = __ext_sig__(( (_d[1] & (0xFFU)) ), 8);
  _m->LATITUDE_SECONDS = __ext_sig__(( (_d[2] & (0xFFU)) ), 8);
  _m->LONGITUDE_DEGREES = __ext_sig__(( (_d[3] & (0xFFU)) ), 8);
  _m->LONGITUDE_MINUTES = __ext_sig__(( (_d[4] & (0xFFU)) ), 8);
  _m->LONGITUDE_SECONDS = __ext_sig__(( (_d[5] & (0xFFU)) ), 8);
  _m->HEADING_ro = __ext_sig__(( ((_d[6] & (0xFFU)) << 8) | (_d[7] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->HEADING_phys = (sigfloat_t)(PACMOD6_HEADING_ro_fromS(_m->HEADING_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < LAT_LON_HEADING_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_LAT_LON_HEADING_RPT_pacmod6(&_m->mon1, LAT_LON_HEADING_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return LAT_LON_HEADING_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_LAT_LON_HEADING_RPT_pacmod6(LAT_LON_HEADING_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < LAT_LON_HEADING_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->HEADING_ro = PACMOD6_HEADING_ro_toS(_m->HEADING_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_LAT_LON_HEADING_RPT_pacmod6(LAT_LON_HEADING_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < LAT_LON_HEADING_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->HEADING_ro = PACMOD6_HEADING_ro_toS(_m->HEADING_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_DATE_TIME_RPT_pacmod6(DATE_TIME_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DATE_YEAR_ro = (_d[0] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->DATE_YEAR_phys = PACMOD6_DATE_YEAR_ro_fromS(_m->DATE_YEAR_ro);
#endif // PACMOD6_USE_SIGFLOAT

  _m->DATE_MONTH_ro = (_d[1] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->DATE_MONTH_phys = PACMOD6_DATE_MONTH_ro_fromS(_m->DATE_MONTH_ro);
#endif // PACMOD6_USE_SIGFLOAT

  _m->DATE_DAY_ro = (_d[2] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->DATE_DAY_phys = PACMOD6_DATE_DAY_ro_fromS(_m->DATE_DAY_ro);
#endif // PACMOD6_USE_SIGFLOAT

  _m->TIME_HOUR = (_d[3] & (0xFFU));
  _m->TIME_MINUTE = (_d[4] & (0xFFU));
  _m->TIME_SECOND = (_d[5] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DATE_TIME_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DATE_TIME_RPT_pacmod6(&_m->mon1, DATE_TIME_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return DATE_TIME_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_DATE_TIME_RPT_pacmod6(DATE_TIME_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DATE_TIME_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->DATE_YEAR_ro = PACMOD6_DATE_YEAR_ro_toS(_m->DATE_YEAR_phys);
  _m->DATE_MONTH_ro = PACMOD6_DATE_MONTH_ro_toS(_m->DATE_MONTH_phys);
  _m->DATE_DAY_ro = PACMOD6_DATE_DAY_ro_toS(_m->DATE_DAY_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_DATE_TIME_RPT_pacmod6(DATE_TIME_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DATE_TIME_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->DATE_YEAR_ro = PACMOD6_DATE_YEAR_ro_toS(_m->DATE_YEAR_phys);
  _m->DATE_MONTH_ro = PACMOD6_DATE_MONTH_ro_toS(_m->DATE_MONTH_phys);
  _m->DATE_DAY_ro = PACMOD6_DATE_DAY_ro_toS(_m->DATE_DAY_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_DETECTED_OBJECT_RPT_pacmod6(DETECTED_OBJECT_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->FRONT_OBJECT_DISTANCE_LOW_RES_ro = ((_d[0] & (0xFFU)) << 16) | ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->FRONT_OBJECT_DISTANCE_LOW_RES_phys = (sigfloat_t)(PACMOD6_FRONT_OBJECT_DISTANCE_LOW_RES_ro_fromS(_m->FRONT_OBJECT_DISTANCE_LOW_RES_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro = ((_d[3] & (0xFFU)) << 16) | ((_d[4] & (0xFFU)) << 8) | (_d[5] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->FRONT_OBJECT_DISTANCE_HIGH_RES_phys = (sigfloat_t)(PACMOD6_FRONT_OBJECT_DISTANCE_HIGH_RES_ro_fromS(_m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DETECTED_OBJECT_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DETECTED_OBJECT_RPT_pacmod6(&_m->mon1, DETECTED_OBJECT_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return DETECTED_OBJECT_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_DETECTED_OBJECT_RPT_pacmod6(DETECTED_OBJECT_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DETECTED_OBJECT_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->FRONT_OBJECT_DISTANCE_LOW_RES_ro = PACMOD6_FRONT_OBJECT_DISTANCE_LOW_RES_ro_toS(_m->FRONT_OBJECT_DISTANCE_LOW_RES_phys);
  _m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro = PACMOD6_FRONT_OBJECT_DISTANCE_HIGH_RES_ro_toS(_m->FRONT_OBJECT_DISTANCE_HIGH_RES_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_DETECTED_OBJECT_RPT_pacmod6(DETECTED_OBJECT_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DETECTED_OBJECT_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->FRONT_OBJECT_DISTANCE_LOW_RES_ro = PACMOD6_FRONT_OBJECT_DISTANCE_LOW_RES_ro_toS(_m->FRONT_OBJECT_DISTANCE_LOW_RES_phys);
  _m->FRONT_OBJECT_DISTANCE_HIGH_RES_ro = PACMOD6_FRONT_OBJECT_DISTANCE_HIGH_RES_ro_toS(_m->FRONT_OBJECT_DISTANCE_HIGH_RES_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_VEH_SPECIFIC_RPT_1_pacmod6(VEH_SPECIFIC_RPT_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SHIFT_POS_1 = (_d[0] & (0xFFU));
  _m->SHIFT_POS_2 = (_d[1] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_SPECIFIC_RPT_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_SPECIFIC_RPT_1_pacmod6(&_m->mon1, VEH_SPECIFIC_RPT_1_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return VEH_SPECIFIC_RPT_1_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_VEH_SPECIFIC_RPT_1_pacmod6(VEH_SPECIFIC_RPT_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < VEH_SPECIFIC_RPT_1_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SHIFT_POS_1 & (0xFFU));
  cframe->Data[1] |= (_m->SHIFT_POS_2 & (0xFFU));

  cframe->MsgId = VEH_SPECIFIC_RPT_1_CANID;
  cframe->DLC = VEH_SPECIFIC_RPT_1_DLC;
  cframe->IDE = VEH_SPECIFIC_RPT_1_IDE;
  return VEH_SPECIFIC_RPT_1_CANID;
}

#else

uint32_t Pack_VEH_SPECIFIC_RPT_1_pacmod6(VEH_SPECIFIC_RPT_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < VEH_SPECIFIC_RPT_1_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SHIFT_POS_1 & (0xFFU));
  _d[1] |= (_m->SHIFT_POS_2 & (0xFFU));

  *_len = VEH_SPECIFIC_RPT_1_DLC;
  *_ide = VEH_SPECIFIC_RPT_1_IDE;
  return VEH_SPECIFIC_RPT_1_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_VEH_DYNAMICS_RPT_pacmod6(VEH_DYNAMICS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->VEH_G_FORCES_ro = (_d[0] & (0xFFU));
#ifdef PACMOD6_USE_SIGFLOAT
  _m->VEH_G_FORCES_phys = (sigfloat_t)(PACMOD6_VEH_G_FORCES_ro_fromS(_m->VEH_G_FORCES_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VEH_DYNAMICS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VEH_DYNAMICS_RPT_pacmod6(&_m->mon1, VEH_DYNAMICS_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return VEH_DYNAMICS_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_VEH_DYNAMICS_RPT_pacmod6(VEH_DYNAMICS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < VEH_DYNAMICS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->VEH_G_FORCES_ro = PACMOD6_VEH_G_FORCES_ro_toS(_m->VEH_G_FORCES_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= (_m->VEH_G_FORCES_ro & (0xFFU));

  cframe->MsgId = VEH_DYNAMICS_RPT_CANID;
  cframe->DLC = VEH_DYNAMICS_RPT_DLC;
  cframe->IDE = VEH_DYNAMICS_RPT_IDE;
  return VEH_DYNAMICS_RPT_CANID;
}

#else

uint32_t Pack_VEH_DYNAMICS_RPT_pacmod6(VEH_DYNAMICS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < VEH_DYNAMICS_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->VEH_G_FORCES_ro = PACMOD6_VEH_G_FORCES_ro_toS(_m->VEH_G_FORCES_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->VEH_G_FORCES_ro & (0xFFU));

  *_len = VEH_DYNAMICS_RPT_DLC;
  *_ide = VEH_DYNAMICS_RPT_IDE;
  return VEH_DYNAMICS_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_VIN_RPT_pacmod6(VIN_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->VEH_MFG_CODE = ((_d[0] & (0xFFU)) << 16) | ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->VEH_MY_CODE = (_d[3] & (0xFFU));
  _m->VEH_SERIAL = ((_d[4] & (0xFFU)) << 16) | ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < VIN_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_VIN_RPT_pacmod6(&_m->mon1, VIN_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return VIN_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_VIN_RPT_pacmod6(VIN_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
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

uint32_t Pack_VIN_RPT_pacmod6(VIN_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_OCCUPANCY_RPT_pacmod6(OCCUPANCY_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DRIVER_SEAT_OCCUPIED = (_d[0] & (0x01U));
  _m->PASS_SEAT_OCCUPIED = ((_d[0] >> 1) & (0x01U));
  _m->REAR_SEAT_OCCUPIED = ((_d[0] >> 2) & (0x01U));
  _m->DRIVER_SEATBELT_BUCKLED = ((_d[0] >> 3) & (0x01U));
  _m->PASS_SEATBELT_BUCKLED = ((_d[0] >> 4) & (0x01U));
  _m->REAR_SEATBELT_BUCKLED = ((_d[0] >> 5) & (0x01U));
  _m->DRIVER_SEAT_OCCUPIED_IS_VALID = (_d[1] & (0x01U));
  _m->PASS_SEAT_OCCUPIED_IS_VALID = ((_d[1] >> 1) & (0x01U));
  _m->REAR_SEAT_OCCUPIED_IS_VALID = ((_d[1] >> 2) & (0x01U));
  _m->DRIVER_SEATBELT_BUCKLED_IS_VALID = ((_d[1] >> 3) & (0x01U));
  _m->PASS_SEATBELT_BUCKLED_IS_VALID = ((_d[1] >> 4) & (0x01U));
  _m->REAR_SEATBELT_BUCKLED_IS_VALID = ((_d[1] >> 5) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < OCCUPANCY_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_OCCUPANCY_RPT_pacmod6(&_m->mon1, OCCUPANCY_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return OCCUPANCY_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_OCCUPANCY_RPT_pacmod6(OCCUPANCY_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < OCCUPANCY_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->DRIVER_SEAT_OCCUPIED & (0x01U)) | ((_m->PASS_SEAT_OCCUPIED & (0x01U)) << 1) | ((_m->REAR_SEAT_OCCUPIED & (0x01U)) << 2) | ((_m->DRIVER_SEATBELT_BUCKLED & (0x01U)) << 3) | ((_m->PASS_SEATBELT_BUCKLED & (0x01U)) << 4) | ((_m->REAR_SEATBELT_BUCKLED & (0x01U)) << 5);
  cframe->Data[1] |= (_m->DRIVER_SEAT_OCCUPIED_IS_VALID & (0x01U)) | ((_m->PASS_SEAT_OCCUPIED_IS_VALID & (0x01U)) << 1) | ((_m->REAR_SEAT_OCCUPIED_IS_VALID & (0x01U)) << 2) | ((_m->DRIVER_SEATBELT_BUCKLED_IS_VALID & (0x01U)) << 3) | ((_m->PASS_SEATBELT_BUCKLED_IS_VALID & (0x01U)) << 4) | ((_m->REAR_SEATBELT_BUCKLED_IS_VALID & (0x01U)) << 5);

  cframe->MsgId = OCCUPANCY_RPT_CANID;
  cframe->DLC = OCCUPANCY_RPT_DLC;
  cframe->IDE = OCCUPANCY_RPT_IDE;
  return OCCUPANCY_RPT_CANID;
}

#else

uint32_t Pack_OCCUPANCY_RPT_pacmod6(OCCUPANCY_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < OCCUPANCY_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->DRIVER_SEAT_OCCUPIED & (0x01U)) | ((_m->PASS_SEAT_OCCUPIED & (0x01U)) << 1) | ((_m->REAR_SEAT_OCCUPIED & (0x01U)) << 2) | ((_m->DRIVER_SEATBELT_BUCKLED & (0x01U)) << 3) | ((_m->PASS_SEATBELT_BUCKLED & (0x01U)) << 4) | ((_m->REAR_SEATBELT_BUCKLED & (0x01U)) << 5);
  _d[1] |= (_m->DRIVER_SEAT_OCCUPIED_IS_VALID & (0x01U)) | ((_m->PASS_SEAT_OCCUPIED_IS_VALID & (0x01U)) << 1) | ((_m->REAR_SEAT_OCCUPIED_IS_VALID & (0x01U)) << 2) | ((_m->DRIVER_SEATBELT_BUCKLED_IS_VALID & (0x01U)) << 3) | ((_m->PASS_SEATBELT_BUCKLED_IS_VALID & (0x01U)) << 4) | ((_m->REAR_SEATBELT_BUCKLED_IS_VALID & (0x01U)) << 5);

  *_len = OCCUPANCY_RPT_DLC;
  *_ide = OCCUPANCY_RPT_IDE;
  return OCCUPANCY_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_INTERIOR_LIGHTS_RPT_pacmod6(INTERIOR_LIGHTS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->FRONT_DOME_LIGHTS_ON = (_d[0] & (0x01U));
  _m->REAR_DOME_LIGHTS_ON = ((_d[0] >> 1) & (0x01U));
  _m->MOOD_LIGHTS_ON = ((_d[0] >> 2) & (0x01U));
  _m->DIM_LEVEL = (_d[1] & (0xFFU));
  _m->FRONT_DOME_LIGHTS_ON_IS_VALID = (_d[2] & (0x01U));
  _m->REAR_DOME_LIGHTS_ON_IS_VALID = ((_d[2] >> 1) & (0x01U));
  _m->MOOD_LIGHTS_ON_IS_VALID = ((_d[2] >> 2) & (0x01U));
  _m->DIM_LEVEL_IS_VALID = ((_d[2] >> 3) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < INTERIOR_LIGHTS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_INTERIOR_LIGHTS_RPT_pacmod6(&_m->mon1, INTERIOR_LIGHTS_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return INTERIOR_LIGHTS_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_INTERIOR_LIGHTS_RPT_pacmod6(INTERIOR_LIGHTS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < INTERIOR_LIGHTS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->FRONT_DOME_LIGHTS_ON & (0x01U)) | ((_m->REAR_DOME_LIGHTS_ON & (0x01U)) << 1) | ((_m->MOOD_LIGHTS_ON & (0x01U)) << 2);
  cframe->Data[1] |= (_m->DIM_LEVEL & (0xFFU));
  cframe->Data[2] |= (_m->FRONT_DOME_LIGHTS_ON_IS_VALID & (0x01U)) | ((_m->REAR_DOME_LIGHTS_ON_IS_VALID & (0x01U)) << 1) | ((_m->MOOD_LIGHTS_ON_IS_VALID & (0x01U)) << 2) | ((_m->DIM_LEVEL_IS_VALID & (0x01U)) << 3);

  cframe->MsgId = INTERIOR_LIGHTS_RPT_CANID;
  cframe->DLC = INTERIOR_LIGHTS_RPT_DLC;
  cframe->IDE = INTERIOR_LIGHTS_RPT_IDE;
  return INTERIOR_LIGHTS_RPT_CANID;
}

#else

uint32_t Pack_INTERIOR_LIGHTS_RPT_pacmod6(INTERIOR_LIGHTS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < INTERIOR_LIGHTS_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->FRONT_DOME_LIGHTS_ON & (0x01U)) | ((_m->REAR_DOME_LIGHTS_ON & (0x01U)) << 1) | ((_m->MOOD_LIGHTS_ON & (0x01U)) << 2);
  _d[1] |= (_m->DIM_LEVEL & (0xFFU));
  _d[2] |= (_m->FRONT_DOME_LIGHTS_ON_IS_VALID & (0x01U)) | ((_m->REAR_DOME_LIGHTS_ON_IS_VALID & (0x01U)) << 1) | ((_m->MOOD_LIGHTS_ON_IS_VALID & (0x01U)) << 2) | ((_m->DIM_LEVEL_IS_VALID & (0x01U)) << 3);

  *_len = INTERIOR_LIGHTS_RPT_DLC;
  *_ide = INTERIOR_LIGHTS_RPT_IDE;
  return INTERIOR_LIGHTS_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_DOOR_RPT_pacmod6(DOOR_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DRIVER_DOOR_OPEN = (_d[0] & (0x01U));
  _m->PASS_DOOR_OPEN = ((_d[0] >> 1) & (0x01U));
  _m->REAR_DRIVER_DOOR_OPEN = ((_d[0] >> 2) & (0x01U));
  _m->REAR_PASS_DOOR_OPEN = ((_d[0] >> 3) & (0x01U));
  _m->HOOD_OPEN = ((_d[0] >> 4) & (0x01U));
  _m->TRUNK_OPEN = ((_d[0] >> 5) & (0x01U));
  _m->FUEL_DOOR_OPEN = ((_d[0] >> 6) & (0x01U));
  _m->DRIVER_DOOR_OPEN_IS_VALID = (_d[1] & (0x01U));
  _m->PASS_DOOR_OPEN_IS_VALID = ((_d[1] >> 1) & (0x01U));
  _m->REAR_DRIVER_DOOR_OPEN_IS_VALID = ((_d[1] >> 2) & (0x01U));
  _m->REAR_PASS_DOOR_OPEN_IS_VALID = ((_d[1] >> 3) & (0x01U));
  _m->HOOD_OPEN_IS_VALID = ((_d[1] >> 4) & (0x01U));
  _m->TRUNK_OPEN_IS_VALID = ((_d[1] >> 5) & (0x01U));
  _m->FUEL_DOOR_OPEN_IS_VALID = ((_d[1] >> 6) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < DOOR_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_DOOR_RPT_pacmod6(&_m->mon1, DOOR_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return DOOR_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_DOOR_RPT_pacmod6(DOOR_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < DOOR_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->DRIVER_DOOR_OPEN & (0x01U)) | ((_m->PASS_DOOR_OPEN & (0x01U)) << 1) | ((_m->REAR_DRIVER_DOOR_OPEN & (0x01U)) << 2) | ((_m->REAR_PASS_DOOR_OPEN & (0x01U)) << 3) | ((_m->HOOD_OPEN & (0x01U)) << 4) | ((_m->TRUNK_OPEN & (0x01U)) << 5) | ((_m->FUEL_DOOR_OPEN & (0x01U)) << 6);
  cframe->Data[1] |= (_m->DRIVER_DOOR_OPEN_IS_VALID & (0x01U)) | ((_m->PASS_DOOR_OPEN_IS_VALID & (0x01U)) << 1) | ((_m->REAR_DRIVER_DOOR_OPEN_IS_VALID & (0x01U)) << 2) | ((_m->REAR_PASS_DOOR_OPEN_IS_VALID & (0x01U)) << 3) | ((_m->HOOD_OPEN_IS_VALID & (0x01U)) << 4) | ((_m->TRUNK_OPEN_IS_VALID & (0x01U)) << 5) | ((_m->FUEL_DOOR_OPEN_IS_VALID & (0x01U)) << 6);

  cframe->MsgId = DOOR_RPT_CANID;
  cframe->DLC = DOOR_RPT_DLC;
  cframe->IDE = DOOR_RPT_IDE;
  return DOOR_RPT_CANID;
}

#else

uint32_t Pack_DOOR_RPT_pacmod6(DOOR_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < DOOR_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->DRIVER_DOOR_OPEN & (0x01U)) | ((_m->PASS_DOOR_OPEN & (0x01U)) << 1) | ((_m->REAR_DRIVER_DOOR_OPEN & (0x01U)) << 2) | ((_m->REAR_PASS_DOOR_OPEN & (0x01U)) << 3) | ((_m->HOOD_OPEN & (0x01U)) << 4) | ((_m->TRUNK_OPEN & (0x01U)) << 5) | ((_m->FUEL_DOOR_OPEN & (0x01U)) << 6);
  _d[1] |= (_m->DRIVER_DOOR_OPEN_IS_VALID & (0x01U)) | ((_m->PASS_DOOR_OPEN_IS_VALID & (0x01U)) << 1) | ((_m->REAR_DRIVER_DOOR_OPEN_IS_VALID & (0x01U)) << 2) | ((_m->REAR_PASS_DOOR_OPEN_IS_VALID & (0x01U)) << 3) | ((_m->HOOD_OPEN_IS_VALID & (0x01U)) << 4) | ((_m->TRUNK_OPEN_IS_VALID & (0x01U)) << 5) | ((_m->FUEL_DOOR_OPEN_IS_VALID & (0x01U)) << 6);

  *_len = DOOR_RPT_DLC;
  *_ide = DOOR_RPT_IDE;
  return DOOR_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_REAR_LIGHTS_RPT_pacmod6(REAR_LIGHTS_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BRAKE_LIGHTS_ON = (_d[0] & (0x01U));
  _m->REVERSE_LIGHTS_ON = ((_d[0] >> 1) & (0x01U));
  _m->BRAKE_LIGHTS_ON_IS_VALID = (_d[1] & (0x01U));
  _m->REVERSE_LIGHTS_ON_IS_VALID = ((_d[1] >> 1) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < REAR_LIGHTS_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_REAR_LIGHTS_RPT_pacmod6(&_m->mon1, REAR_LIGHTS_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return REAR_LIGHTS_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_REAR_LIGHTS_RPT_pacmod6(REAR_LIGHTS_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < REAR_LIGHTS_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BRAKE_LIGHTS_ON & (0x01U)) | ((_m->REVERSE_LIGHTS_ON & (0x01U)) << 1);
  cframe->Data[1] |= (_m->BRAKE_LIGHTS_ON_IS_VALID & (0x01U)) | ((_m->REVERSE_LIGHTS_ON_IS_VALID & (0x01U)) << 1);

  cframe->MsgId = REAR_LIGHTS_RPT_CANID;
  cframe->DLC = REAR_LIGHTS_RPT_DLC;
  cframe->IDE = REAR_LIGHTS_RPT_IDE;
  return REAR_LIGHTS_RPT_CANID;
}

#else

uint32_t Pack_REAR_LIGHTS_RPT_pacmod6(REAR_LIGHTS_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < REAR_LIGHTS_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BRAKE_LIGHTS_ON & (0x01U)) | ((_m->REVERSE_LIGHTS_ON & (0x01U)) << 1);
  _d[1] |= (_m->BRAKE_LIGHTS_ON_IS_VALID & (0x01U)) | ((_m->REVERSE_LIGHTS_ON_IS_VALID & (0x01U)) << 1);

  *_len = REAR_LIGHTS_RPT_DLC;
  *_ide = REAR_LIGHTS_RPT_IDE;
  return REAR_LIGHTS_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_LINEAR_ACCEL_RPT_pacmod6(LINEAR_ACCEL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->LATERAL_NEW_DATA_RX = (_d[0] & (0x01U));
  _m->LONGITUDNAL_NEW_DATA_RX = ((_d[0] >> 1) & (0x01U));
  _m->VERTICAL_NEW_DATA_RX = ((_d[0] >> 2) & (0x01U));
  _m->LATERAL_VALID = ((_d[0] >> 3) & (0x01U));
  _m->LONGITUDNAL_VALID = ((_d[0] >> 4) & (0x01U));
  _m->VERTICAL_VALID = ((_d[0] >> 5) & (0x01U));
  _m->LATERAL_ACCEL_ro = __ext_sig__(( ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->LATERAL_ACCEL_phys = (sigfloat_t)(PACMOD6_LATERAL_ACCEL_ro_fromS(_m->LATERAL_ACCEL_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->LONGITUDNAL_ACCEL_ro = __ext_sig__(( ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->LONGITUDNAL_ACCEL_phys = (sigfloat_t)(PACMOD6_LONGITUDNAL_ACCEL_ro_fromS(_m->LONGITUDNAL_ACCEL_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->VERTICAL_ACCEL_ro = __ext_sig__(( ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->VERTICAL_ACCEL_phys = (sigfloat_t)(PACMOD6_VERTICAL_ACCEL_ro_fromS(_m->VERTICAL_ACCEL_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < LINEAR_ACCEL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_LINEAR_ACCEL_RPT_pacmod6(&_m->mon1, LINEAR_ACCEL_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return LINEAR_ACCEL_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_LINEAR_ACCEL_RPT_pacmod6(LINEAR_ACCEL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < LINEAR_ACCEL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->LATERAL_ACCEL_ro = PACMOD6_LATERAL_ACCEL_ro_toS(_m->LATERAL_ACCEL_phys);
  _m->LONGITUDNAL_ACCEL_ro = PACMOD6_LONGITUDNAL_ACCEL_ro_toS(_m->LONGITUDNAL_ACCEL_phys);
  _m->VERTICAL_ACCEL_ro = PACMOD6_VERTICAL_ACCEL_ro_toS(_m->VERTICAL_ACCEL_phys);
#endif // PACMOD6_USE_SIGFLOAT

  cframe->Data[0] |= (_m->LATERAL_NEW_DATA_RX & (0x01U)) | ((_m->LONGITUDNAL_NEW_DATA_RX & (0x01U)) << 1) | ((_m->VERTICAL_NEW_DATA_RX & (0x01U)) << 2) | ((_m->LATERAL_VALID & (0x01U)) << 3) | ((_m->LONGITUDNAL_VALID & (0x01U)) << 4) | ((_m->VERTICAL_VALID & (0x01U)) << 5);
  cframe->Data[1] |= ((_m->LATERAL_ACCEL_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->LATERAL_ACCEL_ro & (0xFFU));
  cframe->Data[3] |= ((_m->LONGITUDNAL_ACCEL_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->LONGITUDNAL_ACCEL_ro & (0xFFU));
  cframe->Data[5] |= ((_m->VERTICAL_ACCEL_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->VERTICAL_ACCEL_ro & (0xFFU));

  cframe->MsgId = LINEAR_ACCEL_RPT_CANID;
  cframe->DLC = LINEAR_ACCEL_RPT_DLC;
  cframe->IDE = LINEAR_ACCEL_RPT_IDE;
  return LINEAR_ACCEL_RPT_CANID;
}

#else

uint32_t Pack_LINEAR_ACCEL_RPT_pacmod6(LINEAR_ACCEL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < LINEAR_ACCEL_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->LATERAL_ACCEL_ro = PACMOD6_LATERAL_ACCEL_ro_toS(_m->LATERAL_ACCEL_phys);
  _m->LONGITUDNAL_ACCEL_ro = PACMOD6_LONGITUDNAL_ACCEL_ro_toS(_m->LONGITUDNAL_ACCEL_phys);
  _m->VERTICAL_ACCEL_ro = PACMOD6_VERTICAL_ACCEL_ro_toS(_m->VERTICAL_ACCEL_phys);
#endif // PACMOD6_USE_SIGFLOAT

  _d[0] |= (_m->LATERAL_NEW_DATA_RX & (0x01U)) | ((_m->LONGITUDNAL_NEW_DATA_RX & (0x01U)) << 1) | ((_m->VERTICAL_NEW_DATA_RX & (0x01U)) << 2) | ((_m->LATERAL_VALID & (0x01U)) << 3) | ((_m->LONGITUDNAL_VALID & (0x01U)) << 4) | ((_m->VERTICAL_VALID & (0x01U)) << 5);
  _d[1] |= ((_m->LATERAL_ACCEL_ro >> 8) & (0xFFU));
  _d[2] |= (_m->LATERAL_ACCEL_ro & (0xFFU));
  _d[3] |= ((_m->LONGITUDNAL_ACCEL_ro >> 8) & (0xFFU));
  _d[4] |= (_m->LONGITUDNAL_ACCEL_ro & (0xFFU));
  _d[5] |= ((_m->VERTICAL_ACCEL_ro >> 8) & (0xFFU));
  _d[6] |= (_m->VERTICAL_ACCEL_ro & (0xFFU));

  *_len = LINEAR_ACCEL_RPT_DLC;
  *_ide = LINEAR_ACCEL_RPT_IDE;
  return LINEAR_ACCEL_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_ANG_VEL_RPT_pacmod6(ANG_VEL_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->PITCH_NEW_DATA_RX = (_d[0] & (0x01U));
  _m->ROLL_NEW_DATA_RX = ((_d[0] >> 1) & (0x01U));
  _m->YAW_NEW_DATA_RX = ((_d[0] >> 2) & (0x01U));
  _m->PITCH_VALID = ((_d[0] >> 3) & (0x01U));
  _m->ROLL_VALID = ((_d[0] >> 4) & (0x01U));
  _m->YAW_VALID = ((_d[0] >> 5) & (0x01U));
  _m->PITCH_VEL_ro = __ext_sig__(( ((_d[1] & (0xFFU)) << 8) | (_d[2] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->PITCH_VEL_phys = (sigfloat_t)(PACMOD6_PITCH_VEL_ro_fromS(_m->PITCH_VEL_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->ROLL_VEL_ro = __ext_sig__(( ((_d[3] & (0xFFU)) << 8) | (_d[4] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->ROLL_VEL_phys = (sigfloat_t)(PACMOD6_ROLL_VEL_ro_fromS(_m->ROLL_VEL_ro));
#endif // PACMOD6_USE_SIGFLOAT

  _m->YAW_VEL_ro = __ext_sig__(( ((_d[5] & (0xFFU)) << 8) | (_d[6] & (0xFFU)) ), 16);
#ifdef PACMOD6_USE_SIGFLOAT
  _m->YAW_VEL_phys = (sigfloat_t)(PACMOD6_YAW_VEL_ro_fromS(_m->YAW_VEL_ro));
#endif // PACMOD6_USE_SIGFLOAT

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ANG_VEL_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ANG_VEL_RPT_pacmod6(&_m->mon1, ANG_VEL_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return ANG_VEL_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_ANG_VEL_RPT_pacmod6(ANG_VEL_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ANG_VEL_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->PITCH_VEL_ro = PACMOD6_PITCH_VEL_ro_toS(_m->PITCH_VEL_phys);
  _m->ROLL_VEL_ro = PACMOD6_ROLL_VEL_ro_toS(_m->ROLL_VEL_phys);
  _m->YAW_VEL_ro = PACMOD6_YAW_VEL_ro_toS(_m->YAW_VEL_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

uint32_t Pack_ANG_VEL_RPT_pacmod6(ANG_VEL_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ANG_VEL_RPT_DLC) && (i < 8); _d[i++] = 0);

#ifdef PACMOD6_USE_SIGFLOAT
  _m->PITCH_VEL_ro = PACMOD6_PITCH_VEL_ro_toS(_m->PITCH_VEL_phys);
  _m->ROLL_VEL_ro = PACMOD6_ROLL_VEL_ro_toS(_m->ROLL_VEL_phys);
  _m->YAW_VEL_ro = PACMOD6_YAW_VEL_ro_toS(_m->YAW_VEL_phys);
#endif // PACMOD6_USE_SIGFLOAT

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

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_NOTIFICATION_CMD_pacmod6(NOTIFICATION_CMD_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->BUZZER_MUTE = (_d[0] & (0x01U));
  _m->UNDERDASH_LIGHTS_WHITE = ((_d[0] >> 1) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < NOTIFICATION_CMD_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_NOTIFICATION_CMD_pacmod6(&_m->mon1, NOTIFICATION_CMD_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return NOTIFICATION_CMD_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_NOTIFICATION_CMD_pacmod6(NOTIFICATION_CMD_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < NOTIFICATION_CMD_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->BUZZER_MUTE & (0x01U)) | ((_m->UNDERDASH_LIGHTS_WHITE & (0x01U)) << 1);

  cframe->MsgId = NOTIFICATION_CMD_CANID;
  cframe->DLC = NOTIFICATION_CMD_DLC;
  cframe->IDE = NOTIFICATION_CMD_IDE;
  return NOTIFICATION_CMD_CANID;
}

#else

uint32_t Pack_NOTIFICATION_CMD_pacmod6(NOTIFICATION_CMD_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < NOTIFICATION_CMD_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->BUZZER_MUTE & (0x01U)) | ((_m->UNDERDASH_LIGHTS_WHITE & (0x01U)) << 1);

  *_len = NOTIFICATION_CMD_DLC;
  *_ide = NOTIFICATION_CMD_IDE;
  return NOTIFICATION_CMD_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_ESTOP_RPT_pacmod6(ESTOP_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->ESTOP = (_d[0] & (0x01U));
  _m->ESTOP_FAULT = ((_d[0] >> 1) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < ESTOP_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_ESTOP_RPT_pacmod6(&_m->mon1, ESTOP_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return ESTOP_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_ESTOP_RPT_pacmod6(ESTOP_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < ESTOP_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->ESTOP & (0x01U)) | ((_m->ESTOP_FAULT & (0x01U)) << 1);

  cframe->MsgId = ESTOP_RPT_CANID;
  cframe->DLC = ESTOP_RPT_DLC;
  cframe->IDE = ESTOP_RPT_IDE;
  return ESTOP_RPT_CANID;
}

#else

uint32_t Pack_ESTOP_RPT_pacmod6(ESTOP_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < ESTOP_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->ESTOP & (0x01U)) | ((_m->ESTOP_FAULT & (0x01U)) << 1);

  *_len = ESTOP_RPT_DLC;
  *_ide = ESTOP_RPT_IDE;
  return ESTOP_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

uint32_t Unpack_WATCHDOG_RPT_pacmod6(WATCHDOG_RPT_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->GLOBAL_ENABLE_FLAG = (_d[0] & (0x01U));
  _m->GLOBAL_OVERRIDE_ACTIVE = ((_d[0] >> 1) & (0x01U));
  _m->GLOBAL_COMMAND_TIMEOUT_ERROR = ((_d[0] >> 2) & (0x01U));
  _m->GLOBAL_PACMOD_SUBSYSTEM_TIMEOUT = ((_d[0] >> 3) & (0x01U));
  _m->GLOBAL_VEHICLE_CAN_TIMEOUT = ((_d[0] >> 4) & (0x01U));
  _m->GLOBAL_PACMOD_SYSTEM_FAULT_ACTIVE = ((_d[0] >> 5) & (0x01U));
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
  _m->MOD1_CONFIG_FAULT = (_d[5] & (0x01U));
  _m->MOD1_CAN_TIMEOUT = ((_d[5] >> 1) & (0x01U));
  _m->MOD1_COUNTER_FAULT = ((_d[5] >> 2) & (0x01U));
  _m->MOD2_CONFIG_FAULT = ((_d[5] >> 3) & (0x01U));
  _m->MOD2_CAN_TIMEOUT = ((_d[5] >> 4) & (0x01U));
  _m->MOD2_COUNTER_FAULT = ((_d[5] >> 5) & (0x01U));
  _m->MOD3_CONFIG_FAULT = ((_d[5] >> 6) & (0x01U));
  _m->MOD3_CAN_TIMEOUT = ((_d[5] >> 7) & (0x01U));
  _m->MOD3_COUNTER_FAULT = (_d[6] & (0x01U));
  _m->MINI1_RPT_TIMEOUT = ((_d[6] >> 1) & (0x01U));
  _m->MINI1_CONFIG_FAULT = ((_d[6] >> 2) & (0x01U));
  _m->MINI1_CAN_TIMEOUT = ((_d[6] >> 3) & (0x01U));
  _m->MINI1_COUNTER_FAULT = ((_d[6] >> 4) & (0x01U));
  _m->MINI2_RPT_TIMEOUT = ((_d[6] >> 5) & (0x01U));
  _m->MINI2_CONFIG_FAULT = ((_d[6] >> 6) & (0x01U));
  _m->MINI2_CAN_TIMEOUT = ((_d[6] >> 7) & (0x01U));
  _m->MINI2_COUNTER_FAULT = (_d[7] & (0x01U));
  _m->MINI3_RPT_TIMEOUT = ((_d[7] >> 1) & (0x01U));
  _m->MINI3_CONFIG_FAULT = ((_d[7] >> 2) & (0x01U));
  _m->MINI3_CAN_TIMEOUT = ((_d[7] >> 3) & (0x01U));
  _m->MINI3_COUNTER_FAULT = ((_d[7] >> 4) & (0x01U));
  _m->MOD_SYSTEM_PRESENT_FAULT = ((_d[7] >> 5) & (0x01U));
  _m->MINI_SYSTEM_PRESENT_FAULT = ((_d[7] >> 6) & (0x01U));
  _m->GLOBAL_INTERNAL_POWER_SUPPLY_FAULT = ((_d[7] >> 7) & (0x01U));

#ifdef PACMOD6_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < WATCHDOG_RPT_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_WATCHDOG_RPT_pacmod6(&_m->mon1, WATCHDOG_RPT_CANID);
#endif // PACMOD6_USE_DIAG_MONITORS

  return WATCHDOG_RPT_CANID;
}

#ifdef PACMOD6_USE_CANSTRUCT

uint32_t Pack_WATCHDOG_RPT_pacmod6(WATCHDOG_RPT_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < WATCHDOG_RPT_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->GLOBAL_ENABLE_FLAG & (0x01U)) | ((_m->GLOBAL_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->GLOBAL_COMMAND_TIMEOUT_ERROR & (0x01U)) << 2) | ((_m->GLOBAL_PACMOD_SUBSYSTEM_TIMEOUT & (0x01U)) << 3) | ((_m->GLOBAL_VEHICLE_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->GLOBAL_PACMOD_SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->GLOBAL_CONFIG_FAULT_ACTIVE & (0x01U)) << 6) | ((_m->GLOBAL_TIMEOUT & (0x01U)) << 7);
  cframe->Data[1] |= (_m->ACCEL_ENABLED & (0x01U)) | ((_m->ACCEL_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->ACCEL_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->ACCEL_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->ACCEL_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->ACCEL_PACMOD_FAULT & (0x01U)) << 5) | ((_m->ACCEL_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->ACCEL_TIMEOUT & (0x01U)) << 7);
  cframe->Data[2] |= (_m->BRAKE_ENABLED & (0x01U)) | ((_m->BRAKE_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->BRAKE_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->BRAKE_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->BRAKE_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->BRAKE_PACMOD_FAULT & (0x01U)) << 5) | ((_m->BRAKE_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->BRAKE_TIMEOUT & (0x01U)) << 7);
  cframe->Data[3] |= (_m->SHIFT_ENABLED & (0x01U)) | ((_m->SHIFT_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->SHIFT_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->SHIFT_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->SHIFT_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->SHIFT_PACMOD_FAULT & (0x01U)) << 5) | ((_m->SHIFT_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->SHIFT_TIMEOUT & (0x01U)) << 7);
  cframe->Data[4] |= (_m->STEER_ENABLED & (0x01U)) | ((_m->STEER_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->STEER_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->STEER_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->STEER_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->STEER_PACMOD_FAULT & (0x01U)) << 5) | ((_m->STEER_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->STEER_TIMEOUT & (0x01U)) << 7);
  cframe->Data[5] |= (_m->MOD1_CONFIG_FAULT & (0x01U)) | ((_m->MOD1_CAN_TIMEOUT & (0x01U)) << 1) | ((_m->MOD1_COUNTER_FAULT & (0x01U)) << 2) | ((_m->MOD2_CONFIG_FAULT & (0x01U)) << 3) | ((_m->MOD2_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->MOD2_COUNTER_FAULT & (0x01U)) << 5) | ((_m->MOD3_CONFIG_FAULT & (0x01U)) << 6) | ((_m->MOD3_CAN_TIMEOUT & (0x01U)) << 7);
  cframe->Data[6] |= (_m->MOD3_COUNTER_FAULT & (0x01U)) | ((_m->MINI1_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->MINI1_CONFIG_FAULT & (0x01U)) << 2) | ((_m->MINI1_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->MINI1_COUNTER_FAULT & (0x01U)) << 4) | ((_m->MINI2_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->MINI2_CONFIG_FAULT & (0x01U)) << 6) | ((_m->MINI2_CAN_TIMEOUT & (0x01U)) << 7);
  cframe->Data[7] |= (_m->MINI2_COUNTER_FAULT & (0x01U)) | ((_m->MINI3_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->MINI3_CONFIG_FAULT & (0x01U)) << 2) | ((_m->MINI3_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->MINI3_COUNTER_FAULT & (0x01U)) << 4) | ((_m->MOD_SYSTEM_PRESENT_FAULT & (0x01U)) << 5) | ((_m->MINI_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->GLOBAL_INTERNAL_POWER_SUPPLY_FAULT & (0x01U)) << 7);

  cframe->MsgId = WATCHDOG_RPT_CANID;
  cframe->DLC = WATCHDOG_RPT_DLC;
  cframe->IDE = WATCHDOG_RPT_IDE;
  return WATCHDOG_RPT_CANID;
}

#else

uint32_t Pack_WATCHDOG_RPT_pacmod6(WATCHDOG_RPT_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < WATCHDOG_RPT_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->GLOBAL_ENABLE_FLAG & (0x01U)) | ((_m->GLOBAL_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->GLOBAL_COMMAND_TIMEOUT_ERROR & (0x01U)) << 2) | ((_m->GLOBAL_PACMOD_SUBSYSTEM_TIMEOUT & (0x01U)) << 3) | ((_m->GLOBAL_VEHICLE_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->GLOBAL_PACMOD_SYSTEM_FAULT_ACTIVE & (0x01U)) << 5) | ((_m->GLOBAL_CONFIG_FAULT_ACTIVE & (0x01U)) << 6) | ((_m->GLOBAL_TIMEOUT & (0x01U)) << 7);
  _d[1] |= (_m->ACCEL_ENABLED & (0x01U)) | ((_m->ACCEL_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->ACCEL_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->ACCEL_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->ACCEL_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->ACCEL_PACMOD_FAULT & (0x01U)) << 5) | ((_m->ACCEL_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->ACCEL_TIMEOUT & (0x01U)) << 7);
  _d[2] |= (_m->BRAKE_ENABLED & (0x01U)) | ((_m->BRAKE_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->BRAKE_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->BRAKE_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->BRAKE_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->BRAKE_PACMOD_FAULT & (0x01U)) << 5) | ((_m->BRAKE_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->BRAKE_TIMEOUT & (0x01U)) << 7);
  _d[3] |= (_m->SHIFT_ENABLED & (0x01U)) | ((_m->SHIFT_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->SHIFT_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->SHIFT_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->SHIFT_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->SHIFT_PACMOD_FAULT & (0x01U)) << 5) | ((_m->SHIFT_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->SHIFT_TIMEOUT & (0x01U)) << 7);
  _d[4] |= (_m->STEER_ENABLED & (0x01U)) | ((_m->STEER_OVERRIDE_ACTIVE & (0x01U)) << 1) | ((_m->STEER_COMMAND_OUTPUT_FAULT & (0x01U)) << 2) | ((_m->STEER_INPUT_OUTPUT_FAULT & (0x01U)) << 3) | ((_m->STEER_OUTPUT_REPORTED_FAULT & (0x01U)) << 4) | ((_m->STEER_PACMOD_FAULT & (0x01U)) << 5) | ((_m->STEER_VEHICLE_FAULT & (0x01U)) << 6) | ((_m->STEER_TIMEOUT & (0x01U)) << 7);
  _d[5] |= (_m->MOD1_CONFIG_FAULT & (0x01U)) | ((_m->MOD1_CAN_TIMEOUT & (0x01U)) << 1) | ((_m->MOD1_COUNTER_FAULT & (0x01U)) << 2) | ((_m->MOD2_CONFIG_FAULT & (0x01U)) << 3) | ((_m->MOD2_CAN_TIMEOUT & (0x01U)) << 4) | ((_m->MOD2_COUNTER_FAULT & (0x01U)) << 5) | ((_m->MOD3_CONFIG_FAULT & (0x01U)) << 6) | ((_m->MOD3_CAN_TIMEOUT & (0x01U)) << 7);
  _d[6] |= (_m->MOD3_COUNTER_FAULT & (0x01U)) | ((_m->MINI1_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->MINI1_CONFIG_FAULT & (0x01U)) << 2) | ((_m->MINI1_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->MINI1_COUNTER_FAULT & (0x01U)) << 4) | ((_m->MINI2_RPT_TIMEOUT & (0x01U)) << 5) | ((_m->MINI2_CONFIG_FAULT & (0x01U)) << 6) | ((_m->MINI2_CAN_TIMEOUT & (0x01U)) << 7);
  _d[7] |= (_m->MINI2_COUNTER_FAULT & (0x01U)) | ((_m->MINI3_RPT_TIMEOUT & (0x01U)) << 1) | ((_m->MINI3_CONFIG_FAULT & (0x01U)) << 2) | ((_m->MINI3_CAN_TIMEOUT & (0x01U)) << 3) | ((_m->MINI3_COUNTER_FAULT & (0x01U)) << 4) | ((_m->MOD_SYSTEM_PRESENT_FAULT & (0x01U)) << 5) | ((_m->MINI_SYSTEM_PRESENT_FAULT & (0x01U)) << 6) | ((_m->GLOBAL_INTERNAL_POWER_SUPPLY_FAULT & (0x01U)) << 7);

  *_len = WATCHDOG_RPT_DLC;
  *_ide = WATCHDOG_RPT_IDE;
  return WATCHDOG_RPT_CANID;
}

#endif // PACMOD6_USE_CANSTRUCT

