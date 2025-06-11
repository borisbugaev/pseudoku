#pragma once
#include "sudokonst.h"
#include <array>
#include <iostream>

/*
functions to be used in sudoku evaluation
*/

std::array<unsigned short, konst::bs> init_can(
    std::array<unsigned short, konst::bs> board
);

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

std::array<unsigned short, konst::bs> try_solo_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    short counter{0};
    short index = find_solo(b, c);
    while (index != -1)
    {
        counter++;
        short value = equiv(c[index]);
        b[index] = value;
        c = init_can(b);
        index = find_solo(b, c);
    }
    std::cout << "inserted " << counter << " values to board\n";
    return b;
}