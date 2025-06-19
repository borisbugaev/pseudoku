#include "sudokonst.h"
#include <array>
#include <iostream>
#include <string>

const int EXP_ARGC{2};
const std::string EXP_ARGSV[EXP_ARGC]{"SELF", "INPUT FILE"};
const std::string ARG_TYPE{"ENTER NAME OF "};

std::array<short, konst::bs> kommand(
    std::string input, 
    std::array<short, konst::bs> board);
short candidates(unsigned char locale, 
    std::array<short, konst::bs> board);
void draw_board(std::array<short, konst::bs> b);
void draw_candidates(short candidat);
std::array<short, konst::bs> init_blank();
std::array<short, konst::bs> init_from_file(std::string filename);
std::array<short, konst::bs> set_can(
    std::array<short, konst::bs> board);
std::array<short, konst::bs> initialize_candidates(
    std::array<short, konst::bs> c_board);

int main(int argc, char** argv)
{
    std::array<short, konst::bs> board{};
    
    //boilerplate filename input init
    std::string input_arg[EXP_ARGC];
    input_arg[0] = argv[0];
    if (argc == EXP_ARGC)
    {
        for (int i = 1; i < EXP_ARGC; i++)
        {
            input_arg[i] = argv[1];
        }
        board = init_from_file(input_arg[1]);
    }
    else
    {
        board = init_blank();
    }
    draw_board(board);
    // with board initialized
    board = initialize_candidates(board);
    board = set_can(board);
    std::array<short, konst::bs> tboard;
    bool usr_quit{false};
    std::string inputstr{};
    std::cout << pseud::hint;
    std::cout << pseud::prompt;
    std::cin >> inputstr;
    while (!usr_quit)
    {
        tboard = kommand(inputstr, board);
        if (tboard != board)
        {
            board = set_can(tboard);
            board = tboard;
        }
        std::cout << pseud::prompt;
        std::cin >> inputstr;
        if (inputstr.compare("exit") == 0)
        {
            usr_quit = true;
        }
    }
    return 0;
}