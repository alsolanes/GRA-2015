#include "square.h"
#include "iostream"
using namespace std;
Square::Square()
{
    this->edge = 1;
}

Square::Square(float edge)
{
    cout << "Constructor de Square" << endl;
    this->edge = edge;
}

float Square::getPerimeter()
{
    return this->edge*4;
}

Square::~Square()
{
    cout << "Destructor de Square" << endl;
}

