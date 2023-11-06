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
    if(resultStatus != AuthResultStatus::NOT_AUTH)
    {
        return AuthResult(resultStatus);
    }

    // авторизация
    QUrl authUrl("http://127.0.0.1:8080/auth/signin");
    QJsonObject json;
    json["username"] = signInModel.getLogin();
    json["password"] = signInModel.getPassword();

    QString errorText;
    QString token = HttpClient::sendPostRequest(authUrl, json, "", errorText);

    if(!errorText.isEmpty())    // если есть ошибка
    {
        return AuthResult(AuthResultStatus::FAILED);
    }

    // формируем результат авторизации
    AuthResult authResult(AuthResultStatus::SUCCESSFULL);
    authResult.setToken(token);

    return authResult;
}

RegisterResult MembersAuthService::registerUser(SignUpModel signInModel)
{

}
