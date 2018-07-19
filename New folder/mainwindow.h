#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QLabel>

extern "C" {
#include "module3.h"
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Module3 mod3;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void readfile();
    void clearFile();

signals:
    void getMsgQStatus();
    void downloadFile();
    void getShMemStatus();
    void insertRoutineNumber();
    void disconnectClicked();


private slots:
    void handeMsgQ_button();
    void handeShMem_button();
    void initComm();
    void handleRoutineClick();
    void handleDownloadClick();
    void insertRoutine();
    void handleDisconnectClick();
    void terminateProgram();
    void getMsgQ();
    void getFile();
    void getShMem();

private:
    Ui::MainWindow *ui;
    QPushButton *getMsgQ_button;
    QPushButton *dl_button;
    QPushButton *init_button;
    QPushButton *disconnect;
    QPushButton *sendRoutine_button;
    QPushButton *getShMem_button;
    QLineEdit *textUser;
    QLineEdit *routineText;
    QLabel *infoBar;
    QTextEdit *showText;
    QProcess *process;
};

#endif // MAINWINDOW_H
