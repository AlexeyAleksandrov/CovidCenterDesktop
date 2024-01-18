#ifndef ANALYZERRESULT_H
#define ANALYZERRESULT_H

#include <QJsonObject>
#include <QString>

class AnalyzerResult
{
public:
    int id;
    QString status;

    void fromJson(const QJsonObject& jsonObject);
};

#endif // ANALYZERRESULT_H
