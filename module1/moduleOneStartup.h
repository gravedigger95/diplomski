/*
 * moduleOneStartup.h
 *
 *  Created on: Jun 27, 2018
 *      Author: bura
 */

#ifndef MODULEONESTARTUP_H_
#define MODULEONESTARTUP_H_

typedef struct errorStruct
{
    char timestamp[26];
    uint8_t id;
    char description[50];
    uint8_t padding;
}s_ERRORS;

/* Diagnostic data struct */
typedef struct diagnosticDataMsgQ
{
    uint8_t link_status; //basic status reg bit 2 0x1
    uint8_t link_control; //ext control reg bit 15 0x11
    uint8_t power_mode; //ext control reg bit [14:11] 0x11
    uint8_t loopback_mode; //ext control reg bit [4:3] 0x11
    uint8_t phy_init_fail; //interrupt status reg bit 11 0x15
    uint8_t wakeup; //interrupt status reg bit 14 0x15
    uint8_t link_status_fail; //interrupt status reg bit 10 0x15
    uint8_t link_status_up; //interrupt status reg bit 9 0x15
    uint8_t link_up; //comm status reg bit 15 0x17
    uint8_t tx_mode; //comm status reg bit [14:13] 0x17
    uint8_t loc_rcvr_status; //comm status reg bit 12 0x17
    uint8_t rem_rcvr_status; //comm status reg bit 11 0x17
    uint8_t signal_quality;

    uint16_t phy_id_reg1; //phy id reg 1 bit [15:0] 0x2
    uint8_t phy_state;
        
    s_ERRORS errors_array[4];
        
} s_DIAG_DATA;

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
