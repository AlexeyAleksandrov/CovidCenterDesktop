#ifndef SIGNUPMODEL_H
#define SIGNUPMODEL_H

#include <QString>

class SignUpModel
{

public:
    SignUpModel(const QString &login, const QString &password, const QString &passwordConfirm);

    const QString &getLogin() const;
    void setLogin(const QString &newLogin);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);
    const QString &getPasswordConfirm() const;
    void setPasswordConfirm(const QString &newPasswordConfirm);


    const QString &getFullName() const;
    void setFullName(const QString &newFullName);

private:
    QString fullName;
    QString login;
    QString password;
    QString passwordConfirm;
};

#endif // SIGNUPMODEL_H
