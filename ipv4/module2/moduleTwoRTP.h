/*
 * module2.h
 *
 *  Created on: Apr 26, 2018
 *      Author: bura
 */

#ifndef MODULE2_H_
#define MODULE2_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
/* Message queue defines */
#define MAX_MSG         ((uint8_t) 2U)
#define BUFLEN ((uint16_t) 512U)

#define NULL_PTR (void *) (0)
                         
#define TASK_DELAY_25MS (uint32_t) (25U)

#define STATEMACHINE_EXIT_BG_TASK ((uint8_t) 6U)

extern MSG_Q_ID routinesMsgQId;
extern MSG_Q_ID diagMsgQId;
extern MSG_Q_ID messages;

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function sends routine number to module 1 which activates
 *        appropriate routine
 * \param routineNum Number of desired routine
 * \return OK if successful, ERROR otherwise
 */
STATUS _module2_SetRoutineNum(int routineNum);
/** 
 * \brief This function is background task for communication with PC and
 *        triggering appropriate routines for testing.
 */
LOCAL void _backgroundTask(void);
/** 
 * \brief This function is used for initializing RTP module msg queues, shared memory
 *        and tasks. 
 */
LOCAL void _module2_init(void);

#endif /* MODULE2_H_ */
