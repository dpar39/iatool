#ifndef IANNOTATION_H
#define IANNOTATION_H

#include <memory>

class QPainter;
class ICoordinateConverter;

class IAnnotation
{
public:    
    virtual void render(QPainter *painter, ICoordinateConverter *converter) = 0;
};

typedef std::shared_ptr<IAnnotation> IAnnotationSPtr;

#endif // IANNOTATION_H
