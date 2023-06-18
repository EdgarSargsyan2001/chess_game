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
    bool where_can_figure_go(const Point &pos);
    bool where_can_move_Pawn(const Point &pos);   // Զինվոր
    bool where_can_move_Bishop(const Point &pos); // Փիղ
    void change_chess_piece_count(const Figure &f);
    void clear_possible_moves();
    bool check_square(Square *sq, int &c);

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
    while (!enter_Pointer_start(aPoint)) // enter start point
    {
    }

    print_board(); // print possible moves

    Point bPoint;
    while (!enter_Pointer_end(bPoint)) // // enter start point
    {
    }
    clear_possible_moves(); // clear_possible_moves

    Figure figEnd = get_Square(bPoint)->getFigure(); // change_chess_piece_count
    change_chess_piece_count(figEnd);

    // change figures a->b
    Figure figStart = get_Square(aPoint)->getFigure();
    if ((bPoint._x == 1 || bPoint._x == 8) && figStart._name == 'P')
    {
        figStart._name = 'Q';
    }

    get_Square(bPoint)->setFigure(figStart);
    get_Square(aPoint)->setFigure({':', ':'});

    // change turn
    whoseTurn = !whoseTurn;
    return true;
}

bool Chess::where_can_figure_go(const Point &pos)
{
    switch (get_Square(pos)->getFigure()._name)
    {
    case 'P':
        return where_can_move_Pawn(pos);
    case 'B':
        return where_can_move_Bishop(pos);
    default:
        return 0;
    }
}

bool Chess::where_can_move_Pawn(const Point &pos)
{
    int possiblePlaces = 0;

    for (int i = 1; i <= ((pos._x == 2 || pos._x == 7) ? 2 : 1); ++i)
    {
        Square *sq = get_Square(pos._x + (whoseTurn ? -i : i), pos._y);
        if (!sq || sq->getFigure()._name != ':')
        {
            break;
        }
        possiblePlaces++;
        sq->setFigure({'X', ':'});
    }

    int arr[2] = {1, -1};
    for (int i = 0; i < 2; ++i)
    {
        Square *sq = get_Square(pos._x + (whoseTurn ? -1 : 1), (pos._y + arr[i]));
        if (sq)
        {
            Figure fig = sq->getFigure();
            if (fig._owner == (whoseTurn ? 'b' : 'w') && fig._name != 'K')
            {
                possiblePlaces++;
                sq->setFigure({'X', fig._name});
            }
        }
    }
    return possiblePlaces;
}

bool Chess::where_can_move_Bishop(const Point &pos) // Փիղ
{
    int possiblePlaces = 0;
    const int N = 9;

    for (int i = pos._x - 1, j = pos._y - 1; i >= 1 && j >= 1; --i, --j)
    {
        Square *sq = get_Square(i, j);
        if (!check_square(sq, possiblePlaces))
        {
            break;
        }
    }
    for (int i = pos._x + 1, j = pos._y + 1; i < N && j < N; ++i, ++j)
    {
        Square *sq = get_Square(i, j);
        if (!check_square(sq, possiblePlaces))
        {
            break;
        }
    }
    for (int i = pos._x + 1, j = pos._y - 1; i < N && j >= 1; ++i, --j)
    {
        Square *sq = get_Square(i, j);
        if (!check_square(sq, possiblePlaces))
        {
            break;
        }
    }
    for (int i = pos._x - 1, j = pos._y + 1; i >= 1 && j < N; --i, ++j)
    {
        Square *sq = get_Square(i, j);
        if (!check_square(sq, possiblePlaces))
        {
            break;
        }
    }

    return possiblePlaces;
}

bool Chess::check_square(Square *sq, int &c)
{
    if (sq)
    {
        Figure f = sq->getFigure();
        if (f._name == 'K')
        {
            return 0;
        }
        if (f._owner == ':')
        {
            sq->setFigure({'X', ':'});
            c++;
        }
        else
        {
            if (f._owner == (whoseTurn ? 'b' : 'w'))
            {
                sq->setFigure({'X', f._name});
                c++;
            }
            return 0;
        }
    }
    return true;
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
    if (!where_can_figure_go(a))
    {
        std::cout << "that figure cannot move :(\n";
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

    if (get_Square(b)->getFigure()._owner != 'X')
    {
        std::cout << "that figure can't go there :(\n";
        return false;
    }
    return true;
}
Square *Chess::get_Square(short x, short y)
{
    if (x < 1 || x > 8 || y < 1 || y > 8)
    {
        return nullptr;
    }
    return &Board[x][y];
}
Square *Chess::get_Square(Point p)
{
    if (p._x < 1 || p._x > 8 || p._y < 1 || p._y > 8)
    {
        return nullptr;
    }
    return &Board[p._x][p._y];
}
void Chess::clear_possible_moves()
{
    const int N = 8;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            Figure f = Board[i][j].getFigure();
            if (f._owner == 'X')
            {
                if (f._name == ':')
                {
                    Board[i][j].setFigure({':', ':'});
                }
                else
                {
                    Board[i][j].setFigure({(whoseTurn ? 'b' : 'w'), f._name});
                }
            }
        }
    }
}

void Chess::change_chess_piece_count(const Figure &f)
{
    if (f._owner == 'w')
    {
        ChessPieceW--;
    }
    else if (f._owner == 'b')
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
                    Figure f = Board[i][j].getFigure();
                    if (f._owner == (whoseTurn ? 'w' : 'b'))
                    {
                        std::cout << (char)(f._owner - 32);
                    }
                    else
                    {
                        std::cout << f._owner;
                    }
                    std::cout << f._name << "  ";
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