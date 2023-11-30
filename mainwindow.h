#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;

    void clearFocus();
};
#endif // MAINWINDOW_H
