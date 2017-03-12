#ifndef ANNOTATEDIMAGEMODEL_H
#define ANNOTATEDIMAGEMODEL_H

#include <QAbstractListModel>
#include"Common/common.h"

#include "Model/iannotatedimage.h"

DEFINE_VECTOR(IAnnotatedImage)

class ImageCollectionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ImageCollectionModel(QObject *parent, IAnnotatedImageSPtrVecSPtr images);

    void loadDirectoryWithImages(const QString &imageFolder);

private:
    IAnnotatedImageSPtrVecSPtr m_images;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

#endif // ANNOTATEDIMAGEMODEL_H
