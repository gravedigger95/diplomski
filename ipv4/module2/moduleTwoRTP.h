/*
 *  \file 
 *      moduleTwoRTP.h
 *
 *  \brief 
 *      Header file for moduleTwoRTP.c
 *      Includes macros for task and msgQueue
 *
 *  \version
 *       [28-May-2018] [Stefan Masalusic] Initial creation
 *       
 *  \history
 *       [7-Jun-2018]  Added function descriptions
 *       [09-Jul-2018] Added macros
 */

#ifndef MODULE2_H_
#define MODULE2_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
/* Message queue defines */
#define BUFLEN  ((uint16_t) 512U)

#define NULL_PTR (void *) (0)

/* Background task defines */
#define TASK_DELAY_250MS (uint32_t) (25U)
#define BG_TASK_PRIORITY (115)
#define BG_STACK_SIZE    (5000U)
#define RESTART (1U)
#define NO_RESTART 0

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/

#endif /* MODULE2_H_ */
