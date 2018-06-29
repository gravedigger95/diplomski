/**
 *  \file 
 *      moduleOneHandleRoutines.c
 *      
 *  \brief 
 *       Functions for receiving routine numbers and starting test modes.
 *   
 *  \version
 *       [27-Jun-2018] [Stefan Masalusic] Initial creation
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
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include <unistd.h>
#include <ping6Lib.h>
#include <msgQLibCommon.h>
#include <taskLibCommon.h>
#include "moduleOneReadEthPhy.h"
#include "moduleOneHandleRoutines.h"

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
STATUS module1_GetRoutineNum(void)
{
    int32_t routineNum = 0;
    int32_t length     = 0;
    
    FOREVER
    {
        /* Read routine number sent from module 2 */ 
        length = msgQReceive (routinesMsgQId, (char *) &routineNum, sizeof (routineNum), WAIT_FOREVER); /* PRQA S 0310 */ /* PRQA S 3101 */ /* PRQA S 3102 */
        if (length < 0)
        {
            (void) printf ("getRoutineNum ERROR\n");
            return (ERROR);
        }

        (void) printf ("routineNum %d\n", routineNum);
        /* Start desired routine */
        
        _testModes (routineNum);

        (void) taskDelay (TASK_DELAY_100MS);
    }
}

LOCAL STATUS _pingRoutine(void)
{
    int8_t ret = 0;
    
    if (ERROR == ping6 (PC_IPV6, NUM_OF_PACKETS)) /* PRQA S 0752 */
    {
    	(void) printf ("Ping6 ERROR\n");
        ret = ERROR;
    }       
    else
    {
    	(void) printf ("Ping6 success\n");
        ret = OK;
    }

    return ret;
}

LOCAL void _normalOperationTest(uint16_t mode)
{
    mode &= 0xFE3FU;
    mdio_write_br (EXTENDED_CONTROL_REGISTER, mode);
    
    mode = (uint16_t) mdio_read_br (CONFIGURATION_REGISTER_1);
    mode |= (uint16_t) 0x4000U;    
    mdio_write_br (CONFIGURATION_REGISTER_1, mode);
    
    (void) printf ("Normal mode ECR reg: 0x%X\n", mdio_read_br (EXTENDED_CONTROL_REGISTER));
}

LOCAL void _testModes(int routine_trigger)
{
    uint32_t    test_case = 0U;
    uint16_t    mode_reg = 0U;

    test_case = ((uint32_t) routine_trigger & (uint32_t) 0x00FFFFFF);
    
    mode_reg = (uint16_t) mdio_read_br (EXTENDED_CONTROL_REGISTER);
    (void) printf ("ECR reg: 0x%X\n", mdio_read_br (EXTENDED_CONTROL_REGISTER));
    mode_reg |= (uint16_t) ((uint16_t) 1 << (uint16_t) 2);
    mdio_write_br (EXTENDED_CONTROL_REGISTER, mode_reg);
    
    if ((uint32_t) 6 == test_case)
    {
        (void) _pingRoutine();
    }
    else if ((uint32_t) 0 == test_case)
    {
        _normalOperationTest (mode_reg);
    }
    else
    {
        mode_reg = (uint16_t) mdio_read_br (CONFIGURATION_REGISTER_1);
        mode_reg &= 0xBFFFU;
        mdio_write_br (CONFIGURATION_REGISTER_1, mode_reg);
        
        mode_reg = (uint16_t) mdio_read_br (EXTENDED_CONTROL_REGISTER);
        mode_reg &= 0x7FFFU;
        mdio_write_br (EXTENDED_CONTROL_REGISTER, mode_reg);
        
        mode_reg &= 0xFE3FU;
        mode_reg |= (uint16_t) ((uint16_t) test_case << (uint16_t) 6);
        mdio_write_br (EXTENDED_CONTROL_REGISTER, mode_reg);
        
        (void) printf ("Entered test mode %d. ECR reg: 0x%X\n", test_case, mdio_read_br (EXTENDED_CONTROL_REGISTER));
    }

}

