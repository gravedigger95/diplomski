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
#include <pmapLib.h>
#include <vmLibCommon.h>
#include <msgQLibCommon.h>
#include <time.h>
#include <sys/mman.h>
#include <net/utils/ifconfig.h>
#include <sys/fcntlcom.h>
#include <stat.h> 
#include "readEthPhy.h"

/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/

LOCAL s_DIAG_DATA       _diag_data_struct;
LOCAL s_DIAG_SHM_DATA   _diag_shm;
LOCAL s_DIAG_SHM_DATA * _diag_shm_ptr;
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
