#ifndef ANNOTATEDIMAGEVIEW_H
#define ANNOTATEDIMAGEVIEW_H

#include <QWidget>

class ImageCollectionModel;

namespace Ui {
class AnnotatedImageView;
}

class ImageCollectionView : public QWidget
{
    Q_OBJECT

public:
    explicit ImageCollectionView(QWidget *parent);

    ~ImageCollectionView();

    void setModel(ImageCollectionModel *model);

private:
    Ui::AnnotatedImageView *ui;

    ImageCollectionModel *m_model;
};

#endif // ANNOTATEDIMAGEVIEW_H
