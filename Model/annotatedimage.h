#ifndef ANNOTATEDIMAGE_H
#define ANNOTATEDIMAGE_H

#include "Common/common.h"
#include "Model/iannotatedimage.h"
#include "Model/iannotation.h"

class QJsonObject;

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

    QPixmap thumbnail() override;

    IAnnotationSPtrVecSPtr annotations() const override;

    void addAnnotation(IAnnotationSPtr annotation) override;

    void render(QPainter *painter) const override;

    void AnnotatedImage::serialize(QJsonObject &obj);

public:
    /* Factory method */
    static IAnnotatedImageSPtr fromFile(const QString &imageFile);

    // IAnnotatedImage interface
};

#endif // ANNOTATEDIMAGE_H
