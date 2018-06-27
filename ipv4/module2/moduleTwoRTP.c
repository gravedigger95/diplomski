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
#include <sys/mman.h>
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
 * GLOBAL VARIABLES
 ***********************************************************************/
MSG_Q_ID routinesMsgQId    = MSG_Q_ID_NULL;
MSG_Q_ID messages          = MSG_Q_ID_NULL;

/************************************************************************
 * EXTERNAL VARIABLES
 ***********************************************************************/
extern uint8_t _changeState; 
extern uint8_t _msg;

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
    if (_sharedMemAlloc_module2() == ERROR)
    {
        printf ("Error allocating module 2\n");
    }  
    
    messages = msgQCreate (BUFLEN, BUFLEN, MSG_Q_FIFO);
    if (MSG_Q_ID_NULL == messages)
    {
        printf ("MsgQCreate failed!\n");
    }
    _changeState = 1;
    
    if (msgQSend (messages, (char *) &_changeState, sizeof (_changeState), NO_WAIT, MSG_PRI_NORMAL) == ERROR)
    {
        printf ("msgQSend RTP main ERROR\n");
    }
        
    (void) _initCommunication();
        
    if (taskSpawn ("bgTask", 115, VX_FP_TASK, 2000, (FUNCPTR) _backgroundTask, 0, 0,  /* PRQA S 0752 */ /* PRQA S 0313 */
                    0, 0, 0, 0, 0, 0, 0, 0) == ERROR)
    {
        printf("taskSpawn of backgroundTask failed\n");
    }
}

LOCAL void _backgroundTask(void)
{
    printf ("USAO U BG TASK\n\n");
    FOREVER
    {
        msgQReceive (messages, (char *) &_msg, sizeof (_msg), WAIT_FOREVER); /* PRQA S 3101 */ /* PRQA S 3102 */
        if (STATEMACHINE_EXIT_BG_TASK == _msg)
        {
            printf ("Terminating task...\n");
            _processMessage();
            msgQClose (messages);
            taskExit(1);
        }   
        _processMessage();
        
        msgQSend (messages, (char *) &_changeState, sizeof (_changeState), NO_WAIT, MSG_PRI_NORMAL);
    }
} 

STATUS _module2_SetRoutineNum(int routineNum)
{
    int8_t ret = OK;

    /* Open _msg queue */
    routinesMsgQId = msgQOpen ("/routinesMsgQ", MAX_MSG, sizeof(uint32_t), MSG_Q_FIFO, OM_CREATE, NULL_PTR); 
    if (MSG_Q_ID_NULL == routinesMsgQId)
    {
        printf ("setRoutineNum open ERROR\n");
        ret = ERROR;
    }
    
    /* Send routine number to module 1 */ 
    printf ("Set rooutine num: %d\n", routineNum);
    if (msgQSend (routinesMsgQId, (char *) &routineNum, sizeof (routineNum), NO_WAIT, MSG_PRI_NORMAL) == ERROR)
    {
        printf ("setRoutineNum send ERROR\n");
        ret = ERROR;
    }
    return ret;
}






