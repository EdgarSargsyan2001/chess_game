#ifndef CHESS_H
#define CHESS_H
#include <iostream>
#include <string>
#include "square.h"

// Թագուհի - Q (Queen)
// Թագավոր - K (King)
// Նավակ - R (Rook)
// Փիղ - B (Bishop)
// Ձի - N (Knight)
// Զինվոր - P (Pawn)

class Chess
{
public:
    Chess();
    ~Chess();
    bool step();

    // print
    void print_board() const;
    void print_figure_count() const;

private:
    Square *get_Square(short x, short y);
    Square *get_Square(Point p);
    bool enter_Pointer_start(Point &a);
    bool enter_Pointer_end(Point &b);
    bool can_move_there(char fType, const Point &pos, const Point &endPoint);
    bool can_move_Pawn(const Point &pos, const Point &endPoint); // Զինվոր
    void changeChessPieces(Square *);

private:
    short ChessPieceW = 12;
    short ChessPieceB = 12;
    bool whoseTurn = 0;
    Square **Board;
};
Chess::Chess()
{
    const int N = 9;
    Square **matrix = new Square *[N];
    for (int i = 0; i < N; i++)
    {
        matrix[i] = new Square[N];
    }
    std::string pieces = "RNBQKBNR";
    for (int i = 0; i < N; i++)
    {

        for (int j = 0; j < N; ++j)
        {
            if (i == 1 || i == 8)
            {
                Square k(i, j, (i % 2 ? 'b' : 'w'), pieces[j - 1]);
                matrix[i][j] = k;
            }
            else if (i == 2 || i == 7)
            {
                Square k(i, j, (i % 2 ? 'w' : 'b'), 'P');
                matrix[i][j] = k;
            }
            else
            {
                Square k(i, j, ':', ':');
                matrix[i][j] = k;
            }
        }
    }
    Board = matrix;
}
Chess::~Chess()
{
    const int N = 9;
    for (int i = 0; i < N; i++)
    {
        delete[] Board[i];
    }
    delete Board;
}

bool Chess::step()
{
    std::cout << "Turn is " << (whoseTurn ? "White:\n" : "Black:\n");
    Point aPoint;
    while (!enter_Pointer_start(aPoint))
    {
    }

    Point bPoint;
    while (!enter_Pointer_end(bPoint))
    {
    }

    Figure fig = get_Square(aPoint)->getFigure();

    int inputErrorsCount = 0;
    while (!can_move_there(fig._name, aPoint, bPoint))
    {
        std::cout << "you can't go there :(\n";
        if (inputErrorsCount++ == 3)
        {
            std::cerr << "\nENTER START AGAIN :) " << (whoseTurn ? "White Pleyer\n" : "Black Pleyer\n");
            return true;
        }
        while (!enter_Pointer_end(bPoint))
        {
        }
    }

    Square *EndSq = get_Square(bPoint);
    changeChessPieces(EndSq);

    if ((bPoint._x == 1 || bPoint._x == 8) && fig._name == 'P')
    {
        fig._name = 'Q';
    }

    EndSq->setFigure(fig);

    //
    get_Square(aPoint)->setFigure({':', ':'});

    // change turn
    whoseTurn = !whoseTurn;
    return true;
}

bool Chess::can_move_there(char fType, const Point &pos, const Point &endPoint)
{
    // std::cout << "fType: " << fType << "\n";
    switch (fType)
    {
    case 'P':
        return can_move_Pawn(pos, endPoint);

    default:
        return 0;
    }
}

bool Chess::can_move_Pawn(const Point &pos, const Point &endPoint)
{
    bool canMove = false;
    if ((endPoint._y - pos._y) == 0)
    {

        for (int i = 1; i <= ((pos._x == 2 || pos._x == 7) ? 2 : 1); ++i)
        {
            Square *sq = get_Square(pos._x + (whoseTurn ? -i : i), pos._y);

            if (!sq || sq->getFigure()._name != ':')
            {
                canMove = false;
                break;
            }
            else if (sq->isEqualPoint(endPoint))
            {
                canMove = true;
                break;
            }
        }
    }
    else
    {
        int arr[2] = {1, -1};
        for (int i = 0; i < 2; ++i)
        {
            Square *sq = get_Square(pos._x + (whoseTurn ? -1 : 1), (pos._y + arr[i]));
            if (sq)
            {
                Figure fig = sq->getFigure();
                if (sq->isEqualPoint(endPoint) && fig._owner == (whoseTurn ? 'b' : 'w') && fig._name != 'K')
                {
                    canMove = true;
                }
            }
        }
    }

    return canMove;
}

bool Chess::enter_Pointer_start(Point &a)
{
    if (!a.EnterPoint("START"))
    {
        return false;
    }

    if (get_Square(a)->getFigure()._name == ':')
    {
        std::cout << "there isn't figure :(\n";
        return false;
    }
    if (get_Square(a)->getFigure()._owner == (whoseTurn ? 'b' : 'w'))
    {
        std::cout << "it is " << (whoseTurn ? "White" : "Black") << " turn :(" << std::endl;
        return false;
    }
    return true;
}
bool Chess::enter_Pointer_end(Point &b)
{
    if (!b.EnterPoint("END"))
    {
        return false;
    }

    if (get_Square(b)->getFigure()._name == 'K')
    {
        std::cout << "you can't put the figure on the king :(\n";
        return false;
    }
    if (get_Square(b)->getFigure()._owner == (whoseTurn ? 'w' : 'b'))
    {
        std::cout << "you can't put it on your figure :(\n";
        return false;
    }
    return true;
}
Square *Chess::get_Square(short x, short y)
{
    // std::cout << "get_Square: x " << x << "  y " << y << "\n";
    if (x < 1 || x > 8 || y < 1 || y > 8)
    {
        return nullptr;
    }
    return &Board[x][y];
}
Square *Chess::get_Square(Point p)
{
    // std::cout << "get_Square: x " << x << "  y " << y << "\n";
    if (p._x < 1 || p._x > 8 || p._y < 1 || p._y > 8)
    {
        return nullptr;
    }
    return &Board[p._x][p._y];
}
void Chess::changeChessPieces(Square *EndSq)
{
    if (EndSq->getFigure()._owner == 'w')
    {
        ChessPieceW--;
    }
    else if (EndSq->getFigure()._owner == 'b')
    {
        ChessPieceB--;
    }
}

void Chess::print_board() const
{
    const int N = 9;
    for (int i = 0; i < N; i++)
    {
        if (i == 0)
        {
            for (int j = 0; j < N; ++j)
            {
                if (j == 0)
                {
                    std::cout << "    ";
                }
                else
                {
                    std::cout << char(Board[i][j].getPoint()._y + 'A' - 1) << "   ";
                }
            }
        }
        else
        {
            for (int j = 0; j < N; ++j)
            {
                if (j == 0)
                {
                    std::cout << Board[i][j].getPoint()._x << "   ";
                }
                else
                {
                    std::cout << Board[i][j].getFigure()._owner << Board[i][j].getFigure()._name << "  ";
                }
            }
        }

        std::cout << "\n";
    }
}

void Chess::print_figure_count() const
{
    std::cout << "Figures:      B:" << ChessPieceB << "  |  " << ChessPieceW << ":W"
              << "\n";
}

#endif