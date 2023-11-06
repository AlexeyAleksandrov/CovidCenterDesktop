#include "authresult.h"

AuthResult::AuthResult(AuthResultStatus status)
{
    this->status = status;

    errorsText.insert(AuthResultStatus::NOT_AUTH, "Авторизация не была произведена");
    errorsText.insert(AuthResultStatus::SUCCESSFULL, "Авторизация успешна");
    errorsText.insert(AuthResultStatus::FAILED, "Авторизация не пройдена");
    errorsText.insert(AuthResultStatus::INCORRECT_LOGIN, "Некорректный логин");
    errorsText.insert(AuthResultStatus::INCORRECT_PASSWORD, "Некорректный пароль");
    errorsText.insert(AuthResultStatus::BANNED, "Пользователь забанен");
}

AuthResultStatus AuthResult::getStatus() const
{
    return status;
}

void AuthResult::setStatus(AuthResultStatus newStatus)
{
    status = newStatus;
}

// полуучить текст ошибки
QString AuthResult::getErrorText()
{
    return errorsText[status];
}

const QString &AuthResult::getToken() const
{
    return token;
}

void AuthResult::setToken(const QString &newToken)
{
    token = newToken;
}
