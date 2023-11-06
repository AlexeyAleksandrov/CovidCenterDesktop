#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QNetworkReply>
#include <QObject>

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
