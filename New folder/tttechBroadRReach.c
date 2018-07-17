/*
 * tttechBroadRReach.c
 *
 *  Created on: Okt 15, 2015
 *      Author: ext-strauss
 */
/* ------------------------------------------------------------------------- */
/*                         SUPRESSED MISRA VIOLATONS                         */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0841) Using '#undef'.MISRA C:2012 Rule-20.5; REFERENCE - 
 * ISO:C90-6.8.3.5 Scope of Macro Definitions.zFAS Tailoring: justifyable on file 
 * scope; #undef required and used in AUTOSAR MemMap.h files
 * 
 * Justification: It is affected to this .c file only and considered acceptable.    
 */
 /* PRQA S 0841 EOF */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:5124) Use of standard header file <stdio.h>.
 * MISRA C:2012 Rule-21.6     
 * 
 * Justification: The [BRIF] unit is QM level and usage of standard header 
 * file <stdio.h> is considered acceptable.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:3447) 'vxbClkMgrPeriphEnable_desc', '_func_sysEmacPhyInit',
 * 'usrStat',... is being declared with external linkage but this declaration is not in a header 
 * file.MISRA C:2012 Rule-8.5    
 * 
 * Justification : The code that produces this message is part of VxWorks
 *                 kernel code. The globals are not provided through .h files as "extern".
 * Justification : Regarding interface mdio_read_br(), it is left extern but not introduced 
 *                 through .h file because it is going to be used only by test team through console.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:3684) Array declared with unknown size.MISRA C:2012 Rule-8.11  
 * 
 * Justification : The code that produces this message is part of VxWorks
 *                 kernel code.
 */
/* ------------------------------------------------------------------------- */
/* Error message : Msg(7:0602) [U] The identifier '_orig_func_sysEmacInit' is
 * reserved for use by the library.MISRA C:2012 Rule-1.3, Rule-21.2; 
 * REFERENCE - ISO:C90-7.1.3 Reserved Identifier
 * 
 * Justification : Static functions named according to the ZFAS coding guidelines at 
 * contractor-svn.vie.at.tttech.ttt/svn/zFAS_series/Documents/SW/
 * 03_planning&risk-management/CGL/CGL-D-ZFAS-Z-01-001.docx 
 */
/* PRQA S 0602 EOF */
/* ------------------------------------------------------------------------- */
/* Error message : Msg(7:3004) This integral constant expression is being interpreted 
 * as a NULL pointer constant.MISRA C:2012 Rule-11.9; REFERENCE - 
 * ISO:C90-6.2.2.3 Pointers, ISO:C99-6.3.2.3 Pointers
 * 
 * Justification : This is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message:Msg(10:4901) Prefixes for Type Definitions invalid 
 * 'vxbClkMgrPeriphEnable_t'.zFAS-SW Coding Guidelines 3.1.3	Prefixes for 
 * Type Definitions 
 * 
 * Justification : The code that produces this message is part of VxWorks
 *                 kernel code.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1336) Parameter identifiers missing in declaration of a 
 * function type.MISRA C:2012 Rule-8.2
 * 
 * Justification : The code that produces this message is part of VxWorks
 *                 kernel code.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(10:4901) Prefixes for Type Definitions invalid 
 * 'BR_DIAG_DATA'.zFAS-SW Coding Guidelines 3.1.3	Prefixes for Type Definitions
 * 
 * Justification : The code that produces this message is part of VxWorks
 *                 kernel code.
*/
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:3200) 'printf',... returns a value which is not being 
 * used.MISRA C:2012 Rule-17.7
 * 
 * Justification : This is not considered safety critical on QM level so is 
 * considered acceptable.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0752) String literal passed as argument to function 
 * whose parameter is not a 'pointer to const'.MISRA C:2012 Rule-7.4; 
 * REFERENCE - ISO:C90-6.1.4 String Literals - Semantics
 * 
 * Justification : This implementation increase code visibility.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:2001) A 'goto' statement has been used.MISRA C:2012 Rule-15.1
 * 
 * Justification : The functions that use "goto" statement are safety checked
 * and considered acceptable since the other solutions would take significant effort 
 * and increase number of lines of code.
 */
/* PRQA S 2001  EOF */

/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0306) [I] Cast between a pointer to object and an integral 
 * type.MISRA C:2012 Rule-11.4, Rule-11.6; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
 * 
 * Justification : The code that produces this message is part of VxWorks
 * implementation or it is used for the error checking and is considered OK.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4543) A non-negative constant expression of 'essentially 
 * signed' type (signed char) is being used as the left-hand operand of this shift
 *  operator (<<).MISRA C:2012 Rule-10.1
 * 
 * Justification : This is checked and considered safe. This implementation increases 
 * code visibility.
 */

/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4544) A non-negative constant expression of 'essentially 
 * signed' type (signed char) is being used as the right-hand operand of this shift
 *  operator (<<).MISRA C:2012 Rule-10.1
 *  
 * Justification : This is checked and considered safe. This implementation increases
 * code visibility.
 */

/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0310) Casting to different object pointer type.MISRA C:2012 
 * Rule-11.3; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantic
 * 
 * Justification : This is checked and considered safe. It is confirmed by multiple
 * testing cases and long period project usage. 
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4434) A non-constant expression of 'essentially signed' 
 * type (signed char) is being converted to unsigned type, 'unsigned int' on 
 * assignment.MISRA C:2012 Rule-10.3
 *  
 * Justification : This is checked and considered safe. It happens on nonnegative 
 * macro assignment.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0317) [I] Implicit conversion from a pointer to void to
 * a pointer to object type.MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 
 * Cast Operators - Semantics
 * 
 * Justification : This is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0316) [I] Cast from a pointer to void to a pointer to 
 * object type.MISRA C:2012 Rule-11.5; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantics
 * 
 * Justification : This is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1841) The left-hand operand is constant, 'essentially 
 * signed' (signed char) and non-negative but will be implicitly converted to an 
 * unsigned type (unsigned int) in this bitwise operation.MISRA C:2012 Rule-10.4
 * 
 * Justification : This is checked and considered safe. This implementation increases
 * code simplicity and visibility. 
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4542) A non-negative constant expression of 'essentially 
 * signed' type (signed char) is being used as the left-hand operand of this bitwise operator (&).MISRA C:2012 Rule-10.1
 * 
 * Justification : This is checked and considered safe. This implementation increases
 * code simplicity and visibility.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4436) A constant expression of 'essentially signed' type 
 * (signed int) is being converted to unsigned type, 'unsigned short' on assignment.MISRA C:2012 Rule-10.3
 * 
 * Justification : This is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1281) Integer literal constant is of an unsigned type 
 * but does not include a "U" suffix.MISRA C:2012 Rule-7.2; REFERENCE - ISO:C90-6.1.3.2 (Integer Constants)
 * 
 * Justification : The macro is used as bit mask.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4523) An expression of 'essentially enum' type (TJA1100_POWER_DOWN_t,...)
 * is being used as the left-hand operand of this shift operator (<<).MISRA C:2012 Rule-10.1
 * 
 * Justification : This is checked and considered safe. This implementation increases
 * code simplicity and visibility.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4532) An expression of 'essentially signed' type (signed int) 
 * is being used as the right-hand operand of this bitwise operator (&).MISRA C:2012 Rule-10.1
 * 
 * Justification : This is checked and considered safe. The macro is used as bit mask.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1851) The left-hand operand is 'essentially unsigned' 
 * (unsigned short) but will be implicitly converted to a signed type (signed int) 
 * in this bitwise operation.MISRA C:2012 Rule-10.4
 * 
 * Justification : This is checked and considered safe. The usage is for bit position 
 * sensitive register read/write.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1292) An integer constant of 'essentially signed' type 
 * is being converted to type char on assignment.MISRA C:2012 Rule-10.3
 * 
 * Justification : This is checked and considered safe. Used on initialization by zero.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1840) The right-hand operand is constant, 'essentially signed' 
 * (signed char) and non-negative but will be implicitly converted to an unsigned type 
 * (unsigned int) in this arithmetic operation.MISRA C:2012 Rule-10
 * 
 * Justification : This is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1291) An integer constant of 'essentially unsigned' type 
 * is being converted to signed type on assignment.MISRA C:2012 Rule-10.3
 * 
 * Justification : This is checked and considered safe ( Used on assignment of unsigned macros).
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(8:3335) No function declaration. Implicit declaration inserted: 
 * 'extern int ping6();'.MISRA C:2012 Rule-17.3; REFERENCE - ISO:C90-6.3.2.2 Function Calls - Semantics
 * 
 * Justification : This is Wind River's function and is not introduced through .h file
 * so it is used as it is.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:3007) "void" has been omitted when defining a function 
 * with no parameters.MISRA C:2012 Rule-8.2; REFERENCE - ISO:C90-6.5.4.3 Function Declarators 
 * (Including Prototypes) - Semantics, ISO:C90-6.7.1 Function Definitions - Constraints
 * 
 * Justification : This is checked and considered ok. No impact to safety or code execution.
 */

/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0339) Octal constant used.MISRA C:2012 Rule-7.1
 * 
 * Justification : The code that produces this message is part of VxWorks
 *                 kernel code.  
 */

/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1822) The right-hand operand is non-constant and 'essentially signed' 
 * (signed short) but will be implicitly converted to an unsigned type (unsigned int) 
 * in this relational operation.MISRA C:2012 Rule-10.4
 *
 * Justification : This is checked and considered ok. No impact to safety or code execution. 
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4413) An expression of 'essentially character' type (char)
 * is being converted to signed type, 'short' on assignment.MISRA C:2012 Rule-10.3
 *
 * Justification : This is checked and considered ok. 
 */
/* ------------------------------------------------------------------------- */
/* Error Message:Msg(7:4461) A non-constant expression of 'essentially unsigned' 
 * type (unsigned int) is being converted to narrower unsigned type, 'unsigned short' 
 * on assignment.MISRA C:2012 Rule-10.3
 *
 * Justification : This is checked and considered ok. 
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4538) An expression of 'essentially signed' type (signed int) 
 * is being used as the  operand of this logical operator (!).MISRA C:2012 Rule-10.1
 * 
 * Justification : The macro is used as bit mask.
 */
