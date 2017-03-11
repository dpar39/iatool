#include "singlepointannotation.h"
#include <QPainter>

SinglePointAnnotation::SinglePointAnnotation(const QPointF &pt)
    : m_point(pt)
{
}

void SinglePointAnnotation::render(QPainter *painter)
{
    auto tf = painter->transform();
    auto crossCenter = tf.map(m_point);
    painter->resetTransform();
    auto lftPt = (crossCenter + QPointF(-MARKER_SIZE, 0));
    auto rgtPt = (crossCenter + QPointF(+MARKER_SIZE, 0));
    auto topPt = (crossCenter + QPointF(0, -MARKER_SIZE));
    auto botPt = (crossCenter + QPointF(0, +MARKER_SIZE));

    painter->setPen(QPen(Qt::green, 2));

    painter->drawLine(lftPt, rgtPt);
    painter->drawLine(topPt, botPt);
    painter->setTransform(tf);
}
