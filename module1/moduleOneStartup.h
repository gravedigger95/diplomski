/*
 *  \file 
 *      moduleOneStartup.h
 *
 *  \brief 
 *      Header file for moduleOneStartup.c
 *      Includes macros for task spawns and registers offsets
 *
 *  \version
 *       [19-Apr-2018] [Stefan Masalusic] Initial creation
 *       
 *  \history
 *       [24-May-2018] Added function descriptions
 *       [09-Jul-2018] Added macros
 */

#ifndef MODULEONESTARTUP_H_
#define MODULEONESTARTUP_H_

/* ------------------------------------------------------------------------- */
/* ------------------------------   Defines  ------------------------------- */
/* ------------------------------------------------------------------------- */
#define BYTES_NUM                       (0xFF)
#define CYCLONE_ADDRESS_REGISTER_OFFSET (0x10U)
#define CYCLONE_DATA_REGISTER_OFFSET    (0x14U)
#define RTPROCESS_TASK_PRIORITY         (207)
#define RTPROCESS_STACK_SIZE            (0x19000)
#define RTPROCESS_GLOBAL_SYMBOLS        (0x01)

#define DIAG_TASK_PRIORITY (202)
#define DIAG_STACK_SIZE    (2000)

#define ROUTINES_TASK_PRIORITY (204)
#define ROUTINES_STACK_SIZE    (100)

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief Init function for eth phy chip interface.
 */
void module1_InitPhy(void);
/** 
 * \brief Initial function for starting RTP task in user space.
 * \return OK if successful, ERROR otherwise
 * \retVal ERROR if rtpSpawn() function fails
 */
STATUS rtpModule(void);
/** 
 * \brief Functions for starting module 1 tasks for reading ETH PHY chip
 *        registers and retrieving test mode numbers.
 * \metric STAV1 13 Assembler instructions that tool can't handle.
 */
void module1_StartTasks(void);
/** 
 * \brief Configures hmi0 ethernet interface
 */
void module1_ConfigureEthInterface(void);
/** 
 * \brief Configures VLAN interface.
 */
void module1_ConfigureVLAN(void);

#endif /* MODULEONESTARTUP_H_ */
