#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define PAGE_CLIENT_AUTH 0
#define PAGE_CLIENT_REGISTRATION 1
#define PAGE_MEMBER_AUTH 2
#define PAGE_MEMBER_REGISTRATION 3

#define CONNECT_MOVE_PAGE_BUTTON(button, index) connect(button, &QPushButton::clicked, this, [&](){ ui->stackedWidget_auth->setCurrentIndex(index);  clearFocus();  });

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);  

    clearFocus();   // убирвем фокус на lineEdit

    // коннекты для переходов    
    CONNECT_MOVE_PAGE_BUTTON(ui->pushButton_client_auth_move_to_registation, PAGE_CLIENT_REGISTRATION); // регистрация для клиента
    CONNECT_MOVE_PAGE_BUTTON(ui->pushButton_client_auth_move_to_auth_for_members, PAGE_MEMBER_AUTH);    // авторизация для сотрудника
    CONNECT_MOVE_PAGE_BUTTON(ui->pushButton_client_registration_move_to_client_auth, PAGE_CLIENT_AUTH); // авторизация для клиента
    CONNECT_MOVE_PAGE_BUTTON(ui->pushButton_member_auth_move_to_auth_for_clients, PAGE_CLIENT_AUTH);    // авторизация для клиента
    CONNECT_MOVE_PAGE_BUTTON(ui->pushButton_member_auth_move_to_registration_for_members, PAGE_MEMBER_REGISTRATION);    // регистрация для сотрудника
    CONNECT_MOVE_PAGE_BUTTON(ui->pushButton_member_registration_move_to_auth_for_members, PAGE_MEMBER_AUTH);    // авторизация для сотрудника
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearFocus()
{
    ui->label_logo_img->setFocusPolicy(Qt::WheelFocus);
    ui->label_logo_img->setFocus(Qt::OtherFocusReason);
}

