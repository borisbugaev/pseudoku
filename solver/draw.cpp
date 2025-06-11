#pragma once
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

/*
single line of board
*/
std::string board_line(
    std::array<unsigned short, konst::bs> b,
    unsigned short f, 
    char flag)
{
    std::string my_line{std::to_string(b[f]) 
        + ' '
        + std::to_string(b[f + 1])
        + ' '
        + std::to_string(b[f + 2])
        + ' ' + '|' + ' '
        + std::to_string(b[f + konst::sb])
        + ' '
        + std::to_string(b[f + konst::sb + 1])
        + ' '
        + std::to_string(b[f + konst::sb + 2])
        + ' ' + '|' + ' '
        + std::to_string(b[f + konst::sb * 2])
        + ' '
        + std::to_string(b[f + konst::sb * 2 + 1])
        + ' '
        + std::to_string(b[f + konst::sb * 2 + 2])
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
            const char i_c{(char)(f/3 + 'a')};
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
void draw_candidates(unsigned short candidat)
{
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
void draw_board(std::array<unsigned short, konst::bs> b)
{
    for (unsigned short f = 0; f < konst::sb; f+=3)
    {
        if (f/konst::sz != 0 && f%konst::sz == 0)
        {
            std::cout << pseud::sqr_x_brdr << '\n';
        }
        std::cout << board_line(b, f, 'n');
    }
}

/*
draw algebraic notation reference next to the board
*/
void draw_boardref(std::array<unsigned short, konst::bs> b)
{
    std::cout << "  9 8 7   6 5 4   3 2 1\n";
    std::cout << board_line(b, 0, 'a');
    std::cout << board_line(b, 3, 'a');
    std::cout << board_line(b, 6, 'a');
    std::cout << "  " << pseud::sqr_x_brdr << '\n';
    std::cout << board_line(b, 9, 'a');
    std::cout << board_line(b, 12, 'a');
    std::cout << board_line(b, 15, 'a');
    std::cout << "  " << pseud::sqr_x_brdr << '\n';
    std::cout << board_line(b, 18, 'a');
    std::cout << board_line(b, 21, 'a');
    std::cout << board_line(b, 24, 'a');
    std::cout << "  9 8 7   6 5 4   3 2 1\n";
}