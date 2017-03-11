#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QPointF>
#include <QTransform>

class QMouseEvent;
class QLabel;


#include "iannotatedimage.h"
#include "iannotation.h"


class AnnotatedImageViewerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnnotatedImageViewerWidget(QWidget *parent = 0);

    void setAnnotatedImage(IAnnotatedImageSPtr image);

    void addAnnotation(IAnnotationSPtr annotation);

    void setZoom(float value);

    void paintEvent(QPaintEvent *e) override;

    void resizeEvent(QResizeEvent *e) override;

    void mouseDoubleClickEvent(QMouseEvent *e) override;

    void wheelEvent(QWheelEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;

    void mouseMoveEvent(QMouseEvent *e) override;

    void enterEvent(QEvent *e) override;

    void leaveEvent(QEvent *e) override;

signals:
    void imageMove(const QPointF &pt);

    void imageClick(const QPointF &pt);

public slots:

private:

    IAnnotatedImageSPtr m_annotatedImage;

    // Cached transformations from image to widget coordinates and inverse
    QTransform m_imgToClientTForm;
    QTransform m_clientToImgTForm;

    float m_xleft, m_ytop; // Offset in screen pixels
    float m_ratio; // Scale of widget size to image size
    float m_zoom;  // Zoom scale normalized to 1
    int m_imageWidth, m_imageHeight;

    QPointF m_coords; // Latest mouse coordinates

    QPointF m_mouseDownPos;

    QLabel *m_label;

private:
    void calculateZoomFit();
    void calculateTransforms();
};

#endif // IMAGEVIEWER_H
