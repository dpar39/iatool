#ifndef UTILS_H
#define UTILS_H

#include <QJsonObject>
#include <QPointF>



class Utils
{
public:
    static QJsonObject toJson(const QPointF &p);

    static QPointF fromJson(const QJsonObject &obj);
};

#endif // UTILS_H
