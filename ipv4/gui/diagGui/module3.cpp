#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <inttypes.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <time.h>
#include <Windows.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <_module3.h>

using namespace std;

//static const uint8_t zfasAddr[16] = {0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4f};

SOCKET s;

uint32_t cnt = 0U;
uint8_t done = 1;
int commandNum = -1;
uint8_t download = 0;

s_DIAG_DATA diagMsgQ;
s_DIAG_SHM_DATA diagShMem;

pthread_t tid;
void *dequeueLoopWrapper(void *arg);


int Module3::startModule(int insertedNumber)
{
    uint32_t numOfFilesToBeReceived;
    int32_t recvSize;
    FILE * fd_msgq;
    FILE * fd_shmem;

    /* Initialize communication with server side */
    /* Activate thread for downloading files periodically */

    commandNum = insertedNumber;

        if (download == 1)
        {
            return 0;
        }
        if (done == 0)
        {
            return 0;
        }

        commandNum = htonl (commandNum);

        if (send(s, (char *) &commandNum, sizeof (commandNum), 0) < 0)
        {
            printf ("Send failed");
            exit (EXIT_FAILURE);
        }
        printf ("Command sent\n");
        Sleep (SLEEP_TIME);

        commandNum = ntohl (commandNum);


        if (commandNum == 3)
        {
            if ((recvSize = recv (s, (char *) &diagMsgQ, sizeof (diagMsgQ), 0)) == SOCKET_ERROR)
            {
                printf ("Num of files recv() failed\n");
            }

            printStates();


            fd_msgq = fopen ("msgQData.txt", "a");

            if (fd_msgq != NULL)
            {
                fprintf (fd_msgq, "phy_id_reg1 0x%04x\nlink_status 0x%04x\nlink_control 0x%04x\npower_mode 0x%04x\nloopback_mode 0x%04x\nphy_init_fail 0x%04x\nwakeup 0x%04x\nlink_status_fail 0x%04x\nlink_status_up 0x%04x\nlink_up 0x%04x\ntx_mode 0x%04x\nloc_rcvr_status 0x%04x\nrem_rcvr_status 0x%04x\nphy_state 0x%04x\n",
                diagMsgQ.phy_id_reg1, diagMsgQ.link_status, diagMsgQ.link_control, diagMsgQ.power_mode,
                diagMsgQ.loopback_mode, diagMsgQ.phy_init_fail, diagMsgQ.wakeup, diagMsgQ.link_status_fail,
                diagMsgQ.link_status_up, diagMsgQ.link_up, diagMsgQ.tx_mode, diagMsgQ.loc_rcvr_status,
                diagMsgQ.rem_rcvr_status, diagMsgQ.phy_state);

                fclose(fd_msgq);
            }

        }
        else if (commandNum == 4)
        {
            if ((recvSize = recv (s, (char *) &diagShMem, sizeof (diagShMem), 0)) == SOCKET_ERROR)
            {
                printf("Num of files recv() failed");
            }
            printf ("jabber_detect 0x%04x ", diagShMem.jabber_detect);
            if (diagShMem.jabber_detect == 0)
            {
                printf("No jabber condition detected!\n");
            }
            else
            {
                printf("Jabber condition detected!\n");
            }

            printf ("phy_id_reg1 0x%04x\n", diagShMem.phy_id_reg1);
            printf ("phy_id_reg2 0x%04x\n", diagShMem.phy_id_reg2);
            printf ("type_no 0x%04x\n", diagShMem.type_no);
            printf ("revision_no 0x%04x\n", diagShMem.revision_no);
            printf ("phy_id_reg3 0x%04x\n", diagShMem.phy_id_reg3);
            fd_shmem = fopen ("shMemData.txt", "a");

            if (fd_shmem != NULL)
            {
                fprintf (fd_shmem, "jabber_detect 0x%04x\nphy_id_reg1 0x%04x\nphy_id_reg2 0x%04x\ntype_no 0x%04x\nrevision_no 0x%04x\nphy_id_reg3 0x%04x\n",
                diagShMem.jabber_detect, diagShMem.phy_id_reg1, diagShMem.phy_id_reg2,
                diagShMem.type_no, diagShMem.revision_no, diagShMem.phy_id_reg3);
                fclose (fd_shmem);
            }

        }
        else if(commandNum == 0)
        {
            closesocket (s);
            WSACleanup();
            printf ("Waiting for thread to end...\n");
            pthread_join (tid, NULL);
            printf("Thread joined\n");
            printf ("Disconnected\n");

        }


    return 0;
}

