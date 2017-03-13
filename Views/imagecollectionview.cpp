#include "imagecollectionview.h"
#include "ui_annotatedimageview.h"

#include "Model/imagecollectionmodel.h"

ImageCollectionView::ImageCollectionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnnotatedImageView)
{
    ui->setupUi(this);
}

ImageCollectionView::~ImageCollectionView()
{
    delete ui;
}

void ImageCollectionView::setModel(ImageCollectionModel *model)
{
    m_model = model;
    ui->listView->setModel(m_model);
    connect(ui->listView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            m_model, SLOT(onSelectedImage(QItemSelection,QItemSelection)));
}
