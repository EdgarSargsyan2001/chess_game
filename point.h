#ifndef Point_H
#define Point_H
#include <iostream>
#include <string>

struct Point
{
    Point() : _x(-1), _y(-1) {}
    Point(short a, short b) : _x(a), _y(b)
    {
    }
    void initPoint(short a, short b)
    {
        _x = a;
        _y = b;
    }
    //
    bool EnterPoint(std::string s)
    {
        std::cout << "Enter " << s << " Point: ";
        char a;
        char b;
        std::cin >> a >> b;
        if (a > b)
        {
            std::swap(a, b);
        }
        a -= '0';
        if (a < 1 || a > 8)
        {
            std::cout << "Number is out of range ):" << std::endl;
            return false;
        }
        if (b >= 'a' && b <= 'h')
        {
            b = b - ('a' - 'A');
        }
        if (b < 'A' || b > 'H')
        {
            std::cout << "character is out of range ):\n";
            return false;
        }
        _x = a;
        _y = (b - 'A' + 1);
        return true;
    }
    void print() const
    {
        std::cout << "x: " << _x << " y: " << _y << "\n";
    }
    short _x;
    short _y;
};

#endif