#include "sudokonst.h"
#include <array>
#include <cstdlib>

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
    return ((locale % konst::sz) / konst::rt_sz) + offset_f * konst::rt_sz;
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
    return locale % konst::rt_sz + offset_f * konst::rt_sz;
}

/*
calc set of int in given row
*/
short set_parse_row(std::array<short, konst::sqr_sz> board, 
    unsigned char row)
{
    short set_row{0x0};
    long row_start{row * konst::rt_sz};
    long row_indices[konst::sz]
    {   
        row_start,
        row_start + 1,
        row_start + 2,
        row_start + konst::th_sz,
        row_start + konst::th_sz + 1,
        row_start + konst::th_sz + 2,
        row_start + konst::th_sz * 2,
        row_start + konst::th_sz * 2 + 1,
        row_start + konst::th_sz * 2 + 2};
    for (short i = 0; i < konst::sz; ++i)
    {
        short board_item{static_cast<short>(board[row_indices[i]] < 0 ? std::abs(board[row_indices[i]]) : 0)};
        set_row |= (1 << (board_item - 1));
    }
    return set_row;
}

/*
calc set of int in given column
*/
short set_parse_col(std::array<short, konst::sqr_sz> board, 
    unsigned char col)
{
    short set_col{0x0};
    long col_start{col/konst::rt_sz * 24 + col};
    long col_end{konst::sz * konst::rt_sz + col_start};
    for (long i = col_start; i < col_end; i += konst::rt_sz)
    {
        short board_item{static_cast<short>(board[i] < 0 ? std::abs(board[i]) : 0)};
        set_col |= (1 << (board_item - 1));
    }
    return set_col;
}

/*
calc set of int in given square
*/
short set_parse_sqr(std::array<short, konst::sqr_sz> board, 
    unsigned char sqr)
{
    short set_sqr{0x0};
    long start_sqr{sqr * konst::sz};
    long end_sqr{start_sqr + konst::sz};
    for (long i = start_sqr; i < end_sqr; ++i)
    {
        short board_item{static_cast<short>(board[i] < 0 ? std::abs(board[i]) : 0)};
        set_sqr |= (1 << (board_item - 1));
    }
    return set_sqr;
}

/*
calc valid values at given index
*/
short candidates(unsigned char locale, 
    std::array<short, konst::sqr_sz> board)
{
    short can{board[locale]};
    return can 
    & ~set_parse_col(board, my_col(locale)) 
    & ~set_parse_row(board, my_row(locale))
    & ~set_parse_sqr(board, my_square(locale));
}