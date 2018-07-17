/*
 * tttechBroadRReach.h
 *
 *  Created on: Mar 25, 2015
 *      Author: ext-strauss
 */
/* ------------------------------------------------------------------------- */
/*                         SUPRESSED MISRA VIOLATONS                         */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(10:4901) Prefixes for Type Definitions invalid 'TJA1100_SNR_WLIMIT_t',
 * 'TJA1100_SNR_Averaging_t',.... zFAS-SW Coding Guidelines 3.1.3	  
 * 
 * Justification: The naming convention from "zFAS-SW Coding Guidelines" is justified by
 * using Ethernet PHY name as unique name identifier for typedefs related to BR Ethernet.    
 */
/* PRQA S 4901 EOF */
/* ------------------------------------------------------------------------- */

#ifndef VXBBROADRPHY_H_
#define VXBBROADRPHY_H_

//--------------------------------------------------------------------------------
// register depending enumerations
//--------------------------------------------------------------------------------
// register 0x00
//---------------------------------------------------
#define TJA1100_BASIC_CONTROL_REG      (0x00)
#define TJA1100_BASIC_CONTROL_REG_MASK (0xFFE0)
//--------------------------------------
typedef enum
{
  TJA1100_RST_PHY_RESET	= 1,
  TJA1100_RST_NORMAL_OPERATION	= 0
}TJA1100_RESET_t;

#define TJA1100_RST_MASK   (0x8000)   // bit [15]
#define TJA1100_RST_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_LB_LOOPBACK_MODE	= 1,
  TJA1100_LB_NORMAL_OPERATION	= 0
}TJA1100_LOOPBACK_t;

#define TJA1100_LB_MASK   (0x4000)   // bit [14]
#define TJA1100_LB_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1100_SS_LSB_100MBPS	= 1
}TJA1100_SPEED_SELECT_LSB_t;

#define TJA1100_SS_LSB_MASK   (0x2000)   // bit [13]
#define TJA1100_SS_LSB_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1100_ANE_DISABLE_AUTONEGOTIATION_PROCESS	= 0
}TJA1100_AUTONEG_ENABLE_t;

#define TJA1100_ANE_MASK   (0x1000)   // bit [12]
#define TJA1100_ANE_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_PWRD_POWER_DOWN_INTO_STANDBY	= 1,
  TJA1100_PWRD_NORMAL_OPERATION	= 0
}TJA1100_POWER_DOWN_t;

#define TJA1100_PWRD_MASK   (0x800)   // bit [11]
#define TJA1100_PWRD_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_ISL_ISOLATION_OF_PHY_FROM_MII_RMII	= 1,
  TJA1100_ISL_NORMAL_OPERATION	= 0
}TJA1100_ISOLATE_t;

#define TJA1100_ISL_MASK   (0x400)   // bit [10]
#define TJA1100_ISL_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_RAN_NORMAL_OPERATION	= 0
}TJA1100_RE_AUTONEG_t;

#define TJA1100_RAN_MASK   (0x200)   // bit [9]
#define TJA1100_RAN_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1100_DM_FULL_DUPLEX	= 1
}TJA1100_DUPLEX_MODE_t;

#define TJA1100_DM_MASK   (0x100)   // bit [8]
#define TJA1100_DM_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1100_CT_DISABLE_COL_SIGNAL_TEST	= 0
}TJA1100_COLLISION_TEST_t;

#define TJA1100_CT_MASK   (0x80)   // bit [7]
#define TJA1100_CT_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1100_SS_MSB_100MBPS	= 0
}TJA1100_SPEED_SELECT_MSB_t;

#define TJA1100_SS_MSB_MASK   (0x40)   // bit [6]
#define TJA1100_SS_MSB_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1100_UDE_EN_MII_TRANSMIT_WITHOUT_PHY_VALID_LINK	= 1,
  TJA1100_UDE_EN_MII_TRANSMIT_ONLY_WHEN_PHY_VALID_LINK	= 0
}TJA1100_Unidirectional_enable_t;

#define TJA1100_UDE_MASK   (0x20)   // bit [5]
#define TJA1100_UDE_SHIFT  (5)

//---------------------------------------------------
// register 0x01
//---------------------------------------------------
#define TJA1100_BASIC_STATUS_REG      (0x01)
#define TJA1100_BASIC_STATUS_REG_MASK (0xFFFF)
//--------------------------------------
typedef enum
{
  TJA1100_100BASE_T4_PHY_100BASET4_CAPABLE	= 1,
  TJA1100_100BASE_T4_PHY_NOT_100BASET4_CAPABLE	= 0
}TJA1100_100BASE_T4_t;

#define TJA1100_100BASE_T4_MASK   (0x8000)   // bit [15]
#define TJA1100_100BASE_T4_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_100BASE_X_FD_PHY_100BASEX_FD_CAPABLE	= 1,
  TJA1100_100BASE_X_FD_PHY_NOT_100BASETX_FD_CAPABLE	= 0
}TJA1100_100BASE_X_Full_Duplex_t;

#define TJA1100_100BASE_X_FD_MASK   (0x4000)   // bit [14]
#define TJA1100_100BASE_X_FD_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1100_100BASE_X_HD_PHY_100BASEX_HD_CAPABLE	= 1,
  TJA1100_100BASE_X_HD_PHY_NOT_100BASETX_HD_CAPABLE	= 0
}TJA1100_100BASE_X_Half_Duplex_t;

#define TJA1100_100BASE_X_HD_MASK   (0x2000)   // bit [13]
#define TJA1100_100BASE_X_HD_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1100_10MBPS_FD_PHY_10MBPS_FD_CAPABLE	= 1,
  TJA1100_10MBPS_FD_PHY_NOT_10MBPS_FD_CAPABLE	= 0
}TJA1100_10Mbps_Full_Duplex_t;

#define TJA1100_10MBPS_FD_MASK   (0x1000)   // bit [12]
#define TJA1100_10MBPS_FD_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_10MBPS_HD_PHY_10MBPS_HD_CAPABLE	= 1,
  TJA1100_10MBPS_HD_PHY_NOT_10MBPS_HD_CAPABLE	= 0
}TJA1100_10Mbps_Half_Duplex_t;

#define TJA1100_10MBPS_HD_MASK   (0x800)   // bit [11]
#define TJA1100_10MBPS_HD_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_100BASE_T2_FD_PHY_100BASET2_FD_CAPABLE	= 1,
  TJA1100_100BASE_T2_FD_PHY_NOT_100BASET2_FD_CAPABLE	= 0
}TJA1100_100BASE_T2_Full_Duplex_t;

#define TJA1100_100BASE_T2_FD_MASK   (0x400)   // bit [10]
#define TJA1100_100BASE_T2_FD_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_100BASE_T2_HD_PHY_100BASET2_HD_CAPABLE	= 1,
  TJA1100_100BASE_T2_HD_PHY_NOT_100BASET2_HD_CAPABLE	= 0
}TJA1100_100BASE_T2_Half_Duplex_t;

#define TJA1100_100BASE_T2_HD_MASK   (0x200)   // bit [9]
#define TJA1100_100BASE_T2_HD_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1100_ES_EXTENDED_STATUS_INFORMATION_IN_REG_15	= 1,
  TJA1100_ES_NO_EXTENDED_INFORMATION_IN_REG_15	= 0
}TJA1100_EXTENDED_STATUS_t;

