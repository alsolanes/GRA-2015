#include "circle.h"
#include "math.h"
#include "iostream"

using namespace std;

Circle::Circle()
{
    cout << "Constructor de Circle" << endl;
}

Circle::Circle(float radius)
{
    this->radius = radius;
}

float Circle::getPerimeter()
{
    return 2*M_PI*this->radius;
}

void Circle::setRadius(double radius)
{
    this->radius = radius;
}
Circle::~Circle()
{
    cout << "Destructor de Circle" << endl;
}

