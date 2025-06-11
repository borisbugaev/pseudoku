/*
sudoku constants in a shared header
"maybe better!"
*/
#pragma once
#include <string>
#include <vector>
#include <array>

namespace konst
{
    constexpr unsigned char sz{9};
    constexpr unsigned char bs{81};
}

namespace pseud
{
    const std::string prompt{"Pseudoku>"};
    const std::string candidate_prompt{prompt + ".candidate"};
    const std::string hint{"For Commands List use ?\n"};
}

namespace komm
{
    const std::string usr_exit{"exit"};
    const std::string usr_help{"?"};
    const std::string usr_ref{"ref"};
    const std::string usr_step{"step"}; //get next val +=
    const std::string usr_next{"next"}; //return val & loc
    const std::string usr_insr{"insr"};
    const std::string usr_fin{"sol"};
    const std::string usr_srch{"srch"};
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