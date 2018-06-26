/* includes */

#include <vxworks.h>
#include <stdio.h>
#include <msgQLibCommon.h>
#include <msgQLib.h>
#include <time.h>
#include <ioctl.h>
#include <ioLib.h>
#include <rtpLibcommon.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sysctlLib.h>
#include <taskLib.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>
#include <net/route.h>
#include <ipnet/ipioctl.h>
#include <ipnet/ipioctl_var.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>
#include <cpuset.h>
#include <sys/mman.h>
#include <sys/fcntlcom.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <msgQLib.h>
#include <fioLib.h>
#include <sockLib.h>
#include <socket.h>
#include <inetLib.h>
#include <stdarg.h>
#include <stddef.h>
#include <net/if_dl.h>
#include <net/if_types.h>
#include <net/ifaddrs.h>
#include <netinet6/in6_var.h>
#include <netinet/ip.h>
#include <sys/ioctl.h>
#include <timers.h>
#include <timerLib.h>
#include <dirent.h>
#include <zlib.h>
#include <math.h>
#include "module2.h"

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
 /* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:4397) An expression which is the result of a ~ or << 
 * operation has not been cast to its essential type.MISRA C:2012 Rule-10.7
 * 
 * Justification : This is checked and considered safe.
 */  

 
 /************************************************************************
 * GLOBAL VARIABLES
 ***********************************************************************/
MSG_Q_ID routinesMsgQId    = MSG_Q_ID_NULL;
MSG_Q_ID diagMsgQId        = MSG_Q_ID_NULL;

MSG_Q_ID messages = MSG_Q_ID_NULL;
TASK_ID task;


/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL s_DIAG_SHM_DATA * _diag_shm_ptr_check;
LOCAL s_DIAG_SHM_DATA _diag_shm_struct;
LOCAL s_DIAG_DATA _diag_data_struct_mod2;
LOCAL s_DIAG_DATA _diag_data_struct_mod1;

LOCAL char _read_buff[READ_BUFF_SIZE];

LOCAL struct sockaddr_in6 _server;
LOCAL struct sockaddr_in6 _client;
LOCAL int _s, _newSocket, _c, _recvSize;
LOCAL char _buffer[BUFLEN];

LOCAL uint8_t _changeState      = 0;    
LOCAL uint32_t _routineNumRecv  = 0;
LOCAL uint8_t _msg              = 0;

LOCAL char _tempDir[BUFLEN];
LOCAL uint32_t _sdbuf[BUFLEN];
LOCAL FILE * _fs;


