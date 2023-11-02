#ifndef AUTHRESULT_H
#define AUTHRESULT_H

#include "authresultstatus.h"

class AuthResult
{

public:
    AuthResult(AuthResultStatus status);

    AuthResultStatus getStatus() const;
    void setStatus(AuthResultStatus newStatus);

private:
    AuthResultStatus status;

};

#endif // AUTHRESULT_H
