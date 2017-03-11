#include "annotatedimage.h"

#include <QFile>
#include <QPainter>

QImageSPtr AnnotatedImage::getImage() const
{
    return m_image;
}

IAnnotationSPtrCollection AnnotatedImage::annotations() const
{
    return m_annotations;
}

void AnnotatedImage::addAnnotation(IAnnotationSPtr annotation)
{
    m_annotations.push_back(annotation);
}

void AnnotatedImage::render(QPainter *painter) const
{
    if (m_image->isNull())
    {
        return;
    }
    painter->drawImage(0, 0, *m_image);

}

IAnnotatedImageSPtr AnnotatedImage::fromFile(const QString &imageFile)
{
    if (QFile(imageFile).exists())
    {
        auto annotatedImage = std::shared_ptr<AnnotatedImage>(new AnnotatedImage());

        auto img = std::make_shared<QImage>(imageFile);
        if (!img ->isNull())
        {
            // TODO: Now try to read annotations (if any)
            annotatedImage->m_image = img;
            return annotatedImage;
        }
    }
    return IAnnotatedImageSPtr();
}
