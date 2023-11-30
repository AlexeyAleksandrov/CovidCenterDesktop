#include "registerresult.h"

RegisterResult::RegisterResult(RegisterResultStatus status)
{
    this->status = status;

    errorsText.insert(RegisterResultStatus::NOT_REGISTER,           "Регистрация не была произведена");
    errorsText.insert(RegisterResultStatus::FORM_VALID_SUCCESSFULL, "Форма регистрации корректна");
    errorsText.insert(RegisterResultStatus::SUCCESSFULL,            "Регистрация успешно произведена");
    errorsText.insert(RegisterResultStatus::FAILED,                 "Ошибка регистрации");
    errorsText.insert(RegisterResultStatus::INCORRECT_LOGIN,        "Некорректный логин пользователя");
    errorsText.insert(RegisterResultStatus::INCORRECT_PASSWORD,     "Некорректный пароль");
    errorsText.insert(RegisterResultStatus::PASSWORD_NOT_CONFIRM,   "Пароли не совпадают");
    errorsText.insert(RegisterResultStatus::LOGIN_EXISTED,          "Пользователь с таким логином уже существует");
}

RegisterResultStatus RegisterResult::getStatus() const
{
    return status;
}

void RegisterResult::setStatus(RegisterResultStatus newStatus)
{
    status = newStatus;
}

QString RegisterResult::getErrorText()
{
    return errorsText[status];
}
