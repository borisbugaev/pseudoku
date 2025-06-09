#include <iostream>
#include <fstream>
#include <cstdint>
#include <chrono>

constexpr int SIZE{9};
/*
Program to solve sudoku, using human strategies
"The way the author would solve a sudoku"
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
constexpr int my_square(int locale)
{
    return locale / SIZE;
}

/*
calc row of index
*/
constexpr int my_row(int locale)
{
    return ((locale % SIZE) / 3) + ((locale / SIZE) * 3);
}

/*
calc column of index
*/
constexpr int my_col(int locale)
{
    return (locale % 3) + (locale / 27);
}

/*
calc set of int in given row
*/
uint8_t set_parse_row(uint8_t* board, int row)
{
    uint8_t set_row{0b00000000};
    int row_start{row * 3};
    int row_indices[9]
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
    for (int i = 0; i < SIZE; i++)
    {
        set_row = set_row | board[row_indices[i]];
    }
    return set_row;
}

/*
calc set of int in given column
*/
uint8_t set_parse_col(uint8_t* board, int col)
{
    uint8_t set_col{0b00000000};
    int col_start{col/3 * 24 + col};
    int col_end{SIZE * 3 + col_start};
    for (int i = col_start; i < col_end; i += 3)
    {
        set_col = set_col | (1 << board[i]);
    }
    return set_col;
}

/*
calc set of int in given square
*/
uint8_t set_parse_sqr(uint8_t* board, int sqr)
{
    uint8_t set_sqr{0b00000000};
    int start_sqr{sqr * SIZE};
    int end_sqr{start_sqr + SIZE};
    for (int i = start_sqr; i < end_sqr; i++)
    {
        set_sqr = set_sqr | (1 << board[i]);
    }
    return set_sqr;
}

/*
calc set of int for all columns
*/
uint8_t* all_col_sets(uint8_t* board)
{
    uint8_t* cols{};
    for (int i = 0; i < SIZE; i++)
    {
        cols[i] = set_parse_col(board, i);
    }
    return cols;
}

/*
calc set of int for all rows
*/
uint8_t* all_row_sets(uint8_t* board)
{
    uint8_t* rows{}; 
    for (int i = 0; i < SIZE; i++)
    {
        rows[i] = set_parse_row(board, i);
    }
    return rows;
}

/*
calc set of int for all squares
*/
uint8_t* all_sqr_sets(uint8_t* board)
{
    uint8_t* sqrs{};
    for (int i = 0; i < SIZE; i++)
    {
        sqrs[i] = set_parse_sqr(board, i);
    }
    return sqrs;
}

/*
calc valid values at given index
*/
uint8_t candidates(int locale, uint8_t* board)
{
    uint8_t can{0b11111111};
    return can 
    & ~set_parse_col(board, my_col(locale)) 
    & ~set_parse_row(board, my_row(locale))
    & ~set_parse_sqr(board, my_square(locale));
}

int main(int argc, char** argv)
{
    uint8_t* board[81]{};
    uint8_t* square[SIZE]{};
    uint8_t* row[SIZE]{};
    uint8_t* column[SIZE]{};
    return 0;
}