/* ------------------------------------------------------------------------- */
/* Error Message:Msg(7:4522) An expression of 'essentially enum' type (BR_BITMASK_ERROR) 
 * is being used as the  operand of this bitwise operator (~).MISRA C:2012 Rule-10.1
 * 
 * Justification : This is used to increase visibility and code readability .
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(6:2895) Constant: Negative value cast to an unsigned type.MISRA C:2012 Dir-1.1
 * 
 * Justification : The macro is used as bit mask.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:3206) The parameter 'pDev' is not used in this function.MISRA C:2012 Rule-2.7
 * 
 * Justification : Intended for further usage.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:3219) Static function 'tttech_BR_EmacEndInit()' is not 
 * used within this translation unit.MISRA C:2012 Rule-2.1
 * 
 * Justification : Intended for further usage.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1861) The operands of this bitwise operator are of 
 * different 'essential signedness' but will generate a result of type 
 * 'signed int'.MISRA C:2012 Rule-10.41
 * 
 * Justification : This is used as bit mask.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:1843) The left-hand operand is constant, 'essentially signed' 
 * (signed char) and non-negative but will be implicitly converted to an unsigned type 
 * (unsigned int) in this equality operation.MISRA C:2012 Rule-10.4
 * 
 * Justification : This is used to increase visibility and code readability .
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0570) This switch case label of 'essential type' 'signed char',
 * is not consistent with a controlling expression of essential type 'unsigned short'.
 * MISRA C:2012 Rule-10.3
 * 
 * Justification : This is used to increase visibility and code readability .
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(5:0488) Performing pointer arithmetic.MISRA C:2012 Rule-18.4; 
 * REFERENCE - ISO:C90-6.3.6 Additive Operators - Constraints
 * 
 * Justification : This is used for accessing the registers. The offset is added to 
 * mapped address in  virtual memory. It is checked and considered safe.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4414) An expression of 'essentially character' type (char) is being converted to 
 * unsigned type, 'unsigned short' on assignment.MISRA C:2012 Rule-10.3
 * 
 * Justification : This is checked and considered OK. The value of type char is
 * storing number of attempts of PHY initialization which is unsigned value.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0311) Dangerous pointer cast results in loss of const 
 * qualification.MISRA C:2012 Rule-11.8
 * 
 * Justification : This is checked and considered OK. The const value pointed by type 
 * pointer to void is just casted on assigning. Value by itself is not changed.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0563) [C] Right operand of assignment is not of compatible 
 * pointer type.MISRA C:2012 Rule-1.1; REFERENCE - ISO:C90-6.3.16.1 Simple Assignment - Constraints
 * 
 * Justification : This is checked and considered OK on safety aspect. It 
 * is confirmed on long period usage and multiple testing levels.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4397) An expression which is the result of a ~ or << operation 
 * has not been cast to its essential type.MISRA C:2012 Rule-10.7
 * 
 * Justification : This is checked and considered OK on safety aspect.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:3305) Pointer cast to stricter alignment.MISRA C:2012 Rule-11.3
 * 
 * Justification : This is done because of mapping physical address to the kernel virtual
 *  address space, which is done according to "char" length, and is to be used according to
 *  32bit register manipulation.
 */
 /* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:5118) Use of memory allocation or deallocation 
 * function: calloc, malloc, realloc or free.MISRA C:2012 Rule-21.3
 * 
 * Justification : This is done in kernel and in sense of network management
 * rules, and safety is confirmed through long period of use and multiple test cycles.
 */
/* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0694) Array initializer is missing the optional 
 * {.MISRA C:2012 Rule-9.2; REFERENCE - ISO:C90-6.5.7 Initialization - Semant
 * 
 * Justification :  This is checked and considered OK on safety aspect.
 *                  It increases visibility.
 */
 /* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0686) Array has fewer initializers than its declared size. 
 * Default initialization is applied to the remainder of the array elements.
 * MISRA C:2012 Rule-9.3; REFERENCE - ISO:C90-6.5.7 Initialization - Semantics
 * 
 * Justification :  This is checked and considered OK on safety aspect.
 *                  It increases visibility.
 */
/* ------------------------------------------------------------------------- */
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h> /* PRQA S 5124 */
#include <stdlib.h>
#include <string.h>
#include <ioLib.h>
#include <hwif/vxbus.h>
#include <hwif/vxbus/vxbLib.h>
#include <end.h>
#include <vxFdtLib.h>
#include <pmapLib.h>
#include <vmLibCommon.h>
#include <private/vmLibP.h>
#include <alt_soc_gen5.h>
#include <ipnet_cmd.h>
#include <if6Lib.h>
#include <inetlib.h>
#include "ErrorHandlerProxySSH_K/EHPSSH_K_ClientInterface.h"
#include "ErrorHandlerProxySSH_K/EH_ErrorIDMapping_SSH-K.h"
#include "Br_CRC.h"

#include <taskLib.h>
#include <sysLib.h>
#include <dataCollectorLib.h>
#include <private/eventDefsP.h>
#include <ifLib.h>
#include "tttechBroadRReach.h"
#include "tttechBRIF.h"

#include "moduleOneStartup.h"

#include "tttechTimeProvider.h"
#include "firewall_diag.h"

#include <prjParams.h>

#include <net/if.h>
#include <ifaddrs.h>
#include <fcntl.h>

#include <ipcom_clib.h>
#include <ipcom_cmd.h>
#include <ipcom_getopt.h>
#include <ipcom_sysctl.h>
#include <ipcom_time.h>

#include <ping6Lib.h>

#include <net/utils/ifconfig.h>
#include <net/utils/routeCmd.h> 

#include "ipnet.h"
#include "ipnet_cmd.h"
#include "ipnet_ctrl.h"
#include "ipnet_h.h"
#include "ipnet_routesock.h"

/* ------------------------------------------------------------------------- */
/* ------------------------------   Defines  ------------------------------- */
/* ------------------------------------------------------------------------- */
#undef DEBUG_DOS
#undef TEST_CHIP_INIT
#undef DEBUG_BRDIAG
#undef BR_DEBUG_PRINT

/* ------------------------------------------------------------------------- */
/* ------------------------------   Macros  -------------------------------- */
/* ------------------------------------------------------------------------- */
#ifdef DEBUG_BRDIAG
#define BRDBG_MSG(A,...) printf(A,##__VA_ARGS__)
#include <net/if.h>
#include <ifaddrs.h>
#else
#define BRDBG_MSG(A,...)
#endif

#define BR_NULL_PTR        (void*)(0)

#define CLK_MGR_PERPLL_EMAC0_CLK    (1 << 0)
#define CLK_MGR_PERPLL_EMAC1_CLK    (1 << 1)

#define ALT_SYSMGR_EMAC_CTL_PHYSEL_E_GMII_MII   0x0
#define ALT_SYSMGR_EMAC_CTL_PHYSEL_0_CLR_MSK    0xfffffffc
#define ALT_SYSMGR_EMAC_CTL_PHYSEL_1_CLR_MSK    0xfffffff3
#define ALT_SYSMGR_EMAC_CTL_PHYSEL_0_SET(value) ((value) & (~ALT_SYSMGR_EMAC_CTL_PHYSEL_0_CLR_MSK))
#define ALT_SYSMGR_EMAC_CTL_PHYSEL_1_SET(value) (((value) << 2) & (~ALT_SYSMGR_EMAC_CTL_PHYSEL_1_CLR_MSK))
#define ALT_SYSMGR_FPGA_INTF_MOD_EMAC0           0x00000004
#define ALT_SYSMGR_FPGA_INTF_MOD_EMAC1           0x00000008

#define FPGABR_AR_OFFSET 0x284U
#define FPGABR_DR_OFFSET 0x280U

#define ALT_READ_32(reg)         (*(volatile UINT32 *)(reg))
#define ALT_WRITE_32(reg, data)  (*((volatile UINT32 *)(reg)) = (data))

#define MAX_READ_COUNT 40
#define BR_VLAN_ID     (uint16_t)(2U)
/* ------------------------------------------------------------------------- */
/* ------------------------------ Data Types ------------------------------- */
/* ------------------------------------------------------------------------- */
VXB_DEVMETHOD_DECL (vxbClkMgrPeriphEnable) /* PRQA S 3447 */ /* PRQA S 3684 */
typedef STATUS (*vxbClkMgrPeriphEnable_t) (UINT32, BOOL); /* PRQA S 4901 */ /* PRQA S 1336 */

VXB_DEVMETHOD_DECL (vxbRstMgrPeriphEMACReset)  /* PRQA S 3447 */ /* PRQA S 3684 */
typedef STATUS (*vxbRstMgrPeriphEMACReset_t) (UINT32); /* PRQA S 4901 */ /* PRQA S 1336 */
/* ------------------------------------------------------------------------- */
/* -------------------------- Function Prototypes -------------------------- */
/* ------------------------------------------------------------------------- */

LOCAL STATUS _tttechCableTest(void);
LOCAL void _BRDiagTask_entry(void);
LOCAL int _tttechSwitchInfo(void); 
LOCAL int _attach_if_to_device(void);
LOCAL void _tttechBRTestModes(void);
LOCAL void _tttechBRDiagnosis(void);
LOCAL void _ttechStartBRDiagTask(void);

LOCAL void _checkOnAttack(UINT16 *dos_state);
LOCAL STATUS _readRXpackets(uint32_t *packets_cnt);
LOCAL void _BR_chip_reset(void);
LOCAL void _tDoSdetection_entry(void);
LOCAL void _recorder_Shm_Alloc(void);
LOCAL void _enable_BR_link(void);
LOCAL void _disable_BR_link(void);
LOCAL STATUS tttech_sysEmacPhyInit(VXB_DEV_ID  pDev);
LOCAL STATUS tttech_sysEmacEndInit(VXB_DEV_ID  pDev, END_OBJ *pEnd);
LOCAL STATUS tttech_sysEmacInit(VXB_DEV_ID  pDev);
LOCAL STATUS tttech_BR_EmacPhyInit(VXB_DEV_ID  pDev);
LOCAL STATUS tttech_BR_EmacEndInit(VXB_DEV_ID  pDev, END_OBJ *pEnd);
LOCAL STATUS tttech_BR_EmacInit(VXB_DEV_ID  pDev);
LOCAL STATUS mapFpga(void);

/* ------------------------------------------------------------------------- */
/* --------------------------- Global Variables ---------------------------- */
/* ------------------------------------------------------------------------- */

#if defined(DRV_FPGA_FDT_ALT_SOC_GEN5) && defined(DRV_END_FDT_ALT_SOC_GEN5_DWC) /* PRQA S 3447  4 */
    extern STATUS (*_func_sysEmacInit) (VXB_DEV_ID  pDev);
    extern STATUS (*_func_sysEmacEndInit) (VXB_DEV_ID  pDev, END_OBJ *pEnd);
    extern STATUS (*_func_sysEmacPhyInit) (VXB_DEV_ID  pDev);
#endif

extern UINT32 evtAction; /* PRQA S 3447 */

/** \brief isVLANsupport
 *   Flag for storing is VLAN support configured or not.
 */
int isVLANsupport;
LOCAL uint32_t DOS_ON = FALSE;

LOCAL STATUS (*_orig_func_sysEmacInit) (VXB_DEV_ID  pDev) = BR_NULL_PTR;
LOCAL STATUS (*_orig_func_sysEmacEndInit) (VXB_DEV_ID  pDev, END_OBJ *pEnd) = BR_NULL_PTR;
LOCAL STATUS (*_orig_func_sysEmacPhyInit) (VXB_DEV_ID  pDev) = BR_NULL_PTR;

LOCAL char *hmi0_macVirtAddr = BR_NULL_PTR;
LOCAL char *fpgaVirtAddr = BR_NULL_PTR;

LOCAL volatile uint32_t * mdio_master_data_reg_br;
LOCAL volatile uint32_t * mdio_master_addr_reg_br;

LOCAL MSG_Q_ID BRDiag_msgQ_ID = MSG_Q_ID_NULL;
LOCAL MSG_Q_ID BRTriggerTest_msqQ_ID = MSG_Q_ID_NULL;


LOCAL uint64_t *Rec_DoSTimestamp = BR_NULL_PTR;

/**  from SAD ID:1741003    */
LOCAL Dt_RECORD_EHReporterID _Reporter_ID = {
        SWCID_PF_OS,
        0 ,
        0x5a97 };

LOCAL s_BRIF_INFO 	_BRIFInfo;
LOCAL s_BRIF_INFO * _brif_info = BR_NULL_PTR;
LOCAL s_BRIF_DATA	_BRIFData;
s_BRIF_DATA *	_brif_data = BR_NULL_PTR;
LOCAL s_BR_DIAG_PING_DATA _BRIFPingData[BR_MAX_PING_HOSTS];
LOCAL s_BR_DIAG_PING_DATA *	_brif_ping_data = BR_NULL_PTR;

