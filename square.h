#ifndef Square_H
#define Square_H
#include "point.h"
#include "figure.h"

class Square
{
public:
    Square(){};
    Square(short a, short b, char o, char n)
    {
        pos.initPoint(a, b);
        piece.initFigure(o, n);
    };
    bool isEqualPoint(const Point &a) const
    {
        if (pos._x == a._x && pos._y == a._y)
        {
            return 1;
        }
        return 0;
    }
    bool isEqualPoint(int i, int j) const
    {
        if (pos._x == i && pos._y == j)
        {
            return 1;
        }
        return 0;
    }
    // seters
    void setFigure(Figure f)
    {

        piece._owner = f._owner;
        piece._name = f._name;
    }

    // getters
    Point getPoint()
    {
        return pos;
    }
    Figure getFigure()
    {
        return piece;
    }

private:
    Point pos;
    Figure piece;
};

#endif