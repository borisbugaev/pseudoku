#include "sudokonst.h"
#include <array>
#include <string>
#include <iostream>
#include <unordered_map>


std::array<short, konst::bs> init_from_file(std::string filename);
short board_export(
    std::array<short, konst::bs> board,
    std::string filename);
short candidates(unsigned char locale, 
    std::array<short, konst::bs> board);
void draw_board(std::array<short, konst::bs> b);
void draw_cboard(std::array<short, konst::bs> c);
void draw_candidates(short candidat);
void draw_boardref(std::array<short, konst::bs> b);
short equiv(short c);
short find_solo(
    std::array<short, konst::bs> b);
std::array<short, konst::bs> try_solo_find(
    std::array<short, konst::bs> b);
std::array<short, konst::bs> try_sqr_find(
    std::array<short, konst::bs> b);
std::array<short, konst::bs> try_row_find(
    std::array<short, konst::bs> b);
std::array<short, konst::bs> solve_board(
    std::array<short, konst::bs> b);
short set_xor_search(
    std::array<short, konst::bs> b,
    short start,
    char type);
std::array<short, konst::bs> board_import(
    std::string filename);


std::array<short, konst::bs> kommand(
    std::string input, 
    std::array<short, konst::bs> board)
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
        return board;
    }
    else if (input.compare(komm::usr_insr) == 0)
    {
        // request insertion location
        // request insertion value
        // insert value into board
        std::string inputstr{};
        std::cout << "Location: ";
        std::cin >> inputstr;
        short loc = alg_map::u.at(inputstr);
        std::cout << "Value: ";
        std::cin >> inputstr;
        short val = std::stoi(inputstr);
        board[loc] = val;
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
        std::string inputstr{};
        std::cout << "Search at index...";
        std::cin >> inputstr;
        short searchfor = alg_map::u.at(inputstr);
        std::cout << pseud::mv_up << pseud::clr;
        std::cout << "Candidates @ " << inputstr << ": ";
        draw_candidates(board[searchfor]);
        return board;
    }
    else if (input.compare(komm::usr_solo) == 0)
    {
        board = try_solo_find(board);
        return board;
    }
    else if (input.compare(komm::usr_draw) == 0)
    {
        draw_board(board);
    }
    else if (input.compare(komm::usr_col) == 0)
    {
        std::string inputstr{};
        std::cout << "Search Column...";
        std::cin >> inputstr;
        short searchfor = std::stoi(inputstr);
        draw_candidates(set_xor_search(board, searchfor, 'c'));
    }
    else if (input.compare(komm::usr_row) == 0)
    {
        std::string inputstr{};
        std::cout << "Search row...";
        std::cin >> inputstr;
        if (inputstr.compare(komm::usr_fin) == 0)
        {
            return try_row_find(board);
        }
        else
        {
            short searchfor = std::stoi(inputstr);
            draw_candidates(set_xor_search(board, searchfor, 'r'));
        }
    }
    else if (input.compare(komm::usr_sqr) == 0)
    {
        std::string inputstr{};
        std::cout << "Search square...";
        std::cin >> inputstr;
        if (inputstr.compare(komm::usr_fin) == 0)
        {
            return try_sqr_find(board);
        }
        else
        {
            short searchfor = std::stoi(inputstr);
            draw_candidates(set_xor_search(board, searchfor, 's'));
        }
    }
    else if (input.compare(komm::usr_open) == 0)
    {
        std::string inputstr{};
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
        std::string inputstr{};
        std::cout << "Output Filename...";
        std::cin >> inputstr;
        short out_file{board_export(board, inputstr)};
    }
    else if (input.compare(komm::usr_bimp) == 0)
    {
        std::string inputstr{};
        std::cout << "Input Filename...";
        std::cin >> inputstr;
        auto iboard = board_import(inputstr);
        if (iboard != board)
        {
            std::cout << "Successfully imported board at " << inputstr << '\n';
            board = iboard;
        }
    }
    else
    {
        std::cout << "unexpected input\n";
    }
    return board;
}