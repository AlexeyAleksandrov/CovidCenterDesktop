#ifndef SIGNUPMODEL_H
#define SIGNUPMODEL_H

#include <QObject>

class SignUpModel : public QObject
{
    Q_OBJECT
public:
    explicit SignUpModel(QObject *parent = nullptr);
    SignUpModel(const QString &login, const QString &password, const QString &passwordConfirm);

    const QString &getLogin() const;
    void setLogin(const QString &newLogin);
    const QString &getPassword() const;
    void setPassword(const QString &newPassword);
    const QString &getPasswordConfirm() const;
    void setPasswordConfirm(const QString &newPasswordConfirm);

signals:

private:
    QString login;
    QString password;
    QString passwordConfirm;
};

#endif // SIGNUPMODEL_H
