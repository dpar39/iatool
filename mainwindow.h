#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>

#include <QMainWindow>
#include "annotatedimage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void openFolder();
private slots:
    void on_actionOpen_Image_triggered();
    void on_actionOpen_Folder_triggered();

private:
    std::vector<IAnnotatedImageSPtr> m_annotatedImages;
};

#endif // MAINWINDOW_H
