#pragma once
#include "sudokonst.h"
#include <array>
#include <iostream>
#include <chrono>

/*
functions to be used in sudoku evaluation
*/

std::array<unsigned short, konst::bs> init_can(
    std::array<unsigned short, konst::bs> board
);

/*
corrects for rows
*/
short get_row_pos(
    short row_id,
    short index)
{
    switch (index)
    {
        case 0:
        {
            return row_id;
            break;
        }
        case 1:
        {
            return row_id + 1;
            break;
        }
        case 2:
        {
            return row_id + 2;
            break;
        }
        case 3:
        {
            return row_id + konst::sb;
            break;
        }
        case 4:
        {
            return row_id + konst::sb + 1;
            break;
        }
        case 5:
        {
            return row_id + konst::sb + 2;
            break;
        }
        case 6:
        {
            return row_id + konst:: sb * 2;
            break;
        }
        case 7:
        {
            return row_id + konst::sb * 2 + 1;
            break;
        }
        case 8:
        {
            return row_id + konst::sb * 2 + 2;
            break;
        }
        default:
        {
            return row_id;
            break;
        }
    }
}

/*
returns actual value represented in candidates when ==1
*/
short equiv(unsigned short c)
{
    return ((0x100 & c)/0x100) * 9
    + ((0x80 & c)/0x80) * 8
    + ((0x40 & c)/0x40) * 7
    + ((0x20 & c)/0x20) * 6
    + ((0x10 & c)/0x10) * 5
    + ((0x08 & c)/0x08) * 4
    + ((0x04 & c)/0x04) * 3
    + ((0x02 & c)/0x02) * 2
    + (0x01 & c);
}

bool blank_check(
    std::array<unsigned short, konst::bs> b)
{
    for (short i = 0; i < konst::bs; i++)
    {
        if (b[i] == 0)
        {
            return true;
        }
    }
    return false;
}

/*
returns index of first square where there is ==1 candidate
if none, returns -1
*/
short find_solo(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    for (short i = 0; i < konst::bs; i++)
    {
        if ((c[i] & (c[i] - 1)) == 0 && b[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

std::array<short, 0x2> row_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    short row_set{0x0};
    for (short i = 0; i < konst::sb; i+=3)
    {
        for (short j = 0; j < konst::sz; j++)
        {
            row_set ^= c[get_row_pos(i, j)];
        }
        if ((row_set & (row_set - 1)) == 0)
        {
            return {row_set, i};
        }
    }
    return {0x5, 0x5};
}

std::array<short, 0x2> col_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    short col_set{0x0};
    short j{};
    for (short i = 0; i < konst::sz; i++)
    {
        j = get_row_pos(0, i);
        for (short k = j; k < (konst::sb + j); k+=3)
        {
            col_set ^= c[k];
        }
        if ((col_set & (col_set - 1)) == 0)
        {
            return {col_set, j};
        }
    }
    return {0x5, 0x5};
}

std::array<unsigned short, konst::bs> try_solo_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    short index = find_solo(b, c);
    while (index != -1)
    {
        short value = equiv(c[index]);
        b[index] = value;
        c = init_can(b);
        index = find_solo(b, c);
    }

    return b;
}

std::array<unsigned short, konst::bs> try_row_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    std::array<short, 0x2> value = row_find(b, c);
    while (value[0] != 0x5)
    {
        for (short i = 0; i < konst::sz; i++)
        {
            if ((value[0] & c[get_row_pos(value[1], i)]) != 0)
            {
                b[get_row_pos(value[1], i)] = equiv(value[0]);
            }
        }
        c = init_can(b);
        value = row_find(b, c);
    }
    return b;
}

std::array<unsigned short, konst::bs> try_col_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    std::array<short, 0x2> value = col_find(b, c);
    while (value[0] != 0x5)
    {
        for (short i = value[1]; i < (value[1] + konst::sb); i+=3)
        {
            if ((value[0] & c[i]) != 0)
            {
                b[i] = equiv(c[value[0]]);
            }
        }
        c = init_can(b);
        value = col_find(b, c);
    }
    return b;
}

std::array<unsigned short, konst::bs> solve_board(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    auto start = std::chrono::steady_clock::now();
    short counter{0};
    bool blank{blank_check(b)};
    std::array<unsigned short, konst::bs> temp_b;
    while (blank == true)
    {
        temp_b = try_solo_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);
        }
        temp_b = try_row_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);
        }
        temp_b = try_col_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);
        }
        blank = blank_check(b);
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "inserted " << counter << " values to board ";
    std::cout << "in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us\n";
    return b;
}