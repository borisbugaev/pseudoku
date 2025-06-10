#include "sudokonst.h"
#include <array>
#include <string>
#include <iostream>

std::array<unsigned short, konst::bs> kommand(std::string input, std::array<unsigned short, konst::bs> board)
{
    if (input.compare(komm::usr_exit))
    {
        return board;
    }
    else if (input.compare(komm::usr_fin))
    {
        // solve board
        return board;
    }
    else if (input.compare(komm::usr_help))
    {
        // print help message
        return board;
    }
    else if (input.compare(komm::usr_insr))
    {
        // request insertion location
        // request insertion value
        // insert value into board
        return board;
    }
    else if (input.compare(komm::usr_next))
    {
        // solve single square
        // print location of solved square
        // print solution
        // NO INSERT
        return board;
    }
    else if (input.compare(komm::usr_ref))
    {
        // print reference for board locations
        return board;
    }
    else if (input.compare(komm::usr_step))
    {
        // solve single square
        // insert solution into board
        return board;
    }
    return board;
}