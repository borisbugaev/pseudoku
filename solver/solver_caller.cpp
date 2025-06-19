#include "sudokonst.h"
#include <iostream>
#include <chrono>


std::array<unsigned short, konst::bs> prune(
    std::array<unsigned short, konst::bs> c);
std::array<unsigned short, konst::bs> try_sqr_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c);
short diff_magn(
    std::array<unsigned short, konst::bs> b_1,
    std::array<unsigned short, konst::bs> b_2);
std::array<unsigned short, konst::bs> try_col_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c);
std::array<unsigned short, konst::bs> try_row_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c);
std::array<unsigned short, konst::bs> try_solo_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c);
bool blank_check(
    std::array<unsigned short, konst::bs> b);
std::array<unsigned short, konst::bs> set_can(
    std::array<unsigned short, konst::bs> board,
    std::array<unsigned short, konst::bs> c_board);
void draw_board(std::array<unsigned short, konst::bs> b);

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
            counter += diff_magn(b, temp_b);
            b = temp_b;
            c = set_can(b, c);
            //draw_board(b);
        }
        blank = blank_check(b);
        temp_b = try_row_find(b, c);
        if (b != temp_b)
        {
            counter += diff_magn(b, temp_b);
            b = temp_b;
            c = set_can(b, c);
            //draw_board(b);
        }
        blank = blank_check(b);
        temp_b = try_col_find(b, c);
        if (b != temp_b)
        {
            counter += diff_magn(b, temp_b);
            b = temp_b;
            c = set_can(b, c);
            //draw_board(b);
        }
        blank = blank_check(b);
        temp_b = try_sqr_find(b, c);
        if (b != temp_b)
        {
            counter += diff_magn(b, temp_b);
            b = temp_b;
            c = set_can(b, c);
            //draw_board(b);
        }
        if (counter == c_i)
        {
            blank = false;
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "inserted " << counter << " values ";
    std::cout << "in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us\n";
    return b;
}