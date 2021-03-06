/*
 * moduleTwoServer.h
 *
 *  Created on: Jun 27, 2018
 *      Author: bura
 */

#ifndef MODULETWOSERVER_H_
#define MODULETWOSERVER_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
#define SOCKET_ERROR ((int8_t) -1)
#define SWU_BR_SERVERPORT  29170
#define BACKLOG ((int8_t) 10)
#define BUFLEN ((uint16_t) 512U)

#define htons_br(x)        ((((x) & (uint16_t) 0x00ff) << (uint16_t) 8) |    \
                          (((x) & (uint16_t) 0xff00) >> (uint16_t) 8))

/************************************************************************
 * EXTERNAL VARIABLES
 ***********************************************************************/
extern int _newSocket, _s;

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function listen, accept and test communication with PC.
 */
LOCAL void _establishCommunication(void);
/** 
 * \brief This function is used for initializing sockets and testing connection
 *        for communication with PC.
 */
void initCommunication(void);


#endif /* MODULETWOSERVER_H_ */
