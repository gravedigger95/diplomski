/*
 * moduleTwoFileSending.h
 *
 *  Created on: Jun 27, 2018
 *      Author: bura
 */

#ifndef MODULETWOFILESENDING_H_
#define MODULETWOFILESENDING_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
#define BUFLEN ((uint16_t) 512U)
#define SOCKET_ERROR ((int8_t) -1)

#define STATEMACHINE_WAIT_FOR_COMMAND ((uint8_t) 1U)

#define NULL_PTR (void *) (0)

#define htonl_br(x)        ((((x) & 0x000000ffU) << 24U) |   \
                         (((x) & 0x0000ff00U) <<  8U) |   \
                         (((x) & 0x00ff0000U) >>  8U) |   \
                         (((x) & 0xff000000U) >> 24U))

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function prepares and send filename to PC via socket.
 * \param fs_name[] Name of file to be sent
 */
LOCAL void _processFileName(char fs_name[]);
/** 
 * \brief This function prepares and send filesize to PC via socket. 
 */
LOCAL void _processFileSize(void);
/** 
 * \brief This function sends file data through socket.
 * \metric STCAL 10 Required for correct implementation of file sending.
 */
LOCAL void _processFileSending(void);
/** 
 * \brief This function sends number of files that are going to be sent through socket
 *        and calls _sendFile(). 
 */
void uploadFile(void);
/** 
 * \brief This function sends file to PC.
 * \param fs_name[] Name of file to be sent with full path
 */
LOCAL void _sendFile(char fs_name[]);

#endif /* MODULETWOFILESENDING_H_ */
