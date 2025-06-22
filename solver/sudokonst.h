/*
sudoku constants in a shared header
"maybe better!"
*/
#pragma once
#include <string>
#include <array>
#include <unordered_map>

namespace konst
{
    constexpr unsigned char sz{9}; // must be a square number
    constexpr unsigned char sqr_sz{81}; // sz squared
    constexpr unsigned char rt_sz{3};
    constexpr unsigned char th_sz{27}; // cube of sqrt(sz) aka threehalf power of sz
}

namespace pseud
{
    const std::string prompt{"Pseudoku>"};
    const std::string candidate_prompt{prompt + ".candidate"};
    const std::string hint{"For Commands List use ?\n"};
    const std::string sqr_x_brdr{"------x-------x------"};
    const std::string mv_up{"\x1b[1A"};
    const std::string clr{"\x1b[2K"};
}

namespace komm
{
    const std::string usr_open{"open"};
    const std::string usr_exit{"exit"};
    const std::string usr_help{"?"};
    const std::string usr_ref{"reference"};
    const std::string usr_step{"step"}; //get next val +=
    const std::string usr_next{"next"}; //return val & loc
    const std::string usr_insr{"insert"};
    const std::string usr_fin{"solve"};
    const std::string usr_srch{"search"};
    const std::string usr_bexp{"export"};
    const std::string usr_bimp{"import"};

    /*
    commands primarily used for debugging, etc
    */
    const std::string usr_solo{"solo"};
    const std::string usr_draw{"draw"};
    const std::string usr_col{"column"};
    const std::string usr_row{"row"};
    const std::string usr_sqr{"square"};
    const std::string usr_cdrw{"cdraw"};
    const std::string usr_try{"debug"};
}

namespace sqr_sub_id
{
    constexpr short col_3{0};
    constexpr short col_2{1};
    constexpr short col_1{2};
    constexpr short row_a{3};
    constexpr short row_b{4};
    constexpr short row_c{5};
}

namespace algae
{
    const std::array<std::string, konst::sqr_sz> to{
        "a9","a8","a7",
        "b9","b8","b7",
        "c9","c8","c7",
        "d9","d8","d7",
        "e9","e8","e7",
        "f9","f8","f7",
        "g9","g8","g7",
        "h9","h8","h7",
        "i9","i8","i7",
        "a6","a5","a4",
        "b6","b5","b4",
        "c6","c5","c4",
        "d6","d5","d4",
        "e6","e5","e4",
        "f6","f5","f4",
        "g6","g5","g4",
        "h6","h5","h4",
        "i6","i5","i4",
        "a3","a2","a1",
        "b3","b2","b1",
        "c3","c2","c1",
        "d3","d2","d1",
        "e3","e2","e1",
        "f3","f2","f1",
        "g3","g2","g1",
        "h3","h2","h1",
        "i3","i2","i1"
    };
}