#define TJA1100_ES_MASK   (0x100)   // bit [8]
#define TJA1100_ES_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1100_UDA_PHY_ABLE_TO_TRANSMIT_FROM_MII_WITHOUT_VALID_LINK	= 1,
  TJA1100_UDA_PHY_ABLE_TO_TRANSMIT_FROM_MII_ONLY_WHEN_VALID_LINK	= 0
}TJA1100_Unidirectional_ability_t;

#define TJA1100_UDA_MASK   (0x80)   // bit [7]
#define TJA1100_UDA_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1100_MFPS_PHY_WILL_ACCEPT_PREAMBLE_SUPPRESSED_MANAGEMENT_FRAMES	= 1,
  TJA1100_MFPS_PHY_WILL_NOT_ACCEPT_PREAMBLE_SUPPRESSED_MANAGEMENT_FRAMES	= 0
}TJA1100_MF_Preamble_Suppression_t;

#define TJA1100_MFPS_MASK   (0x40)   // bit [6]
#define TJA1100_MFPS_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1100_ANC_AUTONEGOTIATION_PROCESS_COMPLETED	= 1,
  TJA1100_ANC_AUTONEGOTIATION_PROCESS_NOT_COMPLETED	= 0
}TJA1100_AUTONEG_COMPLETE_t;

#define TJA1100_ANC_MASK   (0x20)   // bit [5]
#define TJA1100_ANC_SHIFT  (5)
//--------------------------------------
typedef enum
{
  TJA1100_RF_REMOTE_FAULT_CONDITION_DETECTED	= 1,
  TJA1100_RF_NO_REMOTE_FAULT_CONDITION_DETECTED	= 0
}TJA1100_REMOTE_FAULT_t;

#define TJA1100_RF_MASK   (0x10)   // bit [4]
#define TJA1100_RF_SHIFT  (4)
//--------------------------------------
typedef enum
{
  TJA1100_ANA_PHY_IS_ABLE_TO_PERFORM_AUTONEGOTIATION	= 1,
  TJA1100_ANA_PHY_NOT_ABLE_TO_PERFORM_AUTONEGOTIATION	= 0
}TJA1100_AUTONEG_ABILITY_t;

#define TJA1100_ANA_MASK   (0x08)   // bit [3]
#define TJA1100_ANA_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1100_LS_LINK_IS_UP	= 1,
  TJA1100_LS_LINK_IS_DOWN	= 0
}TJA1100_LINK_STATUS_t;

#define TJA1100_LS_MASK   (0x04)   // bit [2]
#define TJA1100_LS_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1100_JD_JABBER_CONDITION_DETECTED	= 1,
  TJA1100_JD_NO_JABBER_CONDITION_DETECTED	= 0
}TJA1100_JABBER_DETECT_t;

#define TJA1100_JD_MASK   (0x02)   // bit [1]
#define TJA1100_JD_SHIFT  (1)
//--------------------------------------
typedef enum
{
  TJA1100_EC_EXTENDED_REGISTER_CAPABILITIES	= 1,
  TJA1100_EC_BASIC_REGISTER_SET_CAPABILITIES	= 0
}TJA1100_EXTENDED_CAPABILITY_t;

#define TJA1100_EC_MASK   (0x01)   // bit [0]
#define TJA1100_EC_SHIFT  (0)

//---------------------------------------------------
// register 0x02
//---------------------------------------------------
#define TJA1100_PHY_IDENTIFIER_1_REG      (0x02)
#define TJA1100_PHY_IDENTIFIER_1_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA1100_PHY_ID_1_t;

#define TJA1100_PHY_ID1_MASK   (0xFFFF)   // bit [15:0]
#define TJA1100_PHY_ID1_SHIFT  (0)

//---------------------------------------------------
// register 0x03
//---------------------------------------------------
#define TJA1100_PHY_IDENTIFIER_2_REG      (0x03)
#define TJA1100_PHY_IDENTIFIER_2_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA1100_PHY_ID_2_t;

#define TJA1100_PHY_ID2_MASK   (0xFC00)   // bit [15:10]
#define TJA1100_PHY_ID2_SHIFT  (10)
//--------------------------------------
typedef unsigned short TJA1100_TYPE_No_t;

#define TJA1100_TYPE_MASK   (0x3F0)   // bit [9:4]
#define TJA1100_TYPE_SHIFT  (4)
//--------------------------------------
typedef unsigned short TJA1100_REVISION_No_t;

#define TJA1100_REV_MASK   (0x0F)   // bit [3:0]
#define TJA1100_REV_SHIFT  (0)

//---------------------------------------------------
// register 0x0F
//---------------------------------------------------
#define TJA1100_EXTENDED_STATUS_REG      (0x0F)
#define TJA1100_EXTENDED_STATUS_REG_MASK (0xF0C0)
//--------------------------------------
typedef enum
{
  TJA1100_1000BASE_X_FD_PHY_1000BASEX_FD_CAPABLE	= 1,
  TJA1100_1000BASE_X_FD_PHY_NOT_1000BASEX_FD_CAPABLE	= 0
}TJA1100_1000BASE_X_Full_Duplex_t;

#define TJA1100_1000BASE_X_FD_MASK   (0x8000)   // bit [15]
#define TJA1100_1000BASE_X_FD_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_1000BASE_X_HD_PHY_1000BASEX_HD_CAPABLE	= 1,
  TJA1100_1000BASE_X_HD_PHY_NOT_1000BASEX_HD_CAPABLE	= 0
}TJA1100_1000BASE_X_Half_Duplex_t;

#define TJA1100_1000BASE_X_HD_MASK   (0x4000)   // bit [14]
#define TJA1100_1000BASE_X_HD_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1100_1000BASE_T_FD_PHY_1000BASET_FD_CAPABLE	= 1,
  TJA1100_1000BASE_T_FD_PHY_NOT_1000BASET_FD_CAPABLE	= 0
}TJA1100_1000BASE_T_Full_Duplex_t;

#define TJA1100_1000BASE_T_FD_MASK   (0x2000)   // bit [13]
#define TJA1100_1000BASE_T_FD_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1100_1000BASE_T_HD_PHY_1000BASET_HD_CAPABLE	= 1,
  TJA1100_1000BASE_T_HD_PHY_NOT_1000BASET_HD_CAPABLE	= 0
}TJA1100_1000BASE_T_Half_Duplex_t;

#define TJA1100_1000BASE_T_HD_MASK   (0x1000)   // bit [12]
#define TJA1100_1000BASE_T_HD_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_100BASE_BR_PHY_ABLE_TO_1_PAIR_BROADR_REACH_100MBPS	= 1,
  TJA1100_100BASE_BR_PHY_NOT_ABLE_TO_1_PAIR_BROADR_REACH_100MBPS	= 0
}TJA1100_100BASE_BroadR_Reach_t;

#define TJA1100_100BASE_BR_MASK   (0x80)   // bit [7]
#define TJA1100_100BASE_BR_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1100_1000BASE_RTPGE_PHY_ABLE_TO_RTPGE	= 1,
  TJA1100_1000BASE_RTPGE_PHY_NOT_ABLE_TO_RTPGE	= 0
}TJA1100_1000BASE_RTPGE_t;

#define TJA1100_1000BASE_RTPGE_MASK   (0x40)   // bit [6]
#define TJA1100_1000BASE_RTPGE_SHIFT  (6)

//---------------------------------------------------
// register 0x11
//---------------------------------------------------
#define TJA1100_EXTENDED_CONTROL_REG      (0x11)
#define TJA1100_EXTENDED_CONTROL_REG_MASK (0xFFFF)
//--------------------------------------
typedef enum
{
  TJA1100_LC_LINK_CONTROL_ENABLED	= 1,
  TJA1100_LC_LINK_CONTROL_DISABLED	= 0
}TJA1100_LINK_CONTROL_t;

