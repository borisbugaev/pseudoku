#include "sudokonst.h"
#include <array>
#include <string>
#include <iostream>
#include <unordered_map>


void draw_differences(
    std::array<short, konst::sqr_sz> board_1,
    std::array<short, konst::sqr_sz> board_2);
std::array<short, konst::sqr_sz> prune_squares_by_rows(
    std::array<short, konst::sqr_sz> board);
void draw_help_dialog();
std::array<short, konst::sqr_sz> init_from_file(std::string filename);
short board_export(
    std::array<short, konst::sqr_sz> board,
    std::string filename);
short candidates(unsigned char locale, 
    std::array<short, konst::sqr_sz> board);
void draw_board(std::array<short, konst::sqr_sz> board);
void draw_cboard(std::array<short, konst::sqr_sz> board);
void draw_candidates(short candidat);
void draw_boardref(std::array<short, konst::sqr_sz> board);
short equiv(short c);
short find_solo(
    std::array<short, konst::sqr_sz> board);
std::array<short, konst::sqr_sz> try_solo_find(
    std::array<short, konst::sqr_sz> board);
std::array<short, konst::sqr_sz> solve_board(
    std::array<short, konst::sqr_sz> board);
short set_xor_search(
    std::array<short, konst::sqr_sz> board,
    short start,
    char type);
std::array<short, konst::sqr_sz> board_import(
    std::string filename);
std::array<short, konst::sqr_sz> try_generic_find(
    std::array<short, konst::sqr_sz> board,
    char type);

bool input_valid(
    std::string input)
{
    for (short i = '1'; i <= '1' + konst::sz; i++)
    {
        std::string val
            {(char)i};
        if (input.compare(val))
        {
            return true;
        }
    }
    return false;
}

