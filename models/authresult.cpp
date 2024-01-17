#include "authresult.h"

AuthResult::AuthResult(AuthResultStatus status, JwtToken *jwtToken)
{
    this->status = status;

    errorsText.insert(AuthResultStatus::NOT_AUTH,               "Авторизация не была произведена");
    errorsText.insert(AuthResultStatus::FORM_VALID_SUCCESSFULL, "Форма авторизации корректна");
    errorsText.insert(AuthResultStatus::SUCCESSFULL,            "Авторизация успешна");
    errorsText.insert(AuthResultStatus::FAILED,                 "Авторизация не пройдена");
    errorsText.insert(AuthResultStatus::INCORRECT_LOGIN,        "Некорректный логин");
    errorsText.insert(AuthResultStatus::INCORRECT_PASSWORD,     "Некорректный пароль");
    errorsText.insert(AuthResultStatus::BANNED,                 "Пользователь забанен");

    this->jwtToken = jwtToken;
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

JwtToken *AuthResult::getJwtToken() const
{
    return jwtToken;
}




