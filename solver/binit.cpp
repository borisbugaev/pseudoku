#include "sudokonst.h"
#include <fstream>
#include <array>

/*
intiializer for sudoku boards as 1-d array
TODO:
-flags for file init to change formatting
*/

unsigned short candidates(unsigned char locale, 
    std::array<unsigned short, konst::bs> board,
    std::array<unsigned short, konst::bs> c_board);
std::string board_line(
    std::array<unsigned short, konst::bs> b,
    unsigned short f, 
    char flag);
std::array<unsigned short, konst::bs> prune(
    std::array<unsigned short, konst::bs> c);
/*
init board from file
*/
std::array<unsigned short, konst::bs> init_from_file(std::string filename)
{
    std::ifstream file{filename};
    std::array<unsigned short, konst::bs> board{};
    char l{};
    short iterator{0};
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

std::array<unsigned short, konst::bs> board_import(
    std::string filename)
{
    std::ifstream file{filename};
    std::array<unsigned short, konst::bs> board{};
    char l{};
    short iterator{0};
    while (file.get(l) && iterator < konst::bs)
    {
        if ('0' <= l && l <= '9')
        {
            board[tra::nsform.at(iterator)] = (unsigned short)(l - '0');
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
    for (short i = 0; i < konst::bs; i++)
    {
        board[i] = 0;
    }
    return board;
}

std::array<unsigned short, konst::bs> initialize_cb(
    std::array<unsigned short, konst::bs> c_board)
{
    for (short i = 0; i < konst::bs; i++)
    {
        c_board[i] = 0x1ff;
    }
    return c_board;
}
/*
generate candidate board
*/
std::array<unsigned short, konst::bs> set_can(
    std::array<unsigned short, konst::bs> board,
    std::array<unsigned short, konst::bs> c_board
)
{
    for (short i = 0; i < konst::bs; i++)
    {
        if (board[i] == 0)
        {
            c_board[i] = candidates(i, board, c_board);
        }
        else
        {
            c_board[i] = 0;
        }
    }
    c_board = prune(c_board);
    return c_board;
}

short board_export(
    std::array<unsigned short, konst::bs> board,
    std::string filename)
{
    std::ofstream file{filename};
    for (unsigned short f = 0; f < konst::sb; f+=3)
    {
        if (f/konst::sz != 0 && f%konst::sz == 0)
        {
            file << pseud::sqr_x_brdr << '\n';
        }
        file << board_line(board, f, 'n');
    }
    return 0;
}

std::array<unsigned short, konst::bs> board_transformation(
    std::array<unsigned short, konst::bs> b)
{
    std::array<unsigned short, konst::bs> b_transformat{};
    for (short ion = 0; ion < konst::bs; ion++)
    {
        b_transformat[ion] = b[tra::nsform.at(ion)];
    }
    return b_transformat;
}