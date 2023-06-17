#include <iostream>
#include "chess.h"

int main()
{

    Chess game;
    game.print_figure_count();
    game.print_board();

    while (game.step())
    {
        std::cout << std::endl;
        game.print_figure_count();
        game.print_board();
    }
}