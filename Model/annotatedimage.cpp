#include "annotatedimage.h"

#include <QFile>
#include <QFileInfo>
#include <QPainter>
#include <QJsonArray>
#include <QJsonObject>

const QString IMAGE = "image";
const QString ANNOTATIONS = "annotations";



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
    return QFileInfo(m_imageFileName).fileName();
    //return m_imageFileName;
}

QPixmap AnnotatedImage::thumbnail()
{
    return QPixmap::fromImage(*m_image).scaledToWidth(64,Qt::SmoothTransformation);
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

void AnnotatedImage::serialize(QJsonObject &obj)
{
    obj[IMAGE] = imageFileName();
    QJsonArray arr;
    for (const auto &ann : *m_annotations)
    {
        QJsonObject obj;
        ann->serialize(obj);
        arr.append(obj);
    }
    obj[ANNOTATIONS] = arr;
}

IAnnotatedImageSPtr AnnotatedImage::fromFile(const QString &imageFile)
{
    // Get annotated file


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

//IAnnotatedImageSPtr AnnotatedImage::fromJson(const QString &a)
