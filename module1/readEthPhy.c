/**
 *  \file 
 *      readEthPhy.c
 *      
 *  \brief 
 *       Functions to read and write in TJA1100 registers.
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
/* Error Message: Msg(7:4542) A non-negative constant expression of 'essentially 
 * signed' type (signed char) is being used as the left-hand operand of this bitwise operator (&).MISRA C:2012 Rule-10.1
 * 
 * Justification : This is checked and considered safe. This implementation increases
 * code simplicity and visibility.
 */
 /* PRQA S 4542 EOF */
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
/* Error Message: Msg(7:0310) Casting to different object pointer type.MISRA C:2012 
 * Rule-11.3; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantic
 * 
 * Justification : This is checked and considered safe. It is confirmed by multiple
 * testing cases and long period project usage. 
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0316) [I] Cast from a pointer to void to a pointer to 
 * object type.MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
 * 
 * Justification : This is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0339) Octal constant used.MISRA C:2012 Rule-7.1
 * 
 * Justification : The code that produces this message is part of VxWorks
 *                 kernel code.  
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(8:3335) No function declaration. Implicit declaration inserted: 
 * 'extern int ping6();'.MISRA C:2012 Rule-17.3; REFERENCE - ISO:C90-6.3.2.2 Function Calls - Semantics
 * 
 * Justification : This is Wind River's function and is not introduced through .h file
 * so it is used as it is.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1861) The operands of this bitwise operator are of 
 * different 'essential signedness' but will generate a result of type 
 * 'signed int'.MISRA C:2012 Rule-10.41
 * 
 * Justification : This is used as bit mask.
 */
/* ------------------------------------------------------------------------- */
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include <memLib.h>
#include <netLib.h>
#include <pmapLib.h>
#include <vmLibCommon.h>
#include <msgQLibCommon.h>
#include <time.h>
#include <sys/mman.h>
#include <net/utils/ifconfig.h>
#include <rtpLibcommon.h>
#include <sys/fcntlcom.h>
#include <stat.h> 
#include "readEthPhy.h"

/************************************************************************
 * GLOBAL VARIABLES
 ***********************************************************************/
MSG_Q_ID routinesMsgQId = MSG_Q_ID_NULL;
MSG_Q_ID diagMsgQId     = MSG_Q_ID_NULL;

/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL char * ethIf_macVirtAddr = BR_NULL_PTR;
/* Phy address register */
LOCAL volatile uint32_t * phyGmiiAddress;
/* Phy data register */
LOCAL volatile uint32_t * phyGmiiData;

LOCAL s_DIAG_DATA       _diag_data_struct;
LOCAL s_DIAG_SHM_DATA   _diag_shm;
LOCAL s_DIAG_SHM_DATA * _diag_shm_ptr;

LOCAL char _errors[ERROR_BUFF_SIZE];

LOCAL uint8_t _delete_cnt = 0U;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/