std::array<short, konst::sqr_sz> kommand(
    std::string input, 
    std::array<short, konst::sqr_sz> board)
{
    if (input.compare(komm::usr_exit) == 0)
    {
        return board;
    }
    else if (input.compare(komm::usr_fin) == 0)
    {
        // solve board
        board = solve_board(board);
        return board;
    }
    else if (input.compare(komm::usr_help) == 0)
    {
        // print help message
        draw_help_dialog();
        return board;
    }
    else if (input.compare(komm::usr_insr) == 0)
    {
        // request insertion location
        // request insertion value
        // insert value into board
        std::string inputstr
            {};
        std::cout << "Location: ";
        std::cin >> inputstr;
        const short loc = alg_map::u.at(inputstr);
        std::cout << "Value: ";
        std::cin >> inputstr;
        if (input_valid(inputstr))
        {
            const short val = std::stoi(inputstr);
            board[loc] = val;
        }
        else
        {
            std::cout << "input invalid\n";
        }
        return board;
    }
    else if (input.compare(komm::usr_next) == 0)
    {
        // solve single square
        // print location of solved square
        // print solution
        // NO INSERT
        short index = find_solo(board);
        if (index < 0)
        {
            std::cout << "Did not find next answer\n";
        }
        else
        {
            std::cout << "Value at " 
            << algae::to[index]
            << " is ";
            draw_candidates(board[index]);
        }
        return board;
    }
    else if (input.compare(komm::usr_ref) == 0)
    {
        // print reference for board locations
        draw_boardref(board);
        std::cout << "Usage: \"a9\", \"i6\", etc.\n";
        return board;
    }
    else if (input.compare(komm::usr_step) == 0)
    {
        // solve single square
        // insert solution into board
        short index = find_solo(board);
        if (index > 0)
        {
            short value = equiv(board[index]);
            board[index] = -value;
        }
        return board;
    }
    else if (input.compare(komm::usr_srch) == 0)
    {
        std::string inputstr
            {};
        std::cout << "Search at index...";
        std::cin >> inputstr;
        if (input_valid(inputstr))
        {
            short searchfor = alg_map::u.at(inputstr);
            std::cout << pseud::mv_up << pseud::clr;
            std::cout << "Candidates @ " << inputstr << ": ";
            draw_candidates(board[searchfor]);
        }
        else
        {
            std::cout << "input invalid\n";
        }
        return board;
    }
    else if (input.compare(komm::usr_draw) == 0)
    {
        draw_board(board);
    }
    else if (input.compare(komm::usr_col) == 0)
    {
        std::string inputstr
            {};
        std::cout << "Search Column...";
        std::cin >> inputstr;
        if (inputstr.compare(komm::usr_fin) == 0)
        {
            return try_generic_find(board, 'c');
        }
        else if (input_valid(inputstr))
        {
            short searchfor = std::stoi(inputstr);
            draw_candidates(set_xor_search(board, searchfor, 'c'));
        }
        else
        {
            std::cout << "input invalid\n";
        }
    }
    else if (input.compare(komm::usr_row) == 0)
    {
        std::string inputstr
            {};
        std::cout << "Search row...";
        std::cin >> inputstr;
        if (inputstr.compare(komm::usr_fin) == 0)
        {
            return try_generic_find(board, 'r');
        }
        else if (input_valid(inputstr))
        {
            short searchfor = std::stoi(inputstr);
            draw_candidates(set_xor_search(board, searchfor, 'r'));
        }
        else
        {
            std::cout << "input invalid\n";
        }
    }
    else if (input.compare(komm::usr_sqr) == 0)
    {
        std::string inputstr
            {};
        std::cout << "Search square...";
        std::cin >> inputstr;
        if (inputstr.compare(komm::usr_fin) == 0)
        {
            return try_generic_find(board, 's');
        }
        else if (input_valid(inputstr))
        {
            short searchfor = std::stoi(inputstr);
            draw_candidates(set_xor_search(board, searchfor, 's'));
        }
        else
        {
            std::cout << "input invalid\n";
        }
    }
    else if (input.compare(komm::usr_open) == 0)
    {
        std::string inputstr
            {};
        std::cout << "Filename...";
        std::cin >> inputstr;
        board = init_from_file(inputstr);
        return board;
    }
    else if (input.compare(komm::usr_cdrw) == 0)
    {
        draw_cboard(board);
    }
    else if (input.compare(komm::usr_bexp) == 0)
    {
        std::string inputstr
            {};
        std::cout << "Output Filename...";
        std::cin >> inputstr;
        short out_file{board_export(board, inputstr)};
    }
    else if (input.compare(komm::usr_bimp) == 0)
    {
        std::string inputstr
            {};
        std::cout << "Input Filename...";
        std::cin >> inputstr;
        auto iboard = board_import(inputstr);
        if (iboard != board)
        {
            std::cout << "Successfully imported board at " << inputstr << '\n';
            board = iboard;
        }
    }
    else if (input.compare("debug") == 0)
    {
        char inputchar
            {};
        std::cout << "...";
        std::cin >> inputchar;
        std::array<short, konst::sqr_sz> trial_A;
        std::array<short, konst::sqr_sz> trial_B;
        std::array<short, konst::sqr_sz> trial_C;
        bool am_debug
            {true};
        char prev_input
            {};
        while (am_debug)
        {
            switch (inputchar)
            {
                case 'r':
                {
                    trial_A = prune_squares_by_rows(board);
                    break;
                }
                case 'd': // draw differences between board and trialboard
                {
                    draw_differences(board, trial_A);
                    break;
                }
                case 't': // draw trialboard
                {
                    draw_board(trial_A);
                    break;
                }
                case 'e': // end
                {
                    am_debug = false;
                    return board;
                    break;
                }
                case 'q': // difference
                {
                    bool equality
                        {board == trial_A};
                    std::cout << equality;
                    break;
                }
                case 's': // set trial to board
                {
                    board = trial_A;
                    break;
                }
            }
            std::cout << "\n...";
            std::cin >> inputchar;
            if (inputchar == 'e')
            {
                am_debug = false;
                break;
            }
        }
    }
    else
    {
        std::cout << "unexpected input\n";
    }
    return board;
}