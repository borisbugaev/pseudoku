#include "sudokonst.h"
#include <fstream>
#include <array>
#include <cstdlib>

/*
intiializer for sudoku boards as 1-d array
TODO:
-flags for file init to change formatting
*/

short candidates(unsigned char locale, 
    std::array<short, konst::bs> board);
std::string board_line(
    std::array<short, konst::bs> b,
    unsigned short f, 
    char flag);
std::array<short, konst::bs> prune(
    std::array<short, konst::bs> c);
/*
init board from file
*/
std::array<short, konst::bs> init_from_file(std::string filename)
{
    std::ifstream file{filename};
    std::array<short, konst::bs> board{};
    char l{};
    short iterator{0};
    while (file.get(l) && iterator < konst::bs)
    {
        if ('0' <= l && l <= '9')
        {
            board[iterator] = 0x0 - std::abs((short)(l - '0'));
            iterator++;
        }
    }
    file.close();
    return board;
}

std::array<short, konst::bs> board_import(
    std::string filename)
{
    std::ifstream file{filename};
    std::array<short, konst::bs> board{};
    char l{};
    short iterator{0};
    while (file.get(l) && iterator < konst::bs)
    {
        if ('0' <= l && l <= '9')
        {
            board[tra::nsform.at(iterator)] = 0x0 - std::abs((short)(l - '0'));
            iterator++;
        }
    }
    file.close();
    return board;
}

/*
init blank board;
*/
std::array<short, konst::bs> init_blank()
{
    std::array<short, konst::bs> board{};
    for (short i = 0; i < konst::bs; i++)
    {
        board[i] = 0;
    }
    return board;
}

std::array<short, konst::bs> initialize_candidates(
    std::array<short, konst::bs> board)
{
    for (short i = 0; i < konst::bs; i++)
    {
        if (board[i] == 0)
        {
            board[i] = 0x1ff;
        }
    }
    return board;
}
/*
generate candidate board
*/
std::array<short, konst::bs> set_can(
    std::array<short, konst::bs> board)
{
    for (short i = 0; i < konst::bs; i++)
    {
        if (board[i] >= 0)
        {
            board[i] = candidates(i, board);
        }
    }
    board = prune(board);
    return board;
}

short board_export(
    std::array<short, konst::bs> board,
    std::string filename)
{
    std::ofstream file{filename};
    for (short f = 0; f < konst::sb; f+=3)
    {
        if (f/konst::sz != 0 && f%konst::sz == 0)
        {
            file << pseud::sqr_x_brdr << '\n';
        }
        file << board_line(board, f, 'n');
    }
    return 0;
}

std::array<short, konst::bs> board_transformation(
    std::array<short, konst::bs> b)
{
    std::array<short, konst::bs> b_transformat{};
    for (short ion = 0; ion < konst::bs; ion++)
    {
        b_transformat[ion] = b[tra::nsform.at(ion)];
    }
    return b_transformat;
}