/*
 *  \file 
 *      moduleTwoRTP.h
 *
 *  \brief 
 *      Header file for moduleTwoRTP.c
 *      Includes macros for task and msgQueue
 *
 *  \version
 *       [13-Jun-2018] [Stefan Masalusic] Initial creation
 *       
 *  \history
 *       [15-Jun-2018]  Added function descriptions
 *       [09-Jul-2018] Added macros
 */

#ifndef MODULETWOHANDLEROUTINES_H_
#define MODULETWOHANDLEROUTINES_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
/* State machine defines */
#define STATEMACHINE_WAIT_FOR_COMMAND   ((uint8_t) 1U)
#define STATEMACHINE_SEND_FILE          ((uint8_t) 2U)
#define STATEMACHINE_START_ROUTINE      ((uint8_t) 3U)
#define STATEMACHINE_SEND_MSG_QUEUE     ((uint8_t) 4U)
#define STATEMACHINE_SEND_SHARED_MEMORY ((uint8_t) 5U)
#define STATEMACHINE_EXIT_BG_TASK       ((uint8_t) 6U)

#define SOCKET_ERROR ((int8_t) -1)

/* Command defines */
#define EXIT_BG_TASK       ((uint32_t) 0U)
#define SEND_FILE          ((uint32_t) 1U)
#define START_ROUTINE      ((uint32_t) 2U)
#define SEND_MSG_QUEUE     ((uint32_t) 3U)
#define SEND_SHARED_MEMORY ((uint32_t) 4U)


#define ntohl_br(x)      ((((x) & 0x000000ffU) << 24U) |   \
                         (((x) & 0x0000ff00U) <<  8U) |   \
                         (((x) & 0x00ff0000U) >>  8U) |   \
                         (((x) & 0xff000000U) >> 24U))

/************************************************************************
 * EXTERNAL VARIABLES
 ***********************************************************************/
extern uint8_t _changeState; 
extern uint8_t _msg;

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function is simple switch-case which acts like state-machine and calls
 *        functions or sends structs via socket.
 */
void processMessage(void);

#endif /* MODULETWOHANDLEROUTINES_H_ */
