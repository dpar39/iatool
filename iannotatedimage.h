#ifndef IANNOTATEDIMAGE_H
#define IANNOTATEDIMAGE_H

#include "common.h"
#include "iannotation.h"

class ICoordianteConverter;

DEFINE(QImage)

DEFINE(IAnnotatedImage)

typedef std::vector<IAnnotationSPtr> IAnnotationSPtrCollection;

#include "iannotation.h"

class IAnnotatedImage
{
public:
    virtual QImageSPtr getImage() const = 0;

    virtual IAnnotationSPtrCollection annotations() const = 0;

    virtual void addAnnotation(IAnnotationSPtr annotation) = 0;

    virtual void render(QPainter *painter, ICoordinateConverter *canvas) const = 0;
};

#endif // IANNOTATEDIMAGE_H
