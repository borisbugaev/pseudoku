/*
sudoku constants in a shared header
"maybe better!"
*/
#pragma once
#include <string>
#include <vector>

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