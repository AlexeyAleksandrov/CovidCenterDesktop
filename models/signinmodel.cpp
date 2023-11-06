#include "signinmodel.h"

SignInModel::SignInModel(const QString &login, const QString &password) : login(login), password(password)
{

}

const QString &SignInModel::getLogin() const
{
    return login;
}

void SignInModel::setLogin(const QString &newLogin)
{
    login = newLogin;
}

const QString &SignInModel::getPassword() const
{
    return password;
}

void SignInModel::setPassword(const QString &newPassword)
{
    password = newPassword;
}

