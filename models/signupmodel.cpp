#include "signupmodel.h"

SignUpModel::SignUpModel(QObject *parent) : QObject(parent)
{

}

SignUpModel::SignUpModel(const QString &login, const QString &password, const QString &passwordConfirm) :
    login(login),
    password(password),
    passwordConfirm(passwordConfirm)
{}

const QString &SignUpModel::getLogin() const
{
    return login;
}

void SignUpModel::setLogin(const QString &newLogin)
{
    login = newLogin;
}

const QString &SignUpModel::getPassword() const
{
    return password;
}

void SignUpModel::setPassword(const QString &newPassword)
{
    password = newPassword;
}

const QString &SignUpModel::getPasswordConfirm() const
{
    return passwordConfirm;
}

void SignUpModel::setPasswordConfirm(const QString &newPasswordConfirm)
{
    passwordConfirm = newPasswordConfirm;
}
