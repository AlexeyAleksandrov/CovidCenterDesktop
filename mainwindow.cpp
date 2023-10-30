#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define PAGE_CLIENT_AUTH 0
#define PAGE_CLIENT_REGISTRATION 1
#define PAGE_MEMBER_AUTH 3
#define PAGE_MEMBER_REGISTRATION 4


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // убирвем фокус на lineEdit при старте
    ui->label_logo_img->setFocusPolicy(Qt::WheelFocus);
    ui->label_logo_img->setFocus(Qt::OtherFocusReason);

    // коннекты для переходов
    connect(ui->pushButton_client_auth_move_to_registation, &QPushButton::clicked, this, [&](){
        ui->stackedWidget_auth->setCurrentIndex(PAGE_CLIENT_REGISTRATION);
    });     // регистрация для клиента
}

MainWindow::~MainWindow()
{
    delete ui;
}

