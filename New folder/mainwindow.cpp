#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    process = new QProcess(this);
    process->start(QIODevice::ReadWrite);

    ui->setupUi(this);

    getMsgQ_button = new QPushButton("Get MsgQ", this);
    getMsgQ_button->setGeometry(QRect(QPoint(100, 200),
    QSize(100, 25)));

    getShMem_button = new QPushButton("Get ShMem", this);
    getShMem_button->setGeometry(QRect(QPoint(100, 250),
    QSize(100, 25)));

    disconnect = new QPushButton("Exit", this);
    disconnect->setGeometry(QRect(QPoint(100, 350),
    QSize(100, 25)));

    init_button = new QPushButton("Start Client", this);
    init_button->setGeometry(QRect(QPoint(100, 100),
    QSize(100, 25)));

    dl_button = new QPushButton("Download file", this);
    dl_button->setGeometry(QRect(QPoint(100, 150),
    QSize(100, 25)));

    sendRoutine_button = new QPushButton("Send Routine", this);
    sendRoutine_button->setGeometry(QRect(QPoint(100, 300),
    QSize(100, 25)));

    routineText = new QLineEdit(tr(""), this);
    routineText->setGeometry(QRect(QPoint(200,300), QSize(25,25)));

    showText = new QTextEdit(tr(""), this);
    showText->setGeometry(QRect(QPoint(350,100), QSize(500,500)));

    infoBar = new QLabel(this);
    infoBar->setGeometry(QRect(QPoint(100,400), QSize(200,100)));

    QString info = "Routines:\n0 - Normal operation test\n1 to 5 - Test Modes\n6 - Ping routine\n(Click Get msgQ to read result)\n7 - Read Link Fail Count\n(Click get shMem to read result)";

    infoBar->setText(info);

    freopen("output_file.txt", "w", stdout);
    // Connect button signal to appropriate slot
    connect(this->init_button, SIGNAL (released()), this, SLOT (initComm()));
    connect(this->getMsgQ_button, SIGNAL (released()), this, SLOT (handeMsgQ_button()));
    connect(this->getShMem_button, SIGNAL (released()), this, SLOT (handeShMem_button()));
    connect(this->sendRoutine_button, SIGNAL (released()), this, SLOT (handleRoutineClick()));
    connect(this->dl_button, SIGNAL (released()), this, SLOT (handleDownloadClick()));
    connect(this->disconnect, SIGNAL (released()), this, SLOT (handleDisconnectClick()));
    connect(this, SIGNAL (downloadFile()), this, SLOT (getFile()));
    connect(this, SIGNAL (getMsgQStatus()), this, SLOT (getMsgQ()));
    connect(this, SIGNAL (getShMemStatus()), this, SLOT (getShMem()));
    connect(this, SIGNAL (disconnectClicked()), this, SLOT (terminateProgram()));
    connect(this, SIGNAL (insertRoutineNumber()), this, SLOT (insertRoutine()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handeMsgQ_button()
{
    emit getMsgQStatus();
}

void MainWindow::handleDownloadClick()
{
    emit downloadFile();
}

void MainWindow::handeShMem_button()
{
    emit getShMemStatus();
}

void MainWindow::handleRoutineClick()
{
    emit insertRoutineNumber();
}

void MainWindow::handleDisconnectClick()
{
    emit disconnectClicked();
}

void MainWindow::insertRoutine()
{
    int m = routineText->text().toInt();

    if (m <= 7 && m >= 0)
    {

        mod3.startModule(2);
        mod3.sendRoutineNum(m);
    }
    fflush(stdout);
    readfile();
    clearFile();

}

void MainWindow::getMsgQ()
{
    mod3.startModule(3);
    fflush(stdout);
    readfile();
    clearFile();
}

void MainWindow::getFile()
{
    mod3.startModule(1);
    fflush(stdout);
    readfile();
    clearFile();
}

void MainWindow::getShMem()
{
    mod3.startModule(4);
    fflush(stdout);
    readfile();
    clearFile();
}

void MainWindow::initComm()
{
    init_button->setText("Client started");
    init_button->setEnabled(false);
    mod3.initCommunication();
    fflush(stdout);
    readfile();
    clearFile();
}

void MainWindow::terminateProgram()
{
    mod3.startModule(0);
    QApplication::quit();
    fflush(stdout);
    readfile();
    clearFile();
}

void MainWindow::readfile(){
    QString filename="output_file.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "No file! "<<filename;
    }else{
        qDebug() << filename<<" File exists...";
    }
    QString line;
    showText->clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        while (!stream.atEnd()){
            line = stream.readLine();
            showText->setText(showText->toPlainText()+line+"\n");
        }
    }
    file.close();
}

void MainWindow::clearFile()
{
    QString filename="output_file.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "No file! "<<filename;
    }else{
        qDebug() << filename<<" File exists...";
    }
    if (file.open(QIODevice::WriteOnly | QFile::Truncate)){
        qDebug() << "Cleared";
    }

    file.close();
}