#define TJA1100_LC_MASK   (0x8000)   // bit [15]
#define TJA1100_LC_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_PM_NO_CHANGE	= 0,
  TJA1100_PM_NORMAL_MODE	= 3,
  TJA1100_PM_STANDBY_MODE	= 12,
  TJA1100_PM_SLEEP_REQUEST	= 11
}TJA1100_POWER_MODE_t;

#define TJA1100_PM_MASK   (0x7800)   // bit [14:11]
#define TJA1100_PM_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_SJT_SLAVE_JITTER_TEST_ENABLED	= 1,
  TJA1100_SJT_SLAVE_JITTER_TEST_DISABLED	= 0
}TJA1100_SLAVE_JITTER_TEST_t;

#define TJA1100_SJT_MASK   (0x400)   // bit [10]
#define TJA1100_SJT_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_TRS_FORCES_RESTART_OF_TRAINING_PHASE	= 1,
  TJA1100_TRS_STOPS_TRAINING_PHASE	= 0
}TJA1100_TRAINING_RESTART_t;

#define TJA1100_TRS_MASK   (0x200)   // bit [9]
#define TJA1100_TRS_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1100_TM_NO_TEST_MODE	= 0,
  TJA1100_TM_BROADR_REACH_TEST_MODE_1	= 1,
  TJA1100_TM_BROADR_REACH_TEST_MODE_2	= 2,
  TJA1100_TM_BROADR_REACH_TEST_MODE_3	= 3,
  TJA1100_TM_BROADR_REACH_TEST_MODE_4	= 4,
  TJA1100_TM_BROADR_REACH_TEST_MODE_5	= 5
}TJA1100_TEST_MODE_t;

#define TJA1100_TM_MASK   (0x1C0)   // bit [8:6]
#define TJA1100_TM_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1100_CBT_FORCES_TDR_BASED_CABLE_TEST	= 1,
  TJA1100_CBT_STOPS_TDR_BASED_CABLE_TEST	= 0
}TJA1100_CABLE_TEST_t;

#define TJA1100_CBT_MASK   (0x20)   // bit [5]
#define TJA1100_CBT_SHIFT  (5)
//--------------------------------------
typedef enum
{
  TJA1100_LM_INTERNAL_LOOPBACK	= 0,
  TJA1100_LM_EXTERNAL_LOOPBACK1	= 1,
  TJA1100_LM_EXTERNAL_LOOPBACK2	= 2,
  TJA1100_LM_REMOTE_LOOPBACK	= 3
}TJA1100_LOOPBACK_MODE_t;

#define TJA1100_LM_MASK   (0x18)   // bit [4:3]
#define TJA1100_LM_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1100_CFEN_CONFIGURATION_REGISTER_ACCESS_ENABLED	= 1,
  TJA1100_CFEN_CONFIGURATION_REGISTER_ACCESS_DISABLED	= 0
}TJA1100_CONFIG_EN_t;

#define TJA1100_CFEN_MASK   (0x04)   // bit [2]
#define TJA1100_CFEN_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1100_CF_INH_INH_SWITCHED_OFF_IN_DISABLE_MODE	= 0,
  TJA1100_CF_INH_INH_SWITCHED_ON_IN_DISABLE_MODE	= 1
}TJA1100_CONFIG_INH_t;

#define TJA1100_CF_INH_MASK   (0x02)   // bit [1]
#define TJA1100_CF_INH_SHIFT  (1)
//--------------------------------------
typedef enum
{
  TJA1100_WR_START_SENDING_IDLE_SYMBOLS_AS_BUS_WAKEUP_SIGNAL	= 1,
  TJA1100_WR_NO_WAKEUP_SIGNAL_TO_BE_SENT	= 0
}TJA1100_WAKE_REQUEST_t;

#define TJA1100_WR_MASK   (0x01)   // bit [0]
#define TJA1100_WR_SHIFT  (0)

//---------------------------------------------------
// register 0x12
//---------------------------------------------------
#define TJA1100_CONFIGURATION_1_REG      (0x12)
#define TJA1100_CONFIGURATION_1_REG_MASK (0xFFFF)
//--------------------------------------
typedef enum
{
  TJA1100_MS_PHY_CONFIGURED_AS_MASTER	= 1,
  TJA1100_MS_PHY_CONFIGURED_AS_SLAVE	= 0
}TJA1100_MASTER_SLAVE_t;

#define TJA1100_MS_MASK   (0x8000)   // bit [15]
#define TJA1100_MS_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_AOP_AUTONOMOUS_OPERATION	= 1,
  TJA1100_AOP_MANAGED_OPERATION	= 0
}TJA1100_AUTO_OP_t;

#define TJA1100_AOP_MASK   (0x4000)   // bit [14]
#define TJA1100_AOP_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1100_LL_CABLE_LENGTH_LESS_5M	= 0,
  TJA1100_LL_CABLE_LENGTH_5TO10M	= 1,
  TJA1100_LL_CABLE_LENGTH_10TO15M	= 2,
  TJA1100_LL_CABLE_LENGTH_LONGER_15M	= 3
}TJA1100_LINK_LENGTH_t;

#define TJA1100_LL_MASK   (0x3000)   // bit [13:12]
#define TJA1100_LL_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_TXA_TRANSMIT_AMPLITUDE_NOM_500MV	= 0,
  TJA1100_TXA_TRANSMIT_AMPLITUDE_NOM_750_MV	= 1,
  TJA1100_TXA_TRANSMIT_AMPLITUDE_NOM_1000MV	= 2,
  TJA1100_TXA_TRANSMIT_AMPLITUDE_NOM_1250_MV	= 3
}TJA1100_TX_Amplitude_t;

#define TJA1100_TXA_MASK   (0xC00)   // bit [11:10]
#define TJA1100_TXA_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_MIIM_MII_MODE_ENABLED	= 0,
  TJA1100_MIIM_RMII_MODE_ENABLED__50MHZ_INPUT_AT_REFCLK_IN	= 1,
  TJA1100_MIIM_RMII_MODE_ENABLED__25MHZ_XTAL	= 2,
  TJA1100_MIIM_REVERSE_MII_MODE	= 3
}TJA1100_MII_Mode_t;

#define TJA1100_MIIM_MASK   (0x300)   // bit [9:8]
#define TJA1100_MIIM_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1100_MIID_STANDARD_OUTPUT_DRIVER_STRENGTH	= 1,
  TJA1100_MIID_REDUCED_OUTPUT_DRIVER_STRENGTH	= 0
}TJA1100_MII_DRIVER_t;

#define TJA1100_MIID_MASK   (0x80)   // bit [7]
#define TJA1100_MIID_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1100_SCNFM_CONFIRMATION_NEEDED_TO_GO_TO_SLEEP	= 1,
  TJA1100_SCNFM_NO_CONFIRMATION_NEEDED_TO_GO_TO_SLEEP	= 0
}TJA1100_SLEEP_CONFIRM_t;

#define TJA1100_SCNFM_MASK   (0x40)   // bit [6]
#define TJA1100_SCNFM_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1100_LEDM_LINK_STATUS	= 0,
  TJA1100_LEDM_FRAME_RECEPTION	= 1,
  TJA1100_LEDM_SYMBOL_ERROR	= 2,
  TJA1100_LEDM_CRS_SIGNAL	= 3
}TJA1100_LED_MODE_t;

