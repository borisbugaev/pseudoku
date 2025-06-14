/*
sudoku constants in a shared header
"maybe better!"
*/
#pragma once
#include <string>
#include <vector>
#include <array>
#include <unordered_map>

namespace konst
{
    constexpr unsigned char sz{9};
    constexpr unsigned char bs{81};
    constexpr unsigned char sb{27};
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
    const std::string usr_exit{"exit"};
    const std::string usr_help{"?"};
    const std::string usr_ref{"reference"};
    const std::string usr_step{"step"}; //get next val +=
    const std::string usr_next{"next"}; //return val & loc
    const std::string usr_insr{"insert"};
    const std::string usr_fin{"solve"};
    const std::string usr_srch{"search"};
    const std::string usr_solo{"solo"};
    const std::string usr_draw{"draw"};
    const std::string usr_col{"column"};
}

namespace algae
{
    const std::array<std::string, konst::bs> to{
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
        {"a6", konst::sb},
        {"a5", konst::sb + 1},
        {"a4", konst::sb + 2},
        {"a3", konst::sb * 2},
        {"a2", konst::sb * 2 + 1},
        {"a1", konst::sb * 2 + 2},
        {"b9", 3},
        {"b8", 4},
        {"b7", 5},
        {"b6", 3 + konst::sb},
        {"b5", 4 + konst::sb},
        {"b4", 5 + konst::sb},
        {"b3", 3 + konst::sb * 2},
        {"b2", 4 + konst::sb * 2},
        {"b1", 5 + konst::sb * 2},
        {"c9", 6},
        {"c8", 7},
        {"c7", 8},
        {"c6", 6 + konst::sb},
        {"c5", 7 + konst::sb},
        {"c4", 8 + konst::sb},
        {"c3", 6 + konst::sb * 2},
        {"c2", 7 + konst::sb * 2},
        {"c1", 8 + konst::sb * 2},
        {"d9", 9},
        {"d8", 10},
        {"d7", 11},
        {"d6", 9 + konst::sb},
        {"d5", 10 + konst::sb},
        {"d4", 11 + konst::sb},
        {"d3", 9 + konst::sb * 2},
        {"d2", 10 + konst::sb * 2},
        {"d1", 11 + konst::sb * 2},
        {"e9", 12},
        {"e8", 13},
        {"e7", 14},
        {"e6", 12 + konst::sb},
        {"e5", 13 + konst:: sb},
        {"e4", 14 + konst::sb},
        {"e3", 12 + konst::sb * 2},
        {"e2", 13 + konst::sb * 2},
        {"e1", 14 + konst::sb * 2},
        {"f9", 15},
        {"f8", 16},
        {"f7", 17},
        {"f6", 15 + konst::sb},
        {"f5", 16 + konst::sb},
        {"f4", 17 + konst::sb},
        {"f3", 15 + konst::sb * 2},
        {"f2", 16 + konst::sb * 2},
        {"f1", 17 + konst::sb * 2},
        {"g9", 18},
        {"g8", 19},
        {"g7", 20},
        {"g6", 18 + konst::sb},
        {"g5", 19 + konst::sb},
        {"g4", 20 + konst::sb},
        {"g3", 18 + konst::sb * 2},
        {"g2", 19 + konst::sb * 2},
        {"g1", 20 + konst::sb * 2},
        {"h9", 21},
        {"h8", 22},
        {"h7", 23},
        {"h6", 21 + konst::sb},
        {"h5", 22 + konst::sb},
        {"h4", 23 + konst::sb},
        {"h3", 21 + konst::sb * 2},
        {"h2", 22 + konst::sb * 2},
        {"h1", 23 + konst::sb * 2},
        {"i9", 24},
        {"i8", 25},
        {"i7", 26},
        {"i6", 24 + konst::sb},
        {"i5", 25 + konst::sb},
        {"i4", 26 + konst::sb},
        {"i3", 24 + konst::sb * 2},
        {"i2", 25 + konst::sb * 2},
        {"i1", 26 + konst::sb * 2}
    };
}