void Module3::receiveFile()
{
    char fr_name[BUFLEN];
    uint8_t revbuf[BUFLEN];
    char revbufLong[BUFLEN];
    int32_t fr_block_sz = 0;
    int32_t recvNameSize;
    int32_t recvSizeSize;
    long sizeOfFile;
    int32_t iter = 1;
    int32_t i;
    int32_t numOfPackets;
    int32_t leftover;


    /* Clean buffers */
    memset (revbuf, 0, BUFLEN);
    memset (revbufLong, 0, BUFLEN);
    memset (fr_name, 0, BUFLEN);


    /* Receive file name */
    if ((recvNameSize = recv (s, fr_name, sizeof (fr_name), 0)) == SOCKET_ERROR)
    {
        printf ("Name of the file recv() failed");
    }
    Sleep (SLEEP_TIME);

    printf ("File name length: %d\t---------->\t", recvNameSize);
    fr_name[recvNameSize] = '\0';

    if (strcmp (fr_name, "errorLog.txt") == 0)
    {
        if (sprintf(fr_name, "errorLog_%d.txt", cnt) < 0)
        {
            printf ("Sprintf failed.\n");
        }
        cnt++;
    }
    else
    {
        exit(1);
    }

    FILE *fr = fopen (fr_name, "w");
    if (fr == NULL)
    {
        printf ("File %s cannot be opened!\n", fr_name);
    }

    /* Receive file size */
    if ((recvSizeSize = recv(s, (char *) &sizeOfFile, sizeof (sizeOfFile), 0)) == SOCKET_ERROR)
    {
        printf ("Name of the file recv() failed");
    }
    Sleep (SLEEP_TIME);

    printf ("recvSizeSize %d\n", recvSizeSize);

    sizeOfFile = ntohl (sizeOfFile);

    printf ("Size of file: %ld\n\n", sizeOfFile);

    numOfPackets = sizeOfFile / BUFLEN;
    leftover = sizeOfFile % BUFLEN;

    printf ("numOfPackets: %d * BUFLEN \t\t leftover: %d\n\n", numOfPackets, leftover);

    printf ("\n\n\n\n\n\n char: %d, unsigned char: %d, int: %d, long long: %d \n\n\n\n\n\n\n", sizeof (char), sizeof (unsigned char), sizeof (int), sizeof (long long));


    /* Receiving file */
    while ((fr_block_sz = recv(s, revbufLong, sizeof (revbuf), 0)) != 0)
    {
        Sleep (SLEEP_TIME);

        printf ("fr_block_sz %d\n", fr_block_sz);

        printf ("-%x-  ", revbufLong[0]);

        Sleep (SLEEP_TIME);

        /* Write to file on PC */
        fwrite (revbufLong, sizeof (uint8_t), fr_block_sz, fr);
        Sleep (SLEEP_TIME);

        memset (revbuf, 0, fr_block_sz);
        memset (revbufLong, 0, fr_block_sz);

        if (fr_block_sz < sizeof (revbuf))
        {
            break;
        }

    }
    download = 0;

    fclose (fr);
}

