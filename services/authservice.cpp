#include "authservice.h"

AuthResult AuthService::authUser(SignInModel signInModel)
{
    return AuthResult(AuthResultStatus::NOT_AUTH);
}

RegisterResult AuthService::registerUser(SignUpModel signInModel)
{
    return RegisterResult(RegisterResultStatus::NOT_REGISTER);
}
