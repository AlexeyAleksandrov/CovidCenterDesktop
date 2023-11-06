#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <models/signinmodel.h>

#include <services/httpclient.h>
#include <services/membersauthservice.h>

#include <QJsonObject>
#include <QMessageBox>
#include <QUrl>

#define PAGE_AUTH 0
#define PAGE_MEMBER 1

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

    ui->label_user_name->setText("");
    ui->label_time_left->setText("");
    ui->pushButton_logout->hide();
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


// авторизация клиента
void MainWindow::on_pushButton_client_auth_sign_in_clicked()
{

}

// авторизация сотрудника
void MainWindow::on_pushButton_member_auth_sign_in_clicked()
{
    // модель авторизации
    SignInModel signInModel(ui->lineEdit_member_auth_login->text(), ui->lineEdit_member_auth_password->text());

    // сервис авторизации
    MembersAuthService memberAuthService;
    AuthResult authResult = memberAuthService.authUser(signInModel);    // пытаемся авторизовать пользователя

    // если авторизация не пройдена
    if(authResult.getStatus() != AuthResultStatus::SUCCESSFULL)
    {
        QMessageBox::warning(this, "Ошибка авторизации", authResult.getErrorText());    // вывод информации об ошибке
        return;
    }

    // если авторизация успешна
    ui->lineEdit_jwtToken->setText(authResult.getToken());  // выводим токен
    ui->stackedWidget_main->setCurrentIndex(PAGE_MEMBER);   // переключаемся на страницу пользователя

    ui->label_user_name->setText(signInModel.getLogin());
    ui->label_time_left->setText("");
    ui->pushButton_logout->show();

    QMessageBox::information(this, "Авторизация", "Вы успешно авторизовались!");
}

// кнопка проверки логина
void MainWindow::on_pushButton_checkLogin_clicked()
{
    QString token = ui->lineEdit_jwtToken->text();  // получаем токен
    QUrl url("http://localhost:8080/secured/user");     // адрес

    QString errorText;
    QString result = HttpClient::sentGetHttpRequest(url, token, errorText);     // выполняем get-запрос

    if(!errorText.isEmpty())    // если есть ошибка
    {
        QMessageBox::warning(this, "Ошибка", errorText);
        return;
    }

    QMessageBox::information(this, "Логин", "Ваш логин: " + result);
}

// кнопка выхода
void MainWindow::on_pushButton_logout_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(PAGE_AUTH);   // переключаемся на страницу пользователя
    ui->label_user_name->setText("");
    ui->label_time_left->setText("");
    ui->pushButton_logout->hide();
}

