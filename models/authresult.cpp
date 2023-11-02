#include "authresult.h"

AuthResult::AuthResult(QObject *parent) : QObject(parent)
{

}

AuthResult::AuthResult(AuthResultStatus status)
{

}

AuthResultStatus AuthResult::getStatus() const
{
    return status;
}

void AuthResult::setStatus(AuthResultStatus newStatus)
{
    status = newStatus;
}