LOCAL const char _message[]      = "Start";
LOCAL const char _respondOK[]    = "Let's communicate!";
LOCAL const char _respondNotOK[] = "Communication breakdown...";



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
    

    if (taskSpawn ("readErrors", 205, VX_FP_TASK, 200, (FUNCPTR) _module2_ReadErrors, 0, 0,  /* PRQA S 0752 */ /* PRQA S 0313 */
                0, 0, 0, 0, 0, 0, 0, 0) == ERROR)
    {
        printf ("taskSpawn of readErrors failed\n"); 
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

LOCAL void _module2_ReadErrors(void)
{
    int fd;
    int i = 0;


    FOREVER
    {   
        fd = open("/mmc0:1/myErrorsArray", 0,  S_IRUSR); 
        if (ERROR != fd)
        {
            (void) read (fd, _read_buff, sizeof (_read_buff));
            (void) close (fd);
        }
        for (i = 0; i < READ_BUFF_SIZE; i++)
        {
            //printf ("%d ", _read_buff[i]);
        }   
        //printf("\n ");
        (void) taskDelay (TASK_DELAY_100MS);
    }
}

LOCAL STATUS _module2_SetRoutineNum(int routineNum)
{
    int8_t ret = OK;
    _read_buff[1] = (char) 0;
    _read_buff[2] = (char) 0;

    /* Open _msg queue */
    routinesMsgQId = msgQOpen ("/routinesMsgQ", MAX_MSG, sizeof(uint32_t), MSG_Q_FIFO, OM_CREATE, NULL_PTR); 
    if (MSG_Q_ID_NULL == routinesMsgQId)
    {
        printf ("setRoutineNum open ERROR\n");
        _read_buff[1] = (char) 1;
        ret = ERROR;
    }
    
    /* Send routine number to module 1 */ 
    printf ("Set rooutine num: %d\n", routineNum);
    if (msgQSend (routinesMsgQId, (char *) &routineNum, sizeof (routineNum), NO_WAIT, MSG_PRI_NORMAL) == ERROR)
    {
        printf ("setRoutineNum send ERROR\n");
        _read_buff[2] = (char) 1;
        ret = ERROR;
    }
    return ret;
}

LOCAL STATUS _module2_ReadDiagMsgQ(void)
{
    int32_t length;
    int8_t ret   = OK;
    _read_buff[1] = (char) 0;
    _read_buff[3] = (char) 0;
    
    diagMsgQId = msgQOpen ("/diagMsgQ", 1, sizeof (_diag_data_struct_mod1), MSG_Q_FIFO, OM_CREATE, NULL_PTR);
    if (MSG_Q_ID_NULL == diagMsgQId)
    {
        _read_buff[1] = (char) 1;
        ret = ERROR;
    }
    
    /* Read diagnostic data from _msg queue */
    length = msgQReceive (diagMsgQId, (char *) &_diag_data_struct_mod1, sizeof (_diag_data_struct_mod1), WAIT_FOREVER);  /* PRQA S 3101 */ /* PRQA S 3102 */


    _diag_data_struct_mod2 = _diag_data_struct_mod1;

    if (length < 0)
    {
        printf ("checkMSGq ERROR\n");
        _read_buff[3] = (char) 1;
        ret = ERROR;
    }

    /* Read diagnostic data from sh mem */
    (void) _module2_shMem_Check();
    
    return ret;
}

LOCAL STATUS _sharedMemAlloc_module2(void)
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
    _read_buff[5] = (char) 0;
    
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
        _read_buff[5] = (char) 1;
        ret = ERROR;
    }
    return ret;
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

LOCAL void _processMessage(void)
{
    switch (_msg)
    {
        case STATEMACHINE_WAIT_FOR_COMMAND:
            _receiveCommand();
            break;
        case STATEMACHINE_SEND_FILE:
            _uploadFile();
            break;
        case STATEMACHINE_START_ROUTINE:
            _module2_SetRoutineNum ((int32_t) _routineNumRecv);
            _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
            break;
        case STATEMACHINE_SEND_MSG_QUEUE:
            if (send (_newSocket, (char *) &_diag_data_struct_mod2, sizeof (_diag_data_struct_mod2), 0) == SOCKET_ERROR)
            {
                printf ("msgq struct send() FAILED!\n\n");
            }
            printf ("msgq struct  is sent!\n"); 
            _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
            break;
        case STATEMACHINE_SEND_SHARED_MEMORY:
            if (send (_newSocket, (char *) &_diag_shm_struct, sizeof (_diag_shm_struct), 0) == SOCKET_ERROR)
            {
                printf ("shmem struct send() FAILED!\n\n"); 
            }
            printf ("shmem struct  is sent!\n");
            _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
            break;
        default:
            (void) close (_s);
            (void) close (_newSocket);
            printf ("Client disconnected!\n");
            break;
    }
        
}

LOCAL void _uploadFile(void)
{
    uint32_t filesNum        = 1U;
    uint32_t networkFilesNum = 0U;
    DIR * dirp;
    char tempStr[BUFLEN];
    
    printf ("changeSTAT: %d\n\n", _changeState);
    _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
    networkFilesNum = htonl_br (filesNum);
    
    if (send (_newSocket, (char *) &networkFilesNum, sizeof (networkFilesNum), 0) == SOCKET_ERROR)
    {
        printf ("Number of files send() FAILED!\n\n");
    }
    printf ("Number of files is sent!\n");
           
    dirp = opendir ("/mmc0:1/err");
    if (NULL_PTR == dirp) 
    {
        printf ("error opening dir!\n\n");
    }
    else
    {
        strcpy (tempStr, "errorLog.txt");
        _sendFile (tempStr);
        closedir (dirp);  
    }
    printf ("****************************************************");
}

