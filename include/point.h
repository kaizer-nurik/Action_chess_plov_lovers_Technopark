#ifndef POINT_H
#define POINT_H

class Point
{
private:
    int x;
    int y; 

public:
    Point(int x_, int y_);
    Point(Point &p);
    ~Point();
    int getX();
    int getY();
    int setX(int x_);
    int setY(int y_);
};

Point::Point(int x_, int y_)
{
}

Point::~Point()
{
}

#endif