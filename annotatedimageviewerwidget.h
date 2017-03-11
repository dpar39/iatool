#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QPointF>

class QMouseEvent;


#include "iannotatedimage.h"
#include "iannotation.h"

#include "icoordinateconverter.h"


class AnnotatedImageViewerWidget : public QWidget, public ICoordinateConverter
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

public: /* Coordinate conversion */
    QPointF imageToClient(const QPointF &pt) override;

    QPointF clientToImage(const QPointF &pt) override;


signals:

public slots:

private:

    IAnnotatedImageSPtr m_annotatedImage;

    float m_xleft, m_ytop; // Offset in screen pixels
    float m_ratio;
    float m_zoom;

    int m_imageWidth, m_imageHeight;

    QPointF m_coords; // Latest mouse coordinates

    QPointF m_mouseDownPos;

private:
    void calculateZoomFit();

};

#endif // IMAGEVIEWER_H
