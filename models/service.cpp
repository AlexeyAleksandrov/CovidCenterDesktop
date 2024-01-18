#include "service.h"

void Service::fromJson(const QJsonObject &jsonObject) {
    id = jsonObject.value("id").toInt();
    serviceName = jsonObject.value("serviceName").toString();
    price = jsonObject.value("price").toDouble();
}
