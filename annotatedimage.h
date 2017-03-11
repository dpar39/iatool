#ifndef ANNOTATEDIMAGE_H
#define ANNOTATEDIMAGE_H

#include <QString>
#include <QImage>
#include "common.h"

#include "iannotatedimage.h"
#include "iannotation.h"

DEFINE(AnnotatedImage)



class AnnotatedImage : public IAnnotatedImage
{
private:
    AnnotatedImage() {}

    // Private members
private:
    QImageSPtr m_image;

    IAnnotationSPtrCollection m_annotations;

    // IAnnotatedImage interface
public:
    QImageSPtr getImage() const override;

    IAnnotationSPtrCollection annotations() const override;

    void addAnnotation(IAnnotationSPtr annotation) override;

    void render(QPainter *painter, ICoordinateConverter *canvas) const override;
public:
    /* Factory method */
    static IAnnotatedImageSPtr fromFile(const QString &imageFile);
};

#endif // ANNOTATEDIMAGE_H
