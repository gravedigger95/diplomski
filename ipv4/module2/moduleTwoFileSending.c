/*
 * moduleTwoFileSending.c
 *
 *  Created on: Jun 27, 2018
 *      Author: bura
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
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include "moduleTwoFileSending.h"

/************************************************************************
 * EXTERNAL VARIABLES
 ***********************************************************************/
extern uint8_t _changeState; 
extern int _newSocket;

/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL char _tempDir[BUFLEN];
LOCAL uint32_t _sdbuf[BUFLEN];
LOCAL FILE * _fs;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
void _uploadFile(void)
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
