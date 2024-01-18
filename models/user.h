#ifndef USER_H
#define USER_H

#include <QJsonObject>
#include <QString>

class User
{
public:
    int id;
    QString fullName;

    void fromJson(const QJsonObject& jsonObject);
};

#endif // USER_H
