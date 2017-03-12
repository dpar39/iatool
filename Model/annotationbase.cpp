#include "annotationbase.h"

AnnotationBase::AnnotationBase()
    : m_isSelected(false)
{
}

bool AnnotationBase::selected() const
{
    return m_isSelected;
}

void AnnotationBase::setSelected(bool value)
{
    m_isSelected = value;
}
