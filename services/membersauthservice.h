#ifndef MEMBERSAUTHSERVICE_H
#define MEMBERSAUTHSERVICE_H

#include "authservice.h"
#include <QRegularExpression>

class MembersAuthService : public AuthService
{
// AuthService interface
public:
    AuthResult authUser(SignInModel signInModel) override;
    RegisterResult registerUser(SignUpModel signInModel) override;
};

#endif // MEMBERSAUTHSERVICE_H