LOCAL s_BR_DIAG_DATA  _BRDiagData;
LOCAL uint8_t       _SSHProduction_buff[SSH_MAC_PROD_PAGESIZE];
LOCAL uint16_t      _brErrorStatus = 0;
LOCAL uint8_t       _cable_test_counter = 0;
LOCAL uint16_t      _cable_test_result = 0;
LOCAL uint8_t     	_not_started_cycle_num = 0; /* to assure sending initial state only once */

LOCAL const uint8_t _Br_MAC[6] = BR_MAC_ADDRESS_DEFAULT; /* PRQA S 0605 */
LOCAL const Dt_ENUM_EHErrorID _brErrorCodes[5] = {
        ERR_EXTIF_SSH_BROADR_1,
        ERR_EXTIF_SSH_BROADR_2,
        ERR_EXTIF_SSH_BROADR_3,
        ERR_EXTIF_SSH_BROADR_O,
        ERR_EXTIF_SSH_BROADR_S };

LOCAL uint16 br_init_fail_cnt = 0;  /* SAD ID:1429712 */
LOCAL uint16 br_fail_drv_cycle = 0;
LOCAL char rwFile_drv_cnt[1];

/* PRQA S 0750 4 */ /* PRQA S 0759 4 */
LOCAL volatile uint32_t * id_comp_base;
LOCAL union { uint32_t n; uint8_t byte[4]; } ifsetv;



/* ------------------------------------------------------------------------- */
/* ------------------------ Function Implementation ------------------------ */
/* ------------------------------------------------------------------------- */




LOCAL STATUS mapFpga(void) {
    FUNCPTR fpgaMgrIsReady;
    uint32_t phyaddr;
    int offset;
    uint32_t *prop;

    fpgaVirtAddr = BR_NULL_PTR;

    offset = vxFdtPathOffset("/alt_soc/fpga");  /* PRQA S 0752 */
    if (offset <= 0) {
        printf("ERROR: no FPGA unit present in this board\n"); /* PRQA S 3200 */
        return ERROR;
    }
    prop = (uint32_t*) vxFdtPropGet(offset, "reg", BR_NULL_PTR);  /* PRQA S 0752 */ /* PRQA S 0311 */  /* PRQA S 0316 */
    phyaddr = vxFdt32ToCpu(*prop);

    /* OK - now map it */

    fpgaVirtAddr = pmapGlobalMap((PHYS_ADDR) phyaddr, (size_t) 0x1000, /* PRQA S 4436 2 */ /* PRQA S 4542 2 */  /* PRQA S 0317 */
    MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED); 

    if (fpgaVirtAddr == PMAP_FAILED) { /* PRQA S 0306 */
        printf("pmapGlobalMap returned ERROR.\n"); /* PRQA S 3200 */
        return ERROR;
    }

    return OK;
}

LOCAL STATUS tttech_BR_EmacInit(VXB_DEV_ID  pDev)
{
    VXB_DEV_ID          pClkMgr  = BR_NULL_PTR;
    VXB_DEV_ID          pRstMgr  = BR_NULL_PTR;
    
    vxbClkMgrPeriphEnable_t     vxbClkMgrPeriphEnable    = BR_NULL_PTR;
    vxbRstMgrPeriphEMACReset_t  vxbRstMgrPeriphEMACReset = BR_NULL_PTR;

    IMPORT FUNCPTR fpgaMgr_vxbRstMgrBridgeReset; /* PRQA S 3447 3 */ /* PRQA S 3222 3 */
    IMPORT FUNCPTR fpgaMgr_vxbL3FpgaEnable;
    IMPORT FUNCPTR fpgaMgr_vxbSdCtlFpgaPortReset;

    INT32               offset   = 0;
    UINT32            * prop;
    UINT32              phyaddr  = 0;
    char              * virtAddr = BR_NULL_PTR;
    UINT32              emacGrpReg = 0;

    if (BR_NULL_PTR != _func_kprintf) {
        (*_func_kprintf)("tttech_BR_EmacInit(%d)\n", vxbDevUnitGet(pDev));
    }
    VXB_ASSERT (pDev != BR_NULL_PTR, ERROR)

    /* enable emac0 clock */
    pClkMgr = vxbInstByNameFind("altr-clk-mgr", 0); /* PRQA S 0752 */ 
    if (pClkMgr == BR_NULL_PTR) {
        goto FAIL;
    }

    vxbClkMgrPeriphEnable = vxbDevMethodFind (pClkMgr, VXB_DEVMETHOD_CALL(vxbClkMgrPeriphEnable)); /* PRQA S 0306 */
    if (vxbClkMgrPeriphEnable == BR_NULL_PTR) {
        goto FAIL;
    }

    (*vxbClkMgrPeriphEnable) ((vxbDevUnitGet(pDev)==(UINT32)0) ? CLK_MGR_PERPLL_EMAC0_CLK : CLK_MGR_PERPLL_EMAC1_CLK, TRUE); /* PRQA S 4434 */ /* PRQA S 4543 */ /* PRQA S 4544 */

    offset = vxFdtPathOffset("/alt_soc/sysmgr"); /* PRQA S 0752 */ 
    if (offset <= 0) {
        goto FAIL;
    }
    
    prop = (UINT32*) vxFdtPropGet(offset, "reg", BR_NULL_PTR);  /* PRQA S 0752 */ /* PRQA S 0311 */ /* PRQA S 0316 */
    phyaddr = vxFdt32ToCpu(*(UINT32*)prop);

    virtAddr = pmapGlobalMap ((PHYS_ADDR) phyaddr, (size_t) 0x1000, /* PRQA S 4436 2 */ /* PRQA S 4542 2 */ /* PRQA S 0317 */
                                MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | 
                                MMU_ATTR_CACHE_GUARDED);
    if (virtAddr == PMAP_FAILED) { /* PRQA S 0306 */
        goto FAIL;
    }

    /* get the System Manager EMAC control bits */

    emacGrpReg = ALT_READ_32(virtAddr + SYSMGR_EMACGRP_CTRL); /* PRQA S 0488 */  /* PRQA S 0310 */ /* PRQA S 3305 */

    /* clear the System Manager EMAC PHY Select control bits */
    if (vxbDevUnitGet(pDev) == (uint32_t)0)
    {
        emacGrpReg &= ALT_SYSMGR_EMAC_CTL_PHYSEL_0_CLR_MSK;  /* PRQA S 1281 */
    
        /* set the System Manager RGMII bits */
    
        /* port 0, which is our Eth interface on the dev board */
    
        emacGrpReg |= ALT_SYSMGR_EMAC_CTL_PHYSEL_0_SET(ALT_SYSMGR_EMAC_CTL_PHYSEL_E_GMII_MII); /* PRQA S 1281 */  /* PRQA S 1841 */  /* PRQA S 4542 */
    }
    else
    {
        emacGrpReg &= ALT_SYSMGR_EMAC_CTL_PHYSEL_1_CLR_MSK;   /* PRQA S 1281 */
    
        /* set the System Manager RGMII bits */
    
        /* port 0, which is our Eth interface on the dev board */
    
        emacGrpReg |= ALT_SYSMGR_EMAC_CTL_PHYSEL_1_SET(ALT_SYSMGR_EMAC_CTL_PHYSEL_E_GMII_MII);/* PRQA S 4544 */ /* PRQA S 1281 */ /* PRQA S 4543 */  /* PRQA S 1841 */  /* PRQA S 4542 */
        
    }
    ALT_WRITE_32(virtAddr + SYSMGR_EMACGRP_CTRL, emacGrpReg); /* PRQA S 0310 */ /* PRQA S 0488 */ /* PRQA S 3305 */

    /* enable signals from the FPGA fabric to the EMAC module, as PHY is in FPGA PL */
     /* PRQA S 4542 2 */  /* PRQA S 4436 2 */
    ALT_WRITE_32(virtAddr + SYSMGR_FPGAINTFGRP_MODULE, ALT_SYSMGR_FPGA_INTF_MOD_EMAC0 | ALT_SYSMGR_FPGA_INTF_MOD_EMAC1); /* PRQA S 0310 */ /* PRQA S 0488 */ /* PRQA S 3305 */

    /* reset emac0 */
    pRstMgr = vxbInstByNameFind("altr-rst-mgr", 0); /* PRQA S 0752 */
    if (pRstMgr == BR_NULL_PTR) {
        goto FAIL;
    }
    /* PRQA S 0306 3 */
    vxbRstMgrPeriphEMACReset = vxbDevMethodFind (pRstMgr, 
                            VXB_DEVMETHOD_CALL(vxbRstMgrPeriphEMACReset));
    if (vxbRstMgrPeriphEMACReset == BR_NULL_PTR) {
        goto FAIL;
    }

    (*vxbRstMgrPeriphEMACReset) (vxbDevUnitGet(pDev));

    if (vxbDevUnitGet(pDev) == (uint32_t)0)
    {
        /* reset fpga */
        if (fpgaMgr_vxbRstMgrBridgeReset == BR_NULL_PTR) {
            goto FAIL;
        }
        fpgaMgr_vxbRstMgrBridgeReset ();
    
        /* enable fpga */
        if (fpgaMgr_vxbL3FpgaEnable == BR_NULL_PTR) {
            goto FAIL;
        }
        fpgaMgr_vxbL3FpgaEnable ();
    
        if (fpgaMgr_vxbSdCtlFpgaPortReset == BR_NULL_PTR) {
            goto FAIL;
        }
        fpgaMgr_vxbSdCtlFpgaPortReset ();
    }
    if (BR_NULL_PTR != _func_kprintf) {
        (*_func_kprintf)("tttech_BR_EmacInit OK\n");
    }
    return OK;

FAIL:
    if (BR_NULL_PTR != _func_kprintf) {
        (*_func_kprintf)("tttech_BR_EmacInit ERROR\n");
    }
    
    return ERROR;
}

LOCAL STATUS tttech_BR_EmacEndInit(VXB_DEV_ID  pDev, END_OBJ *pEnd) /* PRQA S 3206 */ /* PRQA S 3219 */
{
    return OK;
}

