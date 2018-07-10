/*
 *  \file 
 *      moduleOneHandleRoutines.h
 *
 *  \brief 
 *      Header file for moduleOneHandleRoutines.c
 *      Includes macros for routine state and result
 *
 *  \version
 *       [7-May-2018] [Stefan Masalusic] Initial creation
 *       
 *  \history
 *       [24-May-2018] Added function descriptions
 *       [09-Jul-2018] Added macros
 */

#ifndef MODULEONEHANDLEROUTINES_H_
#define MODULEONEHANDLEROUTINES_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
#define TASK_DELAY_1000MS (uint32_t) (100U)
#define PC_IPV6         "fd53:7cb8:383:3::73"
#define NUM_OF_PACKETS  ((int8_t) 4)

/* Registers */
#define EXTENDED_CONTROL_REGISTER ((uint32_t) (0x11))
#define CONFIGURATION_REGISTER_1  ((uint32_t) (0x12))
#define GENERAL_STATUS_REG    (0x18)
#define LINK_FAIL_COUNTER_REG (0x1A)

/* Link fail masks */
#define REM_RCVR_CNT_MASK  (0x00FFU)
#define LOC_RCVR_CNT_MASK  (0xFF00U)
#define LINK_FAIL_CNT_MASK (0x00F8U)

/* Routine states */
#define ROUTINE_IDLE     (0U)
#define ROUTINE_ACTIVE   (1U)
#define ROUTINE_FINISHED (2U)
#define ROUTINE_ABORTED  (3U)

/* Routine results */
#define ROUTINE_INCORRECTRESULTS (0U)
#define ROUTINE_NORESULT         (2U)
#define ROUTINE_CORRECTRESULTS   (1U)

#define READ_LINK_FAIL    (7U)
#define PING_TEST_ROUTINE (6U)
#define NORMAL_OP         (0U)

#define SHIFT_SIX (6U)
#define SHIFT_TWO (2U)

#define CONFIGURATION_REGISTER_ACCESS_ENABLED (1U)

/************************************************************************
 * EXTERNAL VARIABLES
 ***********************************************************************/
extern MSG_Q_ID routinesMsgQId;

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function gets number of routine which will be called
 *        and calls _testModes(int routine_trigger).
 */
void module1_GetRoutineNum(void);

#endif /* MODULEONEHANDLEROUTINES_H_ */
