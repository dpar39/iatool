#ifndef IANNOTATION_H
#define IANNOTATION_H

#include <memory>

class QPainter;

class IAnnotation
{
public:    
    virtual void render(QPainter *painter) = 0;

    virtual bool selected() const = 0;

    virtual void setSelected(bool value) = 0;
};

typedef std::shared_ptr<IAnnotation> IAnnotationSPtr;

#endif // IANNOTATION_H
