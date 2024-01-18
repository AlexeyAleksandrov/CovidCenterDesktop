#ifndef SERVICEDATA_H
#define SERVICEDATA_H

#include "analyzerresult.h"
#include "service.h"


class ServiceData {
public:
    int id;
    Service service;
    AnalyzerResult analyzerResult;

    void fromJson(const QJsonObject& jsonObject);
};

#endif // SERVICEDATA_H
