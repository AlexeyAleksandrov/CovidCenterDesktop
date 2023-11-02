#ifndef MEMBERSAUTHSERVICE_H
#define MEMBERSAUTHSERVICE_H

#include "authservice.h"

class MembersAuthService : public AuthService
{
public:
    explicit MembersAuthService(QObject *parent = nullptr);

    // AuthService interface
public:
    AuthResult authUser(SignInModel signInModel) override;
    RegisterResult registerUser(SignUpModel signInModel) override;
};

#endif // MEMBERSAUTHSERVICE_H
