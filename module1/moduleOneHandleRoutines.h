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
 *       [7-May-2018]  Added module1_GetRoutineNum function
 *       [9-May-2018]  Added _testModes, _pingRoutine and
 *                     _normalOperationTest functions    
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

/* Routine states */
#define ROUTINE_IDLE     (0U)
#define ROUTINE_ACTIVE   (1U)
#define ROUTINE_FINISHED (2U)
#define ROUTINE_ABORTED  (3U)

/* Routine results */
#define ROUTINE_INCORRECTRESULTS (0U)
#define ROUTINE_NORESULT         (2U)
#define ROUTINE_CORRECTRESULTS   (1U)

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
 * \return OK if successful, ERROR otherwise
 */
STATUS module1_GetRoutineNum(void);
/** 
 * \brief This function is used for activating test routines.
 * \param routine_trigger Number of routine to start
 */
LOCAL void _testModes(int routine_trigger);
/** 
 * \brief Routine used to ping PC when triggered
 * \return OK if successful, ERROR otherwise 
 */
LOCAL STATUS _pingRoutine(void);
/** 
 * \brief Routine for testing normal operation mode.
 * \param mode Number of routine mode
 */
LOCAL void _normalOperationTest(uint16_t mode);

#endif /* MODULEONEHANDLEROUTINES_H_ */
