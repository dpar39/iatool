#include "annotatedimageview.h"
#include <QPainter>
#include <QResizeEvent>

#include <QLabel>

#include <algorithm>

AnnotatedImageView::AnnotatedImageView(QWidget *parent)
    : QWidget(parent),
      m_label(new QLabel(this))
{
    m_zoom = 1.0f;
    m_imageWidth = width();
    m_imageHeight = height();
    setMouseTracking(true);
    QString labelStyle = "font-size:10px;"
                         "font-family:Consolas;"
                         "color:yellowgreen;"
                         "border-width:0px;"
                         "border-radius:2px;"
                         "background-color:#77000000";
    m_label->setStyleSheet(labelStyle);
    m_label->setVisible(false);
}

void AnnotatedImageView::setAnnotatedImage(IAnnotatedImageSPtr image)
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

void AnnotatedImageView::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (m_annotatedImage != nullptr)
    {
        p.setTransform(m_imgToClientTForm);
        m_annotatedImage->render(&p);
    }
}

void AnnotatedImageView::calculateTransforms()
{
    m_imgToClientTForm.setMatrix(m_ratio*m_zoom, 0, 0, 0, m_ratio*m_zoom, 0, m_xleft, m_ytop, 1);
    m_clientToImgTForm = m_imgToClientTForm.inverted();
    m_label->setGeometry(std::max(1.f, m_xleft), std::max(0.0f, m_ytop), 72, 18);
}

void AnnotatedImageView::resizeEvent(QResizeEvent *e)
{
    calculateZoomFit();
    QWidget::resizeEvent(e);
}

void AnnotatedImageView::mouseDoubleClickEvent(QMouseEvent *e)
{
    calculateZoomFit();
    repaint();
    QWidget::mouseDoubleClickEvent(e);
}

void AnnotatedImageView::wheelEvent(QWheelEvent *e)
{
    auto inc = (e->delta() > 0) ? 1.2 : 1/1.2;
    setZoom(m_zoom * inc);
    QWidget::wheelEvent(e);
}

void AnnotatedImageView::mousePressEvent(QMouseEvent *e)
{
    // Store the position where the mouse was pressed
    m_mouseDownPos = e->pos();
    QWidget::mousePressEvent(e);
}

void AnnotatedImageView::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e);

    m_coords = m_clientToImgTForm.map(e->pos());

    QString labelText;

    labelText.sprintf("[%5d, %5d]", (int)m_coords.x(), (int)m_coords.y());
    m_label->setText(labelText);

    if ((e->buttons() && Qt::LeftButton))
    {
        m_xleft -=  (int) ((m_mouseDownPos.x() - e->x()));
        m_ytop  -=  (int) ((m_mouseDownPos.y() - e->y()));
        m_mouseDownPos = e->pos();
        calculateTransforms();
        repaint();
    }
}

void AnnotatedImageView::enterEvent(QEvent *)
{
    m_label->setVisible(true);
}

void AnnotatedImageView::leaveEvent(QEvent *)
{
    m_label->setVisible(false);
}

void AnnotatedImageView::calculateZoomFit()
{
    if (m_imageWidth > 0 && m_imageHeight > 0)
    {
        auto xratio = (float)width() / m_imageWidth;
        auto yratio = (float)height() / m_imageHeight;
        m_ratio = std::min(xratio, yratio);

        setZoom(1.0f);

        m_xleft = (width() - m_ratio * m_imageWidth) / 2.0f;
        m_ytop = (height() - m_ratio * m_imageHeight) / 2.0f;
        calculateTransforms();
    }
}

void AnnotatedImageView::setZoom(float value)
{
    if (value < 1E-05)
    {
        value = 1E-05f;
    }
    m_ytop += (int) (m_coords.y() * m_ratio * (m_zoom - value));
    m_xleft += (int) (m_coords.x() * m_ratio * (m_zoom - value));
    m_zoom = value;

    calculateTransforms();
    repaint();
}
