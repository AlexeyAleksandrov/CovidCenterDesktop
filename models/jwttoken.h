#ifndef JWTTOKEN_H
#define JWTTOKEN_H

#include <QDateTime>
#include <QString>



class JwtToken
{
public:
    JwtToken(QString token);    // принимает на вход токен

    const QString &getToken() const;
    const QString &getSubject() const;
    const QDateTime &getIssuedAt() const;
    const QDateTime &getExpiration() const;
    long getLifeTime() const;

private:
    QString token;  // токен, с которым программа работает

    QString subject;    // логин
    QDateTime issuedAt;     // начало действия токена
    QDateTime expiration;   // окончание действия токена
    long lifeTime;      // время жизни токена
};

#endif // JWTTOKEN_H