int Module3::initCommunication(void)
{
    WSADATA wsa;
    struct sockaddr_in server;
    const char message[] = "Start";
    const char respondOK[] = "Let's communicate!";
    char serverReply[BUFLEN];
    int32_t recvSize;


    pthread_create(&tid, NULL, &dequeueLoopWrapper, NULL);


    printf ("\nInitialising Winsock...");
    if (WSAStartup (MAKEWORD (2, 2), &wsa) != 0)
    {
        printf ("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    printf ("Initialised.\n");


    if ((s = socket (AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf ("Could not create socket : %d", WSAGetLastError());
    }
    printf ("Socket created.\n");

    server.sin_family = AF_INET;
    server.sin_port = htons (SWU_BR_SERVERPORT);
    //server.sin6_addr = in6addr_any;
    //server.sin6_addr.s6_addr = SWUP_ZFAS_IP_ADDRESS;
    //memcpy(server.sin6_addr.s6_addr, zfasAddr, sizeof(zfasAddr));
    //inet_pton(AF_INET6, "::1", &(server.sin6_addr));
    server.sin_addr.s_addr = inet_addr (zFAS_IPv4);

    printf ("Connect to remote server");
    if (::connect(s, (struct sockaddr *) &server, sizeof (server)) < 0)
    {
        printf ("Failed. Error Code : %d\n", WSAGetLastError());
        exit (EXIT_FAILURE);
    }
    printf ("Connected");

    /* Send init message */
    if (send (s, message, strlen (message), 0) < 0)
    {
        printf ("Send failed");
        exit (EXIT_FAILURE);
    }
    printf ("Data sent\n");

    /* Receive ACK that connection is established */
    if ((recvSize = recv (s, serverReply, BUFLEN, 0)) == SOCKET_ERROR)
    {
        printf ("Recv failed");
    }
    printf ("Reply received\n");

    printf ("Server reply: %d\n", recvSize);
    serverReply[recvSize] = '\0';
    printf (serverReply);
    printf ("\n");

    if (strcmp (serverReply, respondOK) == 0)
    {
        printf ("Connection established!!!\n\n");
        printf ("*****************************************************************************");
    }
}


void Module3::sendRoutineNum(int rNum)
{
    struct sockaddr_in server;
    int routineNum;
    uint8_t flag = 0;

    routineNum = rNum;
    while (flag != 1)
    {
        done = 0;
        flag = 0;

        if (routineNum > 6 || routineNum < 0)
        {
            continue;
        }
        flag = 1;
    }

    printf ("Routine number %d\n", routineNum);

    routineNum = htonl (routineNum);

    if (send(s, (char *) &routineNum, sizeof (routineNum), 0) < 0)
    {
        printf ("Send failed");
        exit (EXIT_FAILURE);
    }
    printf ("Routine Num sent\n");
    Sleep (SLEEP_TIME);
    done = 1;
}
void *dequeueLoopWrapper(void *arg)
{
    Module3 * module3 = static_cast<Module3*>(arg);
    module3->threadfunc(arg);
    return nullptr;
}

void *Module3::threadfunc(void * arg)
{

    uint32_t numOfFilesToBeReceived;
    int32_t recvSize;


    printf ("Thread started...\n");
    while (1)
    {
        printf("We are in thread\n");

        if (done == 0)
        {
            continue;
        }

        /* Sleep for 15s */
        Sleep (SLEEP_TIME * 1000);

        if (done == 0)
        {
            continue;
        }
        if (commandNum == 0)
        {
            break;
        }

        if(diagMsgQ.link_status == 0)
        {
            continue;
        }

        download = 1;
        commandNum = 1;
        commandNum = htonl (commandNum);
        if (send (s, (const char *) &commandNum, sizeof (commandNum), 0) < 0)
        {
            printf ("Send failed");
            exit (EXIT_FAILURE);
        }
        printf ("Command sent sent\n");

        if ((recvSize = recv(s, (char *) &numOfFilesToBeReceived, sizeof (numOfFilesToBeReceived), 0)) == SOCKET_ERROR)
        {
            printf ("Num of files recv() failed");
        }
        Sleep (SLEEP_TIME);

        numOfFilesToBeReceived = ntohl (numOfFilesToBeReceived);
        printf ("Number of files to receive: %d\n\n\n", numOfFilesToBeReceived);
        numOfFilesToBeReceived = 1;

        Sleep (SLEEP_TIME);
        printf ("Receiving file...\n");
        receiveFile();

        printf ("\n\n");

        printf ("\n\n\n\n\n\n\n\t\t\t\t\t**********D O N E*********\n\n\n\n\n");

    }

    printf("Thread done!\n");
    return 0;
}

void Module3::printStates(void)
{
    printf("phy_id_reg1 0x%04x\n", diagMsgQ.phy_id_reg1);

    printf("link_status 0x%04x ", diagMsgQ.link_status);
    if (diagMsgQ.link_status == 0)
    {
        printf("Link is down!\n");
    }
    else
    {
        printf("Link is up!\n");
    }

    printf("link_control 0x%04x ", diagMsgQ.link_control);
    if (diagMsgQ.link_control == 0)
    {
        printf("Link control disabled!\n");
    }
    else
    {
        printf("Link control enabled!\n");
    }

    printf("power_mode 0x%04x ", diagMsgQ.power_mode);
    if (diagMsgQ.power_mode == 0)
    {
        printf("No change!\n");
    }
    else if (diagMsgQ.power_mode == 3)
    {
        printf("Normal mode!\n");
    }
    else if (diagMsgQ.power_mode == 12)
    {
        printf("Standby mode!\n");
    }
    else
    {
        printf("Sleep request mode!\n");
    }

    printf("loopback_mode 0x%04x ", diagMsgQ.loopback_mode);
    if (diagMsgQ.loopback_mode == 0)
    {
        printf("Internal loopback!\n");
    }
    else if (diagMsgQ.loopback_mode == 1)
    {
        printf("External loopback!\n");
    }
    else if (diagMsgQ.loopback_mode == 2)
    {
        printf("External loopback!\n");
    }
    else
    {
        printf("Remote loopback!\n");
    }

    printf("phy_init_fail 0x%04x ", diagMsgQ.phy_init_fail);
    if (diagMsgQ.phy_init_fail == 0)
    {
        printf("No PHY initialization error detected!\n");
    }
    else
    {
        printf("PHY initialization error detected!!\n");
    }
    printf("wakeup 0x%04x ", diagMsgQ.wakeup);
    if (diagMsgQ.wakeup == 0)
    {
        printf("No local or remote wake-up detected!\n");
    }
    else
    {
        printf("Local or remote wake-up detected!\n");
    }

    printf("link_status_fail 0x%04x ", diagMsgQ.link_status_fail);
    if (diagMsgQ.link_status_fail == 0)
    {
        printf("Link status not changed!\n");
    }
    else
    {
        printf("Link status bit LINK_UP changed from 'link OK' to 'link fail' !\n");
    }

    printf("link_status_up 0x%04x ", diagMsgQ.link_status_up);
    if (diagMsgQ.link_status_up == 0)
    {
        printf("Link status not changed!\n");
    }
    else
    {
        printf("Link status bit LINK_UP changed from 'link fail' to 'link OK' !\n");
    }

    printf("link_up 0x%04x ", diagMsgQ.link_up);
    if (diagMsgQ.link_up == 0)
    {
        printf("Link failure!\n");
    }
    else
    {
        printf("Link OK!\n");
    }

    printf("tx_mode 0x%04x ", diagMsgQ.tx_mode);
    if (diagMsgQ.tx_mode == 0)
    {
        printf("Transmitter disabled!\n");
    }
    else if (diagMsgQ.tx_mode == 1)
    {
        printf("Transmitter in SEND_N mode!\n");
    }
    else if (diagMsgQ.tx_mode == 2)
    {
        printf("Transmitter in SEND_I mode!\n");
    }
    else
    {
        printf("Transmitter in SEND_Z mode!\n");
    }

    printf("loc_rcvr_status 0x%04x ", diagMsgQ.loc_rcvr_status);
    if (diagMsgQ.loc_rcvr_status == 0)
    {
        printf("Local receiver not OK!\n");
    }
    else
    {
        printf("Local receiver OK!\n");
    }

    printf("rem_rcvr_status 0x%04x ", diagMsgQ.rem_rcvr_status);
    if (diagMsgQ.rem_rcvr_status == 0)
    {
        printf("Remote receiver not OK!\n");
    }
    else
    {
        printf("Remote receiver OK!\n");
    }

    printf("phy_state 0x%04x ", diagMsgQ.phy_state);
    if (diagMsgQ.phy_state == 0)
    {
        printf("PHY Idle!\n");
    }
    else if (diagMsgQ.phy_state == 1)
    {
        printf("PHY Initializing!\n");
    }
    else if (diagMsgQ.phy_state == 2)
    {
        printf("PHY Configured!\n");
    }
    else if (diagMsgQ.phy_state == 3)
    {
        printf("PHY Offline!\n");
    }
    else if (diagMsgQ.phy_state == 4)
    {
        printf("PHY Active!\n");
    }
    else if (diagMsgQ.phy_state == 5)
    {
        printf("PHY Isolate!\n");
    }
    else if (diagMsgQ.phy_state == 6)
    {
        printf("PHY Cable test!\n");
    }
    else
    {
        printf("PHY Test mode!\n");
    }

    printf("\n\n\n ROUTINE STATE: ");
    if(diagMsgQ.routine_status == 1)
    {
        printf("routine active!\n");
    }
    else if(diagMsgQ.routine_status == 2)
    {
        printf("routine finished!\n");
    }
    else if(diagMsgQ.routine_status == 3)
    {
        printf("routine aborted!\n");
    }
    else
    {
        printf("routine idle!\n");
    }

    printf("\n\n\n ROUTINE RESULTS: ");
    if(diagMsgQ.routine_result == 0)
    {
        printf("incorrect results!\n");
    }
    else if(diagMsgQ.routine_result == 2)
    {
        printf("no results available!\n");
    }
    else
    {
        printf("correct results!\n");
    }

    if (diagMsgQ.ping_result == 1)
    {
        printf("Last ping routine result: Ping success!\n");
    }
    else
    {
        printf("Last ping routine result: Ping failed!\n");
    }
}

