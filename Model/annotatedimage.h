#ifndef ANNOTATEDIMAGE_H
#define ANNOTATEDIMAGE_H

#include <QString>
#include <QImage>

#include "Common/common.h"
#include "Model/iannotatedimage.h"
#include "Model/iannotation.h"

DEFINE(AnnotatedImage)

class AnnotatedImage : public IAnnotatedImage
{
private:
    AnnotatedImage();

    // Private members
private:
    QString m_imageFileName;

    QImageSPtr m_image;

    IAnnotationSPtrVecSPtr m_annotations;

    // IAnnotatedImage interface
public:
    QImageSPtr getImage() const override;

    QString imageFileName() const override;

    IAnnotationSPtrVecSPtr annotations() const override;

    void addAnnotation(IAnnotationSPtr annotation) override;

    void render(QPainter *painter) const override;
public:
    /* Factory method */
    static IAnnotatedImageSPtr fromFile(const QString &imageFile);
};

#endif // ANNOTATEDIMAGE_H
