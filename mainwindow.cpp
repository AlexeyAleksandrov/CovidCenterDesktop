#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <models/signinmodel.h>

#include <services/httpclient.h>
#include <services/membersauthservice.h>

#include <QJsonObject>
#include <QMessageBox>
#include <QUrl>

#define ALLOW_WORK_TIME 10   // в секундах

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


    timerThread.start();
    QObject::connect(&timerThread, &TimerThread::timeout, this, &MainWindow::onTimer);

    // настраиваем стартовые окна
    ui->stackedWidget_main->setCurrentIndex(PAGE_AUTH);
    ui->stackedWidget_auth->setCurrentIndex(PAGE_CLIENT_AUTH);
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
    SignInModel signInModel(ui->lineEdit_member_auth_login->text(),
                            ui->lineEdit_member_auth_password->text());

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
    authToken = authResult.getToken();  // сохраняем токен
    ui->lineEdit_jwtToken->setText(authToken);  // выводим токен
    ui->stackedWidget_main->setCurrentIndex(PAGE_MEMBER);   // переключаемся на страницу пользователя

    ui->label_user_name->setText(signInModel.getLogin());
    ui->label_time_left->setText("");
    ui->pushButton_logout->show();

    // зажаем время работы
    timerTime = ALLOW_WORK_TIME*1000;    // 80 секунд
    onTimer();      // обновляем время

    QMessageBox::information(this, "Авторизация", "Вы успешно авторизовались!");
}

// кнопка регистрации сотрудника
void MainWindow::on_pushButton_member_registration_sign_up_clicked()
{
    // форма регистрации
    SignUpModel signUpModel(ui->lineEdit_member_registration_login->text(),
                            ui->lineEdit_member_registration_password->text(),
                            ui->lineEdit_member_registration_password_confirm->text());

    // проверка формы
    MembersAuthService memberAuthService;
    memberAuthService.registerUser(signUpModel);

}

// обновление таймера
void MainWindow::onTimer()
{
    timerTime -= 1000;

    if (timerTime < 0)
    {
        return;
    }

    int seconds = timerTime / 1000;
    int minutes = seconds / 60;
    seconds = seconds % 60;

    QString timeLeftText = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    ui->label_time_left->setText(timeLeftText);

    if(timerTime == 0)
    {
        on_pushButton_logout_clicked();
        QMessageBox::information(this, "Время вышло", "Невозможно продолжить работу! Требуется кварцевание помещения!");
    }
    else if(minutes == 1 && seconds == 0)
    {
        QMessageBox::information(this, "Время", "Через 1 минуту потребуется кварцевание помещения! Завершите работу!");
    }
}

void MainWindow::closeEvent(QCloseEvent *closeEvent)
{
    timerThread.quit(); // отправляем сигнал завершения потока
    timerThread.wait(); // ожидаем завершения потока

    closeEvent->accept();
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

// кнопка выхода для сотрудника
void MainWindow::on_pushButton_logout_clicked()
{
    ui->stackedWidget_main->setCurrentIndex(PAGE_AUTH);   // переключаемся на страницу пользователя
    ui->label_user_name->setText("");
    ui->label_time_left->setText("");
    ui->pushButton_logout->hide();
}


// обновление списка заказов
void MainWindow::on_pushButton_updateMemberOrdersList_clicked()
{
    QUrl url("http://localhost:8080/api/v1/orders/");     // адрес

    QString errorText;
    QString result = HttpClient::sentGetHttpRequest(url, authToken, errorText);     // выполняем get-запрос

    if(!errorText.isEmpty())    // если есть ошибка
    {
        QMessageBox::warning(this, "Ошибка", errorText);
        return;
    }

    QMessageBox::information(this, "Логин", "Список заказов: " + result);
}

