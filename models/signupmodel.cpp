#include "signupmodel.h"

SignUpModel::SignUpModel(const QString &login, const QString &password, const QString &passwordConfirm, const QString &fullName)
{
    this->login = login;
    this->password = password;
    this->passwordConfirm = passwordConfirm;
    this->fullName = fullName;
}

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

const QString &SignUpModel::getFullName() const
{
    return fullName;
}

void SignUpModel::setFullName(const QString &newFullName)
{
    fullName = newFullName;
}
