#ifndef AUTHRESULT_H
#define AUTHRESULT_H

#include <QObject>
#include "authresultstatus.h"

class AuthResult : public QObject
{
    Q_OBJECT

public:
    explicit AuthResult(QObject *parent = nullptr);
    AuthResult(AuthResultStatus status);

    AuthResultStatus getStatus() const;
    void setStatus(AuthResultStatus newStatus);

signals:

private:
    AuthResultStatus status;

};

#endif // AUTHRESULT_H
