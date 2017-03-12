#include "Model/imagecollectionmodel.h"

#include "Model/annotatedimage.h"

#include <QDir>

ImageCollectionModel::ImageCollectionModel(QObject *parent, IAnnotatedImageSPtrVecSPtr images)
    : QAbstractListModel(parent)
    , m_images(images)
{
}

void ImageCollectionModel::loadDirectoryWithImages(const QString &imageFolder)
{
    QDir imageDirectory(imageFolder);


    QStringList allFiles = imageDirectory.entryList({"*.png", "*.jpg"}, QDir::NoDotAndDotDot | QDir::Files);

    beginResetModel();

    for (auto &imageFile : allFiles)
    {
        auto annotatedImage = AnnotatedImage::fromFile(imageDirectory.filePath(imageFile));

        if (annotatedImage != nullptr)
        {
            m_images->push_back(annotatedImage);
            if (m_images->size() == 3)
            {
                break;
            }
        }
    }

    endResetModel();

//    if (!m_annotatedImages->empty())
//    {
//        ui->imageViewer->setAnnotatedImage(m_annotatedImages->front());
//    }
}



int ImageCollectionModel::rowCount(const QModelIndex &) const
{
    return static_cast<int>(m_images->size());
}

QVariant ImageCollectionModel::data(const QModelIndex &index, int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
            return QVariant((*m_images)[index.row()]->imageFileName());
    }

    return QVariant();
}