LOCAL void _receiveCommand(void)
{
    uint32_t commandNum = EXIT_BG_TASK;

    _recvSize = recv (_newSocket, &commandNum, sizeof (commandNum), 0);
    if (SOCKET_ERROR  == _recvSize)
    {
        printf ("Recv from _client failed!");
    }
    commandNum = ntohl_br (commandNum);
    printf ("%d\n", commandNum); 
    
    if (SEND_FILE == commandNum)
    {
        _changeState = STATEMACHINE_SEND_FILE;
    }
    else if (START_ROUTINE == commandNum)
    {
        _recvSize = recv (_newSocket, &_routineNumRecv, sizeof (_routineNumRecv), 0);
        if (SOCKET_ERROR == _recvSize)
        {
            printf ("Recv from _client failed!");
        }
        _routineNumRecv = ntohl_br (_routineNumRecv);
        printf ("routineNum = %d\n", _routineNumRecv);
        _changeState = STATEMACHINE_START_ROUTINE;
    }
    else if (SEND_MSG_QUEUE == commandNum)
    {
        _changeState = STATEMACHINE_SEND_MSG_QUEUE;
    }
    else if (SEND_SHARED_MEMORY == commandNum)
    {
        _changeState = STATEMACHINE_SEND_SHARED_MEMORY;
    }
    else
    {
        _changeState = STATEMACHINE_EXIT_BG_TASK;
    }
}

LOCAL void _sendFile(char fs_name[])
{

    
    _processFileName(fs_name);
    
    _processFileSize();
    
    memset (_sdbuf, 0, BUFLEN);

    _processFileSending();
    printf ("\n\nOk! File %s from _server was sent!\n\n", _tempDir);

    
    /* Remove file when sent */
    if (remove (_tempDir) == ERROR)
    {
        printf ("File has not been deleted!\n");
    }
    else
    {
        printf("File %s deleted\n", _tempDir);
    }
    
    
    //(void) nanosleep (&nsTime, NULL_PTR);
}

LOCAL void _processFileSending(void)
{
    struct timespec nsTime;
    nsTime.tv_sec  = 0;
    nsTime.tv_nsec = 50000000;
    int32_t blockSize = -1;
    
    /* Sending file... */
    while (blockSize != NULL)
    {
        blockSize = (int) fread (_sdbuf, sizeof (int8_t), BUFLEN, _fs);
        if (NULL == blockSize)
        {
            continue;
        }
        (void) nanosleep (&nsTime, NULL_PTR);
        printf ("%x ", _sdbuf[0]);
        (void) nanosleep (&nsTime, NULL_PTR);
     
        if (send (_newSocket, (uint8_t *) _sdbuf, (uint32_t) blockSize, 0) < 0)
        {
            fprintf (stderr, "ERROR: Failed to send file %s. (errno = %d)\n", _tempDir, errno);
            break;
        }
        memset (_sdbuf, 0, (uint32_t) blockSize);
        (void) nanosleep (&nsTime, NULL_PTR);
        
    }
    (void) fclose (_fs);
}

LOCAL void _processFileSize(void)
{
    uint32_t fileLentgh      = 0U;
    uint32_t convertedNumber = 0U;
    
    printf ("Sending %s to the _client... \n\n", _tempDir);
    _fs = fopen (_tempDir, "rb");
    if (NULL_PTR == _fs)
    {
        printf ("ERROR: File %s not found.\n", _tempDir);
    }
        
    fseek (_fs, 0, SEEK_END);
    /* Get file size */
    fileLentgh = (uint32_t) ftell (_fs);
    fseek (_fs, 0, SEEK_SET);
    printf ("Size of file to send: %d\n\n\n", fileLentgh);
    /* Send file size */
    convertedNumber = htonl_br (fileLentgh);
    if (send (_newSocket, (char *) &convertedNumber, sizeof (convertedNumber), 0) == SOCKET_ERROR)
    {
        printf ("Name of the file send() FAILED!\n\n");
    }
    printf ("Size of file is sent!\n");

    printf ("\n\n\n\n\n\n char: %d, unsigned char: %d, int: %d, long long: %d \n\n\n\n\n\n\n",
            sizeof (char), sizeof (unsigned char), sizeof (int), sizeof (long long));
            
}

