#ifndef FIGURE_H
#define FIGURE_H

#include <string>
#include <vector>

#include "type.h"
#include "point.h"


class Figures
{
private:
    std::vector<Figure> figures;
    int countAlive;
    int countDeath;
public:
    Figures(/* args */);
    ~Figures();
    int addFigure(Figure newFigure);
    int delFigure(int index);
    int moveFigure(int index, Point position);
    bool killFigure(int index);
    int getAlive();
    int getDeath();
    std::vector<Figure> getFigures();
};

Figures::Figures(/* args */)
{
}

Figures::~Figures()
{
}

class Figure
{
private:
    Point position;
    Type type;
    int color;
    bool alive;
public:
    Figure(/* args */);
    ~Figure();
    void kill();
    bool move(Point );
};

Figure::Figure(/* args */)
{
}

Figure::~Figure()
{
}


#endif // FIGURE_H