namespace alg_map
{
    const std::unordered_map<std::string, short> u
    {
        {"a9", 0},
        {"a8", 1},
        {"a7", 2},
        {"a6", konst::th_sz},
        {"a5", konst::th_sz + 1},
        {"a4", konst::th_sz + 2},
        {"a3", konst::th_sz * 2},
        {"a2", konst::th_sz * 2 + 1},
        {"a1", konst::th_sz * 2 + 2},
        {"b9", 3},
        {"b8", 4},
        {"b7", 5},
        {"b6", 3 + konst::th_sz},
        {"b5", 4 + konst::th_sz},
        {"b4", 5 + konst::th_sz},
        {"b3", 3 + konst::th_sz * 2},
        {"b2", 4 + konst::th_sz * 2},
        {"b1", 5 + konst::th_sz * 2},
        {"c9", 6},
        {"c8", 7},
        {"c7", 8},
        {"c6", 6 + konst::th_sz},
        {"c5", 7 + konst::th_sz},
        {"c4", 8 + konst::th_sz},
        {"c3", 6 + konst::th_sz * 2},
        {"c2", 7 + konst::th_sz * 2},
        {"c1", 8 + konst::th_sz * 2},
        {"d9", 9},
        {"d8", 10},
        {"d7", 11},
        {"d6", 9 + konst::th_sz},
        {"d5", 10 + konst::th_sz},
        {"d4", 11 + konst::th_sz},
        {"d3", 9 + konst::th_sz * 2},
        {"d2", 10 + konst::th_sz * 2},
        {"d1", 11 + konst::th_sz * 2},
        {"e9", 12},
        {"e8", 13},
        {"e7", 14},
        {"e6", 12 + konst::th_sz},
        {"e5", 13 + konst:: th_sz},
        {"e4", 14 + konst::th_sz},
        {"e3", 12 + konst::th_sz * 2},
        {"e2", 13 + konst::th_sz * 2},
        {"e1", 14 + konst::th_sz * 2},
        {"f9", 15},
        {"f8", 16},
        {"f7", 17},
        {"f6", 15 + konst::th_sz},
        {"f5", 16 + konst::th_sz},
        {"f4", 17 + konst::th_sz},
        {"f3", 15 + konst::th_sz * 2},
        {"f2", 16 + konst::th_sz * 2},
        {"f1", 17 + konst::th_sz * 2},
        {"g9", 18},
        {"g8", 19},
        {"g7", 20},
        {"g6", 18 + konst::th_sz},
        {"g5", 19 + konst::th_sz},
        {"g4", 20 + konst::th_sz},
        {"g3", 18 + konst::th_sz * 2},
        {"g2", 19 + konst::th_sz * 2},
        {"g1", 20 + konst::th_sz * 2},
        {"h9", 21},
        {"h8", 22},
        {"h7", 23},
        {"h6", 21 + konst::th_sz},
        {"h5", 22 + konst::th_sz},
        {"h4", 23 + konst::th_sz},
        {"h3", 21 + konst::th_sz * 2},
        {"h2", 22 + konst::th_sz * 2},
        {"h1", 23 + konst::th_sz * 2},
        {"i9", 24},
        {"i8", 25},
        {"i7", 26},
        {"i6", 24 + konst::th_sz},
        {"i5", 25 + konst::th_sz},
        {"i4", 26 + konst::th_sz},
        {"i3", 24 + konst::th_sz * 2},
        {"i2", 25 + konst::th_sz * 2},
        {"i1", 26 + konst::th_sz * 2}
    };
}

namespace tra
{
    const std::unordered_map<short, short> nsform
    {
        {0, 0}, {1, 1}, {2, 2},
        {3, 27}, {4, 28}, {5, 29},
        {6, 54}, {7, 55}, {8, 56},
        {9, 3}, {10, 4}, {11, 5},
        {12, 30}, {13, 31}, {14, 32},
        {15, 57}, {16, 58}, {17, 59},
        {18, 6}, {19, 7}, {20, 8},
        {21, 33}, {22, 34}, {23, 35},
        {24, 60}, {25, 61}, {26,62},
        {27, 9}, {28, 10}, {29, 11},
        {30, 36}, {31, 37}, {32, 38},
        {33, 63}, {34, 64}, {35, 65},
        {36, 12}, {37, 13}, {38, 14},
        {39, 39}, {40, 40}, {41, 41},
        {42, 66}, {43, 67}, {44, 68},
        {45, 15}, {46, 16}, {47, 17},
        {48, 42}, {49, 43}, {50, 44},
        {51, 69}, {52, 70}, {53, 71},
        {54, 18}, {55, 19}, {56, 20},
        {57, 45}, {58, 46}, {59, 47},
        {60, 72}, {61, 73}, {62, 74},
        {63, 21}, {64, 22}, {65, 23},
        {66, 48}, {67, 49}, {68, 50},
        {69, 75}, {70, 76}, {71, 77},
        {72, 24}, {73, 25}, {74, 26},
        {75, 51}, {76, 52}, {77, 53},
        {78, 78}, {79, 79}, {80, 80}
    };
}

#ifdef DEBUG
constexpr std::array<unsigned short, konst::bs> sref{
    4, 3, 1, 9, 6, 2, 8, 7, 5, 
    6, 2, 7, 5, 4, 9, 1, 8, 3, 
    2, 1, 6, 3, 9, 8, 7, 5, 4, 
    2, 5, 9, 3, 8, 7, 1, 4, 6, 
    4, 9, 3, 8, 2, 1, 6, 7, 5, 
    7, 3, 8, 5, 1, 4, 9, 6, 2, 
    7, 8, 6, 4, 5, 1, 3, 2, 9, 
    8, 1, 5, 6, 7, 3, 9, 4, 2, 
    5, 9, 4, 2, 6, 7, 1, 3, 8
};
#endif