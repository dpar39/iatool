#include "utils.h"


QJsonObject Utils::toJson(const QPointF &p)
{
    QJsonObject obj;
    obj["x"] = p.x();
    obj["y"] = p.y();
    return obj;
}

QPointF Utils::fromJson(const QJsonObject &obj)
{
    return QPointF(obj["x"].toDouble(), obj["y"].toDouble());
}
