#include "figurecontainer.h"
#include "square.h"
#include "circle.h"
using namespace std;
figurecontainer::figurecontainer()
{
    cout << "Constructor de FigureContainer" << endl;
}

void figurecontainer::addFigure(Figure *fig)
{
    this->vectFigures.push_back(fig);
}

int figurecontainer::getSize()
{
    return this->vectFigures.size();
}

double figurecontainer::getPerimeters()
{

    double sum = 0.0;
    for (Figure *f : this->vectFigures)
    {
        sum += f->getPerimeter();
    }

    return sum;
}

figurecontainer::~figurecontainer()
{

    for(unsigned int i = 0; i<this->vectFigures.size(); i++){
        if(dynamic_cast<Square*>(this->vectFigures[i])){
            delete(Square *)(this->vectFigures[i]);
        }
        else if(dynamic_cast<Circle *>(this->vectFigures[i])){
            delete(Circle *)(this->vectFigures[i]);
        }
    }
    cout << "Destructor de FigureContainer" << endl;
}

