#include "sudokonst.h"
#include <array>
#include <iostream>
#include <chrono>


std::array<short, konst::sqr_sz> prune(
    std::array<short, konst::sqr_sz> board);
short diff_magn(
    std::array<short, konst::sqr_sz> board_1,
    std::array<short, konst::sqr_sz> board_2);
std::array<short, konst::sqr_sz> try_solo_find(
    std::array<short, konst::sqr_sz> board);
bool blank_check(
    std::array<short, konst::sqr_sz> board);
std::array<short, konst::sqr_sz> set_can(
    std::array<short, konst::sqr_sz> board);
void draw_board(std::array<short, konst::sqr_sz> board);
std::array<short, konst::sqr_sz> try_generic_find(
    std::array<short, konst::sqr_sz> board,
    char type);

std::array<short, konst::sqr_sz> solve_board(
    std::array<short, konst::sqr_sz> board)
{
    auto start = std::chrono::steady_clock::now();
    short counter
        {0},
    c_i
        {0};
    bool blank
        {blank_check(board)};
    std::array<short, konst::sqr_sz> temp_b;
    while (blank)
    {
        c_i = counter;
        temp_b = try_solo_find(board);
        if (board != temp_b)
        {
            counter += diff_magn(board, temp_b);
            board = temp_b;
            board = set_can(board);
            blank = blank_check(board);
            continue;
        }
        for (char type : konst::types)
        {
            temp_b = try_generic_find(board, type);
            if (board == temp_b)
            {
                continue;
            }
            counter += diff_magn(board, temp_b);
            board = temp_b;
            board = set_can(board);
            blank = blank_check(board);
            break;
        }
        if (c_i == counter)
        {
            blank = false;
            continue;
        }
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "edited " << counter << " values ";
    std::cout << "in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " us\n";
    return board;
}