LOCAL STATUS tttech_BR_EmacPhyInit(VXB_DEV_ID  pDev) /* PRQA S 3206 */
{
    int offset;
    UINT32 *prop;
    uint32_t phy_id;
    uint32_t read_data;
    UINT16 miiVal;
    int i;
    STATUS           status_val;
    if (BR_NULL_PTR != _func_kprintf) {
        (*_func_kprintf)("tttech_BR_EmacPhyInit\n");
    }
    if (fpgaVirtAddr == BR_NULL_PTR){
        mapFpga();/* PRQA S 3200 *//* The status of execution is checked by checking variable 'fpgaVirtAddr' */
    }
    if (fpgaVirtAddr == BR_NULL_PTR) {
        printf("\nError mapping address\n"); /* PRQA S 3200 */

        return (ERROR);
    }

    offset = vxFdtPathOffset("/alt_soc/fpga");  /* PRQA S 0752 */
    if (offset <= 0) {
        printf("ERROR: no FPGA unit present in this board\n"); /* PRQA S 3200 */
        return ERROR;
    }

    mdio_master_data_reg_br = fpgaVirtAddr + FPGABR_DR_OFFSET;  /* PRQA S 0563 */ /* PRQA S 0488 */
    mdio_master_addr_reg_br = fpgaVirtAddr + FPGABR_AR_OFFSET;  /* PRQA S 0563 */ /* PRQA S 0488 */

    if(_cable_test_counter > (uint8_t)0)
    {
        status_val = _tttechCableTest();
        if(status_val == ERROR)
        {
            if (BR_NULL_PTR != _func_kprintf) {
                (*_func_kprintf)("ERORR: Cable Test failed\n");
            }
        }
    }
    _cable_test_counter++;
    /* Get PHY ID */

    phy_id = ((mdio_read_br(TJA1100_PHY_IDENTIFIER_2_REG) << 16) | mdio_read_br(TJA1100_PHY_IDENTIFIER_1_REG));/* PRQA S 4544 */
    //printf("BR PHY ID: 0x%x\n", phy_id);
    
    miiVal = mdio_read_br(TJA1100_EXTENDED_CONTROL_REG); /* PRQA S 4461 */
    miiVal |= (TJA1100_CFEN_CONFIGURATION_REGISTER_ACCESS_ENABLED << TJA1100_CFEN_SHIFT); /* PRQA S 4544 */ /* PRQA S 4434 */ /* PRQA S 4542 */ /* PRQA S 4523 */   /* PRQA S 1851 */
    mdio_write_br(TJA1100_EXTENDED_CONTROL_REG, miiVal);
    
    miiVal = (TJA1100_PWRD_POWER_DOWN_INTO_STANDBY << TJA1100_PWRD_SHIFT); /* PRQA S 4544 */ /* PRQA S 4523 */ /* PRQA S 4436 */
    mdio_write_br(TJA1100_BASIC_CONTROL_REG, miiVal);

    miiVal = 0;
    mdio_write_br(TJA1100_BASIC_CONTROL_REG, miiVal);

    /* Set reset bit and then wait for it to clear. */
    miiVal |= (TJA1100_RST_PHY_RESET << TJA1100_RST_SHIFT); /* PRQA S 4544 */ /* PRQA S 4434 */ /* PRQA S 4542 */ /* PRQA S 4523 */  /* PRQA S 1851 */
    mdio_write_br(TJA1100_BASIC_CONTROL_REG, miiVal);

    for (i = 0; i < 1000; i++)
    {
    	miiVal = mdio_read_br(TJA1100_BASIC_CONTROL_REG);  /* PRQA S 4461 */
    	if (!(miiVal & TJA1100_RST_MASK)) {  /* PRQA S 4523 */ /* PRQA S 1851 */ /* PRQA S 4542 */ /* PRQA S 4538 */
    		break;
    	}
    }
    
    miiVal = mdio_read_br(TJA1100_EXTENDED_CONTROL_REG); /* PRQA S 4461 */
    //kprintf("TJA1100_EXTENDED_CONTROL_REG: 0x%x\n", miiVal);
    miiVal |= (TJA1100_CFEN_CONFIGURATION_REGISTER_ACCESS_ENABLED << TJA1100_CFEN_SHIFT); /* PRQA S 4544 */ /* PRQA S 4434 */ /* PRQA S 4542 */ /* PRQA S 4523 */  /* PRQA S 1851 */
    mdio_write_br(TJA1100_EXTENDED_CONTROL_REG, miiVal);

    miiVal = mdio_read_br(TJA1100_CONFIGURATION_1_REG); /* PRQA S 4461 */
    //kprintf("TJA1100_CONFIGURATION_1_REG: 0x%x\n", miiVal);

    miiVal = miiVal & ~TJA1100_MS_MASK; /* PRQA S 4434 */ /* PRQA S 4542 */ /* PRQA S 4523 */ /* PRQA S 4532 */  /* PRQA S 1851 */
    miiVal |= TJA1100_MS_PHY_CONFIGURED_AS_SLAVE << TJA1100_MS_SHIFT; /* PRQA S 4544 */  /* PRQA S 4434 */ /* PRQA S 4542 */ /* PRQA S 4523 */ /* PRQA S 1851 */
    
    
    miiVal = miiVal & ~TJA1100_LEDEN_MASK; /* PRQA S 4434 */ /* PRQA S 4542 */ /* PRQA S 4523 */ /* PRQA S 4532 */ /* PRQA S 1851 */
    miiVal |= TJA1100_LEDEN_LED_OUTPUT_ENABLED << TJA1100_LEDEN_SHIFT; /* PRQA S 4544 */ /* PRQA S 4434 */ /* PRQA S 4542 */ /* PRQA S 4523 */ /* PRQA S 1851 */

    miiVal = miiVal & ~TJA1100_LEDM_MASK; /* PRQA S 4434 */ /* PRQA S 4542 */ /* PRQA S 4523 */  /* PRQA S 4532 */ /* PRQA S 1851 */
    miiVal |= TJA1100_LEDM_LINK_STATUS << TJA1100_LEDM_SHIFT; /* PRQA S 4544 */ /* PRQA S 4434 */ /* PRQA S 4542 */ /* PRQA S 4523 */ /* PRQA S 1851 */
    mdio_write_br(TJA1100_CONFIGURATION_1_REG, miiVal);
/*    
    miiVal = mdio_read_br(TJA1100_EXTENDED_CONTROL_REG);
    kprintf("TJA1100_EXTENDED_CONTROL_REG: 0x%x\n", miiVal);
    miiVal = mdio_read_br(TJA1100_CONFIGURATION_1_REG);
    kprintf("TJA1100_CONFIGURATION_1_REG: 0x%x\n", miiVal);
*/
    //_tttechCableTest();

    return OK;
}

LOCAL STATUS tttech_sysEmacInit(VXB_DEV_ID  pDev)
{
    STATUS retval = OK;
    if (vxbDevUnitGet(pDev) == (uint32_t)0)
    {
        if (_orig_func_sysEmacInit != BR_NULL_PTR)
        {
            retval = _orig_func_sysEmacInit(pDev);
        }
    }
    else
    {
        retval = tttech_BR_EmacInit(pDev);
    }
    return retval;
}
    
LOCAL STATUS tttech_sysEmacEndInit(VXB_DEV_ID  pDev, END_OBJ *pEnd)
{
    STATUS retval = OK;
    if (_orig_func_sysEmacEndInit != BR_NULL_PTR)
    {
        retval = _orig_func_sysEmacEndInit(pDev, pEnd);
    }
    return retval;
}

LOCAL STATUS tttech_sysEmacPhyInit(VXB_DEV_ID  pDev)
{
    STATUS retval = OK;
    if (vxbDevUnitGet(pDev) == (uint32_t)0)
    {
        if (_orig_func_sysEmacPhyInit != BR_NULL_PTR)
        {
            retval = _orig_func_sysEmacPhyInit(pDev);
        }
    }
    else
    {
        retval = tttech_BR_EmacPhyInit(pDev);
    }
    return retval;
}

/*****************************************************************************
 * _tttechBRDiagnosis
 *****************************************************************************/
/*! \brief        Search for any TJA1100 possible error in registers.
 *
 *                Reads registers and search for any possible defined error.
 *                The error is reported to error handler.
 *                NOTE: debug prints the position of the detected error in
 *                register, not the value of the register.
 *
 *****************************************************************************/
LOCAL void _tttechBRDiagnosis(void)
{
    UINT16      regval = 0;
    ssize_t     msgq_readout = ERROR;
    uint16_t    brErrorStatus_new = 0;
    uint16_t    brErrorStatus_diff = 0;
    uint16_t    brErrorBitmask_var = 1;
    uint32_t	error_pckts = 0;
    uint32_t	summ_err_pckts = 0;
    STATUS      retval = OK;
    int     	fd;
    TJA1100_LINKFAIL_COUNT_t 	lnk_fl_cnt = 0;
    LOCAL uint16_t 				lnk_fl_acc = 0;
    const unsigned int 			hwRegOffset = 0x194;
    unsigned int	regValue = 0;
    int                         linkfaultType = ERROR;
    
    char ip_address[INET6_ADDR_LEN] = {0}; /* PRQA S 1292 */
    int i;
    
    UINT16 isr_regval = 0;
    static uint32_t not_first_status_check = FALSE;
    
    
    /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
    static int vers = 0;
    vers++;
    if (20 == vers)
    {
        printf("\n\n------------------------------------------------------\n"); /* PRQA S 3200 */
        printf("\n--------  Version: BSC Rad Stefan  -------------------------\n"); /* PRQA S 3200 */
        printf("\n------------------------------------------------------\n"); /* PRQA S 3200 */
    }
    /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
    
    
    /* --- Check PHY_INIT_FAIL ---*/
    if(((uint16)0 < br_init_fail_cnt) && ((uint16)(MAX_BR_INIT_FAIL -(uint32_t)1) > br_init_fail_cnt))
    {
        regval = mdio_read_br(TJA1100_INTERRUPT_SOURCE_REG); /* PRQA S 4461 */
        regval &= PHY_INIT_FAIL_MASK; // 11th bit in register set (PHY_INIT_FAIL)
        
#ifdef TEST_CHIP_INIT       
        /** TEST POINT ***/
        regval = 1;
        /** TEST POINT ***/
#endif
        
        if((UINT16)0 != regval)  /* previous init not succeeded */
        {
            _BR_chip_reset();
            br_init_fail_cnt++;
            BRDBG_MSG("BRDIAG: br_init_fail_cnt = %i \n", br_init_fail_cnt);
            retval = tttech_BR_EmacPhyInit(BR_NULL_PTR);
        }
        else  /* init succeeded */
        {
            br_init_fail_cnt = 0;
            br_fail_drv_cycle = 0;
            fd = open(DRV_CYCLE_CNT, O_CREAT | O_RDWR , 0664); /* PRQA S 4542 */ /* PRQA S 0339 */
            if (ERROR != fd)   /*  create the new empty file */
            {
                rwFile_drv_cnt[0] = 0;  /* PRQA S 1292 */
                (void)write(fd, rwFile_drv_cnt , 1); /* write 0 to it */
                BRDBG_MSG("BRDIAG: Zero to file /br_drvcycl_cnt \n");
                (void)close(fd);
            }
            else
            {
                BRDBG_MSG("BRDIAG: Can not create file /br_drvcycl_cnt \n");
            }
            brErrorStatus_new &= (uint16_t) ~BR_BITMASK_ERR1; /* PRQA S 4522 */ /* PRQA S 2895 */
        }
        
    }
    if ((MAX_BR_INIT_FAIL - 1) <= br_init_fail_cnt) /* PRQA S 1840 */ /* PRQA S 1822 */
    {
        // "ERR_EXTIF_SSH_BROADR_1 "
        brErrorStatus_new |= (uint16_t) BR_BITMASK_ERR1;
        //BRDBG_MSG("ERROR: BRDIAG Interrupt Status Reg (cnt): 0x%04X.\n",regval);
        br_init_fail_cnt = (uint16)(MAX_BR_INIT_FAIL - (uint32)1);
        fd = open(DRV_CYCLE_CNT, O_RDONLY , 0664); /* PRQA S 0339 */
        if (ERROR != fd)
        {
            (void)read (fd, rwFile_drv_cnt, 1);
            (void)close(fd);
            
            br_fail_drv_cycle = rwFile_drv_cnt[0]; /* PRQA S 4413 */ /* PRQA S 4414 */
            
            BRDBG_MSG("BRDIAG read: br_fail_drv_cycle = %i\n", br_fail_drv_cycle);
            
            br_fail_drv_cycle++;
            if(MAX_DRV_SESSIONS <= br_fail_drv_cycle) /* PRQA S 1822 */
            {
                br_fail_drv_cycle = MAX_DRV_SESSIONS; /* PRQA S 1291 */
                // "ERR_EXTIF_SSH_BROADR_2 "
                brErrorStatus_new |= (uint16_t) BR_BITMASK_ERR2;
                BRDBG_MSG("ERROR: BRDIAG Interrupt Status Reg (cycle): 0x%04X.\n",regval);
            }
            rwFile_drv_cnt[0] = (char) br_fail_drv_cycle;
            
            fd = open(DRV_CYCLE_CNT, O_RDWR , 0664); /* PRQA S 0339 */
            if (ERROR != fd)
            {
                (void)write(fd, rwFile_drv_cnt, 1);
                (void)close(fd);
            }
            else
            {
                BRDBG_MSG("BRDIAG: Can not open file /br_drvcycl_cnt \n");
            }
    
#ifdef  DEBUG_BRDIAG            
            fd = open(DRV_CYCLE_CNT, O_RDWR , 0664);
            if (ERROR != fd)
            {   rwFile_drv_cnt[0] = 0;
                read (fd, rwFile_drv_cnt, 1);
                BRDBG_MSG("BRDIAG read: br_fail_drv_cycle = %i\n", rwFile_drv_cnt[0]);
                close(fd);
            }
#endif
        }
        else
        {
            BRDBG_MSG("BRDIAG: Can not open file /br_drvcycl_cnt \n");
        }
        
    }
    if ((uint16)0 == br_init_fail_cnt) /* no PHY_INIT_FAIL errors */
    {
    	// perform diag
    }
    
    /*=== REPORT ERRORS ===*/
    i=0;
    /*find differences between last state and current*/
    brErrorStatus_diff = brErrorStatus_new ^ _brErrorStatus;
    /*save current state*/
    _brErrorStatus = brErrorStatus_new;
    brErrorBitmask_var = 1;
    while(brErrorStatus_diff != (uint16_t)0)
    {
        //is there status changed?
        if((brErrorStatus_diff & (uint16_t)0x0001U) != (uint16_t)0)
        {
            //if yes, what kind of change is there?
            if((_brErrorStatus & brErrorBitmask_var) != (uint16_t)0)
            {
                BRDBG_MSG("EHEVENT: BRDIAG %d Error Reported!\n",i+1);
                (void)RPpEHEvent_ReportError (
                        &_Reporter_ID, 
                        _brErrorCodes[i],
                        TRUE
                        );
            }
            else
            {
                BRDBG_MSG("EHEVENT: BRDIAG %d Error Deleted!\n",i+1);
                (void)RPpEHEvent_ReportError (
                        &_Reporter_ID, 
                        _brErrorCodes[i],
                        FALSE
                        );
            }
        }
        //move mask to next error
        brErrorBitmask_var <<= 1; /* PRQA S 4544 */
        //shift next bit (next difference)
        brErrorStatus_diff >>= 1;  /* PRQA S 4544 */
        i++;
    }
    /*=== REPORT ERRORS DONE ===*/ 
    

    
    /* if PHY_INIT_FAIL suspend */
    if (((uint16)(MAX_BR_INIT_FAIL - 1) <= br_init_fail_cnt) && ((uint16)0 < br_fail_drv_cycle))  /* PRQA S 1822 */ /* PRQA S 1840 */
    {
    	BRDBG_MSG("ERROR: BRDIAG task auto-suspended! PHY_INIT_FAIL!\n");
    	(void)taskSuspend(taskIdSelf());
    }
}

