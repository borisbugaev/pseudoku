#pragma once
#include "sudokonst.h"
#include <array>
#include <iostream>
#include <chrono>

/*
functions to be used in sudoku evaluation
TODO: square set eval, set striking
*/


    std::array<unsigned short, konst::bs> init_can(
        std::array<unsigned short, konst::bs> board);
    void draw_board(std::array<unsigned short, konst::bs> b);


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

short high_bit_count(
    unsigned short bit_map)
{
    short counter{0x0};
    for (short i = 0x0; i < 0x10; i++)
    {
        counter += 0x1 & (bit_map >> i);
    }
    return counter;
}

short get_1st_mapped_short(
    unsigned short bit_map)
{
    if (bit_map & 0x1)
    {
        return 0x1;
    }
    else if (bit_map & 0x2)
    {
        return 0x2;
    }
    else if (bit_map & 0x4)
    {
        return 0x4;
    }
    else if (bit_map & 0x8)
    {
        return 0x8;
    }
    else if (bit_map & 0x10)
    {
        return 0x10;
    }
    else if (bit_map & 0x20)
    {
        return 0x20;
    }
    else if (bit_map & 0x40)
    {
        return 0x40;
    }
    else if (bit_map & 0x80)
    {
        return 0x80;
    }
    else if (bit_map & 0x100)
    {
        return 0x100;
    }
    else
    {
        return 0x0;
    }
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

unsigned short s_sqr_set(
    std::array<unsigned short, konst::bs> c,
    short sqr_start)
{
    short s{0x0};
    short sqr_set{0x0};
    for (short i = sqr_start; i < (sqr_start + konst::sz); i++)
    {
        if ((sqr_set & c[i]) != 0)
        {
            s |= (sqr_set & c[i]);
        }
        sqr_set ^= c[i];
    }
    sqr_set &= ~(sqr_set & s);
    return sqr_set;
}

std::array<short, 0x2> sqr_find(
    std::array<unsigned short, konst::bs> c)
{
    short sqr_set{0x0};
    for (short i = 0; i < konst::bs; i+=9)
    {
        sqr_set = s_sqr_set(c, i);
        if (sqr_set != 0)
        {
            if ((sqr_set & (sqr_set - 1)) == 0)
            {
                return {sqr_set, i};
            }
            else
            {
                return {get_1st_mapped_short(sqr_set), i};
            }
        }
        sqr_set = 0x0;
    }
    return {0x5, 0x5};
}

unsigned short s_row_set(
    std::array<unsigned short, konst::bs> c,
    short row_start)
{
    short s{0x0};
    short row_set{0x0};
    for (short i = 0; i < konst::sz; i++)
    {
        short j = get_row_pos(row_start, i);
        if ((row_set & c[j]) != 0)
        {
            s |= (row_set & c[j]);
        }
        row_set ^= c[j];
    }
    row_set &= ~(row_set & s);
    return row_set;
}

std::array<short, 0x2> row_find(
    std::array<unsigned short, konst::bs> c)
{
    short row_set{0x0};
    for (short i = 0; i < konst::sb; i+=3)
    {
        row_set = s_row_set(c, i);
        if (row_set != 0)
        {    
            if ((row_set & (row_set - 1)) == 0)
            {
                return {row_set, i};
            }
            else
            {
                return {get_1st_mapped_short(row_set), i};
            }
        }
        row_set = 0x0;
    }
    return {0x5, 0x5};
}

unsigned short s_col_set(
    std::array<unsigned short, konst::bs> c,
    short col_start)
{
    short s{0x0};
    short col_set{0x0};
    for (short i = col_start; i < (konst::sb + col_start); i+=3)
    {
        if ((col_set & c[i]) != 0)
        {
            s |= (col_set & c[i]);
        }
        col_set ^= c[i];
    }
    col_set &= ~(col_set & s);
    return col_set;
}

std::array<short, 0x2> col_find(
    std::array<unsigned short, konst::bs> c)
{
    short col_set{0x0};
    short j{};
    for (short i = 0; i < konst::sz; i++)
    {
        j = get_row_pos(0, i);
        col_set = s_col_set(c, j);
        if (col_set != 0)
        {
            if ((col_set & (col_set - 1)) == 0)
            {
                return {col_set, j};
            }
            else
            {
                return {get_1st_mapped_short(col_set), j};
            }
        }
        col_set = 0x0;
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
    if (!blank_check(b))
    {
        return b;
    }
    std::array<short, 0x2> value = row_find(c);
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
        value = row_find(c);
    }
    return b;
}

std::array<unsigned short, konst::bs> try_col_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    if (!blank_check(b))
    {
        return b;
    }
    std::array<short, 0x2> value = col_find(c);
    while (value[0] != 0x5)
    {
        for (short i = value[1]; i < (value[1] + konst::sb); i+=3)
        {
            if ((value[0] & c[i]) != 0)
            {
                b[i] = equiv(value[0]);
            }
        }
        c = init_can(b);
        value = col_find(c);
    }
    return b;
}

std::array<unsigned short, konst::bs> try_sqr_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    if (!blank_check(b))
    {
        return b;
    }
    std::array<short, 0x2> value = sqr_find(c);
    while (value[0] != 0x5)
    {
        for (short i = value[1]; i < (value[1] + konst::sz); i++)
        {
            if ((value[0] & c[i]) != 0)
            {
                b[i] = equiv(value[0]);
            }
        }
        c = init_can(b);
        value = sqr_find(c);
    }
    return b;
}

std::array<unsigned short, konst::bs> solve_board(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    auto start = std::chrono::steady_clock::now();
    short counter{0};
    short c_i{0};
    bool blank{blank_check(b)};
    std::array<unsigned short, konst::bs> temp_b;
    while (blank == true)
    {
        c_i = counter;
        temp_b = try_solo_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);

        }
        blank = blank_check(b);
        temp_b = try_row_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);
        }
        blank = blank_check(b);
        temp_b = try_col_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);
        }
        blank = blank_check(b);
        temp_b = try_sqr_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);
        }
        if (counter == c_i)
        {
            blank = false;
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "inserted ";
    std::cout << "in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us\n";
    return b;
}