#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <models/order.h>
#include <models/signinmodel.h>

#include <services/httpclient.h>
#include <services/membersauthservice.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QUrl>

#define ALLOW_WORK_TIME 10*60   // в секундах // 10 минут

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

    ui->tableWidget_memberOrdersList->setRowCount(0);

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
    jwtToken = authResult.getJwtToken();  // сохраняем токен
    ui->stackedWidget_main->setCurrentIndex(PAGE_MEMBER);   // переключаемся на страницу пользователя

    ui->label_user_name->setText(signInModel.getLogin());
    ui->label_time_left->setText("");
    ui->pushButton_logout->show();

    // зажаем время работы
    timerTime = ALLOW_WORK_TIME*1000;    // 80 секунд
    onTimer();      // обновляем время

//    on_pushButton_updateMemberOrdersList_clicked(); // обнавляем список заказов
}

void MainWindow::parseJwtToken(const QString& token) {
    QStringList parts = token.split('.');
    QByteArray payloadData = QByteArray::fromBase64(parts[1].toUtf8());
    QJsonDocument payloadDoc = QJsonDocument::fromJson(payloadData);
    QJsonObject payload = payloadDoc.object();

    qDebug() << "Subject: " << payload["sub"].toString();
    qDebug() << "Issued At: " << QDateTime::fromSecsSinceEpoch(payload["iat"].toInt()).toString("dd.MM.yyyy hh:mm");
    qDebug() << "Expiration: " << QDateTime::fromSecsSinceEpoch(payload["exp"].toInt()).toLocalTime().toString("dd.MM.yyyy hh:mm");
}

// кнопка регистрации сотрудника
void MainWindow::on_pushButton_member_registration_sign_up_clicked()
{
    // ФИО
    QString firstName = ui->lineEdit_member_registration_firstname->text().trimmed();
    QString lastName = ui->lineEdit_member_registration_lastname->text().trimmed();
    QString patronymic = ui->lineEdit_member_registration_patronymic->text().trimmed();

    if(firstName.size() < 2 || lastName.size() < 2 || (patronymic.size() < 2 && patronymic.size() > 0))
    {
        QMessageBox::warning(this, "Ошибка", "Введите корректные данные фамилии, имени и отчетсва!");
        return;
    }

    // фамилия + имя + отчество
    QString fullName = QString("%1 %2 %3").arg(lastName).arg(firstName).arg(patronymic).trimmed();   // формируем ФИО + очищаем пробелы по краям

    // форма регистрации
    SignUpModel signUpModel(ui->lineEdit_member_registration_login->text(),
                            ui->lineEdit_member_registration_password->text(),
                            ui->lineEdit_member_registration_password_confirm->text(),
                            fullName);

    // проверка формы
    MembersAuthService memberAuthService;
    RegisterResult registerResult = memberAuthService.registerUser(signUpModel);

    if(registerResult.getStatus() != RegisterResultStatus::SUCCESSFULL)
    {
        QMessageBox::warning(this, "Ошибка регистрации", registerResult.getErrorText());    // вывод информации об ошибке
        return;
    }

    QMessageBox::information(this, "Регистрация", "Вы успешно зарегистрировались!");
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

// обработчик закрытия программы
void MainWindow::closeEvent(QCloseEvent *closeEvent)
{
    timerThread.quit(); // отправляем сигнал завершения потока
    timerThread.wait(); // ожидаем завершения потока

    closeEvent->accept();
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
    QString result = HttpClient::sentGetHttpRequest(url, jwtToken->getToken(), errorText);     // выполняем get-запрос

    if(!errorText.isEmpty())    // если есть ошибка
    {
        QMessageBox::warning(this, "Ошибка", errorText);
        return;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(result.toUtf8()).array();

    QList<Order> ordersList;

    for (const QJsonValue &value : qAsConst(jsonArray))
    {
        QJsonObject obj = value.toObject();
        Order order;
        order.setUserId(obj["userId"].toInt());
        order.setUserFullName(obj["userFullName"].toString());
        order.setOrderId(obj["orderId"].toInt());
        order.setOrderStatus(Order::OrderStatus(obj["orderStatus"].toInt()));

        QJsonArray servicesArray = obj["services"].toArray();
        QList<long> services;
        for (const QJsonValue &serv : qAsConst(servicesArray))
        {
            services.append(serv.toInt());
        }
        order.setServices(services);

        ordersList.append(order);
    }

    ui->tableWidget_memberOrdersList->setRowCount(ordersList.size());

    for (int i=0; i<ordersList.size(); i++) {

        QTableWidgetItem *orderIdItem = ui->tableWidget_memberOrdersList->item(i, 0);
        QTableWidgetItem *userNameItem = ui->tableWidget_memberOrdersList->item(i, 1);
        QTableWidgetItem *orderStatusItem = ui->tableWidget_memberOrdersList->item(i, 2);

        if(orderIdItem == nullptr)
        {
            orderIdItem = new QTableWidgetItem();
            ui->tableWidget_memberOrdersList->setItem(i, 0, orderIdItem);
        }
        if(userNameItem == nullptr)
        {
            userNameItem = new QTableWidgetItem();
            ui->tableWidget_memberOrdersList->setItem(i, 1, userNameItem);
        }
        if(orderStatusItem == nullptr)
        {
            orderStatusItem = new QTableWidgetItem();
            ui->tableWidget_memberOrdersList->setItem(i, 2, orderStatusItem);
        }

        Order order = ordersList.at(i);

        orderIdItem->setText(QString::number(order.getOrderId()));
        userNameItem->setText(order.getUserFullName());
        orderStatusItem->setText(Order::getNameOfOrderStatus(order.getOrderStatus()));

//        qDebug() << "User ID: " << order.getUserId();
//        qDebug() << "Order ID: " << order.getOrderId();
//        qDebug() << "Services: " << order.getServices();
//        qDebug() << "Order Status: " << (int)order.getOrderStatus();
    }

//    QMessageBox::information(this, "Список заказов", "Список заказов: " + result);
}