/*****************************************************************************
 * _tttechSwitchInfo
 *****************************************************************************/
/*! \brief        Reads revision information about the FPGA firmware
 *
 *                It is stored in _BRDiagData.
 *
 *  \return       ERROR if FPGA cannot be found or mapped, OK else ERRNO: N/A
 *****************************************************************************/
LOCAL int _tttechSwitchInfo ( void ) 
{
    int offset;
    UINT32 *prop;

    if (fpgaVirtAddr == BR_NULL_PTR)
    {
        if (mapFpga() != OK){
            return ERROR;
        }
    }

    if (fpgaVirtAddr == BR_NULL_PTR) {
        printf("\nError mapping address\n"); /* PRQA S 3200 */
        return (ERROR);
    }

    offset = vxFdtPathOffset("/alt_soc/fpga"); /* PRQA S 0752 */
    if (offset <= 0)
    {
        printf("ERROR: No FPGA unit present in this board\n"); /* PRQA S 3200 */
        return ERROR;
    }

    prop = (UINT32*) vxFdtPropGet(offset, "id-comp-base", BR_NULL_PTR); /* PRQA S 0752 */  /* PRQA S 0311 */ /* PRQA S 0316 */
    id_comp_base = fpgaVirtAddr + vxFdt32ToCpu(*prop); /* PRQA S 0488 */ /* PRQA S 0563 */

    ifsetv.n = id_comp_base[4];
    
    return (OK);
}

/*****************************************************************************
 * _tttechCableTest
 *****************************************************************************/
/*! \brief        TJA1100 cable Test functionality
 *
 *                Sets registers in order to run cable test (enabling configuration 
 *                of CONFIG registers,disabling AUTO_OP, disabling LINK_CONTROL) and
 *                returns back configuration as been before cable test. 
 *                
 *                Chip needs minimum of 100us to complete the test. 
 *                (Average measured duration of the function = 750us)
 *
 *  \return       ERROR if it is not in normal mode, else OK
 *****************************************************************************/
LOCAL STATUS _tttechCableTest(void)
{
	 UINT16 regval_prev                  = 0;
	 UINT16 regval                       = 0;
	 UINT16 exst_ctrl_reg_value  = 0;
	    
	 exst_ctrl_reg_value = mdio_read_br(TJA1100_EXTENDED_CONTROL_REG); /* PRQA S 4461 */
	    
	 /* check the normal mode */
	 regval = exst_ctrl_reg_value;
	 regval = regval & 0x7800U;      /*mask bits [14:11]*/

	 if(regval != (UINT16)0x1800){ //TJA1100_NORMAL_MODE_MASK)
	     return ERROR;
	 }
	 //enable configuration
	 regval = exst_ctrl_reg_value;
	 regval |= (TJA1100_CFEN_CONFIGURATION_REGISTER_ACCESS_ENABLED << TJA1100_CFEN_SHIFT);  /* PRQA S 4544 */ /* PRQA S 1851 */ /* PRQA S 4542 */ /* PRQA S 4523 */ /* PRQA S 4434 */
	 mdio_write_br(TJA1100_EXTENDED_CONTROL_REG, regval);

	 //link control disable (disable AUTO_OP)
	 regval = mdio_read_br(TJA1100_CONFIGURATION_1_REG); /* PRQA S 4461 */
	 regval &= 0xBFFFU;
	 mdio_write_br(TJA1100_CONFIGURATION_1_REG, regval);
	    
	 //link control disable (desable LINK_CONTROL)   
	 regval = mdio_read_br(TJA1100_EXTENDED_CONTROL_REG); /* PRQA S 4461 */
	 regval &= 0x7FFFU;
	 mdio_write_br(TJA1100_EXTENDED_CONTROL_REG, regval);
	 //printf("\n\n------linkctrl 0x%04x\n\n", regval);
	    
	 /* start the cable test */
	 regval = mdio_read_br(TJA1100_EXTENDED_CONTROL_REG); /* PRQA S 4461 */
	 regval |= 0x1U << 5U;  /* PRQA S 4397 */ //1 << TJA1100_CABLE_TEST_SHIFT;
	 mdio_write_br(TJA1100_EXTENDED_CONTROL_REG, regval);
	    
	 /* the test lasts for at least 100us*/
	 (void)vxbUsDelay(150); /* PRQA S 3335 */

	 /* read the results from  */
	 _cable_test_result = mdio_read_br(TJA1100_EXTERNAL_STATUS_REG); /* PRQA S 4461 */
	 /*set the AUTO_OP bit*/
	 regval = mdio_read_br(TJA1100_CONFIGURATION_1_REG); /* PRQA S 4461 */
	 regval |= 0x4000; /* PRQA S 4542 */  /* PRQA S 1861 */
	 mdio_write_br(TJA1100_CONFIGURATION_1_REG, regval);
	    
	 /*return old value of the CONFIG_EN bit*/
	 regval_prev = exst_ctrl_reg_value & (UINT16)TJA1100_CFEN_MASK;
	 regval = mdio_read_br(TJA1100_EXTENDED_CONTROL_REG); /* PRQA S 4461 */
	 regval |= regval_prev;
	 mdio_write_br(TJA1100_EXTENDED_CONTROL_REG, regval);

	 return OK;
}


/*****************************************************************************
 * _BR_shMem_Alloc
 *****************************************************************************/
/*! \brief        Allocates shared memory for BRIF address and index report.
 *                
 * \param fname Pointer to reserved shared memory
 * \param size  Size of reserved shared memory
 * 
 * \return      exits with perror() if failed, else returns address 
 *              of shared memory space
 * \decomposed_from[Cluster 2.5: Communication over a gateway and using VLAN]{1707189}
 *****************************************************************************/
LOCAL void * _BR_shMem_Alloc(const char * fname, size_t size)
{
    void * retAddr;
    int fd;

    /* create a new SHM object if it doesn't exist*/
    fd = shm_open(fname, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); /* PRQA S 4542 */
    if (fd == -1) {
        perror("shm_open");
        return BR_NULL_PTR;
    }
    /* set object size */
    if (ftruncate(fd, (off_t)size) == -1) {
        fprintf(stderr, "BR ERROR truncating shm:'%s' sizeof()=%ld\n",fname, (unsigned long) size); /* PRQA S 3200 */
        perror("ftruncate");
        return BR_NULL_PTR;
    }
    /* Map shared memory object in the address space of the process */
    retAddr = mmap(0, size,  /* PRQA S 4542 4 */ /* PRQA S 3004 */
            PROT_READ | PROT_WRITE,
            MAP_SHARED, fd, 0);
    if (retAddr == (void *) MAP_FAILED) { /* PRQA S 0306 */
        perror("mmap");
        return BR_NULL_PTR;
    }
    /* close the file descriptor; the mapping is not impacted by this */
    (void)close(fd);
    /* The mapped memory is now available */

    return retAddr;
}

/*****************************************************************************
 * _attach_if_to_device
 *****************************************************************************/
/*! \brief        attaches the Broader-Reach interface to device
 *
 *                sets MAC address and IPv6 address of interface. If available 
 *                MAC address is read from production data else default MAC
 *                address is set.
 *
 *  \return       ERROR if attaching the interface failed, else OK
 *****************************************************************************/
