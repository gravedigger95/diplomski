#include <vxworks.h>
#include <stdio.h>
#include <msgQLibCommon.h>
#include <vmLibCommon.h>
#include <pmapLib.h>
#include "readEthPhy.h"

/************************************************************************
 * GLOBAL VARIABLES
 ***********************************************************************/
MSG_Q_ID routinesMsgQId = MSG_Q_ID_NULL;
MSG_Q_ID diagMsgQId     = MSG_Q_ID_NULL;

LOCAL char * ethIf_macVirtAddr = BR_NULL_PTR;
/* Phy address register */
volatile uint32_t * phyGmiiAddress;
/* Phy data register */
volatile uint32_t * phyGmiiData;

LOCAL s_DIAG_DATA       _diag_data_struct;

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
	Sysctl("net.inet6.forwarding=1");
}

void module1_ConfigureVLAN(void)
{
	ifconfig("vlan10 create vlan 1234 vlanif hmi0 inet 192.168.122.60 up"); /* PRQA S 3200 */ /* PRQA S 0752 */
	ifconfig("vlan10 inet6 add fd53:7cb8:383:2::4a prefixlen 64 up"); /* PRQA S 3200 */ /* PRQA S 0752 */
}


