#ifndef SIGNINMODEL_H
#define SIGNINMODEL_H

#include <QString>


class SignInModel
{
public:
    SignInModel(const QString &login, const QString &password);

    const QString &getLogin() const;
    void setLogin(const QString &newLogin);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);

private:
    QString login;
    QString password;
};

#endif // SIGNINMODEL_H
