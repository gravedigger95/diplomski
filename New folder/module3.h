//static const uint8_t zfasAddr[16] = {0xfd, 0x53, 0x7c, 0xb8, 0x03, 0x83, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4f};

#include <QMainWindow>
#include <QLineEdit>
#include <QFile>
#include <QDebug>
#include <QTextEdit>


#pragma comment(lib, "ws2_32.lib") //Winsock Library

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define SLEEP_TIME 15
#define SWU_BR_SERVERPORT  29170
#define SWU_BR_CLIENTPORT  29171
//#define SWUP_ZFAS_IP_ADDRESS "fd53:7cb8:383:3::4f"	//zFAS ploca
//#define SWUP_MIB_ZR_IP_ADDRESS "fd53:7cb8:383:3::73"	//PC
#define BUFLEN 512
#define zFAS_IPv4 "192.168.122.60"
//#define PC_IPv4 "192.168.122.40"
//#define PC2_IPv4 "192.168.122.88"

#define ROUTINE_NUM_SENT 1
#define ROUTINE_NUM_NOT_SENT 0

#define DOWNLOAD_IN_PROGRESS 1
#define NOT_DOWNLOADING 0

#define TERMINATE_PROGRAM 0
#define DOWNLOAD_FILE 1
#define GET_MSGQ 3
#define GET_SHMEM 4

typedef struct errorStruct
{
    char	timestamp[26];
    uint8_t id;
    char	description[50];
    uint8_t padding;
}s_ERRORS;

/* Diagnostic data struct */
typedef struct diagnosticDataMsgQ
{
    uint16_t link_status; //basic status reg bit 2 0x1
    uint16_t link_control; //ext control reg bit 15 0x11
    uint16_t power_mode; //ext control reg bit [14:11] 0x11
    uint16_t loopback_mode; //ext control reg bit [4:3] 0x11
    uint16_t phy_init_fail; //interrupt status reg bit 11 0x15
    uint16_t wakeup; //interrupt status reg bit 14 0x15
    uint16_t link_status_fail; //interrupt status reg bit 10 0x15
    uint16_t link_status_up; //interrupt status reg bit 9 0x15
    uint16_t link_up; //comm status reg bit 15 0x17
    uint16_t tx_mode; //comm status reg bit [14:13] 0x17
    uint16_t loc_rcvr_status; //comm status reg bit 12 0x17
    uint16_t rem_rcvr_status; //comm status reg bit 11 0x17
    uint16_t signal_quality;
    uint16_t phy_id_reg1; //phy id reg 1 bit [15:0] 0x2
    uint16_t phy_state;
    uint16_t ping_result;
    uint16_t routine_status;
    uint16_t routine_result;

    s_ERRORS errors_array[4];
} s_DIAG_DATA;

typedef struct diagnosticDataShM
{
    uint16_t jabber_detect; //basic status reg bit 1 0x1
    uint16_t phy_id_reg1; //phy id reg 1 bit [15:0] 0x2
    uint16_t phy_id_reg2; //phy id reg 2 bit [15:10] 0x3
    uint16_t type_no; //phy id reg 2 bit [9:4] 0x3
    uint16_t revision_no; //phy id reg 2 bit [3:0] 0x3
    uint16_t phy_id_reg3; //phy id reg 3 bit [7:0] 0x10
    uint16_t int_status; //gen status reg bit 15 0x18
    uint16_t loc_rcvr_cnt;
    uint16_t rem_rcvr_cnt;
    uint16_t link_fail_cnt;
} s_DIAG_SHM_DATA;


namespace Ui {
class Module3;
}

class Module3 : public QMainWindow
{
    Q_OBJECT

public:
    void *threadfunc(void * arg);

signals:
    void insertNumber();
    void printReceiving();

public slots:
    int startModule(int insertedNumber);
    void receiveFile();
    void initCommunication(void);
    void sendRoutineNum(int rNum);
    void printStates(void);

private:
};

