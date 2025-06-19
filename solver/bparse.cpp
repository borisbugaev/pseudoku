#include "sudokonst.h"
#include <array>

/*
Functions for board-set-parsing re: sudoku
TODO:
--get rid of the inelegant switch statements
--general cleaning
*/

/*
calc square of given index
*/
constexpr unsigned char my_square(unsigned char locale)
{
    return locale / konst::sz;
}

/*
calc row of index
*/
constexpr unsigned char my_row(unsigned char locale)
{
    unsigned char offset_f{0};
    switch (my_square(locale))
    {
        case 1:
        case 4:
        case 7:
        {
            offset_f = 1;
            break;
        }
        case 2:
        case 5:
        case 8:
        {
            offset_f = 2;
        }
        default:
            break;
    }
    return ((locale % konst::sz) / 3) + offset_f * 3;
}

/*
calc column of index
*/
constexpr unsigned char my_col(unsigned char locale)
{
    unsigned char offset_f{0};
    switch (my_square(locale))
    {
        case 3:
        case 4:
        case 5:
        {
            offset_f = 1;
            break;
        }
        case 6:
        case 7:
        case 8:
        {
            offset_f = 2;
            break;
        }
        default:
            break;
    }
    return locale % 3 + offset_f * 3;
}

/*
calc set of int in given row
*/
unsigned short set_parse_row(std::array<unsigned short, konst::bs> board, 
    unsigned char row)
{
    unsigned short set_row{0x0};
    long row_start{row * 3};
    long row_indices[konst::sz]
    {   
        row_start,
        row_start + 1,
        row_start + 2,
        row_start + konst::sb,
        row_start + konst::sb + 1,
        row_start + konst::sb + 2,
        row_start + konst::sb * 2,
        row_start + konst::sb * 2 + 1,
        row_start + konst::sb * 2 + 2};
    for (short i = 0; i < konst::sz; i++)
    {
        set_row |= (1 << (board[row_indices[i]] - 1));
    }
    return set_row;
}

/*
calc set of int in given column
*/
unsigned short set_parse_col(std::array<unsigned short, konst::bs> board, 
    unsigned char col)
{
    unsigned short set_col{0x0};
    long col_start{col/3 * 24 + col};
    long col_end{konst::sz * 3 + col_start};
    for (long i = col_start; i < col_end; i += 3)
    {
        set_col |= (1 << (board[i] - 1));
    }
    return set_col;
}

/*
calc set of int in given square
*/
unsigned short set_parse_sqr(std::array<unsigned short, konst::bs> board, 
    unsigned char sqr)
{
    unsigned short set_sqr{0x0};
    long start_sqr{sqr * konst::sz};
    long end_sqr{start_sqr + konst::sz};
    for (long i = start_sqr; i < end_sqr; i++)
    {
        set_sqr |= (1 << (board[i] - 1));
    }
    return set_sqr;
}

/*
calc valid values at given index
*/
unsigned short candidates(unsigned char locale, 
    std::array<unsigned short, konst::bs> board,
    std::array<unsigned short, konst::bs> c_board)
{
    unsigned short can{c_board[locale]};
    return can 
    & ~set_parse_col(board, my_col(locale)) 
    & ~set_parse_row(board, my_row(locale))
    & ~set_parse_sqr(board, my_square(locale));
}