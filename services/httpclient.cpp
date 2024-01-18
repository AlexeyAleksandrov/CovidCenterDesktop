#include "httpclient.h"

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

HttpClient::HttpClient(QObject *parent)
    : QObject{parent}
{

}

QString HttpClient::sendPostRequest(QUrl url, QJsonObject json, QString token, QString &errorString)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;

    errorString = "";   // пустая строка, ошибок нет

    // Устанавливаем URL для запроса
    request.setUrl(url);

    // Устанавливаем заголовок Authorization
    QString authorizationHeader = "Bearer " + token;
    request.setRawHeader("Authorization", authorizationHeader.toUtf8());

    // Устанавливаем заголовок Content-Type
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Создаем JSON объект для передачи в теле запроса
    QByteArray postData = QJsonDocument(json).toJson();

    // Выполняем POST запрос
    QNetworkReply *reply = manager.post(request, postData);

    // Ожидаем, пока запрос завершится
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    // Читаем ответ
    QByteArray response = reply->readAll();

    // Обрабатываем ответ
    if (reply->error() != QNetworkReply::NoError)
    {
        errorString = reply->errorString();
    }

    // Освобождаем ресурсы
    reply->deleteLater();

    return QString::fromUtf8(response);
}

QString HttpClient::sendPutRequest(QUrl url, QJsonObject json, QString token, QString &errorString)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;

    errorString = "";   // пустая строка, ошибок нет

    // Устанавливаем URL для запроса
    request.setUrl(url);

    // Устанавливаем заголовок Authorization
    QString authorizationHeader = "Bearer " + token;
    request.setRawHeader("Authorization", authorizationHeader.toUtf8());

    // Устанавливаем заголовок Content-Type
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Создаем JSON объект для передачи в теле запроса
    QByteArray putData = QJsonDocument(json).toJson();

    // Выполняем POST запрос
    QNetworkReply *reply = manager.put(request, putData);

    // Ожидаем, пока запрос завершится
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    // Читаем ответ
    QByteArray response = reply->readAll();

    // Обрабатываем ответ
    if (reply->error() != QNetworkReply::NoError)
    {
        errorString = reply->errorString();
    }

    // Освобождаем ресурсы
    reply->deleteLater();

    return QString::fromUtf8(response);
}

QString HttpClient::sendDeleteRequest(QUrl url, QString token, QString &errorString)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;

    errorString = "";   // пустая строка, ошибок нет

    // Устанавливаем URL для запроса
    request.setUrl(url);

    // Устанавливаем заголовок Authorization
    QString authorizationHeader = "Bearer " + token;
    request.setRawHeader("Authorization", authorizationHeader.toUtf8());

    // Устанавливаем заголовок Content-Type
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Выполняем POST запрос
    QNetworkReply *reply = manager.deleteResource(request);

    // Ожидаем, пока запрос завершится
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    // Читаем ответ
    QByteArray response = reply->readAll();

    // Обрабатываем ответ
    if (reply->error() != QNetworkReply::NoError)
    {
        errorString = reply->errorString();
    }

    // Освобождаем ресурсы
    reply->deleteLater();

    return QString::fromUtf8(response);
}

QString HttpClient::sendGetHttpRequest(QUrl url, QString token, QString &errorString)
{
    QNetworkAccessManager manager;
    QNetworkRequest request;

    // Устанавливаем URL для запроса
    request.setUrl(url);

    // Устанавливаем заголовок Authorization
    QString authorizationHeader = "Bearer " + token;
    request.setRawHeader("Authorization", authorizationHeader.toUtf8());

    // Выполняем GET запрос
    QNetworkReply *reply = manager.get(request);

    // Ожидаем, пока запрос завершится
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    // Читаем ответ
    QByteArray response = reply->readAll();

    // Обрабатываем ответ
    if (reply->error() != QNetworkReply::NoError)
    {
        if(reply->error() == QNetworkReply::ContentAccessDenied)
        {
            errorString = "Доступ запрещён!";
        }
        else
        {
            errorString = reply->errorString();
        }

    }

    // Освобождаем ресурсы
    reply->deleteLater();

    return QString::fromUtf8(response);
}
