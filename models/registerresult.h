#ifndef REGISTERRESULT_H
#define REGISTERRESULT_H

#include "registerresultstatus.h"

class RegisterResult
{
public:
    RegisterResult(RegisterResultStatus status);

    RegisterResultStatus getStatus() const;
    void setStatus(RegisterResultStatus newStatus);

private:
    RegisterResultStatus status;
};

#endif // REGISTERRESULT_H
