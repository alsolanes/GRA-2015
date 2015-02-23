#include <vector>
#include <iostream>
#include <figure.h>
#ifndef FIGURECONTAINER_H
#define FIGURECONTAINER_H

using namespace std;

class figurecontainer
{
private:
    vector<Figure *> vectFigures;
public:
    figurecontainer();
    void addFigure(Figure *);
    int getSize();
    double getPerimeters();
    ~figurecontainer();
};

#endif // FIGURECONTAINER_H
