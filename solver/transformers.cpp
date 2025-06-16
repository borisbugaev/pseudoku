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
const short grp(
    const short row_id,
    const short index)
{
    short id{row_id};
    id += index % 0x3;
    id += (index >= 0x3) ? konst::sb : 0;
    id += (index >= 0x6) ? konst::sb : 0;
    return id;
}

/*
returns actual value represented in candidates when ==1
*/
constexpr short equiv(unsigned short c)
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
    for (short i = 0x1; i < 0x200; i = i << 1)
    {
        if (bit_map & i)
        {
            return i;
        }
    }
    return 0x0;
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

unsigned short set_xor_search(
    std::array<unsigned short, konst::bs> c,
    short start,
    char type)
{
    short add_only_set{0x0}, my_set{0x0};
    const short i_col{0x3}, i_els{0x1}, f_row{0x0};
    short by{(type == 'c') ? i_col : i_els}, from{(type == 'r') ? f_row : start};
    for (short i = from; i < (from + konst::sz); i+=by)
    {
        const short j{(type == 'r') ? grp(start, i) : i};
        if ((my_set & c[j]) != 0)
        {
            add_only_set |= my_set & c[j];
        }
        my_set ^= c[j];
    }
    return my_set & ~(my_set & add_only_set); //n-input 'true' xor
}

std::array<short, 0x2> sqr_find(
    std::array<unsigned short, konst::bs> c)
{
    short sqr_set{0x0};
    for (short i = 0; i < konst::bs; i+=9)
    {
        sqr_set = set_xor_search(c, i, 's');
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

std::array<short, 0x2> row_find(
    std::array<unsigned short, konst::bs> c)
{
    short row_set{0x0};
    for (short i = 0; i < konst::sb; i+=3)
    {
        row_set = set_xor_search(c, i, 'r');
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

std::array<short, 0x2> col_find(
    std::array<unsigned short, konst::bs> c)
{
    short col_set{0x0}, j{};
    for (short i = 0; i < konst::sz; i++)
    {
        j = grp(0, i);
        col_set = set_xor_search(c, j, 'c');
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
    while (index != (-1))
    {
        short value = equiv(c[index]);
        b[index] = value;
        c = init_can(b);
        index = (value == 0) ? (-1) : find_solo(b, c);
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
            if ((value[0] & c[grp(value[1], i)]) != 0)
            {
                b[grp(value[1], i)] = equiv(value[0]);
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
    short counter{0}, c_i{0};
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
        std::cout << '.';
        blank = blank_check(b);
        temp_b = try_row_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);
        }
        std::cout << '.';
        blank = blank_check(b);
        temp_b = try_col_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);
        }
        std::cout << '.';
        blank = blank_check(b);
        temp_b = try_sqr_find(b, c);
        if (b != temp_b)
        {
            counter++;
            b = temp_b;
            c = init_can(b);
        }
        std::cout << '.';
        if (counter == c_i)
        {
            blank = false;
        }
        std::cout << blank;
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "inserted ";
    std::cout << "in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us\n";
    return b;
}