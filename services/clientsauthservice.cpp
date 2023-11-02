#include "clientsauthservice.h"

ClientsAuthService::ClientsAuthService(QObject *parent) : AuthService(parent)
{

}


AuthResult ClientsAuthService::authUser(SignInModel signInModel)
{
}

RegisterResult ClientsAuthService::registerUser(SignUpModel signInModel)
{
}
