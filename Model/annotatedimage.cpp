#include "annotatedimage.h"

#include <QFile>
#include <QPainter>

AnnotatedImage::AnnotatedImage()
    : m_annotations(std::make_shared<IAnnotationSPtrVec>())
{
}

QImageSPtr AnnotatedImage::getImage() const
{
    return m_image;
}

QString AnnotatedImage::imageFileName() const
{
    return m_imageFileName;
}

IAnnotationSPtrVecSPtr AnnotatedImage::annotations() const
{
    return m_annotations;
}

void AnnotatedImage::addAnnotation(IAnnotationSPtr annotation)
{
    m_annotations->push_back(annotation);
}

void AnnotatedImage::render(QPainter *painter) const
{
    if (m_image->isNull())
    {
        return;
    }
    painter->drawImage(0, 0, *m_image);

    // Draw annotations
    for (const auto &ann : *m_annotations)
    {
        ann->render(painter);
    }
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
            annotatedImage->m_imageFileName = imageFile;
            annotatedImage->m_image = img;

            return annotatedImage;
        }
    }
    return IAnnotatedImageSPtr();
}

