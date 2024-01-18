#include "analyzerresult.h"

void AnalyzerResult::fromJson(const QJsonObject &jsonObject)
{
    id = jsonObject.value("id").toInt();
    status = jsonObject.value("status").toString();
}
