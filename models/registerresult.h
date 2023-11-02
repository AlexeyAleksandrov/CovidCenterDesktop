#ifndef REGISTERRESULT_H
#define REGISTERRESULT_H

#include <QObject>

#include "registerresultstatus.h"

class RegisterResult : public QObject
{
    Q_OBJECT
public:
    explicit RegisterResult(QObject *parent = nullptr);
    RegisterResult(RegisterResultStatus status);

    RegisterResultStatus getStatus() const;
    void setStatus(RegisterResultStatus newStatus);

signals:

private:
    RegisterResultStatus status;
};

#endif // REGISTERRESULT_H
