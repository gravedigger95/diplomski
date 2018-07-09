/*
 * readEthPhy.h
 
   /* &&&&&&&&& Missing description for the file.  
 *
 *  Created on: Apr 26, 2018
 *      Author: bura
 
  /* &&&&&&&&& Missing "\version" field.  
 */
 
 /* &&&&&&&&& Please consider moving LOCAL function declarations from the .h file into corresponding .c file. */
 
  /* &&&&&&&&& File has to have Unix line endings. */
#ifndef READETHPHY_H_
#define READETHPHY_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
/* Registers base address + offsets and masks */
#define GMIIADDRESS     ((uint32_t) 0xFF702010U)
#define GMIIDATA        ((uint32_t) 0xFF702014U)
#define CLEAR_MASK      ((uint32_t) 0xFFFF0000U)
#define SET_READ_MASK   ((uint32_t) 0x00000001U)
#define SET_WRITE_MASK  ((uint32_t) 0x00000003U)
#define BIT_OFFSET      ((uint8_t) 6U)
/* Message queue defines */
#define MAX_MSG         ((uint8_t) 2U)
#define MAX_MSG_LEN     ((uint8_t) 8U)
/* Eth interface config params */
#define HOST_BR         "fd53:7cb8:383:2::4f"   // IPv6
#define MAC_BR          "8a:23:fe:0x00:0x00:02" // MAC
#define PC_IPV6         "fd53:7cb8:383:3::73"
/* Shared mem params */
#define SH_MEM_NAME     "/shMemModule1to2"
#define READ_BUFF_SIZE  ((int8_t) 6)
#define ERROR_BUFF_SIZE ((uint8_t) 6U)
#define NUM_OF_PACKETS  ((int8_t) 4)

/* Diagnostic data bit masks */
#define LINK_STATUS_MASK        ((uint32_t) 0x0004U)
#define LINK_CONTROL_MASK       ((uint32_t) 0x8000U)
#define POWER_MODE_MASK         ((uint32_t) 0x7800U)
#define LOOPBACK_MODE_MASK      ((uint32_t) 0x0018U)
#define PHY_FAIL_MASK           ((uint32_t) 0x0800U)
#define WAKEUP_MASK             ((uint32_t) 0x4000U)
#define LINK_STATUS_FAIL_MASK   ((uint32_t) 0x0400U)
#define LINK_STATUS_UP_MASK     ((uint32_t) 0x0200U)
#define LINK_UP_MASK            ((uint32_t) 0x8000U)
#define TX_MODE_MASK            ((uint32_t) 0x6000U)
#define LOC_RCVR_MASK           ((uint32_t) 0x1000U)
#define REM_RCVR_MASK           ((uint32_t) 0x0800U) 

/* Diagnostic data shm masks */
#define JABBER_DETECT_MASK  ((uint32_t) 0x0002U)
#define PHY_ID_REG2_MASK    ((uint32_t) 0xFC00U)
#define TYPE_NO_MASK        ((uint32_t) 0x03F0U)
#define REVISION_NO_MASK    ((uint32_t) 0x000FU)
#define PHY_ID_REG3_MASK    ((uint32_t) 0x00FFU)
#define INT_STATUS_MASK     ((uint32_t) 0x8000U)

#define BR_NULL_PTR     (void *) (0)/*&&&&&&&&& Unnecessary doubling the same define   */
#define NULL_PTR        (void *) (0)

#define TASK_DELAY_25MS (uint32_t) (25U) /*&&&&&&&&& Please change misleading macro name for task delay - it is 250ms dela */
#define TASK_DELAY_100MS (uint32_t) (100U)/*&&&&&&&&& Please change misleading macro name for task delay - it is 1000ms dela */

/* Registers */
#define BASIC_STATUS_REGISTER ((uint32_t) (0x1))
#define PHY_ID_REGISTER_1 ((uint32_t) (0x2))
#define PHY_ID_REGISTER_2 ((uint32_t) (0x3))
#define PHY_ID_REGISTER_3 ((uint32_t) (0x10))
#define GENERAL_STATUS_REGISTER ((uint32_t) (0x18))
#define EXTENDED_CONTROL_REGISTER ((uint32_t) (0x11))
#define INTERRUPT_SOURCE_REGISTER ((uint32_t) (0x15))
#define COMMUNICATION_STATUS_REGISTER ((uint32_t) (0x17))
#define CONFIGURATION_REGISTER_1 ((uint32_t) (0x12))

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

extern MSG_Q_ID diagMsgQId;

/* Phy address register */
extern volatile uint32_t * phyGmiiAddress;
/* Phy data register */
extern volatile uint32_t * phyGmiiData;

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief Function that reads registers and fill diag data structure
 * \metric STAV1 10 Loading data in msgQ struct. 
 */
LOCAL void _module1_ReadChipRegisters(void);
/** 
 * \brief This function reads TJA1100 address register 
 * 
 * \param regNumber Number of desired BroadRReach register
 * \return dataRead Data read from register
 */
uint32_t mdio_read_br(uint32_t regNumber);
/** 
 * \brief This function writes to TJA1100 address register 
 * \param regNumber Number of desired BroadRReach register
 * \param dataWrite Data to be written
 */
void mdio_write_br(uint32_t regNumber, uint16_t dataWrite);
/** 
 * \brief This is task function for module1ReadChipRegisters()
 *        used for reading TJA1100 registers and sending data to 
 *        diagMsgQ via diag_data_struct
 * \return OK if successful, ERROR otherwise
 */
void module1_ReadChipRegistersTask(void);
/** 
 * \brief This function takes pointer to allocated shared memory
 * \return OK if successful, ERROR otherwise 
 */
LOCAL STATUS _sharedMemAlloc(void);
/** 
 * \brief This function fills DIAG_SHM_DATA_t struct with diagnostic data 
 *        that is doesn't change often
 * \metric STAV1 10 Loading data in shMem structure.
 * \return OK if successful, ERROR otherwise 
 */
LOCAL STATUS _module1_FillSharedMem(void);
/** 
 * \brief This function opens shared memory in module 1 and allocates it
 * \return Pointer to allocated shared memory 
 */
LOCAL void * _module1_shMem_Alloc(const char * fname, size_t size);
/** 
 * \brief Function that gets time of error.
 * \metric STAV1 11 Library functions.
 */
LOCAL void _module1_getErrorTime(struct tm const * time_info, uint8_t pos);

#endif /* READETHPHY_H_ */
