#ifndef AUTHRESULT_H
#define AUTHRESULT_H

#include "authresultstatus.h"
#include "jwttoken.h"

#include <QString>
#include <QMap>

class AuthResult
{

public:
    AuthResult(AuthResultStatus status, JwtToken *jwtToken);

    AuthResultStatus getStatus() const;
    void setStatus(AuthResultStatus newStatus);

    QString getErrorText();     // получить текст ошибки   
    JwtToken *getJwtToken() const;

private:
    AuthResultStatus status;    // статус авторизации
    JwtToken *jwtToken = nullptr;

    QMap<AuthResultStatus, QString> errorsText;     // тексты ошибок
};

#endif // AUTHRESULT_H
