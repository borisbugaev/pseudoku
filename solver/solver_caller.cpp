#include "sudokonst.h"
#include <iostream>
#include <chrono>


std::array<short, konst::sqr_sz> prune(
    std::array<short, konst::sqr_sz> b);
std::array<short, konst::sqr_sz> try_sqr_find(
    std::array<short, konst::sqr_sz> b);
short diff_magn(
    std::array<short, konst::sqr_sz> b_1,
    std::array<short, konst::sqr_sz> b_2);
std::array<short, konst::sqr_sz> try_col_find(
    std::array<short, konst::sqr_sz> b);
std::array<short, konst::sqr_sz> try_row_find(
    std::array<short, konst::sqr_sz> b);
std::array<short, konst::sqr_sz> try_solo_find(
    std::array<short, konst::sqr_sz> b);
bool blank_check(
    std::array<short, konst::sqr_sz> b);
std::array<short, konst::sqr_sz> set_can(
    std::array<short, konst::sqr_sz> board);
void draw_board(std::array<short, konst::sqr_sz> b);

std::array<short, konst::sqr_sz> solve_board(
    std::array<short, konst::sqr_sz> b)
{
    auto start = std::chrono::steady_clock::now();
    short counter{0}, c_i{0};
    bool blank{blank_check(b)};
    std::array<short, konst::sqr_sz> temp_b;
    while (blank == true)
    {
        c_i = counter;
        temp_b = try_solo_find(b);
        if (b != temp_b)
        {
            counter += diff_magn(b, temp_b);
            b = temp_b;
            b = set_can(b);
        }
        blank = blank_check(b);
        temp_b = try_row_find(b);
        if (b != temp_b)
        {
            counter += diff_magn(b, temp_b);
            b = temp_b;
            b = set_can(b);
        }
        blank = blank_check(b);
        temp_b = try_col_find(b);
        if (b != temp_b)
        {
            counter += diff_magn(b, temp_b);
            b = temp_b;
            b = set_can(b);
        }
        blank = blank_check(b);
        temp_b = try_sqr_find(b);
        if (b != temp_b)
        {
            counter += diff_magn(b, temp_b);
            b = temp_b;
            b = set_can(b);
        }
        if (counter == c_i)
        {
            blank = false;
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "edited " << counter << " values ";
    std::cout << "in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us\n";
    return b;
}