LOCAL int _attach_if_to_device(void)
{       
    int         i;
    int         status = -1;
    char        ip_address[INET6_ADDR_LEN] = {0}; /* PRQA S 1292 2 */
    char        ifconfig_command[IF_CMD_LEN_BUF] = {0};
    uint8_t 	prod_buf[SSH_MAC_PROD_PAGESIZE] = {0};
    uint8_t 	br_mac[6] = BR_MAC_ADDRESS_DEFAULT;
    int32_t 	nvmm_fd = ERROR;
    uint8_t 	set_vlan = 0;
    off_t 		offset_seek = 0;
    uint8_t 	read_code_vlan[1] = {0};
    uint32_t    Prod_CRC_calculated = 0;
    struct in6_addr  	dst;
    s_BRIF_DATA brif;
    
    /* attach BR interface to device */
    status = ipcom_drv_eth_ip_attach(EMAC1_NAME, HMI0_NAME);  /* PRQA S 3335 */
    
    // disable path MTU 
    (void)ipcom_sysvar_set("ipnet.inet.EnablePathMtuDiscovery", "no", IPCOM_SYSVAR_FLAG_OVERWRITE);
    
    if (0 == status) 
    {

        /*Read complete production data from NOR including production CRC*/
        if (OK == sysFlashGet((char *)&prod_buf, SSH_MAC_PROD_PAGESIZE, SSH_MAC_PROD_OFFSET)) /* PRQA S 0310 */  /* PRQA S 3335 */
        {
            /* warning: portability issue must be LITTLE ENDIAN */
        	/* PRQA S 3200 2 *//* The status of execution is checked by checking variable 'Prod_CRC_calculated' */
            Br_Calc_Crc(prod_buf, &Prod_CRC_calculated, SSH_MAC_PROD_PAGESIZE-4); /* PRQA S 1840 */ 
            //printf("CRC calc %d; CRC Prod %d\n", Prod_CRC_calculated,  *((uint32_t*) &prod_buf[SSH_MAC_PROD_PAGESIZE-4]));
            
            /* MISRA  vioaltion
             * Error Message: Msg(7:3305) Pointer cast to stricter alignment.MISRA C:2012 Rule-11.3
             * 
             * Justification : This is done with intension and care. The purpose is to access structure type data 
             * in memory created by length in bytes. 
             */
            /* PRQA S 3305 2 */
            /* check if calculated CRC matches with read CRC */
			if(Prod_CRC_calculated == *((uint32_t*) &prod_buf[SSH_MAC_PROD_PAGESIZE-4])) /* PRQA S 0310 */ /* PRQA S 1840 */
			{
				(void)memcpy(br_mac, prod_buf, sizeof br_mac);
			}
			else
			{
				/* error while reading production data, default mac is used */
				printf("CRC failed - default mac set \n"); /* PRQA S 3200 */
				(void)memcpy(br_mac, _Br_MAC, sizeof br_mac);
			}
        } 
        else 
        {
            printf("Broader-Reach: error reading production data -> setting default MAC address \n"); /* PRQA S 3200 */
            (void)memcpy(br_mac, _Br_MAC, sizeof br_mac);
        }
        
	    /* open file descriptor */
        nvmm_fd = open(NVMM_DIAG_VLAN, O_RDONLY, 0644); /* PRQA S 0339 */

	    if (ERROR != nvmm_fd)
	    {
	    	
	    	if (0 < read(nvmm_fd, (char *) read_code_vlan, 1)) /* PRQA S 0310 */
	    	{	    	
				set_vlan = read_code_vlan[0]; /* PRQA S 1840 */
				set_vlan &= (uint8_t)MASK_SET_VLAN;  /* PRQA S 4542 */
				(void)close(nvmm_fd);
	    	}
	    	else 
	    	{
	    		printf("VLAN IF: Failed to read from file ' %s ' \n",NVMM_DIAG_VLAN); /* PRQA S 3200 */
	    	}
	    }
	    else
	    {
	    	printf("VLAN IF: Failed to open file: ' %s ' \n",NVMM_DIAG_VLAN); /* PRQA S 3200 */
	    }
	    /* preparing the ifconfig command for setting the MAC and apply it */
		snprintf(ifconfig_command,IF_CMD_LEN_BUF,"%s lladdr %02x:%02x:%02x:%02x:%02x:%02x", /* PRQA S 3200 */
				HMI0_NAME, br_mac[0], br_mac[1], br_mac[2], br_mac[3], br_mac[4], br_mac[5]);
		status -= ifconfig(ifconfig_command);

        /* Bind BRIFInfo and BRIFData shared memory */

        _brif_data = _BR_shMem_Alloc("/brif_diag_data", sizeof(_BRIFData)); /* PRQA S 0752 */ /* PRQA S 0317 */
        if (BR_NULL_PTR == _brif_data)
        {
        	printf("Can not open BRIFData shared memory!\n"); /* PRQA S 3200 */
        }

        _brif_ping_data = _BR_shMem_Alloc("/brif_diag_ping_data", BR_MAX_PING_HOSTS*sizeof(s_BR_DIAG_PING_DATA)); /* PRQA S 0752 */ /* PRQA S 0317 */
        if (BR_NULL_PTR == _brif_ping_data)
        {
        	_brif_ping_data = &_BRIFPingData[0];
        	printf("Can not open BRIFPingData shared memory!\n"); /* PRQA S 3200 */
        }        
        
        _brif_info = _BR_shMem_Alloc("/brif_info", sizeof(_BRIFInfo)); /* PRQA S 0752 */ /* PRQA S 0317 */
        if (BR_NULL_PTR == _brif_info)
        {
        	/*If opening SHM failed let _brif_ifo point to local struct to preserve further code execution
        	 * , altought it is not going to be provided to DSC through SHM .*/
        	_brif_info = &_BRIFInfo;
        	printf("Can not open /brif_info shared memory!\n"); /* PRQA S 3200 */
        }
        else
        {
            /*Initialization of the field "br_com_error" to the default value  
             * -  OPEN circuit, 
             * -  SHORT circuit or
             * - NON_ELECTRICEL_FAULT. */          
            if((_cable_test_result & (uint16_t)TJA1100_ODS_MASK) && !(_cable_test_result & (uint16_t)TJA1100_SDS_MASK))/* PRQA S 4558 */
            {
                _brif_info->br_com_error = ERR_EXTIF_SSH_BROADR_O;
            }
            else if(!(_cable_test_result & (uint16_t)TJA1100_ODS_MASK) && (_cable_test_result & (uint16_t)TJA1100_SDS_MASK))/* PRQA S 4558 */
            {
                _brif_info->br_com_error = ERR_EXTIF_SSH_BROADR_S;
            }
            else
            {
                _brif_info->br_com_error = ERR_EXTIF_SSH_BROADR_3;// NON_ELECTRICAL_FAULT;
            }                    
        }
        printf("\n\n_--------------------brif_info->br_com_error %d\n\n", _brif_info->br_com_error ); /* PRQA S 3200 */
        //set_vlan =1;
	    if (set_vlan == (uint8_t)1 )
	    {
	    	module1_ConfigureVLAN();
	    }
	    else 
	    {
	    	module1_ConfigureEthInterface();
	    }
        
        
	    /* update sh mem fields for CL2.5 BEGIN */
        if(BR_NULL_PTR != _brif_data)
        {
            _brif_data->variant[0] = ifsetv.byte[0];
            _brif_data->variant[1] = ifsetv.byte[1];
            _brif_data->variant[2] = ifsetv.byte[2];
            _brif_data->switch_core_ip_rev = id_comp_base[3];
            _brif_data->switch_config_rev = id_comp_base[5];
        }
        /* update sh mem fields for CL2.5 END */
	    status = (status != 0) ? ERROR : OK;
	}   
	else 
	{
		status = ERROR;
	}
#ifdef BR_DEBUG_PRINT
   char addr_show[46] = {0};
   ifconfig("-a");  /* PRQA S 0752 */
   //netstat("-rn");
   inet_ntop(AF_INET6, &_brif_info->br_ip, addr_show, sizeof(addr_show));
   printf("IP addr saved: %s\n", addr_show); /* PRQA S 3200 */
   printf("NetIF idx: %i\n", _brif_info->if_nr); /* PRQA S 3200 */
   printf("sizeof /brif_info = %d \n", sizeof(_BRIFInfo)); /* PRQA S 3200 10 */

   printf("sizeof /brif_data = %d\n", sizeof(_BRIFData));
   //printf("VLAN NetIF idx: %i\n", _brif_data->vlan_br_id);
   inet_ntop(AF_INET6, &_brif_data->ip_br, addr_show, sizeof(addr_show));
   printf("IP BR: %s\n",addr_show);
   inet_ntop(AF_INET6, &_brif_data->ip_ll_br, addr_show, sizeof(addr_show));
   printf("LL IP: %s\n", addr_show);
#endif
   
   return status;
     
}


/*****************************************************************************
 *  _BR_chip_reset
 *****************************************************************************/
/*! \brief        Resets BR chip
 *
 *                Writes to TJA1100_BASIC_CONTROL_REG and TJA1100_RST_PHY_RESET
 *                In loop waits for reset is done
 *
 *****************************************************************************/
LOCAL void _BR_chip_reset(void)
{
UINT16 miiVal;
UINT16 i;

    miiVal = 0;
    mdio_write_br(TJA1100_BASIC_CONTROL_REG, miiVal);

    /* Set reset bit and then wait for it to clear. */
    miiVal |= (TJA1100_RST_PHY_RESET << TJA1100_RST_SHIFT);  /* PRQA S 4544 */ /* PRQA S 1851 */ /* PRQA S 4542 */ /* PRQA S 4523 */ /* PRQA S 4434 */
    mdio_write_br(TJA1100_BASIC_CONTROL_REG, miiVal);

    for (i = 0; i < (UINT16)1000; i++)
    {
        miiVal = mdio_read_br(TJA1100_BASIC_CONTROL_REG); /* PRQA S 4461 */
        if (!(miiVal & TJA1100_RST_MASK)) {  /* PRQA S 1851 */ /* PRQA S 4542 */ /* PRQA S 4538 */
        break;
        }
    }

}


/*****************************************************************************
 * _BRDiagTask_entry
 *****************************************************************************/
/*! \brief        Set-up all diagnostic requirements
 *
 *                Calls Cable Test function.
 *                Reads NOR flash and check the CRC.
 *                Set MAC address.
 *                Delete automatic IPv6 address.
 *                Enter loop repeating every 240ms
 *                In loop it calls _tttechBRDiagnosis and _tttechBRTestModes
 *
 *  \return       ERROR if it is not in normal mode, else OK
 *****************************************************************************/
LOCAL void _BRDiagTask_entry(void)
{       
    int             i;
    uint32_t        cycle_cnt = 0;
    char            ip_address[INET6_ADDR_LEN] = {0}; /* PRQA S 1292 2 */
    char            ifconfig_command[IF_CMD_LEN_BUF] = {0};
    uint32_t        Prod_CRC = 0;
    uint32_t        Prod_CRC_calculated = 0;
    uint8_t*        mac_addr_ptr;
    STATUS          status_val;
    struct in6_addr dst;
    UINT16          regval;

    
    /*reset error data*/
    for(i=0;i<8;i++)
    {
        (void)RPpEHEvent_ReportError (
                &_Reporter_ID, 
                _brErrorCodes[i],
                FALSE
                );
    }
    
    /* --- Check PHY_INIT_FAIL ---*/
    regval = mdio_read_br(TJA1100_INTERRUPT_SOURCE_REG); /* PRQA S 4461 */
    regval &= PHY_INIT_FAIL_MASK; // 11th bit in register set (PHY_INIT_FAIL)
    
    if((UINT16)0 != regval)
    {
            br_init_fail_cnt++;
            _BR_chip_reset();
    }
    else 
    {
    	br_init_fail_cnt = 0; 
    }
    
    /*this is not cyclic reporter therefore only setting the error is available (set = TRUE)*/
    if((_cable_test_result & 0x0080U) && !(_cable_test_result & 0x0100U)) /* open detected */ /* PRQA S 4558 */
    {
        /* --- Additional signal quality check ---*/
        regval = mdio_read_br(TJA1100_COMMUNICATION_STATUS_REG); /* PRQA S 4461 */
        regval >>= 6;  /* PRQA S 4544 */
        regval = regval & 0x0003U; 
        _BRDiagData.ethernet_signalquality = (uint8_t) regval;

        if(regval == (UINT16)0)
        {
        printf("EHEVENT: BRDIAG Open Circuit Error reported\n"); /* PRQA S 3200 */
        (void)RPpEHEvent_ReportError (
                &_Reporter_ID, 
                ERR_EXTIF_SSH_BROADR_O,
                TRUE
                );
        }
    }
    if((_cable_test_result & 0x0100U) && !(_cable_test_result & 0x0080U)) /* short detected */ /* PRQA S 4558 */
    {
        printf("EHEVENT: BRDIAG Short Circuit Error reported\n"); /* PRQA S 3200 */
        (void)RPpEHEvent_ReportError (
                &_Reporter_ID, 
                ERR_EXTIF_SSH_BROADR_S,
                TRUE
                );
    }
    if((_cable_test_result & 0x0100U) && (_cable_test_result & 0x0080U)) /* both detected */ /* PRQA S 4558 */
    {
        BRDBG_MSG("BRDIAG: False alarm due \n");
    }

    while(1)
    {
        // _tttechBRTestModes();
        _tttechBRDiagnosis();
        (void)taskDelay(24);
        if (cycle_cnt == (uint32_t)15) // wait ndp cache is fully updated before reading and storeing to the sh_mem 
        {
        (void) rtpModule();
          if (ERROR == readNDPcache(_brif_info->if_nr))
        	  {
        	      BRDBG_MSG("BRDIAG: readNDPcache failed \n");  	  
        	  }
          //printf("entry mac:  %s \n", (*_brif_data).Ip_ndp_cache_list[0].ndp_mac);
        }
        cycle_cnt++;
    }
}





