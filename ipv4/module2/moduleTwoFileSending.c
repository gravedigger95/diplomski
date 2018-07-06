/**
 *  \file 
 *      moduleTwoFileSending.c
 *      
 *  \brief 
 *       Functions that handle file sending to PC side.
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
/* Error message : Msg(7:0602) [U] The identifier '<identifier_name>' is reserved for 
 * use by the library.
 * 
 * Justification : Named according to the ZFAS coding guidelines at 
 * CGL-D-ZFAS-Z-01-001.docx 
 */
/* PRQA S 0602 EOF */
  /* ------------------------------------------------------------------------- */
/* Error Message: Msg(7:0310) Casting to different object pointer type.MISRA C:2012 
 * Rule-11.3; REFERENCE - ISO:C90-6.3.4 Cast Operators - Semantic
 * 
 * Justification : This is checked and considered safe. It is confirmed by multiple
 * testing cases and long period project usage. 
 */
/* ------------------------------------------------------------------------- */
/* ------------------------------  Includes  ------------------------------- */
/* ------------------------------------------------------------------------- */
#include <vxworks.h>
#include <stdio.h>
#include <dirent.h>
#include <sockLib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "moduleTwoServer.h"
#include "moduleTwoHandleRoutines.h"
#include "moduleTwoFileSending.h"

/************************************************************************
 * INTERNAL VARIABLES
 ***********************************************************************/
LOCAL char _tempDir[BUFLEN];
LOCAL FILE * _fs;

/************************************************************************
 * FUNCTION IMPLEMENTATION
 ***********************************************************************/
void uploadFile(void)
{
    uint32_t networkFilesNum = 1U;
    DIR * dirp;
    char tempStr[BUFLEN];
    
    (void) printf ("changeSTAT: %d\n\n", _changeState);
    _changeState = STATEMACHINE_WAIT_FOR_COMMAND;
    networkFilesNum = htonl_br (networkFilesNum);
    
    if (send (_newSocket, (char *) &networkFilesNum, sizeof (networkFilesNum), 0) == SOCKET_ERROR) /* PRQA S 0310 */
    {
    	(void) printf ("Number of files send() FAILED!\n\n");
    }
    (void) printf ("Number of files is sent!\n");
           
    dirp = opendir ("/mmc0:1/err");
    if (NULL_PTR == dirp) 
    {
    	(void) printf ("error opening dir!\n\n");
    }
    else
    {
        (void) strcpy (tempStr, "errorLog.txt");
        _sendFile (tempStr);
        (void) closedir (dirp);  
    }
    (void) printf ("****************************************************");
}


LOCAL void _sendFile(char fs_name[])
{
    _processFileName(fs_name);
    
    _processFileSize();
    
    _processFileSending();
    (void) printf ("\n\nOk! File %s from _server was sent!\n\n", _tempDir);
    
    /* Remove file when sent */
    if (remove (_tempDir) == ERROR)
    {
    	(void) printf ("File has not been deleted!\n");
    }
    else
    {
    	(void) printf("File %s deleted\n", _tempDir);
    }    
}

LOCAL void _processFileSending(void)
{
    struct timespec nsTime;
    nsTime.tv_sec  = 0;
    nsTime.tv_nsec = 50000000;
    int32_t blockSize = -1;
    uint32_t sdbuf[BUFLEN];
    
    (void) memset (sdbuf, 0, BUFLEN);
    (void) fseek (_fs, 0, SEEK_SET);

    /* Sending file... */
    while (blockSize != NULL)
    {
        blockSize = (int) fread (sdbuf, sizeof (int8_t), BUFLEN, _fs);
        if (NULL == blockSize)
        {
            continue;
        }
        (void) nanosleep (&nsTime, NULL_PTR);
        (void) printf ("%x ", sdbuf[0]);
        (void) nanosleep (&nsTime, NULL_PTR);
     
        if (send (_newSocket, (uint8_t *) sdbuf, (uint32_t) blockSize, 0) < 0) /* PRQA S 0310 */
        {
        	(void) fprintf (stderr, "ERROR: Failed to send file %s. (errno = %d)\n", _tempDir, errno);
            break;
        }
        (void) memset (sdbuf, 0, (uint32_t) blockSize);
        (void) nanosleep (&nsTime, NULL_PTR);
        
    }
    (void) fclose (_fs);
}

LOCAL void _processFileSize(void)
{
    uint32_t fileLentgh      = 0U;
    
    (void) printf ("Sending %s to the _client... \n\n", _tempDir);
    _fs = fopen (_tempDir, "rb");
    if (NULL_PTR == _fs)
    {
    	(void) printf ("ERROR: File %s not found.\n", _tempDir);
    }
        
    (void) fseek (_fs, 0, SEEK_END);
    /* Get file size */
    fileLentgh = (uint32_t) ftell (_fs);
    
    /* Send file size */
    fileLentgh = htonl_br (fileLentgh);
    if (send (_newSocket, (char *) &fileLentgh, sizeof (fileLentgh), 0) == SOCKET_ERROR) /* PRQA S 0310 */
    {
    	(void) printf ("Name of the file send() FAILED!\n\n");
    }
    (void) printf ("Size of file is sent!\n");

    (void) printf ("\n\n\n\n\n\n char: %d, unsigned char: %d, int: %d, long long: %d \n\n\n\n\n\n\n",
            sizeof (char), sizeof (unsigned char), sizeof (int), sizeof (long long));          
}

LOCAL void _processFileName(char fs_name[])
{
    struct timespec nsTime;
    nsTime.tv_sec  = 0;
    nsTime.tv_nsec = 50000000;
    
    (void) printf ("File name to send: %s\n", fs_name);
    
    (void) nanosleep (&nsTime, NULL_PTR);
    
    /* Send file name without path */
    if (send (_newSocket, fs_name, strlen (fs_name), 0) == SOCKET_ERROR)
    {
    	(void) printf("Name of the file send() FAILED!\n\n");
    }
    (void) nanosleep (&nsTime, NULL_PTR);

    (void) printf ("Name of file is sent\n\n");
    
    (void) memset (_tempDir, 0, BUFLEN); 
    (void) strcpy (_tempDir, "/mmc0:1/err/");
    
    /* Concatenate filename with path */
    (void) strcat (_tempDir, fs_name);
    (void) printf ("Fullpath: %s", _tempDir);
}
