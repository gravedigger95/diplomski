/*
 * moduleTwoHandleRoutines.c
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
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include "moduleTwoCommunication.h"
#include "moduleTwoHandleRoutines.h"
#include "moduleTwoFileSending.h"
#include "moduleTwoRTP.h"
/************************************************************************
 * GLOBAL VARIABLES
 ***********************************************************************/
uint8_t _changeState            = 0;    
uint8_t _msg                    = 0;
LOCAL uint32_t _routineNumRecv  = 0;

/************************************************************************
 * EXTERNAL VARIABLES
 ***********************************************************************/
extern s_DIAG_DATA _diag_data_struct_mod2;
extern s_DIAG_SHM_DATA _diag_shm_struct;
extern int _newSocket, _s, _recvSize;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
void _processMessage(void)
{
    switch (_msg)
    {
        case STATEMACHINE_WAIT_FOR_COMMAND:
            _receiveCommand();
            break;
        case STATEMACHINE_SEND_FILE:
            _uploadFile();
            break;
        case STATEMACHINE_START_ROUTINE:
            _module2_SetRoutineNum ((int32_t) _routineNumRecv);
            _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
            break;
        case STATEMACHINE_SEND_MSG_QUEUE:
            if (send (_newSocket, (char *) &_diag_data_struct_mod2, sizeof (_diag_data_struct_mod2), 0) == SOCKET_ERROR)
            {
                printf ("msgq struct send() FAILED!\n\n");
            }
            printf ("msgq struct  is sent!\n"); 
            _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
            break;
        case STATEMACHINE_SEND_SHARED_MEMORY:
            if (send (_newSocket, (char *) &_diag_shm_struct, sizeof (_diag_shm_struct), 0) == SOCKET_ERROR)
            {
                printf ("shmem struct send() FAILED!\n\n"); 
            }
            printf ("shmem struct  is sent!\n");
            _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
            break;
        default:
            (void) close (_s);
            (void) close (_newSocket);
            printf ("Client disconnected!\n");
            break;
    }
}

LOCAL void _receiveCommand(void)
{
    uint32_t commandNum = EXIT_BG_TASK;

    _recvSize = recv (_newSocket, &commandNum, sizeof (commandNum), 0);
    if (SOCKET_ERROR  == _recvSize)
    {
        printf ("Recv from _client failed!");
    }
    commandNum = ntohl_br (commandNum);
    printf ("%d\n", commandNum); 
    
    if (SEND_FILE == commandNum)
    {
        _changeState = STATEMACHINE_SEND_FILE;
    }
    else if (START_ROUTINE == commandNum)
    {
        _recvSize = recv (_newSocket, &_routineNumRecv, sizeof (_routineNumRecv), 0);
        if (SOCKET_ERROR == _recvSize)
        {
            printf ("Recv from _client failed!");
        }
        _routineNumRecv = ntohl_br (_routineNumRecv);
        printf ("routineNum = %d\n", _routineNumRecv);
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