/*****************************************************************************
 * _ttechStartBRDiagTask
 *****************************************************************************/
/*! \brief        Spawns the tBRDiagTask
 *****************************************************************************/
LOCAL void _ttechStartBRDiagTask(void)
{
    TASK_ID        tid;
    const PHYS_ADDR hwRegHmi0BaseAddr = (UINT64)0xFF702000U;

    /* HW register, Base Address: FF702000 , Offset: 0x194 - CRC Errors Number */
	hmi0_macVirtAddr = pmapGlobalMap(hwRegHmi0BaseAddr, (size_t) 0xFF, /* PRQA S 0317 */ /* PRQA S 4436 2 */ /* PRQA S 4542 2 */
    		MMU_ATTR_SUP_RW | MMU_ATTR_CACHE_OFF | MMU_ATTR_CACHE_GUARDED); 

	if ((hmi0_macVirtAddr == PMAP_FAILED) || (hmi0_macVirtAddr == BR_NULL_PTR))  /* PRQA S 0306 */
    {
        printf("pmapGlobalMap returned ERROR. (hmi0)\n"); /* PRQA S 3200 */
    }

    
    tid = taskSpawn("tBRDiagTask", 186, 0, 5000, (FUNCPTR)_BRDiagTask_entry,0,0,0,0,0,0,0,0,0,0);/* PRQA S 0752 */ /* PRQA S 0313 */
    if( tid == TASK_ID_ERROR )
    {
        if (BR_NULL_PTR != _func_kprintf){
            (*_func_kprintf)("ERORR: tBRDiagTask is not created\n");
        }
    }

    module1_StartTasks();
}

void tttechBRInit(void)
{
	module1_InitPhy();
	
// hook into the emac configuration callbacks and insert a wrapper function
// to be able to configure br as well	
#if defined(DRV_FPGA_FDT_ALT_SOC_GEN5) && defined(DRV_END_FDT_ALT_SOC_GEN5_DWC)
    _orig_func_sysEmacInit = _func_sysEmacInit;
    _orig_func_sysEmacEndInit = _func_sysEmacEndInit;
    _orig_func_sysEmacPhyInit = _func_sysEmacPhyInit;

    _func_sysEmacInit = tttech_sysEmacInit;
    _func_sysEmacEndInit = tttech_sysEmacEndInit;
    _func_sysEmacPhyInit = tttech_sysEmacPhyInit;
    
#endif
}

void tttechBRDiagInit(void)
{
    int         status_val;
    int             fd;
    STATUS ret_initFwS = ERROR;
    
    
    /*read the Switch information*/
    status_val = _tttechSwitchInfo();
    if(status_val == ERROR)
    {
        if (BR_NULL_PTR != _func_kprintf){
            (*_func_kprintf)("ERROR: Switch info failed\n");
        }
    }
    
    //create file for driving cycle cnt to check on broken chip 
    
    fd = open(DRV_CYCLE_CNT, O_RDWR , 0664); /* PRQA S 0339 */
    if(ERROR == fd)                      /* if file does not exist */
    {
        fd = open(DRV_CYCLE_CNT, O_CREAT | O_RDWR , 0664); /* PRQA S 4542 */ /* PRQA S 0339 */
        if (ERROR != fd)    /*  create one            */
        {
            rwFile_drv_cnt[0] = 0; /* PRQA S 1292 */
            (void)write(fd, rwFile_drv_cnt , 1);/*  write 0 to it */
            BRDBG_MSG("BRDIAG: create file /br_drvcycl_cnt \n");
            (void)close(fd);
        }
        else
        {
            BRDBG_MSG("BRDIAG: Can not create file /br_drvcycl_cnt \n");
        }
    }
    else
    {
        BRDBG_MSG("BRDIAG: file /br_drvcycl_cnt exists \n");
        (void)close(fd);
    }
    
     /* setup hmi0*/
    if(ERROR == _attach_if_to_device()){
	    printf("BR: ERROR - _attach_if_to_device failed! \n"); /* PRQA S 3200 */
    }

    ret_initFwS = initFirewallStat(); /* Init for functions reading the firewall statistics */
     if (ERROR == ret_initFwS){ 
    	 printf ("BR: ERROR - FIREWALL: init for read firewall stats failed \n"); /* PRQA S 3200 */
     }
    /*early start of the task*/
    _ttechStartBRDiagTask();
    
}

/* ****************************DoS******************************* */
#ifdef INCLUDE_DOS_DETECTION
/*****************************************************************************
 * _disable_BR_link
 *****************************************************************************/
/*! \brief        turn down the PHY link in BroadR Reach TJA1100
 * 
 *                function that change 3 bits in TJA1100 registers in order
 *                to disable physical link of the PHY chip TJA1100.
 *                First it enables configuration, then disable auto operation
 *                and in the end turn of the PHY link bit.
 *
 *****************************************************************************/
LOCAL void _disable_BR_link(void)
{
    UINT16 regval;
    printf("BR-link is disabled \n"); /* PRQA S 3200 */
    //enable configuration
    regval = mdio_read_br(TJA1100_EXTENDED_CONTROL_REG); /* PRQA S 4461 */
    regval |= (TJA1100_CFEN_CONFIGURATION_REGISTER_ACCESS_ENABLED << TJA1100_CFEN_SHIFT);  /* PRQA S 4544 */ /* PRQA S 1851 */ /* PRQA S 4542 */ /* PRQA S 4523 */ /* PRQA S 4434 */
    mdio_write_br(TJA1100_EXTENDED_CONTROL_REG, regval);

    //link control disable (disable AUTO_OP)
    regval = mdio_read_br(TJA1100_CONFIGURATION_1_REG); /* PRQA S 4461 */
    regval &= 0xBFFFU;
    mdio_write_br(TJA1100_CONFIGURATION_1_REG, regval);
    //link control disable (disable LINK_CONTROL)   
    regval = mdio_read_br(TJA1100_EXTENDED_CONTROL_REG); /* PRQA S 4461 */
    regval &= 0x7FFFU;
    mdio_write_br(TJA1100_EXTENDED_CONTROL_REG, regval);
}

/*****************************************************************************
 * _enabled_BR_link
 *****************************************************************************/
/*! \brief        turn on the PHY link in BroadR Reach TJA1100
 * 
 *                It only restore AUTO_OP bit back and the PHY
 *                link is active again.
 *
 *****************************************************************************/
LOCAL void _enable_BR_link(void)
{
    UINT16 regval;
    
    //restore auto operation
    regval = mdio_read_br(TJA1100_CONFIGURATION_1_REG); /* PRQA S 4461 */
    regval |= 0x4000; /* PRQA S 4542 */ /* PRQA S 1861 */
    mdio_write_br(TJA1100_CONFIGURATION_1_REG, regval);
    printf("BR-link is enabled \n"); /* PRQA S 3200 */
}

LOCAL void _recorder_Shm_Alloc(void)
{
    Rec_DoSTimestamp = (uint64_t *)_BR_shMem_Alloc("/Recorder_DoS_Shm", sizeof(uint64_t)); /* PRQA S 0752 *//* PRQA S 0316 */
    
    if (Rec_DoSTimestamp == BR_NULL_PTR)
    {
    	printf("BR ERROR : SHM Recorder_DoS_Shm allocation failed \n"); /* PRQA S 3200 */
    }
}

/*****************************************************************************
 * _tDoSdetection_entry
 *****************************************************************************/
/*! \brief        DoS Service function. It monitors the hmi0 interrupts. 
 *
 *                When zFAS gets flooded, it shall back off all Ethernet 
 *                traffic on the BR interface for one major frame (80 ms). 
 *                After this it shall try again. When there is still an 
 *                unacceptable number of interrupts, it backs off for 
 *                2 major frames…..3 major frames…until backing off for 
 *                10 major frames. After reaching this 10 major frames 
 *                threshold it initiates an entry into the zFAS recorder 
 *                and log a DoS attack. Backing off for 10 major frames 
 *                shall last until the zFAS doesn’t sense flooding any more. 
 *                Attention: this should not apply when we are in software 
 *                download mode, because here we need the whole bandwidth!
 *                SAD 1237095.
 *****************************************************************************/
LOCAL void _tDoSdetection_entry(void)
{
   
    printf("DoS detection started \n"); /* PRQA S 3200 */
    
    uint64      timestamp = 0; 
    e_TP_ZgtState_SSH zgtState;
    
    
    UINT16  dos_state = 0;

    while(1)
    {
        switch (dos_state)
        {    /* PRQA S 0570 2 */
        case 0: // check hmi0 on DoS attacks  
                _checkOnAttack(&dos_state);
                (void)taskDelay(8);
                break;
                /* PRQA S 0570 2 */
        case 1: // attack stayed for to long - write to zFas Recorder and stay unconnected
                printf("DoS: Persistent Attack Detected! BroadR Reach PHY link disabled!\n"); /* PRQA S 3200 */
                
                (void)TP_tttGetZgt64 (&timestamp, &zgtState, TRUE);
                
                    if (BR_NULL_PTR != Rec_DoSTimestamp)
                    {
                        *Rec_DoSTimestamp = timestamp;
                        BRDBG_MSG("DoS Timestamp shm: %lld \n", *Rec_DoSTimestamp);
                    }
                    else
                    {
                        printf("SHM: '/Recorder_DoS_Shm' no access!!\n");  /* PRQA S 3200 */      
                    }
                dos_state = 2;
                break;
                
        case 2: BRDBG_MSG("DoS task idle\n"); /* PRQA S 0570 */
                (void)taskSuspend(taskIdSelf());
                break;
                
        default:
        	break;
        }
    }
}

