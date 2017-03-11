#include "annotatedimageviewerwidget.h"
#include <QPainter>
#include <QResizeEvent>

#include <algorithm>

AnnotatedImageViewerWidget::AnnotatedImageViewerWidget(QWidget *parent) : QWidget(parent)
{
    m_zoom = 1.0f;
    m_imageWidth = width();
    m_imageHeight = height();
    setMouseTracking(true);
}

void AnnotatedImageViewerWidget::setAnnotatedImage(IAnnotatedImageSPtr image)
{
    m_annotatedImage = image;
    m_imageWidth =  m_annotatedImage->getImage()->width();
    m_imageHeight =  m_annotatedImage->getImage()->height();

    calculateZoomFit();
    // Calculate viewport
    repaint();
}


void AnnotatedImageViewerWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (m_annotatedImage != nullptr)
    {
        m_annotatedImage->render(&p, this);
    }
}

void AnnotatedImageViewerWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    if (m_annotatedImage != nullptr)
    {
//        auto rx = e->size().width() / e->oldSize().width();
//        auto ry = e->size().height() / e->oldSize().width();
//        auto new_zoom = m_zoom * std::min(rx, ry);
//        setZoom(new_zoom);
    }
}

void AnnotatedImageViewerWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    QWidget::mouseDoubleClickEvent(e);
    calculateZoomFit();
    repaint();
}

void AnnotatedImageViewerWidget::wheelEvent(QWheelEvent *e)
{
    QWidget::wheelEvent(e);
    auto inc = (e->delta() > 0) ? 1.2 : 1/1.2;
    setZoom(m_zoom * inc);
}

void AnnotatedImageViewerWidget::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
    m_mouseDownPos = e->pos();
}

void AnnotatedImageViewerWidget::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);

    m_coords = clientToImage(e->pos());

    if ((e->buttons() && Qt::LeftButton))
    {
        m_xleft -=  (int) ((m_mouseDownPos.x() - e->x()));
        m_ytop  -=  (int) ((m_mouseDownPos.y() - e->y()));
        m_mouseDownPos = e->pos();
        repaint();
    }
}

QPointF AnnotatedImageViewerWidget::imageToClient(const QPointF &pt)
{
    auto x = m_xleft + pt.x() * m_ratio * m_zoom;
    auto y = m_ytop + pt.y() * m_ratio* m_zoom;
    return QPointF(x, y);
}

QPointF AnnotatedImageViewerWidget::clientToImage(const QPointF &pt)
{
    auto x = (pt.x() - m_xleft) / m_ratio /m_zoom;
    auto y = (pt.y() - m_ytop) / m_ratio/ m_zoom;
    return QPointF(x, y);
}

void AnnotatedImageViewerWidget::calculateZoomFit()
{
    if (m_imageWidth > 0 && m_imageHeight > 0)
    {
        auto xratio = (float)width() / m_imageWidth;
        auto yratio = (float)height() / m_imageHeight;
        m_ratio = std::min(xratio, yratio);

        setZoom(1.0f);

        m_xleft = (width() - m_ratio * m_imageWidth) / 2.0f;
        m_ytop = (height() - m_ratio * m_imageHeight) / 2.0f;
    }
}

void AnnotatedImageViewerWidget::setZoom(float value)
{
    if (value < 1E-05)
    {
        value = 1E-05f;
    }
    m_ytop += (int) (m_coords.y() * m_ratio * (m_zoom - value));
    m_xleft += (int) (m_coords.x() * m_ratio * (m_zoom - value));
    m_zoom = value;

    repaint();
}
