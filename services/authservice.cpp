#include "authservice.h"

#include <QRegularExpression>

// виртуальный метод авторизации пользователя
AuthResult AuthService::authUser(SignInModel signInModel)
{
    Q_UNUSED(signInModel);
    return AuthResult(AuthResultStatus::NOT_AUTH);
}

// виртуальный метод регистрации пользователя
RegisterResult AuthService::registerUser(SignUpModel signUpModel)
{
    Q_UNUSED(signUpModel);
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

    return AuthResultStatus::FORM_VALID_SUCCESSFULL;
}

// функция проверки корректности формы регистрации
RegisterResultStatus AuthService::checkRegisterForm(SignUpModel signUpModel)
{
    // проверка на длину логина
    if(signUpModel.getLogin().length() < 6 || signUpModel.getLogin().length() > 20)
    {
        return RegisterResultStatus::INCORRECT_LOGIN;
    }

    // проверка на корректность логина
    if (!QRegularExpression("^[A-Za-z0-9]+$").match(signUpModel.getLogin()).hasMatch())
    {
        return RegisterResultStatus::INCORRECT_LOGIN;
    }

    // проверка на длину пароля
    if(signUpModel.getPassword().length() < 6 || signUpModel.getPassword().length() > 20)
    {
        return RegisterResultStatus::INCORRECT_PASSWORD;
    }

    // проверка на одинаковость паролей
    if(signUpModel.getPassword().length() < 6 || signUpModel.getPassword().length() > 20)
    {
        return RegisterResultStatus::PASSWORD_NOT_CONFIRM;
    }

    return RegisterResultStatus::FORM_VALID_SUCCESSFULL;
}
