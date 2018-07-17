/**
 *  \file 
 *      moduleTwoHandleRoutines.c
 *      
 *  \brief 
 *       State machine functions that handle user commands using state machine.
 *   
 *  \version
 *       [13-Jun-2018] [Stefan Masalusic] Initial creation
 *       [15-Jun-2018] [Stefan Masalusic] Added functions
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
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include <sockLib.h>
#include "moduleTwoCommunication.h"
#include "moduleTwoHandleRoutines.h"
#include "moduleTwoFileSending.h"
#include "moduleTwoServer.h"
#include "moduleTwoRTP.h"

/************************************************************************
 * LOCAL FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function is used for receiving command from user via socket.
 */
LOCAL void _receiveCommand(void);

/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL uint32_t _routineNumRecv  = 0;

/************************************************************************
 * GLOBAL VARIABLES
 ***********************************************************************/
uint8_t _changeState = 0;
uint8_t _msg         = 0;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
void processMessage(void)
{
    switch (_msg)
    {
        case STATEMACHINE_WAIT_FOR_COMMAND:
        	/* Receive command from user via socket */
            _receiveCommand();
            break;
        case STATEMACHINE_SEND_FILE:
        	/* Send file to PC */
            uploadFile();
            break;
        case STATEMACHINE_START_ROUTINE:
        	/* Start routine or test mode */
            (void) module2_SetRoutineNum ((int32_t) _routineNumRecv);
            _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
            break;
        case STATEMACHINE_SEND_MSG_QUEUE:
        	/* Send diagnostic data to user */
            if (send (_newSocket, (char *) &_diag_data_struct_mod1, sizeof (_diag_data_struct_mod1), 0) == SOCKET_ERROR) /* PRQA S 0310 */
            {
                (void) printf ("msgq struct send() FAILED!\n\n");
            }
            (void) printf ("Message Queue struct is sent!\n"); 
            _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
            break;
        case STATEMACHINE_SEND_SHARED_MEMORY:
        	/* Send diagnostic data to user */
            if (send (_newSocket, (char *) &_diag_shm_struct, sizeof (_diag_shm_struct), 0) == SOCKET_ERROR) /* PRQA S 0310 */
            {
                (void) printf ("Shared memory struct send() FAILED!\n\n"); 
            }
            (void) printf ("Shared memory struct  is sent!\n");
            _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
            break;
        default:
        	/* User terminated program */
            (void) close (_s);
            (void) close (_newSocket);
            (void) printf ("Client disconnected!\n");
            break;
    }
}

LOCAL void _receiveCommand(void)
{
    int recvSize;
    uint32_t commandNum = EXIT_BG_TASK;
    
    /* Receive command number from user */
    recvSize = recv (_newSocket, &commandNum, sizeof (commandNum), 0);
    if (SOCKET_ERROR  == recvSize)
    {
        (void) printf ("Recv from _client failed!");
    }
    commandNum = ntohl_br (commandNum);
    
    if (SEND_FILE == commandNum)
    {
        _changeState = STATEMACHINE_SEND_FILE;
    }
    else if (START_ROUTINE == commandNum)
    {
    	/* Receive routine number from user */
        recvSize = recv (_newSocket, &_routineNumRecv, sizeof (_routineNumRecv), 0);
        if (SOCKET_ERROR == recvSize)
        {
            (void) printf ("Recv from _client failed!");
        }
        _routineNumRecv = ntohl_br (_routineNumRecv);
        _changeState = STATEMACHINE_START_ROUTINE;
    }
    else if (SEND_MSG_QUEUE == commandNum)
    {
        _changeState = STATEMACHINE_SEND_MSG_QUEUE;
    }
    else if (SEND_SHARED_MEMORY == commandNum)
    {
        _changeState = STATEMACHINE_SEND_SHARED_MEMORY;
    }
    else
    {
        _changeState = STATEMACHINE_EXIT_BG_TASK;
    }
}

