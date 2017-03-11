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
    if (m_annotatedImage != nullptr)
    {
        m_imageWidth =  m_annotatedImage->getImage()->width();
        m_imageHeight =  m_annotatedImage->getImage()->height();
        calculateZoomFit();
    }
    repaint();
}

void AnnotatedImageViewerWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (m_annotatedImage != nullptr)
    {
        p.setTransform(m_imgToClientTForm);
        m_annotatedImage->render(&p);
    }
}

void AnnotatedImageViewerWidget::setTransform()
{
    m_imgToClientTForm.setMatrix(m_ratio*m_zoom, 0, 0, 0, m_ratio*m_zoom, 0, m_xleft, m_ytop, 1);
    m_clientToImgTForm = m_imgToClientTForm.inverted();
}

void AnnotatedImageViewerWidget::resizeEvent(QResizeEvent *e)
{
    calculateZoomFit();
    QWidget::resizeEvent(e);
}

void AnnotatedImageViewerWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    calculateZoomFit();
    repaint();
    QWidget::mouseDoubleClickEvent(e);
}

void AnnotatedImageViewerWidget::wheelEvent(QWheelEvent *e)
{
    auto inc = (e->delta() > 0) ? 1.2 : 1/1.2;
    setZoom(m_zoom * inc);
    QWidget::wheelEvent(e);
}

void AnnotatedImageViewerWidget::mousePressEvent(QMouseEvent *e)
{
    // Store the position where the mouse was pressed
    m_mouseDownPos = e->pos();
    QWidget::mousePressEvent(e);    
}

void AnnotatedImageViewerWidget::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);

    m_coords = m_clientToImgTForm.map(e->pos());

    if ((e->buttons() && Qt::LeftButton))
    {
        m_xleft -=  (int) ((m_mouseDownPos.x() - e->x()));
        m_ytop  -=  (int) ((m_mouseDownPos.y() - e->y()));
        m_mouseDownPos = e->pos();
        setTransform();
        repaint();
    }
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
        setTransform();
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

    setTransform();
    repaint();
}
