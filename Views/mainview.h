#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "Common/common.h"

#include <vector>
#include <QMainWindow>

DEFINE(IAnnotatedImage)
DEFINE_VECTOR(IAnnotatedImage)

namespace Ui {
class MainView;
}

class ImageCollectionModel;

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private:
    Ui::MainView *ui;

public slots:
    void openFolder();
private slots:
    void on_actionOpen_Image_triggered();
    void on_actionOpen_Folder_triggered();

private:
    IAnnotatedImageSPtrVecSPtr m_annotatedImages;

    ImageCollectionModel *m_annotatedImagesModel;
};

#endif // MAINVIEW_H