#define TJA1100_LEDM_MASK   (0x30)   // bit [5:4]
#define TJA1100_LEDM_SHIFT  (4)
//--------------------------------------
typedef enum
{
  TJA1100_LEDEN_LED_OUTPUT_ENABLED	= 1,
  TJA1100_LEDEN_LED_OUTPUT_DISABLED_WAKEUP_INPUT_ENABLED	= 0
}TJA1100_LED_ENABLE_t;

#define TJA1100_LEDEN_MASK   (0x08)   // bit [3]
#define TJA1100_LEDEN_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1100_CFW_RATIO_METRIC_INPUT_THRESHOLD__VDDIO	= 1,
  TJA1100_CFW_ABSOLUTE_INPUT_THRESHOLD	= 0
}TJA1100_CONFIG_WAKE_t;

#define TJA1100_CFW_MASK   (0x04)   // bit [2]
#define TJA1100_CFW_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1100_APD_AUTONOMOUS_POWER_DOWN_ENABLED	= 1,
  TJA1100_APD_AUTONOMOUS_POWER_DOWN_DISABLED	= 0
}TJA1100_AUTO_PWD_t;

#define TJA1100_APD_MASK   (0x02)   // bit [1]
#define TJA1100_APD_SHIFT  (1)
//--------------------------------------
typedef enum
{
  TJA1100_LPSACT_AUTONOMOUS_TRANSITION_NORMAL_TO_SLEEP_REQUEST_ENABLED	= 1,
  TJA1100_LPSACT_AUTONOMOUS_TRANSITION_NORMAL_TO_SLEEP_REQUEST_DISABLED	= 0
}TJA1100_LPS_ACTIVE_t;

#define TJA1100_LPSACT_MASK   (0x01)   // bit [0]
#define TJA1100_LPSACT_SHIFT  (0)

//---------------------------------------------------
// register 0x13
//---------------------------------------------------
#define TJA1100_CONFIGURATION_2_REG      (0x13)
#define TJA1100_CONFIGURATION_2_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA1100_PHYAD4to0_t;

#define TJA1100_PHYAD_MASK   (0xF800)   // bit [15:11]
#define TJA1100_PHYAD_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_SNRA_SNR_AVERAGING_OVER_32_SYMBOLS	= 0,
  TJA1100_SNRA_SNR_OVER_64_SYMBOLS	= 1,
  TJA1100_SNRA_SNR_AVERAGING_OVER_128_SYMBOLS	= 2,
  TJA1100_SNRA_SNR_AVERAGING_OVER_256_SYMBOLS	= 3
}TJA1100_SNR_Averaging_t;

#define TJA1100_SNRA_MASK   (0x600)   // bit [10:9]
#define TJA1100_SNRA_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1100_SNRWL_NO_WARNING_LIMIT	= 0,
  TJA1100_SNRWL_CLASS_A_SN_RATIO_LIMIT	= 1,
  TJA1100_SNRWL_CLASS_B_SN_RATIO_LIMIT	= 2,
  TJA1100_SNRWL_CLASS_C_SN_RATIO_LIMIT	= 3,
  TJA1100_SNRWL_CLASS_D_SN_RATIO_LIMIT	= 4,
  TJA1100_SNRWL_CLASS_E_SN_RATIO_LIMIT	= 5,
  TJA1100_SNRWL_CLASS_F_SN_RATIO_LIMIT	= 6,
  TJA1100_SNRWL_CLASS_G_SN_RATIO_LIMIT	= 7
}TJA1100_SNR_WLIMIT_t;

#define TJA1100_SNRWL_MASK   (0x1C0)   // bit [8:6]
#define TJA1100_SNRWL_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1100_SNRFL_NO_FAIL_LIMIT	= 0,
  TJA1100_SNRFL_CLASS_A_SN_RATIO_LIMIT	= 1,
  TJA1100_SNRFL_CLASS_B_SN_RATIO_LIMIT	= 2,
  TJA1100_SNRFL_CLASS_C_SN_RATIO_LIMIT	= 3,
  TJA1100_SNRFL_CLASS_D_SN_RATIO_LIMIT	= 4,
  TJA1100_SNRFL_CLASS_E_SN_RATIO_LIMIT	= 5,
  TJA1100_SNRFL_CLASS_F_SN_RATIO_LIMIT	= 6,
  TJA1100_SNRFL_CLASS_G_SN_RATIO_LIMIT	= 7
}TJA1100_SNR_FAILLIMIT_t;

#define TJA1100_SNRFL_MASK   (0x38)   // bit [5:3]
#define TJA1100_SNRFL_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1100_JE_PACKETS_UP_TO_16KB_ARE_SUPPORTED	= 1,
  TJA1100_JE_PACKETS_UP_TO_4KB_ARE_SUPPORTED	= 0
}TJA1100_JUMBO_ENABLE_t;

#define TJA1100_JE_MASK   (0x04)   // bit [2]
#define TJA1100_JE_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1100_SRT_400NS_TIMEOUT	= 0,
  TJA1100_SRT_1MS_TIMEOUT	= 1,
  TJA1100_SRT_4MS_TIMEOUT	= 2,
  TJA1100_SRT_16MS_TIMEOUT	= 3
}TJA1100_SLEEP_REQUEST_TO_t;

#define TJA1100_SRT_MASK   (0x03)   // bit [1:0]
#define TJA1100_SRT_SHIFT  (0)

//---------------------------------------------------
// register 0x14
//---------------------------------------------------
#define TJA1100_SYMBOL_ERROR_COUNTER_REG      (0x14)
#define TJA1100_SYMBOL_ERROR_COUNTER_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA1100_SYM_ERR_CNT_t;

#define TJA1100_SEC_MASK   (0xFFFF)   // bit [15:0]
#define TJA1100_SEC_SHIFT  (0)

//---------------------------------------------------
// register 0x15
//---------------------------------------------------
#define TJA1100_INTERRUPT_SOURCE_REG      (0x15)
#define TJA1100_INTERRUPT_SOURCE_REG_MASK (0xFFFF)
//--------------------------------------
typedef enum
{
  TJA1100_PO_POWER_ON_DETECTED	= 1,
  TJA1100_PO_NO_POWER_ON_DETECTED	= 0
}TJA1100_PWON_t;

#define TJA1100_PO_MASK   (0x8000)   // bit [15]
#define TJA1100_PO_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_WU_WAKE_UP_DETECTED	= 1,
  TJA1100_WU_NO_WAKE_UP_DETECTED	= 0
}TJA1100_WAKEUP_t;

#define TJA1100_WU_MASK   (0x4000)   // bit [14]
#define TJA1100_WU_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1100_WUR_WAKE_UP_REQUEST_DETECTED	= 1,
  TJA1100_WUR_NO_WAKE_UP_REQUEST_DETECTED	= 0
}TJA1100_WUR_RECEIVED_t;

#define TJA1100_WUR_MASK   (0x2000)   // bit [13]
#define TJA1100_WUR_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1100_LPSR_LPS_CODE_GROUPS_RECEIVED	= 1,
  TJA1100_LPSR_NO_LPS_CODE_GROUPS_RECEIVED	= 0
}TJA1100_LPS_RECEIVED_t;

#define TJA1100_LPSR_MASK   (0x1000)   // bit [12]
#define TJA1100_LPSR_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_PHYIF_PHY_INITIALIZATION_ERROR_DETECTED	= 1,
  TJA1100_PHYIF_NO_PHY_INITIALIZATION_ERROR	= 0
}TJA1100_PHY_INIT_FAIL_t;

#define TJA1100_PHYIF_MASK   (0x800)   // bit [11]
#define TJA1100_PHYIF_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_LSF_LINK_STATUS_CHANGED_FROM_OK_TO_FAIL	= 1,
  TJA1100_LSF_NO_CHANGE_OF_LINK_STATUS	= 0
}TJA1100_LINK_STATUS_FAIL_t;

