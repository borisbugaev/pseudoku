#include "sudokonst.h"
#include <string>
#include <array>
#include <iostream>

/*
reference board:
00 01 02 | 27 28 29 | 54 55 56
03 04 05 | 30 31 32 | 57 58 59
06 07 08 | 33 34 35 | 60 61 62
---------x----------x---------
09 10 11 | 36 37 38 | 63 64 65
12 13 14 | 39 40 41 | 66 67 68
15 16 17 | 42 43 44 | 69 70 71
---------x----------x---------
18 19 20 | 45 46 47 | 72 73 74
21 22 23 | 48 49 50 | 75 76 77
24 25 26 | 51 52 53 | 78 79 80
*/

void draw_help_dialog()
{
    std::cout << "COMMANDS:\n"
    << '>' << komm::usr_draw <<'\n'
    << "draw the current board\n"
    << '>' << komm::usr_ref << '\n'
    << "draw board with algebraic notation for reference\n"
    << '>' << komm::usr_srch << '\n'
    << "search for candidates at given index\n"
    << '>' << komm::usr_bimp << '\n'
    << "import a board from a file\n"
    << '>' << komm::usr_insr << '\n'
    << "insert a value at a given index\n"
    << '>' << komm::usr_fin << '\n'
    << "solve current board\n"
    << '>' << komm::usr_next << '\n'
    << "solve next value\n"
    << '>' << komm::usr_exit << '\n'
    << "exit\n";
}

std::string value_str(
    short value)
{
    std::string my_value{};
    short my_s_value = value < 0 ? -value : 0;
    if (my_s_value)
    {
        my_value = std::to_string(my_s_value);
    }
    else
    {
        my_value = "_";
    }
    return my_value;
}

/*
single line of board
*/
std::string board_line(
    std::array<short, konst::sqr_sz> board,
    unsigned short index, 
    char flag)
{
    std::string my_line{value_str(board[index]) 
        + ' '
        + value_str(board[index + 1])
        + ' '
        + value_str(board[index + 2])
        + ' ' + '|' + ' '
        + value_str(board[index + konst::th_sz])
        + ' '
        + value_str(board[index + konst::th_sz + 1])
        + ' '
        + value_str(board[index + konst::th_sz + 2])
        + ' ' + '|' + ' '
        + value_str(board[index + konst::th_sz * 2])
        + ' '
        + value_str(board[index + konst::th_sz * 2 + 1])
        + ' '
        + value_str(board[index + konst::th_sz * 2 + 2])
    };
    switch (flag)
    {
        case 'n':
        {
            my_line.append(1, '\n');
            break;
        }
        case 'a':
        {
            const char i_c{(char)(index/3 + 'a')};
            my_line.insert(0, 1, '|');
            my_line.insert(0, 1, i_c);
            my_line.append(1, '|');
            my_line.append(1, i_c);
            my_line.append(1, '\n');
            break;
        }
        default:
        {
            break;
        }
    }
    return my_line;
}

/*
draw data represented in candidate register
*/
void draw_candidates(short candidat)
{
    if (candidat < 0)
    {
        return;
    }
    if (candidat & 0x100)
    {
        std::cout << '9' << ' ';
    }
    if (candidat & 0x80)
    {
        std::cout << '8' << ' ';
    }
    if (candidat & 0x40)
    {
        std::cout << '7' << ' ';
    }
    if (candidat & 0x20)
    {
        std::cout << '6' << ' ';
    }
    if (candidat & 0x10)
    {
        std::cout << '5' << ' ';
    }
    if (candidat & 0x8)
    {
        std::cout << '4' << ' ';
    }
    if (candidat & 0x4)
    {
        std::cout << '3' << ' ';
    }
    if (candidat & 0x2)
    {
        std::cout << '2' << ' ';
    }
    if (candidat & 0x1)
    {
        std::cout << '1' << ' ';
    }
    std::cout << '\n';
}

/*
draw board as it should appear
*/
void draw_board(std::array<short, konst::sqr_sz> board)
{
    for (unsigned short f = 0; f < konst::th_sz; f += konst::rt_sz)
    {
        if (f / konst::sz != 0 && f % konst::sz == 0)
        {
            std::cout << pseud::sqr_x_brdr << '\n';
        }
        std::cout << board_line(board, f, 'n');
    }
}

void draw_cboard(std::array<short, konst::sqr_sz> board)
{
    for (unsigned short f = 0; f < konst::th_sz; f += konst::rt_sz)
    {
        if (f / konst::sz != 0 && f % konst::sz == 0)
        {
            std::cout << pseud::sqr_x_brdr << '\n';
        }
        std::cout << board_line(board, f, 'n');
    }
}

/*
draw algebraic notation reference next to the board
*/
void draw_boardref(std::array<short, konst::sqr_sz> board)
{
    std::cout << "  9 8 7   6 5 4   3 2 1\n";
    std::cout << board_line(board, 0, 'a');
    std::cout << board_line(board, 3, 'a');
    std::cout << board_line(board, 6, 'a');
    std::cout << "  " << pseud::sqr_x_brdr << '\n';
    std::cout << board_line(board, 9, 'a');
    std::cout << board_line(board, 12, 'a');
    std::cout << board_line(board, 15, 'a');
    std::cout << "  " << pseud::sqr_x_brdr << '\n';
    std::cout << board_line(board, 18, 'a');
    std::cout << board_line(board, 21, 'a');
    std::cout << board_line(board, 24, 'a');
    std::cout << "  9 8 7   6 5 4   3 2 1\n";
}