#ifndef MEMBERSAUTHSERVICE_H
#define MEMBERSAUTHSERVICE_H

#include "authservice.h"

class MembersAuthService : public AuthService
{
// AuthService interface
public:
    AuthResult authUser(SignInModel signInModel) override;
    RegisterResult registerUser(SignUpModel signUpModel) override;
};

#endif // MEMBERSAUTHSERVICE_H
