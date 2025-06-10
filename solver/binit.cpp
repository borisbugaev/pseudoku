#include "sudokonst.h"
#include <fstream>
#include <array>

/*
intiializer for sudoku boards as 1-d array
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

std::array<unsigned short, konst::bs> init_blank()
{
    std::array<unsigned short, konst::bs> board{};
    for (unsigned char i = 0; i < konst::bs; i++)
    {
        board[i] = 0;
    }
    return board;
}