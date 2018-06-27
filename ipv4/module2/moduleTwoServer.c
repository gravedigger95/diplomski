/*
 * moduleTwoServer.c
 *
 *  Created on: Jun 27, 2018
 *      Author: bura
 */
 /* ------------------------------------------------------------------------- */
/*                         SUPRESSED MISRA VIOLATONS                         */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
 /* ------------------------------------------------------------------------- */
/* Error message : Msg(7:0602) [U] The identifier '<identifier_name>' is reserved for 
 * use by the library.
 * 
 * Justification : Named according to the ZFAS coding guidelines at 
 * CGL-D-ZFAS-Z-01-001.docx 
 */
/* PRQA S 0602 EOF */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:3200) 'printf',... returns a value which is not being 
 * used.MISRA C:2012 Rule-17.7
 * 
 * Justification : This is not considered safety critical on QM level so is 
 * considered acceptable.
 */
/* PRQA S 3200 EOF */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0306) [I] Cast between a pointer to object and an integral 
 * type.MISRA C:2012 Rule-11.4, Rule-11.6; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
 * 
 * Justification : The code that produces this message is part of VxWorks
 * implementation or it is used for the error checking and is considered OK.
 */
 /* PRQA S 0306 EOF */
  /* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0316) [I] Cast from a pointer to void to a pointer to 
 * object type.MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
 * 
 * Justification : This is checked and considered safe.
 */
 /* PRQA S 0316 EOF */ 
  /* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0310) Casting to different object pointer type.MISRA C:2012 
 * Rule-11.3; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantic
 * 
 * Justification : This is checked and considered safe. It is confirmed by multiple
 * testing cases and long period project usage. 
 */
 /* PRQA S 0310 EOF */
 /* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4397) An expression which is the result of a ~ or << 
 * operation has not been cast to its essential type.MISRA C:2012 Rule-10.7
 * 
 * Justification : This is checked and considered safe.
 */  
/* ------------------------------------------------------------------------- */
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include <socket.h>
#include <inetLib.h>
#include <errno.h>
#include <string.h>
#include "moduleTwoServer.h"

/************************************************************************
 * GLOBAL VARIABLES
 ***********************************************************************/
struct sockaddr_in _server;
struct sockaddr_in _client;
int _s, _newSocket, _c, _recvSize;

/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL const char _message[]      = "Start";
LOCAL const char _respondOK[]    = "Let's communicate!";
LOCAL const char _respondNotOK[] = "Communication breakdown...";

LOCAL char _buffer[BUFLEN];

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
void _initCommunication(void)
{
    /*
        struct addrinfo hints;
        struct addrinfo * firstres;
        struct addrinfo * res;
        int rc;
        int size;

        memset(&hints, 0, sizeof(hints));
        
        hints.ai_family = AF_UNSPEC;
        hints.ai_protocol = IPPROTO_TCP;
        
        rc = getaddrinfo("fd53:7cb8:383:3::73", "tcp", &hints, &firstres);
        
        res = fistres;
        
        _s = socket (res->ai_family, res->ai_socktype, res->ai_protocol);

        if (SOCKET_ERROR == _s)
        {
            printf ("Could not create socket!\n"); 
        }
        printf ("\n\nSocket created.\n");
                
        size = 65536;
        setsockopt(_s, SOL_SOCKET, SO_SNDBUF, (char *) &size, sizeof(size));
        setsockopt(_s, SOL_SOCKET, sO_RCVBUF, (char *) &size, sizeof(size));
    */    
    
    _s = socket (AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == _s)
    {
        printf ("Could not create socket!\n");
    }
    printf ("\n\nSocket created.\n");
    
    memset ((char *) &_server, 0, sizeof (_server));
    _server.sin_family = AF_INET;
    _server.sin_addr.s_addr = INADDR_ANY;
    _server.sin_port = htons_br ((uint16_t) SWU_BR_SERVERPORT); /* PRQA S 4397 */
    //inet_pton(AF_INET6, "::0", &_server.sin6_addr);
    
    if (bind (_s, (struct sockaddr *) &_server , (int32_t) sizeof (_server)) == SOCKET_ERROR)
    {
        printf ("Bind failed: %s\n", strerror (errno));
    }
             
    printf ("Bind done!");
            
    printf ("Listetning...\n");
            
   _establishCommunication();
}

void _establishCommunication(void)
{
    listen (_s, BACKLOG);
    
    printf ("Waiting for incoming connections...\n\n\n\n");
    
    _c = (int32_t) sizeof (struct sockaddr_in); 
    
    _newSocket = accept (_s, (struct sockaddr *) &_client, &_c);
    if (SOCKET_ERROR == _newSocket)
    {
        printf ("Accept failed with error!\n");
    }
    printf ("Connection accepted!");
    
    /* Receive initial message from client */
    _recvSize = recv (_newSocket, _buffer, BUFLEN, 0);
    if (SOCKET_ERROR == _recvSize)
    {
        printf ("Recv from _client failed!");
    }
    printf ("Reply received --------->");
    
    _buffer[_recvSize] = '\0';
    printf (_buffer);
    printf ("\n");
    
    /* Send initial response to client */
    if (strcmp (_buffer, _message) == 0)
    {
        if (send (_newSocket, _respondOK, strlen (_respondOK), 0) == SOCKET_ERROR)
        {
            printf ("First send() failed\n");
        }
        printf ("Everything is fine, let's chat!\n\n");
    }
    else
    {
        if (send (_newSocket, _respondNotOK, strlen (_respondOK), 0) == SOCKET_ERROR)
        {
            printf ("Second send() failed\n");
        }
    }
}

