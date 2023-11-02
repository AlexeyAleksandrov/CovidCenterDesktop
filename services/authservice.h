#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include "models/signinmodel.h"
#include "models/signupmodel.h"
#include "models/authresult.h"
#include "models/registerresult.h"

class AuthService
{
public:
    virtual AuthResult authUser(SignInModel signInModel);
    virtual RegisterResult registerUser(SignUpModel signInModel);
};

#endif // AUTHSERVICE_H