#define TJA1100_LSF_MASK   (0x400)   // bit [10]
#define TJA1100_LSF_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_LSU_LINK_STATUS_CHANGED_FROM_FAIL_TO_OK	= 1,
  TJA1100_LSU_NO_CHANGE_OF_LINK_STATUS	= 0
}TJA1100_LINK_STATUS_UP_t;

#define TJA1100_LSU_MASK   (0x200)   // bit [9]
#define TJA1100_LSU_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1100_SYMBE_SYMBOL_ERROR_DETECTED	= 1,
  TJA1100_SYMBE_NO_SYMBOL_ERROR_DETECTED	= 0
}TJA1100_SYM_ERROR_t;

#define TJA1100_SYMBE_MASK   (0x100)   // bit [8]
#define TJA1100_SYMBE_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1100_TF_TRAINING_PHASE_FAILURE_DETECTED	= 1,
  TJA1100_TF_NO_TRAINING_PHASE_FAILURE_DETECTED	= 0
}TJA1100_TRAINING_FAILED_t;

#define TJA1100_TF_MASK   (0x80)   // bit [7]
#define TJA1100_TF_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1100_SNRW_SNR_VALUE_BELOW_WARNING_LIMIT	= 1,
  TJA1100_SNRW_SNR_VALUE_ABOVE_WARNING_LIMIT	= 0
}TJA1100_SNR_WARNING_t;

#define TJA1100_SNRW_MASK   (0x40)   // bit [6]
#define TJA1100_SNRW_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1100_CTRLE_SMI_CONTROL_ERROR_DETECTED	= 1,
  TJA1100_CTRLE_NO_SMI_CONTROL_ERROR_DETECTED	= 0
}TJA1100_CONTROL_ERROR_t;

#define TJA1100_CTRLE_MASK   (0x20)   // bit [5]
#define TJA1100_CTRLE_SHIFT  (5)
//--------------------------------------
typedef enum
{
  TJA1100_TXEC_TXEN_CLAMPING_DETECTED	= 1,
  TJA1100_TXEC_NO_TXEN_CLAMPING_DETECTED	= 0
}TJA1100_TXEN_CLAMPED_t;

#define TJA1100_TXEC_MASK   (0x10)   // bit [4]
#define TJA1100_TXEC_SHIFT  (4)
//--------------------------------------
typedef enum
{
  TJA1100_UVE_UNDERVOLTAGE_DETECTED	= 1,
  TJA1100_UVE_NO_UNDERVOLTAGE_DETECTED	= 0
}TJA1100_UV_ERROR_t;

#define TJA1100_UVE_MASK   (0x08)   // bit [3]
#define TJA1100_UVE_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1100_UVR_UNDERVOLTAGE_RECOVERY_DETECTED	= 1,
  TJA1100_UVR_NO_UNDERVOLTAGE_RECOVERY	= 0
}TJA1100_UV_RECOVERY_t;

#define TJA1100_UVR_MASK   (0x04)   // bit [2]
#define TJA1100_UVR_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1100_TER_OVERTEMPERATURE_ERROR_DETECTED	= 1,
  TJA1100_TER_NO_OVERTEMPERATURE_ERROR_DETECTED	= 0
}TJA1100_TEMP_ERROR_t;

#define TJA1100_TER_MASK   (0x02)   // bit [1]
#define TJA1100_TER_SHIFT  (1)
//--------------------------------------
typedef enum
{
  TJA1100_SLPABRT_SLEEP_TRANSITION_ABORTED	= 1,
  TJA1100_SLPABRT_SLEEP_TRANSITION_NOT_ABORTED	= 0
}TJA1100_SLEEP_ABORT_t;

#define TJA1100_SLPABRT_MASK   (0x01)   // bit [0]
#define TJA1100_SLPABRT_SHIFT  (0)

//---------------------------------------------------
// register 0x16
//---------------------------------------------------
#define TJA1100_INTERRUPT_MASK_REG      (0x16)
#define TJA1100_INTERRUPT_MASK_REG_MASK (0xFFFF)
//--------------------------------------
typedef enum
{
  TJA1100_POEN_PWON_INTERRUPT_ENABLED	= 1,
  TJA1100_POEN_PWON_INTERRUPT_DISABLED	= 0
}TJA1100_PWON_EN_t;

#define TJA1100_POEN_MASK   (0x8000)   // bit [15]
#define TJA1100_POEN_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_WUEN_WAKEUP_INTERRUPT_ENABLED	= 1,
  TJA1100_WUEN_WAKEUP_INTERRUPT_DISABLED	= 0
}TJA1100_WAKEUP_EN_t;

#define TJA1100_WUEN_MASK   (0x4000)   // bit [14]
#define TJA1100_WUEN_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1100_WUREN_WAKEUP_INTERRUPT_ENABLED	= 1,
  TJA1100_WUREN_WAKEUP_INTERRUPT_DISABLED	= 0
}TJA1100_WUR_RECEIVED_EN_t;

#define TJA1100_WUREN_MASK   (0x2000)   // bit [13]
#define TJA1100_WUREN_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1100_LPSREN_LPS_RECEIVED_INTERRUPT_ENABLED	= 1,
  TJA1100_LPSREN_LPS_RECEIVED_INTERRUPT_DISABLED	= 0
}TJA1100_LPS_RECEIVED_EN_t;

#define TJA1100_LPSREN_MASK   (0x1000)   // bit [12]
#define TJA1100_LPSREN_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_PHYIFEN_PHY_INIT_FAIL_INTERRUPT_ENABLED	= 1,
  TJA1100_PHYIFEN_PHY_INIT_FAIL_INTERRUPT_DISABLED	= 0
}TJA1100_PHY_INIT_FAIL_EN_t;

#define TJA1100_PHYIFEN_MASK   (0x800)   // bit [11]
#define TJA1100_PHYIFEN_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_LSFEN_LINK_STATUS_FAIL_INTERRUPT_ENABLED	= 1,
  TJA1100_LSFEN_LINK_STATUS_FAIL_INTERRUPT_DISABLED	= 0
}TJA1100_LINK_STATUS_FAIL_EN_t;

#define TJA1100_LSFEN_MASK   (0x400)   // bit [10]
#define TJA1100_LSFEN_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_LSUEN_LINK_STATUS_UP_INTERRUPT_ENABLED	= 1,
  TJA1100_LSUEN_LINK_STATUS_UP_INTERRUPT_DISABLED	= 0
}TJA1100_LINK_STATUS_UP_EN_t;

#define TJA1100_LSUEN_MASK   (0x200)   // bit [9]
#define TJA1100_LSUEN_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1100_SEEN_SYM_ERROR_INTERRUPT_ENABLED	= 1,
  TJA1100_SEEN_SYM_ERROR_INTERRUPT_DISABLED	= 0
}TJA1100_SYM_ERROR_EN_t;

#define TJA1100_SEEN_MASK   (0x100)   // bit [8]
#define TJA1100_SEEN_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1100_TFEN_TRAINING_FAILED_INTERRUPT_ENABLED	= 1,
  TJA1100_TFEN_TRAINING_FAILED_INTERRUPT_DISABLED	= 0
}TJA1100_TRAINING_FAILED_EN_t;

#define TJA1100_TFEN_MASK   (0x80)   // bit [7]
#define TJA1100_TFEN_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1100_SNWEN_SNR_WARNING_INTERRUPT_ENABLED	= 1,
  TJA1100_SNWEN_SNR_WARNING_INTERRUPT_DISABLED	= 0
}TJA1100_SNR_WARNING_EN_t;

