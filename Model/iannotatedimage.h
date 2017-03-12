#ifndef IANNOTATEDIMAGE_H
#define IANNOTATEDIMAGE_H

#include "Common/common.h"
#include "Model/iannotation.h"
#include <vector>
#include <QString>

DEFINE(QImage)

DEFINE(IAnnotatedImage)

DEFINE_VECTOR(IAnnotatedImage)

#include "iannotation.h"

class IAnnotatedImage
{
public:
    virtual QImageSPtr getImage() const = 0;

    virtual QString imageFileName() const = 0;

    virtual IAnnotationSPtrVecSPtr annotations() const = 0;

    virtual void addAnnotation(IAnnotationSPtr annotation) = 0;

    virtual void render(QPainter *painter) const = 0;
};

#endif // IANNOTATEDIMAGE_H
