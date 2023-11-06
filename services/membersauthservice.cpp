#include "membersauthservice.h"

// авторизация сотрудника
AuthResult MembersAuthService::authUser(SignInModel signInModel)
{
    // проверка на форматирвоание логина и пароля
    AuthResultStatus resultStatus = AuthService::checkAuthForm(signInModel);
    if(resultStatus != AuthResultStatus::NOT_AUTH)
    {
        return AuthResult(resultStatus);
    }

    // авторизация
}

RegisterResult MembersAuthService::registerUser(SignUpModel signInModel)
{

}
