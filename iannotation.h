#ifndef IANNOTATION_H
#define IANNOTATION_H

#include <memory>
#include "common.h"

DEFINE(IAnnotation)

class QJsonObject;
class QPainter;

class IAnnotation
{
public:    
    virtual void render(QPainter *painter) = 0;

    virtual bool selected() const = 0;

    virtual void setSelected(bool value) = 0;

    virtual void serialize(QJsonObject &obj) = 0;
};

#endif // IANNOTATION_H
