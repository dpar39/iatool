#ifndef ICOORDINATECONVERTER_H
#define ICOORDINATECONVERTER_H

#include <QPoint>
#include <QPointF>

class ICoordinateConverter
{
public:
    virtual QPointF imageToClient(const QPointF &pt) = 0;

    virtual QPointF clientToImage(const QPointF &pt) = 0;
};

#endif // ICOORDINATECONVERTER_H