LOCAL void _module1_ReadChipRegisters(void)
{
    uint8_t i = 0;
    time_t rawtime = time (NULL_PTR);
    struct tm * timeinfo;
    uint32_t size_f;
    
    (void) time (&rawtime);

    for (i = 0U; i < 4U; i++)
    {
        _errors[i] = (char) 0;
    }

    /*
    printf ("BCR 0x%04x\n\n", mdio_read_br (0x0));
    printf ("BSR 0x%04x\n\n", mdio_read_br (0x1));
    printf ("ESR 0x%04x\n\n", mdio_read_br (0xF));
    printf ("ECR 0x%04x\n\n", mdio_read_br (0x11));
    printf ("CR1 0x%04x\n\n", mdio_read_br (0x12));
    printf ("CR2 0x%04x\n\n", mdio_read_br (0x13));
    printf ("ISR 0x%04x\n\n", mdio_read_br (0x15));
    printf ("IER 0x%04x\n\n", mdio_read_br (0x16));
    printf ("CSR 0x%04x\n\n", mdio_read_br (0x17));
    printf ("GSR 0x%04x\n\n", mdio_read_br (0x18));
    printf ("BCR 0x%04x\n\n", mdio_read_br (0x1A));
    */
    
    _diag_data_struct.phy_id_reg1 = (uint16_t) (mdio_read_br (PHY_ID_REGISTER_1));
    //printf ("MSGQ phy_id_reg1 0x%04x\n\n", _diag_data_struct.phy_id_reg1);

    _diag_data_struct.link_status = (uint8_t) (mdio_read_br (BASIC_STATUS_REGISTER) & LINK_STATUS_MASK);
    //printf ("link_status 0x%04x\n\n", _diag_data_struct.link_status);

    if ((uint8_t) 0U == _diag_data_struct.link_status)
    {
        i = 0;
        (void) strcpy (_diag_data_struct.errors_array[i].description, "Link is down.");
        timeinfo = localtime (&rawtime);
        _module1_getErrorTime(timeinfo, i);
    }
    
    _diag_data_struct.link_control = (uint8_t) (mdio_read_br (EXTENDED_CONTROL_REGISTER) & LINK_CONTROL_MASK);
    //printf ("link_control 0x%04x\n\n", _diag_data_struct.link_control);
    _diag_data_struct.power_mode = (uint8_t) (mdio_read_br (EXTENDED_CONTROL_REGISTER) & POWER_MODE_MASK);
    //printf ("power_mode 0x%04x\n\n", _diag_data_struct.power_mode);
    _diag_data_struct.loopback_mode = (uint8_t) (mdio_read_br (EXTENDED_CONTROL_REGISTER) & LOOPBACK_MODE_MASK);
    //printf ("loopback_mode 0x%04x\n\n", _diag_data_struct.loopback_mode);
    _diag_data_struct.phy_init_fail = (uint8_t) (mdio_read_br (INTERRUPT_SOURCE_REGISTER) & PHY_FAIL_MASK);
    //printf ("phy_init_fail 0x%04x\n\n", _diag_data_struct.phy_init_fail);
    
    if ((uint8_t) 1U == _diag_data_struct.phy_init_fail)
    {
        i = 1;
        (void) strcpy (_diag_data_struct.errors_array[i].description, "PHY initialization error detected.");
        timeinfo = localtime (&rawtime);
        _module1_getErrorTime(timeinfo, i);
    }
    
    _diag_data_struct.wakeup = (uint8_t) (mdio_read_br (INTERRUPT_SOURCE_REGISTER) & WAKEUP_MASK);
    //printf ("wakeup 0x%04x\n\n", _diag_data_struct.wakeup);
    _diag_data_struct.link_status_fail = (uint8_t) (mdio_read_br (INTERRUPT_SOURCE_REGISTER) & LINK_STATUS_FAIL_MASK);
    //printf ("link_status_fail 0x%04x\n\n", _diag_data_struct.link_status_fail);
    
    if ((uint8_t) 1U == _diag_data_struct.link_status_fail)
    {
        i = 2;
        (void) strcpy (_diag_data_struct.errors_array[i].description, "LINK_UP bit changed from OK to FAIL.");
        timeinfo = localtime (&rawtime);
        _module1_getErrorTime(timeinfo, i);
    }
    
    _diag_data_struct.link_status_up = (uint8_t) (mdio_read_br (INTERRUPT_SOURCE_REGISTER) & LINK_STATUS_UP_MASK);
    //printf ("link_status_up 0x%04x\n\n", _diag_data_struct.link_status_up);
    _diag_data_struct.link_up = (uint8_t) (mdio_read_br (COMMUNICATION_STATUS_REGISTER) & LINK_UP_MASK);
    //printf ("link_up 0x%04x\n\n", _diag_data_struct.link_up);
    
    if ((uint8_t) 0U == _diag_data_struct.link_up)
    {
        i = 3;
        (void) strcpy (_diag_data_struct.errors_array[i].description, "Link failure.");
        timeinfo = localtime (&rawtime);
        _module1_getErrorTime(timeinfo, i);
    }
    
    _diag_data_struct.tx_mode = (uint8_t) (mdio_read_br (COMMUNICATION_STATUS_REGISTER) & TX_MODE_MASK);
    //printf ("tx_mode 0x%04x\n\n", _diag_data_struct.tx_mode);
    _diag_data_struct.loc_rcvr_status = (uint8_t) (mdio_read_br (COMMUNICATION_STATUS_REGISTER) & LOC_RCVR_MASK);
    //printf ("loc_rcvr_status 0x%04x\n\n", _diag_data_struct.loc_rcvr_status);
    _diag_data_struct.rem_rcvr_status = (uint8_t) (mdio_read_br (COMMUNICATION_STATUS_REGISTER) & REM_RCVR_MASK);   
    //printf ("rem_rcvr_status 0x%04x\n\n", _diag_data_struct.rem_rcvr_status);

    _diag_data_struct.phy_state = (uint8_t)  (mdio_read_br (COMMUNICATION_STATUS_REGISTER) & 0x0003U);
    //printf ("phy_state 0x%04x\n\n", _diag_data_struct.phy_state);
    
    _diag_data_struct.signal_quality = (uint8_t) (mdio_read_br (COMMUNICATION_STATUS_REGISTER) & 0x00C0U);
    
    
    _delete_cnt++;

    if (_delete_cnt == (uint8_t) 255U)
    {
        remove ("/mmc0:1/err/errorLog.txt");
    }
    
}

