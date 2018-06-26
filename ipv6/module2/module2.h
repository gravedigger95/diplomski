/*
 * readEthPhy.h
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

/* Shared mem params */
#define SH_MEM_NAME     "/shMemModule1to2"
#define READ_BUFF_SIZE  ((int8_t) 6)
#define ERROR_BUFF_SIZE ((uint8_t) 6U)
#define NUM_OF_PACKETS  ((int8_t) 4)

#define BR_NULL_PTR     (void*)(0)

#define SWU_BR_SERVERPORT  29170
#define SWU_BR_CLIENTPORT  29171
#define SWUP_ZFAS_IP_ADDRESS "fd53:7cb8:383:3::4f"//zFAS
#define SWUP_MIB_ZR_IP_ADDRESS "fd53:7cb8:383:3::73"//PC
#define SOCKET_ERROR ((int8_t) -1)
#define BUFLEN ((uint16_t) 512U)
#define BACKLOG ((int8_t) 10)

#define NULL_PTR (void *) (0)

#define ntohl_br(x)        ((((x) & 0x000000ffU) << 24U) |   \
                         (((x) & 0x0000ff00U) <<  8U) |   \
                         (((x) & 0x00ff0000U) >>  8U) |   \
                         (((x) & 0xff000000U) >> 24U))
                         
#define htonl_br(x)        ((((x) & 0x000000ffU) << 24U) |   \
                         (((x) & 0x0000ff00U) <<  8U) |   \
                         (((x) & 0x00ff0000U) >>  8U) |   \
                         (((x) & 0xff000000U) >> 24U))
                         
#define ntohs_br(x)        ((((x) & (uint16_t) 0x00ff) << (uint16_t) 8) |    \
                         (((x) & (uint16_t) 0xff00) >> (uint16_t) 8))

#define htons_br(x)        ((((x) & (uint16_t) 0x00ff) << (uint16_t) 8) |    \
                          (((x) & (uint16_t) 0xff00) >> (uint16_t) 8))
                         
#define TASK_DELAY_25MS (uint32_t) (25U)
#define TASK_DELAY_100MS (uint32_t) (100U)

/* Command defines */
#define EXIT_BG_TASK ((uint32_t) 0U)
#define SEND_FILE ((uint32_t) 1U)
#define START_ROUTINE ((uint32_t) 2U)
#define SEND_MSG_QUEUE ((uint32_t) 3U)
#define SEND_SHARED_MEMORY ((uint32_t) 4U)

/* State machine defines */
#define STATEMACHINE_EXIT_BG_TASK ((uint8_t) 6U)
#define STATEMACHINE_SEND_FILE ((uint8_t) 2U)
#define STATEMACHINE_START_ROUTINE ((uint8_t) 3U)
#define STATEMACHINE_SEND_MSG_QUEUE ((uint8_t) 4U)
#define STATEMACHINE_SEND_SHARED_MEMORY ((uint8_t) 5U)
#define STATEMACHINE_WAIT_FOR_COMMAND ((uint8_t) 1U)

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

extern MSG_Q_ID routinesMsgQId;
extern MSG_Q_ID diagMsgQId;
extern MSG_Q_ID messages;
extern TASK_ID task;

/************************************************************************
 * INTERNAL FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function periodically reads diagnostic msgQ and shared memory
 * \return OK if successful, ERROR otherwise
 */
LOCAL STATUS _module2_ReadDiagMsgQ(void);
/** 
 * \brief This function opens shared memory in module 2 and allocates it
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
 * \brief This function sends routine number to module 1 which activates
 *        appropriate routine
 * \param routineNum Number of desired routine
 * \return OK if successful, ERROR otherwise
 */
LOCAL STATUS _module2_SetRoutineNum(int routineNum);
/** 
 * \brief This function opens shared memory in module 1 and allocates it
 * \return OK if successful, ERROR otherwise
 */
LOCAL STATUS _sharedMemAlloc_module2(void);
/** 
 * \brief This function reads file with error flags array
 */
LOCAL void _module2_ReadErrors(void);
/** 
 * \brief This function is background task for communication with PC and
 *        triggering appropriate routines for testing.
 */
LOCAL void _backgroundTask(void);
/** 
 * \brief This function sends file to PC.
 */
LOCAL void _sendFile(char fs_name[]);
/** 
 * \brief This function is used for initializing sockets and testing connection
 *        for communication with PC.
 */
LOCAL void _initCommunication(void);
/** 
 * \brief This function is used for initializing RTP module msg queues, shared memory
 *        and tasks. 
 */
LOCAL void _module2_init(void);
/** 
 * \brief This function sends number of files that are going to be sent through socket
 *        and calls _sendFile(). 
 */
LOCAL void _uploadFile(void);
/** 
 * \brief This function is used for receiving command from user via socket.
 */
LOCAL void _receiveCommand(void);
/** 
 * \brief This function is simple switch-case which acts like state-machine and calls
 *        functions or sends structs via socket.
 */
LOCAL void _processMessage(void);
/** 
 * \brief This function listen, accept and test communication with PC.
 */
LOCAL void _establishCommunication(void);
/** 
 * \brief This function prepares and send filename to PC via socket.
 */
LOCAL void _processFileName(char fs_name[]);
/** 
 * \brief This function prepares and send filesize to PC via socket. 
 */
LOCAL void _processFileSize(void);
/** 
 * \brief This function sends file data through socket.
 * \metric STCAL 9 Required for correct implementation of file sending.
 */
LOCAL void _processFileSending(void);

#endif /* MODULE2_H_ */
