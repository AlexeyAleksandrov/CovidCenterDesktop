#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setFocusPolicy(Qt::WheelFocus);
    ui->label->setFocus(Qt::OtherFocusReason);
}

MainWindow::~MainWindow()
{
    delete ui;
}

