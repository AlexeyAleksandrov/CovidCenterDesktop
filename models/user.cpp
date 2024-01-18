#include "user.h"

void User::fromJson(const QJsonObject &jsonObject)
{
    id = jsonObject.value("id").toInt();
    fullName = jsonObject.value("fullName").toString();
}
