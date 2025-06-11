#pragma once
#include "sudokonst.h"
#include <fstream>
#include <array>

/*
intiializer for sudoku boards as 1-d array
TODO:
-flags for file init to change formatting
*/

unsigned short candidates(unsigned char locale, 
    std::array<unsigned short, konst::bs> board);

/*
init board from file
*/
std::array<unsigned short, konst::bs> init_from_file(std::string filename)
{
    std::ifstream file{filename};
    std::array<unsigned short, konst::bs> board{};
    char l{};
    unsigned char iterator{0};
    while (file.get(l) && iterator < konst::bs)
    {
        if ('0' <= l && l <= '9')
        {
            board[iterator] = (unsigned short)(l - '0');
            iterator++;
        }
    }
    file.close();
    return board;
}

/*
init blank board;
*/
std::array<unsigned short, konst::bs> init_blank()
{
    std::array<unsigned short, konst::bs> board{};
    for (unsigned char i = 0; i < konst::bs; i++)
    {
        board[i] = 0;
    }
    return board;
}

/*
generate candidate board
*/
std::array<unsigned short, konst::bs> init_can(
    std::array<unsigned short, konst::bs> board
)
{
    std::array<unsigned short, konst::bs> c_board{};
    for (unsigned char i = 0; i < konst::bs; i++)
    {
        c_board[i] = candidates(i, board);
        if (board[i] != 0)
        {
            c_board[i] = 0;
        }
    }
    return c_board;
}