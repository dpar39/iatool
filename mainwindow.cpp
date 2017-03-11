#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto annotatedImage = AnnotatedImage::fromFile("W:\\GITHUB\\ppp\\research\\mugshot_frontal_original_all\\001_frontal.jpg");

    ui->imageViewer->setAnnotatedImage(annotatedImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFolder()
{

}

void MainWindow::on_actionOpen_Image_triggered()
{

}

void MainWindow::on_actionOpen_Folder_triggered()
{
    auto folder = QFileDialog::getExistingDirectory(this, "Select folder with images");
    if (folder.isEmpty())
    {
        return;
    }
    QDir imageDirectory(folder);
    QStringList allFiles = imageDirectory.entryList(QDir::NoDotAndDotDot | QDir::Files);

    for (auto &imageFile : allFiles)
    {
        auto annotatedImage = AnnotatedImage::fromFile(imageDirectory.filePath(imageFile));

        if (annotatedImage != nullptr)
        {
            m_annotatedImages.push_back(annotatedImage);
            break;
        }
    }
    if (!m_annotatedImages.empty())
    {
        ui->imageViewer->setAnnotatedImage(m_annotatedImages.front());
    }
}