LOCAL void _processFileName(char fs_name[])
{
    struct timespec nsTime;
    nsTime.tv_sec  = 0;
    nsTime.tv_nsec = 50000000;
    
    
    printf ("File name to send: %s\n", fs_name);
    
    (void) nanosleep (&nsTime, NULL_PTR);
    
    /* Send file name without path */
    if (send (_newSocket, fs_name, strlen (fs_name), 0) == SOCKET_ERROR)
    {
        printf("Name of the file send() FAILED!\n\n");
    }
    (void) nanosleep (&nsTime, NULL_PTR);

    printf ("Name of file is sent\n\n"); 
    printf ("size of name sent: %d\n", strlen (fs_name));
    
    
    memset (_tempDir, 0, BUFLEN); 
    strcpy (_tempDir, "/mmc0:1/err/");
    
    /* Concatenate filename with path */
    strcat (_tempDir, fs_name);
    printf ("Fullpath: %s", _tempDir);
    printf ("");
}

LOCAL void _initCommunication(void)
{
    /*
        struct addrinfo hints;
        struct addrinfo * firstres;
        struct addrinfo * res;
        int rc;
        int size;

        memset(&hints, 0, sizeof(hints));
        
        hints.ai_family = AF_UNSPEC;
        hints.ai_protocol = IPPROTO_TCP;
        
        rc = getaddrinfo("fd53:7cb8:383:3::73", "tcp", &hints, &firstres);
        
        res = fistres;
        
        _s = socket (res->ai_family, res->ai_socktype, res->ai_protocol);

        if (SOCKET_ERROR == _s)
        {
            printf ("Could not create socket!\n"); 
        }
        printf ("\n\nSocket created.\n");
                
        size = 65536;
        setsockopt(_s, SOL_SOCKET, SO_SNDBUF, (char *) &size, sizeof(size));
        setsockopt(_s, SOL_SOCKET, sO_RCVBUF, (char *) &size, sizeof(size));
    */    
    
    _s = socket (AF_INET6, SOCK_STREAM, 0);
    if (SOCKET_ERROR == _s)
    {
        printf ("Could not create socket!\n");
    }
    printf ("\n\nSocket created.\n");
    
    memset ((char *) &_server, 0, sizeof (_server));
    _server.sin6_family = AF_INET6;
    //_server.sin_addr.s_addr = INADDR_ANY;
    _server.sin6_port = htons_br ((uint16_t) SWU_BR_SERVERPORT); /* PRQA S 4397 */
    inet_pton(AF_INET6, "::0", &_server.sin6_addr);
    
    if (bind (_s, (struct sockaddr *) &_server , (int32_t) sizeof (_server)) == SOCKET_ERROR)
    {
        printf ("Bind failed: %s\n", strerror (errno));
    }
             
    printf ("Bind done!");
            
    printf ("Listetning...\n");
            
   _establishCommunication();

}

LOCAL void _establishCommunication(void)
{
    listen (_s, BACKLOG);
    
    printf ("Waiting for incoming connections...\n\n\n\n");
    
    _c = (int32_t) sizeof (struct sockaddr_in6); 
    
    _newSocket = accept (_s, (struct sockaddr *) &_client, &_c);
    if (SOCKET_ERROR == _newSocket)
    {
        printf ("Accept failed with error!\n");
    }
    printf ("Connection accepted!");
    
    /* Receive initial message from client */
    _recvSize = recv (_newSocket, _buffer, BUFLEN, 0);
    if (SOCKET_ERROR == _recvSize)
    {
        printf ("Recv from _client failed!");
    }
    printf ("Reply received --------->");
    
    _buffer[_recvSize] = '\0';
    printf (_buffer);
    printf ("\n");
    
    /* Send initial response to client */
    if (strcmp (_buffer, _message) == 0)
    {
        if (send (_newSocket, _respondOK, strlen (_respondOK), 0) == SOCKET_ERROR)
        {
            printf ("First send() failed\n");
        }
        printf ("Everything is fine, let's chat!\n\n");
    }
    else
    {
        if (send (_newSocket, _respondNotOK, strlen (_respondOK), 0) == SOCKET_ERROR)
        {
            printf ("Second send() failed\n");
        }
    }
}


