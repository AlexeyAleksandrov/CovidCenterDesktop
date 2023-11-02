#ifndef SIGNINMODEL_H
#define SIGNINMODEL_H

#include <QObject>

class SignInModel : public QObject
{
    Q_OBJECT
public:
    explicit SignInModel(QObject *parent = nullptr);
    SignInModel(const QString &login, const QString &password);

    const QString &getLogin() const;
    void setLogin(const QString &newLogin);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);

signals:

private:
    QString login;
    QString password;
};

#endif // SIGNINMODEL_H
