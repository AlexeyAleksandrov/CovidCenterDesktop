#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QNetworkReply>
#include <QObject>

#define HOST_URL QString("http://127.0.0.1:8080")    // адрес хоста

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QObject *parent = nullptr);

    static QString sendPostRequest(QUrl url, QJsonObject json, QString token, QString &errorString);
    static QString sentGetHttpRequest(QUrl url, QString token, QString &errorString);

signals:

};

#endif // HTTPCLIENT_H