#define TJA1100_SNWEN_MASK   (0x40)   // bit [6]
#define TJA1100_SNWEN_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1100_CTRLEREN_CONTROL_ERROR_INTERRUPT_ENABLED	= 1,
  TJA1100_CTRLEREN_CONTROL_ERROR_INTERRUPT_DISABLED	= 0
}TJA1100_CONTROL_ERROR_EN_t;

#define TJA1100_CTRLEREN_MASK   (0x20)   // bit [5]
#define TJA1100_CTRLEREN_SHIFT  (5)
//--------------------------------------
typedef enum
{
  TJA1100_TXECEN_TXEN_CLAMPED_INTERRUPT_ENABLED	= 1,
  TJA1100_TXECEN_TXEN_CLAMPED_INTERRUPT_DISABLED	= 0
}TJA1100_TXEN_CLAMPED_EN_t;

#define TJA1100_TXECEN_MASK   (0x10)   // bit [4]
#define TJA1100_TXECEN_SHIFT  (4)
//--------------------------------------
typedef enum
{
  TJA1100_UVEEN_UV_ERROR_INTERRUPT_ENABLED	= 1,
  TJA1100_UVEEN_UV_ERROR_INTERRUPT_DISABLED	= 0
}TJA1100_UV_ERROR_EN_t;

#define TJA1100_UVEEN_MASK   (0x08)   // bit [3]
#define TJA1100_UVEEN_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1100_UVREN_UV_RECOVERY_INTERRUPT_ENABLED	= 1,
  TJA1100_UVREN_UV_RECOVERY_INTERRUPT_DISABLED	= 0
}TJA1100_UV_RECOVERY_EN_t;

#define TJA1100_UVREN_MASK   (0x04)   // bit [2]
#define TJA1100_UVREN_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1100_TEREN_TEMP_ERROR_INTERRUPT_ENABLED	= 1,
  TJA1100_TEREN_TEMP_ERROR_INTERRUPT_DISABLED	= 0
}TJA1100_TEMP_ERROR_EN_t;

#define TJA1100_TEREN_MASK   (0x02)   // bit [1]
#define TJA1100_TEREN_SHIFT  (1)
//--------------------------------------
typedef enum
{
  TJA1100_SLPABRTEN_SLEEP_TRANSITION_ABORTED_INTERRUPT_ENABLED	= 1,
  TJA1100_SLPABRTEN_SLEEP_TRANSITION_ABORTED_INTERRUPT_DISABLED	= 0
}TJA1100_SLEEP_ABORT_EN_t;

#define TJA1100_SLPABRTEN_MASK   (0x01)   // bit [0]
#define TJA1100_SLPABRTEN_SHIFT  (0)

//---------------------------------------------------
// register 0x17
//---------------------------------------------------
#define TJA1100_COMMUNICATION_STATUS_REG      (0x17)
#define TJA1100_COMMUNICATION_STATUS_REG_MASK (0xFFFF)
//--------------------------------------
typedef enum
{
  TJA1100_LU_OK	= 1,
  TJA1100_LU_FAIL	= 0
}TJA1100_LINK_UP_t;

#define TJA1100_LU_MASK   (0x8000)   // bit [15]
#define TJA1100_LU_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_TXM_TRANSMITTER_DISABLED	= 0,
  TJA1100_TXM_TX_MODE_SEND_N	= 1,
  TJA1100_TXM_TX_MODE_SEND_I	= 2,
  TJA1100_TXM_TX_MODE_SEND_Z	= 3
}TJA1100_TX_MODE_t;

#define TJA1100_TXM_MASK   (0x6000)   // bit [14:13]
#define TJA1100_TXM_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1100_LRS_LOC_RCVR_STATUS_IS_OK	= 1,
  TJA1100_LRS_LOC_RCVR_STATUS_IS_NOT_OK_SINCE_LAST_READ	= 0
}TJA1100_LOC_RCVR_STATUS_t;

#define TJA1100_LRS_MASK   (0x1000)   // bit [12]
#define TJA1100_LRS_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_RRS_REM_RCVR_STATUS_IS_OK	= 1,
  TJA1100_RRS_REM_RCVR_STATUS_IS_NOT_OK_SINCE_LAST_READ	= 0
}TJA1100_REM_RCVR_STATUS_t;

#define TJA1100_RRS_MASK   (0x800)   // bit [11]
#define TJA1100_RRS_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_SCRL_DESCRAMBLER_LOCKED	= 1,
  TJA1100_SCRL_DESCRAMBLER_UNLOCKED	= 0
}TJA1100_SCR_LOCKED_t;

#define TJA1100_SCRL_MASK   (0x400)   // bit [10]
#define TJA1100_SCRL_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_SSDE_SSD_ERROR_DETECTED_SINCE_LAST_READ	= 1,
  TJA1100_SSDE_NO_SSD_ERROR_DETECTED	= 0
}TJA1100_SSD_ERROR_t;

#define TJA1100_SSDE_MASK   (0x200)   // bit [9]
#define TJA1100_SSDE_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1100_ESDE_ESD_ERROR_DETECTED_SINCE_LAST_READ	= 1,
  TJA1100_ESDE_NO_ESD_ERROR_DETECTED	= 0
}TJA1100_ESD_ERROR_t;

#define TJA1100_ESDE_MASK   (0x100)   // bit [8]
#define TJA1100_ESDE_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1100_SNR_NO_SN_RATIO_VALUE_AVAILABLE	= 0,
  TJA1100_SNR_CLASS_A_SN_RATIO	= 1,
  TJA1100_SNR_CLASS_B_SN_RATIO	= 2,
  TJA1100_SNR_CLASS_C_SN_RATIO	= 3,
  TJA1100_SNR_CLASS_D_SN_RATIO	= 4,
  TJA1100_SNR_CLASS_E_SN_RATIO	= 5,
  TJA1100_SNR_CLASS_F_SN_RATIO	= 6,
  TJA1100_SNR_CLASS_G_SN_RATIO	= 7
}TJA1100_SNR_t;

#define TJA1100_SNR_MASK   (0xE0)   // bit [7:5]
#define TJA1100_SNR_SHIFT  (5)
//--------------------------------------
typedef enum
{
  TJA1100_RXE_RECEIVE_ERROR_DETECTED_SINCE_LAST_READ	= 1,
  TJA1100_RXE_NO_RECEIVE_ERROR_DETECTED	= 0
}TJA1100_RECEIVE_ERROR_t;

#define TJA1100_RXE_MASK   (0x10)   // bit [4]
#define TJA1100_RXE_SHIFT  (4)
//--------------------------------------
typedef enum
{
  TJA1100_TXE_TRANSMIT_ERROR_CODE_RECEIVED_SINCE_LAST_READ	= 1,
  TJA1100_TXE_NO_TRANSMIT_ERROR_CODE_RECEIVED	= 0
}TJA1100_TRANSMIT_ERROR_t;

#define TJA1100_TXE_MASK   (0x08)   // bit [3]
#define TJA1100_TXE_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1100_PHYS_PHY_IDLE	= 0,
  TJA1100_PHYS_PHY_INIT	= 1,
  TJA1100_PHYS_PHY_CONFIG	= 2,
  TJA1100_PHYS_PHY_OFFLINE	= 3,
  TJA1100_PHYS_PHY_ACTIVE	= 4,
  TJA1100_PHYS_PHY_ISOLATE	= 5,
  TJA1100_PHYS_PHY_CABLE_TEST	= 6,
  TJA1100_PHYS_PHY_TESTMODE	= 7
}TJA1100_PHY_STATE_t;

