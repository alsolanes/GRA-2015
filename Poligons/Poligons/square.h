#include <figure.h>
#ifndef SQUARE_H
#define SQUARE_H


class Square: public Figure
{
private:
    float edge;
public:
    Square();
    Square(float edge);
    virtual float getPerimeter();
    virtual ~Square();
};

#endif // SQUARE_H
