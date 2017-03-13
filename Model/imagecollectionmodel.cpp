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

    QStringList allFiles = imageDirectory.entryList({"*.png", "*.jpg"},
                                                    QDir::NoDotAndDotDot | QDir::Files);
    beginResetModel();
    m_images->clear();
    for (auto &imageFile : allFiles)
    {
        auto annotatedImage = AnnotatedImage::fromFile(imageDirectory.filePath(imageFile));
        if (annotatedImage != nullptr)
        {
            m_images->push_back(annotatedImage);
        }
    }
    endResetModel();

    if (!m_images->empty())
    {
        emit selectedImageChanged(m_images->front());
    }
}

void ImageCollectionModel::onSelectedImage(QItemSelection selected, QItemSelection deselected)
{
    if (!selected.empty())
    {
        int imgIndex = selected.first().indexes().first().row();
        emit selectedImageChanged(m_images->at(imgIndex));
    }
}

int ImageCollectionModel::rowCount(const QModelIndex &) const
{
    return static_cast<int>(m_images->size());
}

QVariant ImageCollectionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= m_images->size())
    {
        return QVariant();
    }
    auto image = m_images->at(index.row());

    switch(role)
    {
        case Qt::DisplayRole:
            return image->imageFileName();
        case Qt::DecorationRole:
            return image->thumbnail();
        case Qt::ToolTipRole:
        case Qt::SizeHintRole:
            break;
    }

    return QVariant();
}
