#ifndef REGISTERRESULT_H
#define REGISTERRESULT_H

#include "registerresultstatus.h"

#include <QMap>
#include <QString>

class RegisterResult
{
public:
    RegisterResult(RegisterResultStatus status);

    RegisterResultStatus getStatus() const;
    void setStatus(RegisterResultStatus newStatus);

    QString getErrorText();     // получить текст ошибки

private:
    RegisterResultStatus status;

    QMap<RegisterResultStatus, QString> errorsText;     // тексты ошибок
};

#endif // REGISTERRESULT_H
