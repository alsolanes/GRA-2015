#ifndef BOLA_H
#define BOLA_H


class Bola
{
public:
    Bola();
    ~Bola();

private:
    int a;
    int p;

    point4 [4];
    color4 vertex_colors[4];

    void quad(int a, int b, int c, int d);
};

#endif // BOLA_H
