#include "authservice.h"

#include <QRegularExpression>

AuthResult AuthService::authUser(SignInModel signInModel)
{
    return AuthResult(AuthResultStatus::NOT_AUTH);
}

RegisterResult AuthService::registerUser(SignUpModel signInModel)
{
    return RegisterResult(RegisterResultStatus::NOT_REGISTER);
}

// функция проверки корректности формы авторизации
AuthResultStatus AuthService::checkAuthForm(SignInModel signInModel)
{
    // проверка на длину логина
    if(signInModel.getLogin().length() < 6 || signInModel.getLogin().length() > 20)
    {
        return AuthResultStatus::INCORRECT_LOGIN;
    }

    // проверка на корректность логина
    if (!QRegularExpression("^[A-Za-z0-9]+$").match(signInModel.getLogin()).hasMatch())
    {
        return AuthResultStatus::INCORRECT_LOGIN;
    }

    // проверка на длину пароля
    if(signInModel.getPassword().length() < 6 || signInModel.getPassword().length() > 20)
    {
        return AuthResultStatus::INCORRECT_PASSWORD;
    }

    return AuthResultStatus::NOT_AUTH;
}