void module1_InitPhy(void)
{
    FILE * fd;
    
    const UINT32 hwRegEthIfBaseaddr = (UINT32) 0xFF702000U;
    _errors[0] = (char) 0;

    ethIf_macVirtAddr = pmapGlobalMap (hwRegEthIfBaseaddr, (size_t) 0xFF,  /* PRQA S 0317 */
                MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED); /* PRQA S 4436 */
    
    if ((ethIf_macVirtAddr == PMAP_FAILED) || (ethIf_macVirtAddr == BR_NULL_PTR)) /* PRQA S 0306 */
    {
        printf ("pmapGlobalMap returned ERROR. (ethIf)\n"); 
        _errors[0] = (char) 1;
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

uint32_t mdio_read_br(uint32_t regNumber)
{
    uint8_t cnt = 0U;
    uint32_t temp = 0U;

    temp = *phyGmiiAddress;
    temp &= CLEAR_MASK;

    /* Setting mask on address register */
    regNumber <<= (uint32_t) BIT_OFFSET;
    regNumber += (uint32_t) SET_READ_MASK;
    temp |= regNumber;

    *phyGmiiAddress = temp;

    while (((uint32_t) 0x0 != (*phyGmiiAddress & (uint32_t) 0x1)) || ((uint8_t) 255 != cnt))
    {
        cnt++;
    }
    
    return *phyGmiiData;
}

void mdio_write_br(uint32_t regNumber, uint16_t dataWrite)
{
    uint8_t cnt = 0U;
    uint32_t temp = 0U;

    /* Setting mask on address register */
    temp = *phyGmiiAddress;
    temp &= CLEAR_MASK;
    regNumber <<= BIT_OFFSET;
    regNumber += SET_WRITE_MASK;
    temp |= regNumber;
    
    *phyGmiiData = dataWrite;
    *phyGmiiAddress = temp;
    
    while (((uint32_t) 0x0 != (*phyGmiiAddress & (uint32_t) 0x1)) || ((uint8_t) 255 != cnt))
    {
        cnt++;
    }
}

LOCAL STATUS _module1_CreateMsgQueues(void)
{
    int8_t ret = OK;
    _errors[1] = (char) 0;

    /* Open public message queues */
    diagMsgQId = msgQOpen ("/diagMsgQ", MAX_MSG, sizeof (_diag_data_struct), MSG_Q_FIFO, OM_CREATE, NULL_PTR);
    if (MSG_Q_ID_NULL == diagMsgQId)
    {
        printf ("openMsgQ  diagMsgQId ERROR\n");
        _errors[1] = (char) 1;
        ret = ERROR;
    }
    
    routinesMsgQId = msgQOpen ("/routinesMsgQ", MAX_MSG, sizeof (uint32_t), MSG_Q_FIFO, OM_CREATE, NULL_PTR);
    if (MSG_Q_ID_NULL == routinesMsgQId)
    {
        printf ("openMsgQ  routinesMsgQId ERROR\n");   
        _errors[1] = (char) 1;
        ret = ERROR;
    }
    return ret;
}

void module1_ReadChipRegistersTask(void)
{
    _sharedMemAlloc();
    
    FOREVER
    {
        /* Read register values for msg queue */
        _module1_ReadChipRegisters();
        /* Send to msg queue */
        (void) msgQSend (diagMsgQId, (char *) &_diag_data_struct, sizeof (_diag_data_struct), NO_WAIT, MSG_PRI_NORMAL); /* PRQA S 0310 */  

        /* Read register values for sh mem */
        (void) _module1_FillSharedMem();
        (void) taskDelay (TASK_DELAY_25MS);
    }
}


STATUS module1_GetRoutineNum(void)
{
    int32_t routineNum = 0;
    int32_t length     = 0;
    _errors[3]         = (char) 0;
    
    FOREVER
    {
        /* Read routine number sent from module 2 */ 
        length = msgQReceive (routinesMsgQId, (char *) &routineNum, sizeof (routineNum), WAIT_FOREVER); /* PRQA S 0310 */ /* PRQA S 3101 */ /* PRQA S 3102 */
        if (length < 0)
        {
            printf ("getRoutineNum ERROR\n");
            _errors[3] = (char) 1;
            return (ERROR);
        }
        else
        {
            _errors[3] = (char) 0;
        }
        printf ("routineNum %d\n", routineNum);
        /* Start desired routine */
        
        _testModes (routineNum);

        (void) taskDelay (TASK_DELAY_100MS);
    }
}

LOCAL STATUS _sharedMemAlloc(void)
{
    int8_t err = OK;

    /* Take pointers to shared memories */
    _diag_shm_ptr = (s_DIAG_SHM_DATA *) _module1_shMem_Alloc (SH_MEM_NAME, sizeof (s_DIAG_SHM_DATA)); /* PRQA S 0316 */

    if (NULL_PTR == _diag_shm_ptr)
    {
        printf("module 1 shared memory alloc error.\n");
        err = ERROR;
    }
    
    return err;
}

LOCAL STATUS _module1_FillSharedMem(void)
{
    int8_t ret = OK;
    _errors[4] = (char) 0;

    if (_diag_shm_ptr != NULL_PTR)
    {
        _diag_shm_ptr->jabber_detect = (uint8_t) (mdio_read_br (BASIC_STATUS_REGISTER) & JABBER_DETECT_MASK);
        //printf ("jabber_detect 0x%04x\n\n", _diag_shm_ptr->jabber_detect);
        _diag_shm_ptr->phy_id_reg1 = (uint16_t) (mdio_read_br (PHY_ID_REGISTER_1));
        //printf ("SHARED FILL phy_id_reg1 0x%04x\n\n", _diag_shm_ptr->phy_id_reg1);  
        _diag_shm_ptr->phy_id_reg2 = (uint8_t) (mdio_read_br (PHY_ID_REGISTER_2) & PHY_ID_REG2_MASK);
        //printf ("phy_id_reg2 0x%04x\n\n", _diag_shm_ptr->phy_id_reg2);
        _diag_shm_ptr->type_no = (uint8_t) (mdio_read_br (PHY_ID_REGISTER_2) & TYPE_NO_MASK);
        //printf ("type_no 0x%04x\n\n", _diag_shm_ptr->type_no);
        _diag_shm_ptr->revision_no = (uint8_t) (mdio_read_br (PHY_ID_REGISTER_2) & REVISION_NO_MASK);
        //printf ("revision_no 0x%04x\n\n", _diag_shm_ptr->revision_no);
        _diag_shm_ptr->phy_id_reg3 = (uint8_t) (mdio_read_br (PHY_ID_REGISTER_3) & PHY_ID_REG3_MASK);
        //printf ("phy_id_reg3 0x%04x\n\n", _diag_shm_ptr->phy_id_reg3);
        _diag_shm_ptr->int_status = (uint8_t) (mdio_read_br (GENERAL_STATUS_REGISTER) & INT_STATUS_MASK);

        /*
        printf("REGISTAR 0x00 = 0x%04x\n\n", mdio_read_br(0x00));
        printf("REGISTAR 0x01 = 0x%04x\n\n", mdio_read_br(0x01));
        printf("REGISTAR 0x02 = 0x%04x\n\n", mdio_read_br(0x02));
        printf("REGISTAR 0x03 = 0x%04x\n\n", mdio_read_br(0x03));
        printf("REGISTAR 0x0F = 0x%04x\n\n", mdio_read_br(0x0f));
        printf("REGISTAR 0x10 = 0x%04x\n\n", mdio_read_br(0x10));
        printf("REGISTAR 0x11 = 0x%04x\n\n", mdio_read_br(0x11));
        printf("REGISTAR 0x12 = 0x%04x\n\n", mdio_read_br(0x12));
        printf("REGISTAR 0x13 = 0x%04x\n\n", mdio_read_br(0x13));
        printf("REGISTAR 0x14 = 0x%04x\n\n", mdio_read_br(0x14));
        printf("REGISTAR 0x15 = 0x%04x\n\n", mdio_read_br(0x15));
        printf("REGISTAR 0x16 = 0x%04x\n\n", mdio_read_br(0x16));
        printf("REGISTAR 0x17 = 0x%04x\n\n", mdio_read_br(0x17));
        printf("REGISTAR 0x18 = 0x%04x\n\n", mdio_read_br(0x18));
         */

    }
    else
    {
        printf ("fillShMem ERROR\n");
        _errors[4] = (char) 1;
        ret = ERROR;
    }
    return ret;
}

LOCAL void * _module1_shMem_Alloc(const char * fname, size_t size)
{
    void * retAddr;
    int fd;
    int8_t err = OK;

    /* create a new SHM object if it doesn't exist*/
    fd = shm_open (fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1) 
    {
        perror ("shm_open");
        err = ERROR;
        retAddr = NULL_PTR;
    }
    /* set object size */
    if ((ftruncate (fd, (off_t) size) == -1) || (ERROR == err))
    {
        fprintf (stderr, "BR ERROR truncating shm:'%s' sizeof()=%ld\n", fname, (unsigned long) size);
        perror ("ftruncate");
        err = ERROR;  
        retAddr = NULL_PTR;
    }
    /* Map shared memory object in the address space of the process */
    retAddr = mmap(NULL_PTR, size,
            PROT_READ | PROT_WRITE, /* PRQA S 0306 */
            MAP_SHARED, fd, 0);
    if ((MAP_FAILED == retAddr) || (ERROR == err)) /* PRQA S 0306 */
    { 
        perror ("mmap");
        err = ERROR;
        retAddr = NULL_PTR;
    }
    /* close the file descriptor; the mapping is not impacted by this */
    (void) close (fd);
    /* The mapped memory is now available */

    return retAddr;
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

void writeToFile(void)
{
    int fd;
    
    /* Write _errors to file */
    FOREVER 
    {
        fd = open ("/mmc0:1/myErrorsArray", O_RDWR, 0664); /* PRQA S 0339 */
        if (ERROR == fd) 
        {                   
            fd = open ("/mmc0:1/myErrorsArray", O_CREAT | O_RDWR, 0664); /* PRQA S 0339 */
            if (ERROR != fd)
            {
                write (fd, _errors , sizeof (_errors));
                (void) close (fd);
            }
            else
            {
                printf ("------------------------------------Can not create file /myErrorsArray\n");
            }
        }
        else
        {
            write (fd, _errors , sizeof (_errors));
            (void) close (fd);
        }

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

LOCAL void _module1_getErrorTime(struct tm const * time_info, uint8_t pos)
{
    FILE * fd;  
    _diag_data_struct.errors_array[pos].id = pos;

    if (strftime (_diag_data_struct.errors_array[pos].timestamp, 26, "%Y-%m-%d %H:%M:%S", time_info) == (size_t) 0)
    {
        printf ("sprintf error\n");
    }   
    fd = fopen ("/mmc0:1/err/errorLog.txt", "a");

    if (NULL_PTR != fd)
    {
        (void) fprintf (fd, "Error %d | %s | %s\n", _diag_data_struct.errors_array[pos].id, _diag_data_struct.errors_array[pos].description, _diag_data_struct.errors_array[pos].timestamp);
        (void) fclose (fd);
    }   
}
