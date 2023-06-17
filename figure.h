#ifndef FIGURE_H
#define FIGURE_H
#include <iostream>

struct Figure
{
    void initFigure(char o, char n)
    {
        _owner = o;
        _name = n;
    }
    
    void print()
    {
        std::cout << _owner << _name << "\n";
    }

    char _owner;
    char _name;
};

#endif