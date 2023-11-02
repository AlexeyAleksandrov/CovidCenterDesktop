#include "authresult.h"

AuthResult::AuthResult(AuthResultStatus status)
{
    this->status = status;
}

AuthResultStatus AuthResult::getStatus() const
{
    return status;
}

void AuthResult::setStatus(AuthResultStatus newStatus)
{
    status = newStatus;
}
