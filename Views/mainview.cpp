
#include "Views/MainView.h"
#include "Model/singlepointannotation.h"
#include "Model/annotatedimage.h"
#include "Model/imagecollectionmodel.h"
#include "ui_mainview.h"

#include <QFileDialog>
#include <QFileSystemModel>


MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView),
    m_annotatedImages(std::make_shared<IAnnotatedImageSPtrVec>()),
    m_annotatedImagesModel(new ImageCollectionModel(this, m_annotatedImages))
{
    ui->setupUi(this);

    auto annotatedImage = AnnotatedImage::fromFile("W:\\GITHUB\\ppp\\research\\mugshot_frontal_original_all\\001_frontal.jpg");

    auto ann = std::make_shared<SinglePointAnnotation>(QPointF(1000, 2000));
    annotatedImage->addAnnotation(ann);

    ui->imageViewer->setAnnotatedImage(annotatedImage);

    m_annotatedImagesModel = new ImageCollectionModel(this, m_annotatedImages);
    ui->annotatedImagesView->setModel(m_annotatedImagesModel);
}

MainView::~MainView()
{
    delete ui;
}

void MainView::openFolder()
{

}

void MainView::on_actionOpen_Image_triggered()
{

}

void MainView::on_actionOpen_Folder_triggered()
{
    auto folder = QFileDialog::getExistingDirectory(this, "Select folder with images", "W:/GITHUB/ppp/research");
    if (folder.isEmpty())
    {
        return;
    }

    m_annotatedImagesModel->loadDirectoryWithImages(folder);

}
