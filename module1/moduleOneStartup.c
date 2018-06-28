/**
 *  \file 
 *      moduleOneStartup.c
 *      
 *  \brief 
 *       Interface functions for starting module that are used in
 *       tttechBroadRReach.c file.
 *   
 *  \version
 *       [19-Apr-2018] [Stefan Masalusic] Initial creation
 * ------------------------------------------------------------------------------
 */
 /* ------------------------------------------------------------------------- */
/*                         SUPRESSED MISRA VIOLATONS                         */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:3200) 'printf',... returns a value which is not being 
 * used.MISRA C:2012 Rule-17.7
 * 
 * Justification : This is not considered safety critical on QM level so is 
 * considered acceptable.
 */
 /* PRQA S 3200 EOF */
 /* ------------------------------------------------------------------------- */
 /* Error message : Msg(7:0602) [U] The identifier '<identifier_name>' is reserved for 
 * use by the library.
 * 
 * Justification : Named according to the ZFAS coding guidelines at 
 * CGL-D-ZFAS-Z-01-001.docx 
 */
/* PRQA S 0602 EOF */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4542) A non-negative constant expression of 'essentially 
 * signed' type (signed char) is being used as the left-hand operand of this bitwise operator (&).MISRA C:2012 Rule-10.1
 * 
 * Justification : This is checked and considered safe. This implementation increases
 * code simplicity and visibility.
 */
 /* PRQA S 4542 EOF */
/* Error Message: Msg(5:0317) [I] Implicit conversion from a pointer to void to
 * a pointer to object type.MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 
 * Cast Operators - Semantics
 * 
 * Justification : This is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4436) A constant expression of 'essentially signed' type 
 * (signed int) is being converted to unsigned type, 'unsigned short' on assignment.MISRA C:2012 Rule-10.3
 * 
 * Justification : This is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0306) [I] Cast between a pointer to object and an integral 
 * type.MISRA C:2012 Rule-11.4, Rule-11.6; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
 * 
 * Justification : The code that produces this message is part of VxWorks
 * implementation or it is used for the error checking and is considered OK.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0563) [C] Right operand of assignment is not of compatible 
 * pointer type.MISRA C:2012 Rule-1.1; REFERENCE - ISO:C90-6.3.16.1 Simple Assignment - Constraints
 * 
 * Justification : This is checked and considered OK on safety aspect. It 
 * is confirmed on long period usage and multiple testing levels.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0488) Performing pointer arithmetic.MISRA C:2012 Rule-18.4; 
 * REFERENCE - ISO:C90-6.3.6 Additive Operators - Constraints
 * 
 * Justification : This is used for accessing the registers. The offset is added to 
 * mapped address in  virtual memory. It is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(8:3335) No function declaration. Implicit declaration inserted: 
 * 'extern int Sysctl();'.MISRA C:2012 Rule-17.3; REFERENCE - ISO:C90-6.3.2.2 Function Calls - Semantics
 * 
 * Justification : This is Wind River's function and is not introduced through .h file
 * so it is used as it is.
 */
/* ------------------------------------------------------------------------- */
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include <msgQLibCommon.h>
#include <vmLibCommon.h>
#include <rtpLibcommon.h>
#include <taskLibcommon.h>
#include <pmapLib.h>
#include <net/utils/ifconfig.h>
#include "moduleOneHandleRoutines.h"
#include "moduleOneStartup.h"
#include "moduleOneReadEthPhy.h"

/************************************************************************
 * GLOBAL VARIABLES
 ***********************************************************************/
MSG_Q_ID routinesMsgQId = MSG_Q_ID_NULL;
MSG_Q_ID diagMsgQId     = MSG_Q_ID_NULL;

/* Phy address register */
volatile uint32_t * phyGmiiAddress;
/* Phy data register */
volatile uint32_t * phyGmiiData;

