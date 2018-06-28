/**
 *  \file 
 *      moduleTwoCommunication.c
 *      
 *  \brief 
 *       Interface functions for reading shared memory and message queues for
 *       reading diagnostic data from module one.
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
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include <msgQLibCommon.h>
#include <sys/mman.h>
#include "moduleTwoCommunication.h"

/************************************************************************
 * GLOBAL VARIABLES
 ***********************************************************************/
s_DIAG_SHM_DATA _diag_shm_struct;
s_DIAG_DATA _diag_data_struct_mod1;
s_DIAG_DATA _diag_data_struct_mod2;

MSG_Q_ID diagMsgQId = MSG_Q_ID_NULL;

/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL s_DIAG_SHM_DATA * _diag_shm_ptr_check;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
STATUS _module2_ReadDiagMsgQ(void)
{
    int32_t length;
    int8_t ret   = OK;
    
    diagMsgQId = msgQOpen ("/diagMsgQ", 1, sizeof (_diag_data_struct_mod1), MSG_Q_FIFO, OM_CREATE, NULL_PTR);
    if (MSG_Q_ID_NULL == diagMsgQId)
    {
        ret = ERROR;
    }
    
    /* Read diagnostic data from _msg queue */
    length = msgQReceive (diagMsgQId, (char *) &_diag_data_struct_mod1, sizeof (_diag_data_struct_mod1), WAIT_FOREVER);  /* PRQA S 3101 */ /* PRQA S 3102 */

    _diag_data_struct_mod2 = _diag_data_struct_mod1;

    if (length < 0)
    {
        printf ("checkMSGq ERROR\n");
        ret = ERROR;
    }

    /* Read diagnostic data from sh mem */
    (void) _module2_shMem_Check();
    
    return ret;
}

STATUS _sharedMemAlloc_module2(void)
{
    int8_t err = OK;
    
    /* Take pointers to shared memories */
    _diag_shm_ptr_check = (s_DIAG_SHM_DATA *) _module2_shMem_open(SH_MEM_NAME, sizeof (s_DIAG_SHM_DATA));

    if (NULL_PTR == _diag_shm_ptr_check)
    {
        printf("module 2 shared memory alloc error.\n");
        err = ERROR;
    }
    
    return err;
}

LOCAL void * _module2_shMem_open(const char * fname, size_t size)
{
    void * retAddr;
    int fd;
    int8_t err = OK;
    
    /* create a new SHM object if it doesn't exist*/
    fd = shm_open (SH_MEM_NAME, 2, (int32_t) (0x0100U | 0x0080U));
    if (fd == -1) 
    {
        perror("shm_open");
        err = ERROR;
        retAddr = NULL_PTR; 
    }
    
    if ((ftruncate (fd, (off_t) size) == -1) || (ERROR == err)) 
    {
        fprintf (stderr, "BR ERROR truncating shm:'%s' sizeof()=%ld\n", fname, (unsigned long) size);
        perror ("ftruncate");
        err = ERROR;
        retAddr = NULL_PTR;
    }
    
    /* Map shared memory object in the address space of the process */
    retAddr = mmap (NULL_PTR, size,
             (int32_t) (0x0001U | 0x0002U),
             0x0001, fd, 0);
    if ((retAddr == (void *) (-1)) || (ERROR == err))
    {
         perror ("mmap");
         err = ERROR;
         retAddr = NULL_PTR;
    }
    /* close the file descriptor; the mapping is not impacted by this */
    (void) close (fd);
    
    return retAddr;
}

LOCAL STATUS _module2_shMem_Check(void)
{
    int8_t ret    = OK;
    
    if (NULL_PTR != _diag_shm_ptr_check)
    {
        _diag_shm_struct.jabber_detect = _diag_shm_ptr_check->jabber_detect;
        _diag_shm_struct.phy_id_reg1 = _diag_shm_ptr_check->phy_id_reg1;
        _diag_shm_struct.phy_id_reg2 = _diag_shm_ptr_check->phy_id_reg2;
        _diag_shm_struct.type_no = _diag_shm_ptr_check->type_no;
        _diag_shm_struct.revision_no = _diag_shm_ptr_check->revision_no;
        _diag_shm_struct.phy_id_reg3 = _diag_shm_ptr_check->phy_id_reg3;
    }
    else
    {
        printf ("shMemCheck ERROR\n");
        ret = ERROR;
    }
    return ret;
}

