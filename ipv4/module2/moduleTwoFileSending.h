/*
 *  \file 
 *      moduleTwoFileSending.h
 *
 *  \brief 
 *      Header file for moduleTwoFileSending.c
 *      Includes macro for htonl(x) function
 *
 *  \version
 *       [8-Jun-2018] [Stefan Masalusic] Initial creation
 *       
 *  \history
 *       [15-Jun-2018]  Added function descriptions
 *       [09-Jul-2018] Added macros
 */

#ifndef MODULETWOFILESENDING_H_
#define MODULETWOFILESENDING_H_

/************************************************************************
 * PRIVATE MACRO DEFINITIONS
 ***********************************************************************/
#define BUFLEN ((uint16_t) 512U)
#define SOCKET_ERROR ((int8_t) -1)

#define NULL_PTR (void *) (0)

#define htonl_br(x)      ((((x) & 0x000000ffU) << 24U) |   \
                         (((x) & 0x0000ff00U) <<  8U) |   \
                         (((x) & 0x00ff0000U) >>  8U) |   \
                         (((x) & 0xff000000U) >> 24U))

/************************************************************************
 * FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function sends number of files that are going to be sent through socket
 *        and calls _sendFile(). 
 */
void uploadFile(void);

#endif /* MODULETWOFILESENDING_H_ */