#define TJA1100_PHYS_MASK   (0x07)   // bit [2:0]
#define TJA1100_PHYS_SHIFT  (0)

//---------------------------------------------------
// register 0x18
//---------------------------------------------------
#define TJA1100_GENERAL_STATUS_REG      (0x18)
#define TJA1100_GENERAL_STATUS_REG_MASK (0xFEF8)
//--------------------------------------
typedef enum
{
  TJA1100_INTS_UNMASKED_INTERRUPT_CURRENTLY_ACTIVE	= 1,
  TJA1100_INTS_ALL_INTERRUPTS_CLEARED	= 0
}TJA1100_INT_STATUS_t;

#define TJA1100_INTS_MASK   (0x8000)   // bit [15]
#define TJA1100_INTS_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_PLLL_PLL_STABLE_AND_LOCKED	= 1,
  TJA1100_PLLL_PLL_UNSTABLE_AND_NOT_LOCKED	= 0
}TJA1100_PLL_LOCKED_t;

#define TJA1100_PLLL_MASK   (0x4000)   // bit [14]
#define TJA1100_PLLL_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1100_LWU_LOCAL_WAKEUP_DETECTED	= 1,
  TJA1100_LWU_NO_LOCAL_WAKEUP_DETECTED	= 0
}TJA1100_LOCAL_WU_t;

#define TJA1100_LWU_MASK   (0x2000)   // bit [13]
#define TJA1100_LWU_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1100_RWU_REMOTE_WAKEUP_DETECTED	= 1,
  TJA1100_RWU_NO_REMOTE_WAKEUP_DETECTED	= 0
}TJA1100_REMOTE_WU_t;

#define TJA1100_RWU_MASK   (0x1000)   // bit [12]
#define TJA1100_RWU_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_DDWU_DATA_DETECTED_IN_SLEEP_REQUEST	= 1,
  TJA1100_DDWU_NO_DATA_DETECTED_IN_SLEEP_REQUEST	= 0
}TJA1100_DATA_DET_WU_t;

#define TJA1100_DDWU_MASK   (0x800)   // bit [11]
#define TJA1100_DDWU_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_ENS_EN_WAS_LOW_SINCE_LAST_READ	= 1,
  TJA1100_ENS_EN_NOT_LOW	= 0
}TJA1100_EN_STATUS_t;

#define TJA1100_ENS_MASK   (0x400)   // bit [10]
#define TJA1100_ENS_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_RSTS_HARDWARE_RESET_DETECTED_SINCE_LAST_READ	= 1,
  TJA1100_RSTS_NO_HARDWARE_RESET_DETECTED	= 0
}TJA1100_RESET_STATUS_t;

#define TJA1100_RSTS_MASK   (0x200)   // bit [9]
#define TJA1100_RSTS_SHIFT  (9)
//--------------------------------------
typedef unsigned short TJA1100_LINKFAIL_COUNT_t;

#define TJA1100_LFCNT_MASK   (0xF8)   // bit [7:3]
#define TJA1100_LFCNT_SHIFT  (3)

//---------------------------------------------------
// register 0x19
//---------------------------------------------------
#define TJA1100_EXTERNAL_STATUS_REG      (0x19)
#define TJA1100_EXTERNAL_STATUS_REG_MASK (0x7FE0)
//--------------------------------------
typedef enum
{
  TJA1100_UV3V3S_UNDERVOLTAGE_DETECTED_ON_VDDA_3V3	= 1,
  TJA1100_UV3V3S_NO_UNDERVOLTAGE_DETECTED_ON_VDDA_3V3	= 0
}TJA1100_UV_VDDA_3V3_t;

#define TJA1100_UV3V3S_MASK   (0x4000)   // bit [14]
#define TJA1100_UV3V3S_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1100_UVD1V8S_UNDERVOLTAGE_DETECTED_ON_VDDD_1V8	= 1,
  TJA1100_UVD1V8S_NO_UNDERVOLTAGE_DETECTED_ON_VDDD_1V8	= 0
}TJA1100_UV_VDDD_1V8_t;

#define TJA1100_UVD1V8S_MASK   (0x2000)   // bit [13]
#define TJA1100_UVD1V8S_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1100_UVA1V8S_UNDERVOLTAGE_DETECTED_ON_VDDA_1V8	= 1,
  TJA1100_UVA1V8S_NO_UNDERVOLTAGE_DETECTED_ON_VDDA_1V8	= 0
}TJA1100_UV_VDDA_1V8_t;

#define TJA1100_UVA1V8S_MASK   (0x1000)   // bit [12]
#define TJA1100_UVA1V8S_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_UVIOS_UNDERVOLTAGE_DETECTED_ON_VDDIO1_VDDIO2	= 1,
  TJA1100_UVIOS_NO_UNDERVOLTAGE_DETECTED_ON_VDDIO1_VDDIO2	= 0
}TJA1100_UV_VDDIO_t;

#define TJA1100_UVIOS_MASK   (0x800)   // bit [11]
#define TJA1100_UVIOS_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_TEMPHS_TEMPERATURE_ABOVE_HIGH_LEVEL	= 1,
  TJA1100_TEMPHS_TEMPERATURE_BELOW_HIGH_LEVEL	= 0
}TJA1100_TEMP_HIGH_t;

#define TJA1100_TEMPHS_MASK   (0x400)   // bit [10]
#define TJA1100_TEMPHS_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_TEMPWS_TEMPERATURE_ABOVE_WARNING_LEVEL	= 1,
  TJA1100_TEMPWS_TEMPERATURE_BELOW_WARNING_LEVEL	= 0
}TJA1100_TEMP_WARN_t;

#define TJA1100_TEMPWS_MASK   (0x200)   // bit [9]
#define TJA1100_TEMPWS_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1100_SDS_SHORT_CIRCUIT_DETECTED_SINCE_LAST_READ	= 1,
  TJA1100_SDS_NO_SHORT_CIRCUIT_DETECTED	= 0
}TJA1100_SHORT_DETECT_t;

#define TJA1100_SDS_MASK   (0x100)   // bit [8]
#define TJA1100_SDS_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1100_ODS_OPEN_DETECTED_SINCE_LAST_READ	= 1,
  TJA1100_ODS_NO_OPEN_DETECTED	= 0
}TJA1100_OPEN_DETECT_t;

#define TJA1100_ODS_MASK   (0x80)   // bit [7]
#define TJA1100_ODS_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1100_PDMS_POLARITY_INVERSION_AT_MDI	= 1,
  TJA1100_PDMS_NO_POLARITY_INVERSION_AT_MDI_DETECTED	= 0
}TJA1100_POLARITY_DETECTOR_MDI_t;

#define TJA1100_PDMS_MASK   (0x40)   // bit [6]
#define TJA1100_PDMS_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1100_IDS_INTERLEAVING_TERNARY_SYMBOLS_DETECTED	= 1,
  TJA1100_IDS_NO_INTERLEAVING_TERNARY_SYMBOLS_DETECTED	= 0
}TJA1100_INTERLEAVE_DETECT_t;

#define TJA1100_IDS_MASK   (0x20)   // bit [5]
#define TJA1100_IDS_SHIFT  (5)

//---------------------------------------------------
// register 0x1A
//---------------------------------------------------
#define TJA1100_LINK_FAIL_COUNTER_REG      (0x1A)
#define TJA1100_LINK_FAIL_COUNTER_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA1100_LOC_RCVR_COUNTER_t;

