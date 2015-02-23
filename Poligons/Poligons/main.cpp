#include <iostream>
#include <square.h>
#include <circle.h>
#include <figurecontainer.h>

using namespace std;

int main()
{
    Square *quadrat = new Square(10);
    Circle *cercle = new Circle(10);
    Square *quadrat2 = new Square(100);
    figurecontainer *f = new figurecontainer();

    f->addFigure(quadrat);
    f->addFigure(cercle);
    f->addFigure(quadrat2);

    cout << "Perimetre quadrat de 10 de costat: " << quadrat->getPerimeter() << endl;
    cout << "Perimetre cercle de 10 de radi: " << cercle->getPerimeter() << endl;
    cout << "Suma de perimetres: " << f->getPerimeters() << endl;

    cout << "Modificat radi de cercle!\n\tAbans perimetre: "<< cercle->getPerimeter() << endl;
    cercle->setRadius(5);
    cout << "\tDesprés perimetre: " << cercle->getPerimeter() << endl;



    cout << "Suma de perimetres: " << f->getPerimeters() << endl;


    /*delete quadrat;
    delete cercle;
    delete f;*/
    delete f;
    return 0;
}

