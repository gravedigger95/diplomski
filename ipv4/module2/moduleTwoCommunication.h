/*
 * moduleTwoCommunication.h
 *
 *  Created on: Jun 27, 2018
 *      Author: bura
 */

#ifndef MODULETWOCOMMUNICATION_H_
#define MODULETWOCOMMUNICATION_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
#define NULL_PTR (void *) (0)
#define SH_MEM_NAME     "/shMemModule1to2"

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

typedef struct diagnosticDataShM
{
    uint8_t jabber_detect; //basic status reg bit 1 0x1
    uint16_t phy_id_reg1; //phy id reg 1 bit [15:0] 0x2
    uint8_t phy_id_reg2; //phy id reg 2 bit [15:10] 0x3
    uint8_t type_no; //phy id reg 2 bit [9:4] 0x3
    uint8_t revision_no; //phy id reg 2 bit [3:0] 0x3
    uint8_t phy_id_reg3; //phy id reg 3 bit [7:0] 0x10
    uint8_t int_status; //gen status reg bit 15 0x18
    
} s_DIAG_SHM_DATA;

/************************************************************************
 * EXTERNAL VARIABLES
 ***********************************************************************/
extern s_DIAG_SHM_DATA _diag_shm_struct;
extern s_DIAG_DATA _diag_data_struct_mod1;

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function periodically reads diagnostic msgQ and shared memory
 * \return OK if successful, ERROR otherwise
 */
STATUS _module2_ReadDiagMsgQ(void);
/** 
 * \brief This function opens shared memory in module 2 and allocates it
 * \param fname Name of shared memory
 * \param size Size of shared memory
 * \return Pointer to allocated shared memory 
 */
LOCAL void * _module2_shMem_open(const char * fname, size_t size);
/** 
 * \brief This function is used for checking if module 1 wrote correctly
 *        in shared memory
 * \return OK if successful, ERROR otherwise 
 */
LOCAL STATUS _module2_shMem_Check(void);
/** 
 * \brief This function opens shared memory in module 1 and allocates it
 * \return OK if successful, ERROR otherwise
 */
STATUS sharedMemAlloc_module2(void);

#endif /* MODULETWOCOMMUNICATION_H_ */
