#include "jwttoken.h"
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>

JwtToken::JwtToken(QString token)
{
    this->token = token;    // сохрянем токен

    QStringList parts = token.split('.');
    QByteArray payloadData = QByteArray::fromBase64(parts[1].toUtf8());
    QJsonDocument payloadDoc = QJsonDocument::fromJson(payloadData);
    QJsonObject payload = payloadDoc.object();

    this->subject = payload["sub"].toString();      // логин
    this->issuedAt = QDateTime::fromSecsSinceEpoch(payload["iat"].toInt());     // время начала
    this->expiration = QDateTime::fromSecsSinceEpoch(payload["exp"].toInt());   // время окончания

    this->lifeTime = issuedAt.secsTo(expiration);   // время жизни токена
}

const QString &JwtToken::getToken() const
{
    return token;
}

const QString &JwtToken::getSubject() const
{
    return subject;
}

const QDateTime &JwtToken::getIssuedAt() const
{
    return issuedAt;
}

const QDateTime &JwtToken::getExpiration() const
{
    return expiration;
}

long JwtToken::getLifeTime() const
{
    return lifeTime;
}
