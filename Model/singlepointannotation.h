#ifndef SINGLEPOINTANNOTATION_H
#define SINGLEPOINTANNOTATION_H

#include "annotationbase.h"

#include <QPointF>

class SinglePointAnnotation : public AnnotationBase
{
public:
    SinglePointAnnotation(const QPointF &pt);

    // IAnnotation interface
public:
    void render(QPainter *painter) override;

    void serialize(QJsonObject &obj) override;

private:
    QPointF m_point;
    const float MARKER_SIZE = 8.0f;
};

#endif // SINGLEPOINTANNOTATION_H