LOCAL void _checkOnAttack(UINT16 *dos_state)
{
    uint32_t packet_rate = 0;
    uint32_t hmi0_rx_packets = 0;       
    static uint32_t hmi0_rx_packets_last = 0;
   
    static uint32_t dos_on_count_rounds = 0;
    static uint32_t cnt = 0;

    (void)_readRXpackets(&hmi0_rx_packets);
    BRDBG_MSG("RX packets: %d \n", hmi0_rx_packets);
    if (hmi0_rx_packets >= hmi0_rx_packets_last)
    {
    	packet_rate = hmi0_rx_packets - hmi0_rx_packets_last;
    }
    else
    {
    	packet_rate = UINT32_MAX - (hmi0_rx_packets_last - hmi0_rx_packets);
    }
    hmi0_rx_packets_last = hmi0_rx_packets;
    BRDBG_MSG("rate %d \n", packet_rate);

    if ( (HMI0_DOS_PACKET_MAX_LIMIT < packet_rate) && ((uint32_t)FALSE == DOS_ON) )  /* PRQA S 1843 */
    {
        DOS_ON = TRUE;
        dos_on_count_rounds ++;
        _disable_BR_link();
        printf("DoS: Attack Detected(%d)!\n",dos_on_count_rounds); /* PRQA S 3200 */
    }
    
    if ((uint32_t)TRUE == DOS_ON)/* PRQA S 1843 */
    {
        if (HMI0_DOS_ROUNDS_MAX_LIMIT > dos_on_count_rounds )
        {
            *dos_state = 0;
            
            if(cnt >= dos_on_count_rounds)
            {
                _enable_BR_link();
                (void)taskDelay(1);
                DOS_ON = FALSE;
                cnt = 0;
            }
            else 
            {
                cnt++;
                BRDBG_MSG("counter %i \n", cnt);
            }
        }
        else
        {
            *dos_state = 1; // change state to persistent BRIF disable 
        }
    }
    else
    {
        if ((uint32_t)0 < dos_on_count_rounds){
        	printf("DoS cleared on round %i \n", dos_on_count_rounds); /* PRQA S 3200 */
        }
        dos_on_count_rounds = 0;
        cnt = 0;
    }
}

LOCAL STATUS _readRXpackets(uint32_t *packets_cnt)
{
#define SFMT IPNET_IFI_STAT_FMT
    int                     name[6];
    Ip_u8                  *if_data;
    Ip_size_t               if_data_len;
    Ip_size_t               if_data_offset;
    struct Ipnet_if_msghdr *ifm;
    struct Ip_sockaddr     *hwaddr;
    char                    ifname[IP_IFNAMSIZ];
    char                    str[80];
    struct Ip_ifreq         ifreq;
   
    name[0] = IP_CTL_NET;
    name[1] = IP_AF_ROUTE;
    name[2] = 0;    /* Always 0 */
    name[3] = 0; // domain
    name[4] = IP_NET_RT_IFLIST;
    name[5] = _brif_info->if_nr; // index 

    restart_ifconfig:
        if (ipcom_sysctl(name, 6, IP_NULL, &if_data_len, IP_NULL, 0) < 0) /* PRQA S 3004 */
        {
            ipcom_printf("ifconfig: ipnet_sysctl() failed: %s"IP_LF, ipcom_strerror(ipcom_errno)); /* PRQA S 3200 */
            return ERROR;
        }

        if_data = ipcom_malloc(if_data_len); /* PRQA S 5118 */
        if (if_data == IP_NULL) /* PRQA S 3004 */
        {
            ipcom_printf("ifconfig: out of memory"IP_LF); /* PRQA S 3200 */
            return ERROR;
        }

        if (ipcom_sysctl(name, 6, if_data, &if_data_len, IP_NULL, 0) < 0) /* PRQA S 3004 */
        {
            if (ipcom_errno == IP_ERRNO_ENOMEM)
            {
                ipcom_free(if_data);  /* PRQA S 5118 */
                goto restart_ifconfig;
            }

            ipcom_printf("ifconfig: ipnet_sysctl() failed: %s"IP_LF, ipcom_strerror(ipcom_errno)); /* PRQA S 3200 */
            goto cleanup;
        }

        if_data_offset = 0;
        /*  MISRA  vioaltion
         * Error Message: Msg(7:3305) Pointer cast to stricter alignment.MISRA C:2012 Rule-11.3
         * 
         * Justification : This is done with intension and care. The purpose is to access structure type data 
         * in memory created by length in bytes. 
         */
        /* PRQA S 3305 2 */
        ifm = (struct Ipnet_if_msghdr *) &if_data[if_data_offset];  /* PRQA S 0310 */
        hwaddr = (struct Ip_sockaddr *) &if_data[if_data_offset + sizeof(struct Ipnet_if_msghdr)];  /* PRQA S 0310 */

        (void)ipcom_memset(&ifreq, 0, sizeof(struct Ip_ifreq));
        (void)ipcom_strlcpy(ifreq.ifr_name, ifname, IP_IFNAMSIZ);
        //if (ipcom_socketioctl(fd, IP_SIOCGIFVR, &ifreq) < 0)
            /* Default to VR 0 if the kernel is lacking VR support */
        ifreq.ip_ifr_vr = 0;

#ifdef  DEBUG_DOS       
        /* Resolve the interface name */
        ipcom_if_indextoname(ifm->ifm_index, ifname);
        ipcom_printf("%s\tLink type:%s", ifname, ipnet_cmd_if_type_to_str(ifm->ifm_data.ifi_type, str, sizeof(str)));
        if (((struct Ip_sockaddr_dl *) hwaddr)->sdl_alen != 0)
        {
            ipcom_printf("  HWaddr %s", ipcom_cmd_sockaddr_to_str(hwaddr, IP_FALSE, IP_TRUE, str, sizeof(str)));
        }

        ipcom_printf(IP_LF);
        ipcom_printf("\t%s"IP_LF, ipcom_cmd_if_flags_to_str(ifm->ifm_flags, str, sizeof(str)));
        ipcom_printf("\tMTU:%u  metric:%u  VR:%u  ifindex:%u",
                     ifm->ifm_data.ifi_mtu ,
                     ifm->ifm_data.ifi_metric,
                     ifreq.ip_ifr_vr,
                     ifm->ifm_index);
        ipcom_printf(IP_LF"\tRX packets:"SFMT" mcast:"SFMT" errors:"SFMT" dropped:"SFMT IP_LF,
                     ifm->ifm_data.ifi_ipackets, ifm->ifm_data.ifi_imcasts,
                     ifm->ifm_data.ifi_ierrors, ifm->ifm_data.ifi_iqdrops);
        ipcom_printf("\tTX packets:"SFMT" mcast:"SFMT" errors:"SFMT IP_LF,
                     ifm->ifm_data.ifi_opackets, ifm->ifm_data.ifi_omcasts,
                     ifm->ifm_data.ifi_oerrors);
        ipcom_printf("\tcollisions:"SFMT" unsupported proto:"SFMT IP_LF,
                     ifm->ifm_data.ifi_collisions, ifm->ifm_data.ifi_noproto);
        ipcom_printf(IP_LF IP_LF);
#endif
            
         *packets_cnt = ifm->ifm_data.ifi_ipackets;
        
    cleanup:
        ipcom_free(if_data); /* PRQA S 5118 */
        return 0;
        
}

/*****************************************************************************
 * startDosdetection
 *****************************************************************************/
/*! \brief        Spawns the tDoSdetection
 *****************************************************************************/
STATUS startDosdetection(void)
{

    cpuset_t affinity;
    int tid;
    /* Create the task but only activate it after setting its affinity */
    tid = taskCreate ("tDoSdetection", HMI0_DOS_TASK_PRIORITY, VX_FP_TASK, 5000,(FUNCPTR)_tDoSdetection_entry,  /* PRQA S 1291 */ /* PRQA S 0752 */ /* PRQA S 0313 */
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if (tid == NULL) 
    {
        printf("ERORR: tDoSdetection is not created\n"); /* PRQA S 3200 */
        return (ERROR);
    }
    
    /* Clear the affinity CPU set and set index for CPU 0 */
    CPUSET_ZERO (affinity);
    CPUSET_SET (affinity, 0);    /* PRQA S 4542 */ /* PRQA S 1841 */ /* PRQA S 4543 */  /* PRQA S 4544 */
    if (taskCpuAffinitySet (tid, affinity) == ERROR)
    {
    /* Either CPUs are not enabled or we are in UP mode */
        printf("ERROR: tDoSdetection affinity set\n"); /* PRQA S 3200 */
        (void)taskDelete (tid);
        return (ERROR);
    }
    /* Now let the task run on CPU 0 */
    (void)taskActivate (tid);
    
    /* Bind Recorder_DoS_Shm */
    _recorder_Shm_Alloc();
    
    //printf("tDoSdetection started\n");
    
    return 0;

}

#endif


#ifdef  DEBUG_BRDIAG
void brTestf(int input_p)
{
    MSG_Q_ID        msgq_retval;
    s_BR_DIAG_DATA    test_msg;
    int             i;

    if(input_p == 99)
    {
        struct ifaddrs *myaddrs, *ifa;
        struct sockaddr_in *s4;
        struct sockaddr_in6 *s6;
        int status;
        /* buff must be big enough for an IPv6 address (e.g. 3ffe:2fa0:1010:ca22:020a:95ff:fe8a:1cf8) */
        char buf[64];

        status = getifaddrs(&myaddrs);
        if (status != 0)
        {
            perror("getifaddrs");
            return;
        }

        for (ifa = myaddrs; ifa != NULL; ifa = ifa->ifa_next)
        {
            if (ifa->ifa_addr == NULL) continue;
            if ((ifa->ifa_flags & IFF_UP) == 0) continue;

            if (ifa->ifa_addr->sa_family == AF_INET)
            {
                s4 = (struct sockaddr_in *)(ifa->ifa_addr);
                if (inet_ntop(ifa->ifa_addr->sa_family, (void *)&(s4->sin_addr), buf, sizeof(buf)) == NULL)
                {
                    printf("%s: inet_ntop failed!\n", ifa->ifa_name);
                }
                else
                {
                    printf("%s: %s\n", ifa->ifa_name, buf);
                }
            }
            else if (ifa->ifa_addr->sa_family == AF_INET6)
            {
                s6 = (struct sockaddr_in6 *)(ifa->ifa_addr);
                if (inet_ntop(ifa->ifa_addr->sa_family, (void *)&(s6->sin6_addr), buf, sizeof(buf)) == NULL)
                {
                    printf("%s: inet_ntop failed!\n", ifa->ifa_name);
                }
                else
                {
                    printf("%s: %s\n", ifa->ifa_name, buf);
                }
            }
        }
        freeifaddrs(myaddrs);
    }
    else if(input_p==98)
    {
            msgq_retval = msgQOpen("/BRDiag_msgQ",1,sizeof(s_BR_DIAG_DATA),0,0,0);
            msgQReceive(msgq_retval, (char*)&test_msg, sizeof(s_BR_DIAG_DATA), NO_WAIT);
            msgQClose(msgq_retval);

            printf("DATA from BRDiag_msgQ:\n");
            printf("* eth_sig_quality:%d\n", test_msg.ethernet_signalquality);
            printf("* ping_resp:      %d\n", test_msg.ping_response);
            printf("* status_routine: %d\n", test_msg.status_routine);
            printf("* status_val:     %d\n", test_msg.status_val);
//            printf("* ip_br:          ");
//            for(i=0;i<8;i++) printf("%02x%02x:",test_msg.ip_br[i*2],test_msg.ip_br[i*2+1]);
//            printf("\n* mac_br:          ");
//            for(i=0;i<6;i++) printf("%02X:",test_msg.mac_br[i]);
//            printf("\n");
//            printf("* Switch Core IP SVN: %d\n"
//                   "* Switch Config SVN: %d\n"
//                   "* Switch Config IF-Set: %u.%u.%u\n",
//                   test_msg.switch_core_ip_rev, test_msg.switch_config_rev,
//                   test_msg.variant[0], test_msg.variant[1], test_msg.variant[2]);
    }
    else if(input_p==97)
    {
#ifdef INCLUDE_DOS_DETECTION
        _enable_BR_link();
#endif
    }
    else
    {
        // msgq_retval = msgQOpen("/BRTriggerTest_msqQ",1,sizeof(int),0,0,0);
        // msgQSend(msgq_retval, (char*)&input_p, sizeof(int), NO_WAIT, MSG_PRI_NORMAL);
        // msgQClose(msgq_retval);
    }
}
#endif

