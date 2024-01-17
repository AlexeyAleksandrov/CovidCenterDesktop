#include "httpclient.h"
#include "membersauthservice.h"

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>

// авторизация сотрудника
AuthResult MembersAuthService::authUser(SignInModel signInModel)
{
    // проверка на форматирование логина и пароля
    AuthResultStatus resultStatus = AuthService::checkAuthForm(signInModel);
    if(resultStatus != AuthResultStatus::FORM_VALID_SUCCESSFULL)
    {
        return AuthResult(resultStatus, nullptr);
    }

    // авторизация
    QUrl authUrl(HOST_URL + "/auth/signin");
    QJsonObject json;
    json["username"] = signInModel.getLogin();
    json["password"] = signInModel.getPassword();

    QString errorText;
    QString token = HttpClient::sendPostRequest(authUrl, json, "", errorText);

    if(!errorText.isEmpty())    // если есть ошибка
    {
        return AuthResult(AuthResultStatus::FAILED, nullptr);
    }

    // формируем результат авторизации
    JwtToken *jwt = new JwtToken(token);
    AuthResult authResult(AuthResultStatus::SUCCESSFULL, jwt);

    return authResult;
}

RegisterResult MembersAuthService::registerUser(SignUpModel signUpModel)
{
    // проверка корректноти формы регистрации
    RegisterResultStatus registerStatus = AuthService::checkRegisterForm(signUpModel);
    if(registerStatus != RegisterResultStatus::FORM_VALID_SUCCESSFULL)
    {
        return RegisterResult(registerStatus);
    }

    // регистрация
    QUrl authUrl(HOST_URL + "/auth/signup");
    QJsonObject json;
    json["fullName"] = signUpModel.getLogin();  //  TODO: Сделать ввод ФИО
    json["username"] = signUpModel.getLogin();
    json["password"] = signUpModel.getPassword();

    QString errorText;
    HttpClient::sendPostRequest(authUrl, json, "", errorText);

    if(!errorText.isEmpty())    // если есть ошибка
    {
        return RegisterResult(RegisterResultStatus::FAILED);
    }

    // возвращаем результат регистрации
    return RegisterResult(RegisterResultStatus::SUCCESSFULL);
}
