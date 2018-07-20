/**
 *  \file 
 *      moduleTwoRTP.c
 *      
 *  \brief 
 *       Functions for initializing module two RTP, starting background task
 *       state machine and sending routine number to module one.
 *   
 *  \version
 *       [28-May-2018] [Stefan Masalusic] Initial creation
 *  \history
 *       [29-May-2018] Added _module2_init and module2_SetRoutineNum functions
 *       [6-Jun-2018]  Added _backgroundTask function
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
 * testing cases.
 */
/* ------------------------------------------------------------------------- */
/* Error message : Msg(7:3101) Unary '-' applied to an operand of type unsigned int 
 * or unsigned long gives an unsigned result.MISRA C:2012 Rule-10.1;
 * REFERENCE - ISO:C90-6.3.3.3 Unary Arithmetic Operators - Semantics
 * 
 * Justification : This is VxWorks macro. It is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error message : Msg(7:3102) Unary '-' applied to an operand whose underlying
 * type is unsigned.MISRA C:2012 Rule-10.1; REFERENCE - 
 * ISO:C90-6.3.3.3 Unary Arithmetic Operators - Semantics
 * 
 * Justification : This is VxWorks macro. It is checked and considered safe.
 */
 /* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0752) String literal passed as argument to function 
 * whose parameter is not a 'pointer to const'.MISRA C:2012 Rule-7.4; 
 * REFERENCE - ISO:C90-6.1.4 String Literals - Semantics
 * 
 * Justification : This implementation increase code visibility.
 */
 /* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0429) [C] Function argument is not of arithmetic type.
 * MISRA C:2012 Rule-1.1; REFERENCE - ISO:C90-6.3.2.2 Function calls
 * 
 * Justification : This is Wind River macro. It is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include <msgQLibCommon.h>
#include <taskLib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "moduleTwoServer.h"
#include "moduleTwoHandleRoutines.h"
#include "moduleTwoFileSending.h"
#include "moduleTwoCommunication.h"
#include "moduleTwoRTP.h"

/************************************************************************
 * LOCAL FUNCTION DECLARATIONS
 ***********************************************************************/
/** 
 * \brief This function is background task for communication with PC and
 *        triggering appropriate routines for testing.
 */
LOCAL void _backgroundTask(void);
/** 
 * \brief This function is used for initializing RTP module msg queues, shared memory
 *        and tasks. 
 */
LOCAL void _module2_init(void);

/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL MSG_Q_ID messages = MSG_Q_ID_NULL;
LOCAL MSG_Q_ID restartMsgQId = MSG_Q_ID_NULL;
LOCAL uint32_t restart = NO_RESTART;
LOCAL RTP_ID id;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
int main (void) 
{
	restart = NO_RESTART;
    /* Initialize RTP */
    _module2_init();
    /* Start RTP task */
    FOREVER
    {
        if (restart == RESTART)
        {
            _module2_init();
            (void) taskRestart (id); /* PRQA S 0429 */ /* PRQA S 2753 */
            restart = NO_RESTART;
        }
        (void) _module2_ReadDiagMsgQ();
        (void) taskDelay (TASK_DELAY_250MS); 
    }

    return 0;
}

LOCAL void _module2_init(void)
{
    if (sharedMemAlloc_module2() == ERROR)
    {
        (void) printf ("Error allocating module 2\n");
    }  
    messages = msgQCreate (BUFLEN, BUFLEN, MSG_Q_FIFO);
    if (MSG_Q_ID_NULL == messages)
    {
        (void) printf ("MsgQCreate failed!\n");
    }
    /* Set state machine initial state */
    _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
    if (msgQSend (messages, (char *) &_changeState, sizeof (_changeState), NO_WAIT, MSG_PRI_NORMAL) == ERROR) /* PRQA S 0310 */
    {
        (void) printf ("msgQSend RTP main ERROR\n");
    }

    restartMsgQId = msgQOpen ("/restartMsgQ", MAX_MSG, sizeof(id), MSG_Q_FIFO, OM_CREATE, NULL_PTR); 
    if (MSG_Q_ID_NULL == restartMsgQId)
    {
        (void) printf ("restartMsgQId open ERROR\n");
    }
    
    (void) msgQReceive (restartMsgQId, (char *) &id, sizeof (id), NO_WAIT); /* PRQA S 3101 */ /* PRQA S 3102 */ /* PRQA S 0310 */ 

    /* Start server */
    (void) initCommunication();
        
    /* Start background task */
    if (taskSpawn ("bgTask", BG_TASK_PRIORITY, VX_FP_TASK, BG_STACK_SIZE, (FUNCPTR) _backgroundTask, 0, 0,  /* PRQA S 0752 */ /* PRQA S 0313 */ /* PRQA S 0310 */
            0, 0, 0, 0, 0, 0, 0, 0) == ERROR)
    {
        (void) printf("taskSpawn of backgroundTask failed\n");
    }
}

LOCAL void _backgroundTask(void)
{	
    FOREVER
    {		
    	/* Receive command and process it */
        (void) msgQReceive (messages, (char *) &_msg, sizeof (_msg), WAIT_FOREVER); /* PRQA S 3101 */ /* PRQA S 3102 */ /* PRQA S 0310 */ 
        if (STATEMACHINE_EXIT_BG_TASK == _msg)
        {
            (void) printf ("Terminating task...\n");
            processMessage();
            (void) msgQClose (messages);
            restart = RESTART;
            taskExit(1);
        }   
        processMessage();
        /* Return to idle state */
        (void) msgQSend (messages, (char *) &_changeState, sizeof (_changeState), NO_WAIT, MSG_PRI_NORMAL); /* PRQA S 0310 */
    }
}
