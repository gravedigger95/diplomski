/*
 * moduleOneHandleRoutines.c
 *
 *  Created on: Jun 27, 2018
 *      Author: bura
 */
/* ------------------------------------------------------------------------- */
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
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
            printf ("getRoutineNum ERROR\n");
            return (ERROR);
        }

        printf ("routineNum %d\n", routineNum);
        /* Start desired routine */
        
        _testModes (routineNum);

        (void) taskDelay (TASK_DELAY_100MS);
    }
}

LOCAL STATUS _pingRoutine(void)
{
    int8_t ret = 0;
    
    if (ERROR == ping6 (PC_IPV6, NUM_OF_PACKETS)) /* PRQA S 3335 */
    {
        printf ("Ping6 ERROR\n");
        ret = ERROR;
    }       
    else
    {
        printf ("Ping6 success\n");
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
    
    printf ("Normal mode ECR reg: 0x%X\n", mdio_read_br (EXTENDED_CONTROL_REGISTER));
}

LOCAL void _testModes(int routine_trigger)
{
    uint32_t    test_case = 0U;
    uint16_t    mode_reg = 0U;

    test_case = ((uint32_t) routine_trigger & (uint32_t) 0x00FFFFFF);
    
    mode_reg = (uint16_t) mdio_read_br (EXTENDED_CONTROL_REGISTER);
    printf ("ECR reg: 0x%X\n", mdio_read_br (EXTENDED_CONTROL_REGISTER));
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
        
        printf ("Entered test mode %d. ECR reg: 0x%X\n", test_case, mdio_read_br (EXTENDED_CONTROL_REGISTER));
    }

}

