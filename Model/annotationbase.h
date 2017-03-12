#ifndef ANNOTATIONBASE_H
#define ANNOTATIONBASE_H

#include "iannotation.h"



class AnnotationBase : public IAnnotation
{
protected:
    AnnotationBase();

protected:
    bool m_isSelected;

    // IAnnotation interface
public:
    bool selected() const override;
    void setSelected(bool value) override;
};

#endif // ANNOTATIONBASE_H
