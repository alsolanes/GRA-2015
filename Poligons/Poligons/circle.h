#include <figure.h>
#ifndef CIRCLE_H
#define CIRCLE_H


class Circle: public Figure
{
private:
    float radius;
public:
    Circle();
    Circle(float radius);
    virtual float getPerimeter();
    void setRadius(double radius);
    virtual ~Circle();
};

#endif // CIRCLE_H
