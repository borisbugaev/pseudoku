#pragma once
#include "sudokonst.h"
#include <array>

/*
Functions for board-set-parsing re: sudoku
TODO:
--get rid of the inelegant switch statements
--general cleaning
*/

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
        row_start + 27,
        row_start + 27 + 1,
        row_start + 27 + 2,
        row_start + 27 + 27,
        row_start + 27 + 27 + 1,
        row_start + 27 + 27 + 2};
    for (unsigned char i = 0; i < konst::sz; i++)
    {
        set_row = set_row | (1 << (board[row_indices[i]] - 1));
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
        set_col = set_col | (1 << (board[i] - 1));
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
        set_sqr = set_sqr | (1 << (board[i] - 1));
    }
    return set_sqr;
}

/*
calc set of int for all columns
*/
std::array<unsigned short, konst::bs> all_col_sets(
    std::array<unsigned short, konst::bs> board)
{
    std::array<unsigned short, konst::bs> cols{};
    for (unsigned char i = 0; i < konst::sz; i++)
    {
        cols[i] = set_parse_col(board, i);
    }
    return cols;
}

/*
calc set of int for all rows
*/
std::array<unsigned short, konst::bs> all_row_sets(
    std::array<unsigned short, konst::bs> board)
{
    std::array<unsigned short, konst::bs> rows{}; 
    for (unsigned char i = 0; i < konst::sz; i++)
    {
        rows[i] = set_parse_row(board, i);
    }
    return rows;
}

/*
calc set of int for all squares
*/
std::array<unsigned short, konst::bs> all_sqr_sets(
    std::array<unsigned short, konst::bs> board)
{
    std::array<unsigned short, konst::bs> sqrs{};
    for (unsigned char i = 0; i < konst::sz; i++)
    {
        sqrs[i] = set_parse_sqr(board, i);
    }
    return sqrs;
}

/*
calc valid values at given index
*/
unsigned short candidates(unsigned char locale, 
    std::array<unsigned short, konst::bs> board)
{
    unsigned short can{0x1ff};
    return can 
    & ~set_parse_col(board, my_col(locale)) 
    & ~set_parse_row(board, my_row(locale))
    & ~set_parse_sqr(board, my_square(locale));
}