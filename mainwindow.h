#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "timerthread.h"

#include <QMainWindow>
#include <QTimer>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_client_auth_sign_in_clicked();

    void on_pushButton_member_auth_sign_in_clicked();

    void on_pushButton_checkLogin_clicked();

    void on_pushButton_logout_clicked();

    void on_pushButton_member_registration_sign_up_clicked();

private slots:
    void onTimer();
    void closeEvent(QCloseEvent *closeEvent);

    void on_pushButton_updateMemberOrdersList_clicked();

private:
    Ui::MainWindow *ui;

    void clearFocus();

//    QTimer timer;   // таймер для автоматического выхода
    TimerThread timerThread;
    int timerTime = -1; // текущее время таймера

    QString authToken;  // JWT токен
};
#endif // MAINWINDOW_H