#define TJA1100_LRC_MASK   (0xFF00)   // bit [15:8]
#define TJA1100_LRC_SHIFT  (8)
//--------------------------------------
typedef unsigned short TJA1100_REM_RCVR_COUNTER_t;

#define TJA1100_RRC_MASK   (0xFF)   // bit [7:0]
#define TJA1100_RRC_SHIFT  (0)

/*---------------------------------------------------
 * Diagnostics definitions
 * --------------------------------------------------
 * */

# ifndef ROUTINE_RESERVED 
#  define ROUTINE_RESERVED (0U)
# endif 
# ifndef ROUTINE_ACTIVE 
#  define ROUTINE_ACTIVE (1U)
# endif 
# ifndef ROUTINE_NOTACTIVEORFINISHEDCORRECTLY 
#  define ROUTINE_NOTACTIVEORFINISHEDCORRECTLY (2U)
# endif 
# ifndef ROUTINE_ABORTED 
#  define ROUTINE_ABORTED (3U)
# endif
# ifndef ROUTINE_INCORRECTRESULTS 
#  define ROUTINE_INCORRECTRESULTS (0U)
# endif 
# ifndef ROUTINE_NORESULTSAVAILABLE 
#  define ROUTINE_NORESULTSAVAILABLE (1U)
# endif 
# ifndef ROUTINE_SYSDEFINERESULT 
#  define ROUTINE_SYSDEFINERESULT (2U)
# endif 
# ifndef ROUTINE_CORRECTRESULTS 
#  define ROUTINE_CORRECTRESULTS (65535U)
# endif

/* BR Test Options */
#define BR_TESTMODE_NORMAL_OPERATION                (0u)
#define BR_TESTMODE_TRANSMIT_DROOP_TEST             (1u)
#define BR_TESTMODE_TRANSMIT_JITTER_MASTER          (2u)
#define BR_TESTMODE_TRANSMIT_JITTER_SLAVE           (3u)
#define BR_TESTMODE_TRANSMITTER_DISTORTION_TEST     (4u)
#define BR_TESTMODE_NORMAL_OPERATION_FULL_POWER     (5u)
#define BR_TESTMODE_CONNECTIVITY_CHECK              (6u)
#define BR_RESET_IP_COUNTER_WRONG_IPV6_ADDRESSES    (7u)
#define BR_RESET_IP_COUNTER_WRONG_VLANS             (8u)
#define BR_RESET_IP_COUNTER_WRONG_TCP_PORTS         (9u)
#define BR_RESET_IP_COUNTER_WRONG_UDP_PORTS         (10u)

#define HMI0_NAME                    "hmi0"
#define EMAC1_NAME                   "emac1"
#define IPV6_ADDRESS_BR              "FD53:7CB8:0383:0003::004F"
#define IPV4_ADDRESS_BR              "192.168.10.100"
#define MAC_LEN_B                    (6U)
#define IF_CMD_LEN_BUF               (50U)
#define SSH_MAC_PROD_PAGESIZE        (96U)
#define SSH_MAC_PROD_OFFSET	         (0x03FC0020U)
/* default MAC (8A:23:FE:00:00:02) is specified in the item ALM_Specification 820453  */
#define BR_MAC_ADDRESS_DEFAULT       {0x8a,0x23,0xfe,0x00,0x00,0x02};
#define BR_PING6_TIMEOUT_REQUESTED (uint32_t)(5000u) /*Ping6 timeout requested by AUDI, Issue118524 message msg1185411.*/

#define NVMM_DIAG_CODING  	     	"/nvmm/diag_coding.bin"
#define NVMM_DIAG_VLAN  	     	"/nvmm/diag_vlan.bin"
#define PADDING_GAP8_1				13U
#define MASK_SET_VLAN			 	0x01

#define BR_PING6_PARAM               "-w1000 -c1 "
#define BR_MAX_PING_HOSTS            (30U)

typedef struct BR_DIAG_PING_DATA
{
	uint8_t IPv6_address[16];
	uint8_t result;
	uint8_t paddingGap8_1;
	uint16_t paddingGap16_2;
} s_BR_DIAG_PING_DATA;

#define PHY_INIT_FAIL_MASK 			(0x800U)	
#define DRV_CYCLE_CNT   			"/nvmm/br_drvcycl_cnt"
#define MAX_CONSQ_DOS				(10U)
#define MAX_BR_INIT_FAIL			(10U)
#define MAX_DRV_SESSIONS			(5U)

/* Reporter ID - WARNING: SWCID_PF_OS unreachable and defined locally!*/
#  ifndef SWCID_PF_OS
#   define SWCID_PF_OS (235U)
#  endif

typedef enum
{
	BR_BITMASK_ERR1 = (0x01U),
	BR_BITMASK_ERR2 = (0x02U),
	BR_BITMASK_ERR3 = (0x04U),
	BR_BITMASK_ERR4 = (0x08U),
	BR_BITMASK_ERR5 = (0x10U),
	BR_BITMASK_ERR6 = (0x20U),
	
}BR_BITMASK_ERROR;

/** \struct BRDiagData
*  \brief description
*  \var :status_routine
*  status for routine control - DSC specific
*  \var :status_val
*  status of the value - DSC specific
*  \var :ping_response
*  response time of a executed ping test (connectivity check)
*  \var :br_com_error
*  signal communication errors to the DSC
*  \var :ip_counter_dropped_messages
*  Ip_counter_dropped_messages_0x014E - counter of dropped messages from the network stack
*  \var :ip_counter_wrong_vlans
*  Ip_counter_wrong_vlans_0x0A2B - counter for messages sent from a unexpected VLAN
*  \var :ip_counter_wrong_ipv6_addresses
*  Ip_counter_wrong_ipv6_addresses_0x0A2C - counter for messages sent from an unexpected IP
*  \var :ip_counter_wrong_tcp_ports
*  Ip_counter_wrong_tcp_ports_0x0A2E - counter for TCP messages (unexpected dest. port)
*  \var :ip_counter_wrong_udp_ports
*  Ip_counter_wrong_udp_ports_0x0A2F - counter for UDP messages (unexpected dest. port)
*  \var :ethernet_signalquality
*  represents the quality of the link read from the chip
*  \var :ethernet_link_lost_counter
*  Ethernet_link_lost_counter_0x010E - counter for lost links
*  \var :ethernet_CRC_error_counter
*  Ethernet_CRC_error_counter_0x010F - counter for explicitly dropped messages because of crc errors (FCS)
*/
typedef struct BRDiagData{
    uint32_t        status_routine;
    uint32_t        status_val;
    uint32_t   		ping_response;
    uint16_t		br_com_error;
    uint16_t		ip_dropped_msg;
    uint16_t    	cnt_wrong_VLAN;
    uint16_t    	cnt_wrong_IP;
    uint16_t    	cnt_wrong_TCPport;
    uint16_t    	cnt_wrong_UDPport;
    uint8_t         ethernet_signalquality;
    uint8_t		    eth_link_lost_cnt;
    uint8_t         eht_crc_err_cnt;
    uint8_t			paddingGap8_1;
}s_BR_DIAG_DATA;

/** \struct BR_Info
*  \brief description
*  \var int 	if_nr;
*  - number of the interface hmi
*  \var uint16  br_com_error
*  - signal communication errors to the EthCom SWC
*  \var char 	br_ip[46];
*  - ipv6 of the interface
*  */
typedef struct BR_Info{
	int 	   if_nr;
    uint16_t   br_com_error;
	char 	   br_ip[46];
}s_BRIF_INFO;


#endif /* VXBBROADRPHY_H_ */
