#ifndef AUTHRESULT_H
#define AUTHRESULT_H

#include "authresultstatus.h"

#include <QString>
#include <QMap>

class AuthResult
{

public:
    AuthResult(AuthResultStatus status);

    AuthResultStatus getStatus() const;
    void setStatus(AuthResultStatus newStatus);

    QString getErrorText();     // получить текст ошибки

    const QString &getToken() const;
    void setToken(const QString &newToken);

private:
    AuthResultStatus status;    // статус авторизации
    QString token;

    QMap<AuthResultStatus, QString> errorsText;     // тексты ошибок
};

#endif // AUTHRESULT_H
