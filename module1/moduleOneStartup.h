/*
 * moduleOneStartup.h
 *
 *  Created on: Jun 27, 2018
 *      Author: bura
 */

#ifndef MODULEONESTARTUP_H_
#define MODULEONESTARTUP_H_

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief Init function for eth phy chip interface.
 */
void module1_InitPhy(void);
/*
 * \brief This function creates two public message queues.
 *        One for sending diagnostic data to user space, and other
 *        for calling different routines, e.g. ping...
 *        
 * \return OK if queues creating was successful, ERROR otherwise
 */
LOCAL STATUS _module1_CreateMsgQueues(void);
/** 
 * \brief Initial function for starting RTP task in user space.
 * \metric STAV1 10 Assembler instructions that tool can't handle.
 *
 * \return OK if successful, ERROR otherwise 
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