/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL char * ethIf_macVirtAddr = BR_NULL_PTR;
LOCAL s_DIAG_DATA       _diag_data_struct;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
void module1_InitPhy(void)
{
    FILE * fd;
    
    const UINT32 hwRegEthIfBaseaddr = (UINT32) 0xFF702000U;

    ethIf_macVirtAddr = pmapGlobalMap (hwRegEthIfBaseaddr, (size_t) 0xFF,  /* PRQA S 0317 */
                MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED); /* PRQA S 4436 */
    
    if ((ethIf_macVirtAddr == PMAP_FAILED) || (ethIf_macVirtAddr == BR_NULL_PTR)) /* PRQA S 0306 */
    {
        printf ("pmapGlobalMap returned ERROR. (ethIf)\n"); 
    }
    
    phyGmiiAddress = ethIf_macVirtAddr + 0x10U; /* PRQA S 0488 */ /* PRQA S 0563 */
    phyGmiiData = ethIf_macVirtAddr + 0x14U; /* PRQA S 0488 */ /* PRQA S 0563 */
   
    fd = fopen ("/mmc0:1/err/errorLog.txt", "w");
    if (NULL_PTR != fd)  
    { 
        fprintf (fd, "Error log: \n"); 
        (void) fclose (fd);
    }

    (void) _module1_CreateMsgQueues(); 
}

STATUS rtpModule(void)
{
    RTP_ID id;
    const char * argv[] = {"/mmc0:1/module2.vxe", "module2", NULL_PTR};
    const char * envp[] = {"HEAP_INITIAL_SIZE=0x19000", "HEAP_MAX_SIZE=0x1000000", NULL_PTR};
    
    id = rtpSpawn (argv[0], argv, envp, 207, 0x19000, 0x01, VX_FP_TASK);
    
    if (RTP_ID_ERROR == id) /* PRQA S 0306 */
    {
        printf ("ERROR to start %s\n", argv[0]);
    }
    
    return (OK);
}

LOCAL STATUS _module1_CreateMsgQueues(void)
{
    int8_t ret = OK;

    /* Open public message queues */
    diagMsgQId = msgQOpen ("/diagMsgQ", MAX_MSG, sizeof (_diag_data_struct), MSG_Q_FIFO, OM_CREATE, NULL_PTR);
    if (MSG_Q_ID_NULL == diagMsgQId)
    {
        printf ("openMsgQ  diagMsgQId ERROR\n");
        ret = ERROR;
    }
    
    routinesMsgQId = msgQOpen ("/routinesMsgQ", MAX_MSG, sizeof (uint32_t), MSG_Q_FIFO, OM_CREATE, NULL_PTR);
    if (MSG_Q_ID_NULL == routinesMsgQId)
    {
        printf ("openMsgQ  routinesMsgQId ERROR\n");   
        ret = ERROR;
    }
    return ret;
}

void module1_StartTasks(void)
{
    if (taskSpawn("readDiag", 202, 0, 2000, (FUNCPTR) module1_ReadChipRegistersTask, 0, 0, /* PRQA S 0752 */ /* PRQA S 0313 */
            0, 0, 0, 0, 0, 0, 0, 0) == ERROR)
    {
            printf("taskSpawn of readDiagTask failed\n"); /* PRQA S 3200 */
            (void) msgQClose(diagMsgQId);
            (void) msgQUnlink("/diagMsgQ");
    }
    
    if (taskSpawn("getRoutine", 204, 0, 100, (FUNCPTR) module1_GetRoutineNum, 0, 0, /* PRQA S 0752 */
            0, 0, 0, 0, 0, 0, 0, 0) == ERROR)
    {
        printf("taskSpawn of getRoutineNum failed\n"); /* PRQA S 3200 */
        (void) msgQClose(routinesMsgQId);
        (void) msgQUnlink("/routinesMsgQ");
    }
    
}    

void module1_ConfigureEthInterface(void)
{
    ifconfig("hmi0 inet6 add fd53:7cb8:383:3::4f prefixlen 64"); /* PRQA S 3200 */ /* PRQA S 0752 */
    ifconfig("hmi0 up"); /* PRQA S 3200 */ /* PRQA S 0752 */
    Sysctl("net.inet6.forwarding=1"); /* PRQA S 3335 */
}

void module1_ConfigureVLAN(void)
{
    ifconfig("vlan10 create vlan 1234 vlanif hmi0 inet 192.168.122.60 up"); /* PRQA S 3200 */ /* PRQA S 0752 */
    ifconfig("vlan10 inet6 add fd53:7cb8:383:2::4a prefixlen 64 up"); /* PRQA S 3200 */ /* PRQA S 0752 */
}


