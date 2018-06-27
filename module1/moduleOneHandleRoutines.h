/*
 * moduleOneHandleRoutines.h
 *
 *  Created on: Jun 27, 2018
 *      Author: bura
 */

#ifndef MODULEONEHANDLEROUTINES_H_
#define MODULEONEHANDLEROUTINES_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
#define TASK_DELAY_100MS (uint32_t) (100U)
#define PC_IPV6         "fd53:7cb8:383:3::73"
#define NUM_OF_PACKETS  ((int8_t) 4)

/* Registers */
#define EXTENDED_CONTROL_REGISTER ((uint32_t) (0x11))
#define CONFIGURATION_REGISTER_1 ((uint32_t) (0x12))

extern MSG_Q_ID routinesMsgQId;

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function gets number of routine which will be called
 * \return OK if successful, ERROR otherwise
 */
STATUS module1_GetRoutineNum(void);
/** 
 * \brief This function is used for activating desired routines.
 */
LOCAL void _testModes(int routine_trigger);
/** 
 * \brief Routine used to ping PC when triggered
 * \return OK if successful, ERROR otherwise 
 */
LOCAL STATUS _pingRoutine(void);
/** 
 * \brief This function sends routine number to module 1 which activates
 *        appropriate routine
 * \param routineNum Number of desired routine
 * \return OK if successful, ERROR otherwise
 */
LOCAL STATUS _module2_SetRoutineNum(uint8_t routineNum);

#endif /* MODULEONEHANDLEROUTINES_H_ */
