/**
 *  \file 
 *      moduleTwoServer.c
 *      
 *  \brief 
 *       Functions for starting TCP/IP server and accepting communication
 *       with PC side via socket.
 *   
 *  \version
 *       [30-May-2018] [Stefan Masalusic] Initial creation
 *  \history
 *       [31-May-2018] Added _establishCommunication and initCommunication functions
 *       
 * ------------------------------------------------------------------------------
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
/* Error Message: Msg(7:0310) Casting to different object pointer type.MISRA C:2012 
 * Rule-11.3; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantic
 * 
 * Justification : This is checked and considered safe. It is confirmed by multiple
 * testing cases and long period project usage. 
 */
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
#include <sockLib.h>
#include <inetLib.h>
#include <errno.h>
#include <string.h>
#include "moduleTwoServer.h"

/************************************************************************
 * LOCAL FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function listen, accept and test communication with PC.
 */
LOCAL void _establishCommunication(void);

/************************************************************************
 * GLOBAL VARIABLES
 ***********************************************************************/
int _s, _newSocket;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
void initCommunication(void)
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
	
    struct sockaddr_in server;
    
    /* Create socket */
    _s = socket (AF_INET, SOCK_STREAM, 0);
    if (SOCKET_ERROR == _s)
    {
        (void) printf ("Could not create socket!\n");
    }
    (void) printf ("\n\nSocket created.\n");
    
    /* Fill socket structure */
    (void) memset ((char *) &server, 0, sizeof (server)); /* PRQA S 0310 */
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons_br ((uint16_t) SWU_BR_SERVERPORT); /* PRQA S 4397 */
    //inet_pton(AF_INET6, "::0", &server.sin6_addr);
    
    /* Bind address to socket */
    if (bind (_s, (struct sockaddr *) &server , (int32_t) sizeof (server)) == SOCKET_ERROR) /* PRQA S 0310 */
    {
        (void) printf ("Bind failed: %s\n", strerror (errno));
    }
             
    (void) printf ("Bind done!");
            
    (void) printf ("Listening...\n");
            
   _establishCommunication();
}

LOCAL void _establishCommunication(void)
{
    const char message[]      = "Start";
    const char respondOK[]    = "Let's communicate!";
    const char respondNotOK[] = "Communication breakdown...";
    char buffer[BUFLEN];
    struct sockaddr_in client;
    int recvSize;
    int c;
    
    /* Listen and accept communication on socket */
    (void) listen (_s, BACKLOG);
    
    (void) printf ("Waiting for incoming connections...\n\n\n\n");
    
    c = (int32_t) sizeof (struct sockaddr_in); 
    
    _newSocket = accept (_s, (struct sockaddr *) &client, &c); /* PRQA S 0310 */
    if (SOCKET_ERROR == _newSocket)
    {
        (void) printf ("Accept failed with error!\n");
    }
    (void) printf ("Connection accepted!\n");
    
    /* Receive initial message from client */
    recvSize = recv (_newSocket, buffer, BUFLEN, 0);
    if (SOCKET_ERROR == recvSize)
    {
        (void) printf ("Recv from client failed!");
    }
    (void) printf ("Reply received --------->");
    
    buffer[recvSize] = '\0';
    (void) printf (buffer);
    (void) printf ("\n");
    
    /* Send initial response to client */
    if (strcmp (buffer, message) == 0)
    {
        if (send (_newSocket, respondOK, strlen (respondOK), 0) == SOCKET_ERROR)
        {
            (void) printf ("First send() failed\n");
        }
        (void) printf ("Connection established!\n\n");
    }
    else
    {
        if (send (_newSocket, respondNotOK, strlen (respondOK), 0) == SOCKET_ERROR)
        {
            (void) printf ("Connection refused!\n");
        }
    }
}

