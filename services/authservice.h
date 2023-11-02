#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <QObject>

#include "models/signinmodel.h"
#include "models/signupmodel.h"
#include "models/authresult.h"
#include "models/registerresult.h"

class AuthService : public QObject
{
    Q_OBJECT
public:
    explicit AuthService(QObject *parent = nullptr);

signals:

public:
    virtual AuthResult authUser(SignInModel signInModel);
    virtual RegisterResult registerUser(SignUpModel signInModel);
};

#endif // AUTHSERVICE_H
