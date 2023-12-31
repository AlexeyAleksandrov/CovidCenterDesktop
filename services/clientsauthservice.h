#ifndef CLIENTSAUTHSERVICE_H
#define CLIENTSAUTHSERVICE_H

#include "authservice.h"

class ClientsAuthService : public AuthService
{
// AuthService interface
public:
    AuthResult authUser(SignInModel signInModel) override;
    RegisterResult registerUser(SignUpModel signInModel) override;
};

#endif // CLIENTSAUTHSERVICE_H
