#include "servicedata.h"


void ServiceData::fromJson(const QJsonObject &jsonObject)
{
    id = jsonObject.value("id").toInt();

    // Извлечение данных из вложенных объектов
    service.fromJson(jsonObject.value("service").toObject());
    analyzerResult.fromJson(jsonObject.value("analyzerResult").toObject());
}
