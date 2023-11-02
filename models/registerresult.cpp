#include "registerresult.h"

RegisterResult::RegisterResult(RegisterResultStatus status) : status(status)
{}

RegisterResultStatus RegisterResult::getStatus() const
{
    return status;
}

void RegisterResult::setStatus(RegisterResultStatus newStatus)
{
    status = newStatus;
}
