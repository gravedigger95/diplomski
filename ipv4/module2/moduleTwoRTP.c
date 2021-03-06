/**
 *  \file 
 *      moduleTwoRTP.c
 *      
 *  \brief 
 *       Functions for initializing module two RTP and starting background task
 *       state machine.
 *   
 *  \version
 *       [27-Jun-2018] [Stefan Masalusic] Initial creation
 * ------------------------------------------------------------------------------
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
/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL MSG_Q_ID messages = MSG_Q_ID_NULL;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
int main (void) {   
    
    _module2_init();
    
    FOREVER
    {
        (void) _module2_ReadDiagMsgQ();
        (void) taskDelay (TASK_DELAY_25MS); 
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
    _changeState = 1;
    
    if (msgQSend (messages, (char *) &_changeState, sizeof (_changeState), NO_WAIT, MSG_PRI_NORMAL) == ERROR) /* PRQA S 0310 */
    {
    	(void) printf ("msgQSend RTP main ERROR\n");
    }
        
    (void) initCommunication();
        
    if (taskSpawn ("bgTask", 115, VX_FP_TASK, 2000, (FUNCPTR) _backgroundTask, 0, 0,  /* PRQA S 0752 */ /* PRQA S 0313 */ /* PRQA S 0310 */
                    0, 0, 0, 0, 0, 0, 0, 0) == ERROR)
    {
    	(void) printf("taskSpawn of backgroundTask failed\n");
    }
}

LOCAL void _backgroundTask(void)
{
    FOREVER
    {
        (void) msgQReceive (messages, (char *) &_msg, sizeof (_msg), WAIT_FOREVER); /* PRQA S 3101 */ /* PRQA S 3102 */ /* PRQA S 0310 */ 
        if (STATEMACHINE_EXIT_BG_TASK == _msg)
        {
        	(void) printf ("Terminating task...\n");
            processMessage();
            (void) msgQClose (messages);
            taskExit(1);
        }   
        processMessage();
        
        (void) msgQSend (messages, (char *) &_changeState, sizeof (_changeState), NO_WAIT, MSG_PRI_NORMAL); /* PRQA S 0310 */
    }
} 

STATUS module2_SetRoutineNum(int routineNum)
{
    int8_t ret              = OK;
    MSG_Q_ID routinesMsgQId = MSG_Q_ID_NULL;

    /* Open _msg queue */
    routinesMsgQId = msgQOpen ("/routinesMsgQ", MAX_MSG, sizeof(uint32_t), MSG_Q_FIFO, OM_CREATE, NULL_PTR); 
    if (MSG_Q_ID_NULL == routinesMsgQId)
    {
    	(void) printf ("setRoutineNum open ERROR\n");
        ret = ERROR;
    }
    
    /* Send routine number to module 1 */ 
    if (msgQSend (routinesMsgQId, (char *) &routineNum, sizeof (routineNum), NO_WAIT, MSG_PRI_NORMAL) == ERROR) /* PRQA S 0310 */
    {
    	(void) printf ("setRoutineNum send ERROR\n");
        ret = ERROR;
    }
    return ret;
}
