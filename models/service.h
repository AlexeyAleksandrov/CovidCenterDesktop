#ifndef SERVICE_H
#define SERVICE_H

#include <QJsonObject>
#include <QString>

class Service
{
public:
    int id;
    QString serviceName;
    double price;

    void fromJson(const QJsonObject& jsonObject);
};

#endif // SERVICE_H
