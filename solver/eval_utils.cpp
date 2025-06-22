#include "sudokonst.h"
#include <array>
//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

/*
functions to be used in sudoku evaluation
TODO: square set eval, set striking
*/

constexpr unsigned char my_square(unsigned char locale);
void draw_candidates(short candidat);
std::array<short, konst::sqr_sz> set_can(
    std::array<short, konst::sqr_sz> board);
void draw_board(std::array<short, konst::sqr_sz> b);


/*
corrects for rows
*/
const short grp(
    const short row_id,
    const short index)
{
    short id{row_id};
    id += index % 0x3;
    id += (index >= 0x3) ? konst::th_sz : 0;
    id += (index >= 0x6) ? konst::th_sz : 0;
    return id;
}

/*
returns actual value represented in candidates when ==1
*/
constexpr short equiv(short c)
{
    return ((0x100 & c) ? 9 : 0)
    + ((0x80 & c) ? 8 : 0)
    + ((0x40 & c) ? 7 : 0)
    + ((0x20 & c) ? 6 : 0)
    + ((0x10 & c) ? 5 : 0)
    + ((0x08 & c) ? 4 : 0)
    + ((0x04 & c) ? 3 : 0)
    + ((0x02 & c) ? 2 : 0)
    + (0x01 & c);
}

bool blank_check(
    std::array<short, konst::sqr_sz> board)
{
    for (short i = 0; i < konst::sqr_sz; i++)
    {
        if (board[i] <= 0)
        {
            return true;
        }
    }
    return false;
}

bool high_bit_count(
    short bit_map,
    short quant)
{
    short counter{0x0};
    for (short i = 0x0; i < 0x10; i++)
    {
        counter += 0x1 & (bit_map >> i);
        if (counter > quant)
        {
            return false;
        }
    }
    bool is_equal{(counter == quant) ? true : false};
    return is_equal;
}


short high_bit_count(
    short bit_map)
{
    short counter{0x0};
    for (short i = 0x0; i < 0x10; i++)
    {
        counter += 0x1 & (bit_map >> i);
    }
    return counter;
}

short get_1st_mapped_short(
    short bit_map)
{
    for (short i = 0x1; i < 0x200; i = i << 1)
    {
        if (bit_map & i)
        {
            return i;
        }
    }
    return 0x0;
}

/*
returns index of first square where there is ==1 candidate
if none, returns -1
*/
short find_solo(
    std::array<short, konst::sqr_sz> board)
{
    for (short i = 0; i < konst::sqr_sz; i++)
    {
        if ((board[i] & (board[i] - 1)) == 0 && board[i] > 0)
        {
            return i;
        }
    }
    return -1;
}

short set_xor_search(
    std::array<short, konst::sqr_sz> board,
    short start,
    char type)
{
    short add_only_set{0x0}, my_set{0x0};
    const short i_col{konst::rt_sz}, i_els{0x1}, f_row{0x0};
    short by{(type == 'c') ? i_col : i_els};
    short from{(type == 'r') ? f_row : start};
    short buf{(type == 'c') ? konst::th_sz : konst::sz};
    for (short i = from; i < (from + buf); i+=by)
    {
        const short j{(type == 'r') ? grp(start, i) : i};
        const short cn_at_j{static_cast<short>(board[j] >= 0 ? board[j] : 0)};
        add_only_set |= my_set & cn_at_j;
        my_set ^= cn_at_j;
    }
    return my_set & ~add_only_set; //n-input 'true' xor
}

std::array<short, 0x2> sqr_find(
    std::array<short, konst::sqr_sz> board)
{
    short sqr_set{0x0};
    for (short i = 0; i < konst::sqr_sz; i += konst::sz)
    {
        sqr_set = set_xor_search(board, i, 's');
        if (sqr_set != 0)
        {
            return {get_1st_mapped_short(sqr_set), i};
        }
        sqr_set = 0x0;
    }
    return {0x5, 0x5};
}

std::array<short, 0x2> row_find(
    std::array<short, konst::sqr_sz> board)
{
    short row_set{0x0};
    for (short i = 0; i < konst::th_sz; i += konst::rt_sz)
    {
        row_set = set_xor_search(board, i, 'r');
        if (row_set != 0)
        {
            return {get_1st_mapped_short(row_set), i};
        }
        row_set = 0x0;
    }
    return {0x5, 0x5};
}

std::array<short, 0x2> col_find(
    std::array<short, konst::sqr_sz> board)
{
    short col_set{0x0}, j{};
    for (short i = 0; i < konst::sz; i++)
    {
        j = grp(0, i);
        col_set = set_xor_search(board, j, 'c');
        if (col_set != 0)
        {
            return {get_1st_mapped_short(col_set), j};
        }
        col_set = 0x0;
    }
    return {0x5, 0x5};
}

std::array<short, konst::sqr_sz> cull_square_from_row(
    std::array<short, konst::sqr_sz> board,
    short square_number,
    short value_to_cull,
    short subscript_to_preserve)
{
    // this is certainly incorrect. I will figure out why later.
    short start{static_cast<short>((subscript_to_preserve == sqr_sub_id::row_a) ? sqr_sub_id::row_a : 0)};
    short end{static_cast<short>((subscript_to_preserve == sqr_sub_id::row_c) ? sqr_sub_id::row_a : 0)};
    for (short i = square_number + start; i < square_number + konst::rt_sz - end; i++)
    {
        if (subscript_to_preserve == sqr_sub_id::row_b 
            && i == (square_number + start + sqr_sub_id::row_b))
        {
            i += konst::rt_sz;
            continue;
        }
        if (board[i] > 0)
        {
            board[i] &= ~value_to_cull;
        }
    }
    return board;
}

const short col_intersec(
    short subscript)
{
    short intersec{0x0};
    const short start{grp(0, subscript)};
    for (short i = start; i < start + konst::th_sz; i += konst::rt_sz)
    {
        intersec |= 1 << my_square(i);
    }
    return intersec;
}

const short row_intersec(
    short subscript)
{
    short intersec{0x0};
    for (short i = 0; i < konst::sz; i++)
    {
        const short my_loc{grp(subscript, i)};
        intersec |= 1 << my_square(my_loc);
    }
    return intersec;
}

short square_subset_get(
    std::array<short, konst::sqr_sz> board,
    short square_number,
    short subset_id)
{
    short square_set{0x0};
    const short squid{static_cast<short>(square_number * konst::sz)};
    if (subset_id < sqr_sub_id::row_a)
    {
        for (short i = squid + subset_id; i < konst::sz + squid + subset_id; i += konst::rt_sz)
        {
            square_set |= (board[i] > 0) ? board[i] : 0;
        }
    }
    else
    {
        const short a_subset_id{static_cast<short>((subset_id - konst::rt_sz) * konst::rt_sz)};
        for (short i = squid + a_subset_id; i < squid + a_subset_id + konst::rt_sz; i++)
        {
            square_set |= (board[i] > 0) ? board[i] : 0;
        }
    }
    return square_set;
}

// un tested
std::array<short, konst::sqr_sz> prune_squares_by_rows(
    std::array<short, konst::sqr_sz> board)
{
    std::array<short, konst::rt_sz> sq_rw{}, int_sq{};
    for (short i = 0; i < konst::th_sz; i+=konst::rt_sz)
    {
        const short intersects_squares{row_intersec(i)};
        short temp_isec{intersects_squares};
        const short hbc{high_bit_count(intersects_squares)};
        if (hbc != konst::rt_sz)
        {
            break;
        }
        const short subrow{static_cast<short>((i % konst::sz) / konst::rt_sz + sqr_sub_id::row_a)};
        short superset{0x0}, xorset{0x0};
        for (short j = 0; j < konst::rt_sz; j++)
        {
            int_sq[j] = equiv(get_1st_mapped_short(temp_isec));
            sq_rw[j] = square_subset_get(board, int_sq[j], subrow);
            temp_isec &= ~get_1st_mapped_short(temp_isec);
        }
        for (short j = 0; j < konst::rt_sz; j++)
        {
            superset |= xorset & sq_rw[j];
            xorset ^= sq_rw[j];
        }
        xorset &= ~superset;
        if (xorset == 0)
        {
            continue;
        }
        const short xs{high_bit_count(xorset)};
        short temp_xset{xorset};
        short x_sqr_id{0x0};
        for (short xj = 0; xj < xs; xj++)
        {
            short xset_next{get_1st_mapped_short(temp_xset)};
            for (short j = 0; j < konst::rt_sz; j++)
            {
                x_sqr_id |= (xset_next & sq_rw[j]) ? (1 << j) : 0;
            }
            temp_xset &= ~xset_next;
        }
        const short x_hbc{high_bit_count(x_sqr_id)};
        temp_xset = xorset;
        for (short j = 0; j < x_hbc; j++)
        {
            short square_to_cull = equiv(get_1st_mapped_short(x_sqr_id));
            short square_number{int_sq[square_to_cull]};
            short value{get_1st_mapped_short(temp_xset)};
            board = cull_square_from_row(board, square_number, value,subrow);
            temp_xset &= ~value;
            x_sqr_id &= ~square_to_cull;
        }
        // get square subsets for given row
        // comparison....
        // something?
    }
    return board;
}

std::array<short, konst::sqr_sz> sqr_prune(
    std::array<short, konst::sqr_sz> board)
{
    short candidate_pair{0x0};
    for (short i = 0; i < konst::sqr_sz; i += konst::sz)
    {
        for (short j = 0; j < konst::sz; j++)
        {
            if (board[i+j] <= 0)
            {
                continue;
            }
            else if (high_bit_count(board[i+j], 2))
            {
                for (short k = j + 1; k < konst::sz - j; k++)
                {
                    candidate_pair = board[i+j] == board[i+k] ? board[i+j] : candidate_pair;
                }
            }
        }
        if (high_bit_count(candidate_pair, 2))
        {
            for (short j = 0; j < konst::sz; j++)
            {
                if (board[i+j] <= 0)
                {
                    continue;
                }
                else if (board[i+j] != candidate_pair && high_bit_count(board[i+j]) > 1)
                {
                    #ifdef DEBUG
                    std::cout << "sqr_set " << algae::to[i+j] << " from ";
                    draw_candidates(c[i+j]);
                    #endif
                    board[i+j] &= ~candidate_pair;
                    #ifdef DEBUG
                    std::cout << "\t   to   ";
                    draw_candidates(c[i+j]);
                    #endif
                }
            }
        }
        candidate_pair = 0x0;
        // if 2 squares each have 2 candidates
        // and those 2 candidates are the same
        // then remove those candidates from all other candidate sets
    }
    return board;
}

std::array<short, konst::sqr_sz> row_prune(
    std::array<short, konst::sqr_sz> board)
{
    short candidate_pair{0x0};
    for (short i = 0; i < konst::th_sz; i += konst::rt_sz)
    {
       for (short j = 0; j < konst::sz; j++)
       {
            //i = (i<0) ? 0 : i;
            const short r_1{grp(i, j)};
            if (board[r_1] <= 0)
            {
                continue;
            }
            else if (high_bit_count(board[r_1], 2))
            {
                for (short k = j + 1; k < konst::sz - j; k++)
                {
                    const short r_2{grp(i, k)};
                    candidate_pair = board[r_1] == board[r_2] ? board[r_1] : candidate_pair;
                }
            }
       }
        if (high_bit_count(candidate_pair, 2))
        {
            for (short j = 0; j < konst::sz; j++)
            {
                const short r{grp(i, j)};
                if (board[r] <= 0)
                {
                    continue;
                }
                else if (board[r] != candidate_pair && high_bit_count(board[r]) > 1)
                {
                    #ifdef DEBUG
                    std::cout << "row_set " << algae::to[r] << " from ";
                    draw_candidates(c[r]);
                    #endif
                    board[r] &= ~candidate_pair;
                    #ifdef DEBUG
                    std::cout << "\t   to   ";
                    draw_candidates(c[r]);
                    #endif
                }
            }
        }
       candidate_pair = 0x0;
    }
    return board;
}

std::array<short, konst::sqr_sz> col_prune(
    std::array<short, konst::sqr_sz> board)
{
    short candidate_pair{0x0};
    for (short i = 0; i < konst::sz; i++)
    {
        const short r{grp(0, i)};
        for (short j = r; j < r + konst::th_sz; j += konst::rt_sz)
        {
            if (board[j] <= 0)
            {
                continue;
            }
            else if (high_bit_count(board[j], 2))
            {
                for (short k = (j + 3); k < r + konst::th_sz; k += konst::rt_sz)
                {
                    candidate_pair = board[j] == board[k] ? board[j] : candidate_pair;
                }
            }
        }
        if (high_bit_count(candidate_pair, 2))
        {
            for (short j = r; j < r + konst::th_sz; j += konst::rt_sz)
            {
                if (board[j] <= 0)
                {
                    continue;
                }
                else if (board[j] != candidate_pair && high_bit_count(board[j]) > 1)
                {
                    #ifdef DEBUG
                    std::cout << "col_set " << algae::to[j] << " from ";
                    draw_candidates(c[j]);
                    #endif
                    board[j] &= ~candidate_pair;
                    #ifdef DEBUG
                    std::cout <<"\t   to   ";
                    draw_candidates(c[j]);
                    #endif
                }
            }
        }
        candidate_pair = 0x0;
    }
    return board;
}

std::array<short, konst::sqr_sz> prune(
    std::array<short, konst::sqr_sz> board)
{
    board = sqr_prune(board);
    board = row_prune(board);
    board = col_prune(board);
    return board;
}

std::array<short, konst::sqr_sz> try_solo_find(
    std::array<short, konst::sqr_sz> board)
{
    short index = find_solo(board);
    while (index != (-1))
    {
        short value = equiv(board[index]);
        board[index] = -value;
        #ifdef DEBUG
        bool FAILURE{(b[index] == sref[index]) ? false : true};
        if (FAILURE)
        {
            std::cout << "ERR\n";
        }
        std::cout << "sol_i_" << b[index] << "_at_" << algae::to[index] << '\n';
        #endif
        board = set_can(board);
        index = (value == 0) ? (-1) : find_solo(board);
    }
    return board;
}

std::array<short, konst::sqr_sz> try_row_find(
    std::array<short, konst::sqr_sz> board)
{
    if (!blank_check(board))
    {
        return board;
    }
    std::array<short, 0x2> value = row_find(board);
    while (value[0] != 0x5)
    {
        for (short i = 0; i < konst::sz; i++)
        {
            const short position{grp(value[1], i)};
            if ((value[0] & board[position]) != 0 && board[position] > 0)
            {
                board[position] = -equiv(value[0]);
                #ifdef DEBUG
                bool FAILURE{(b[grp(value[1], i)] == sref[grp(value[1], i)]) ? false : true};
                if (FAILURE)
                {
                    std::cout << "ERR\n";
                }
                short grep{grp(value[1], i)};
                std::cout << "row_i_" << b[grep] << "_at_" << algae::to[grep] << '\n';
                #endif
            }
        }
        board = set_can(board);
        value = row_find(board);
    }
    return board;
}

std::array<short, konst::sqr_sz> try_col_find(
    std::array<short, konst::sqr_sz> board)
{
    if (!blank_check(board))
    {
        return board;
    }
    std::array<short, 0x2> value = col_find(board);
    while (value[0] != 0x5)
    {
        for (short i = value[1]; i < (value[1] + konst::th_sz); i += konst::rt_sz)
        {
            if ((value[0] & board[i]) != 0 && board[i] > 0)
            {
                board[i] = -equiv(value[0]);
                #ifdef DEBUG
                bool FAILURE{(b[i] == sref[i]) ? false : true};
                if (FAILURE)
                {
                    std::cout << "ERR\n";
                }
                std::cout << "col_i_" << b[i] << "_at_" << algae::to[i] << '\n';
                #endif
            }
        board = set_can(board);
        }
        value = col_find(board);
    }
    return board;
}

std::array<short, konst::sqr_sz> try_sqr_find(
    std::array<short, konst::sqr_sz> board)
{
    if (!blank_check(board))
    {
        return board;
    }
    std::array<short, 0x2> value = sqr_find(board);
    while (value[0] != 0x5)
    {
        for (short i = value[1]; i < (value[1] + konst::sz); i++)
        {
            if ((value[0] & board[i]) != 0 && board[i] > 0)
            {
                board[i] = -equiv(value[0]);
                #ifdef DEBUG
                bool FAILURE{(b[i] == sref[i]) ? false : true};
                if (FAILURE)
                {
                    std::cout << "ERR\n";
                }
                std::cout << "sqr_i_" << b[i] << "_at_" << algae::to[i] << '\n';
                #endif
            }
        }
        board = set_can(board);
        value = sqr_find(board);
    }
    return board;
}

short diff_magn(
    std::array<short, konst::sqr_sz> board_1,
    std::array<short, konst::sqr_sz> board_2)
{
    short diff_counter{0};
    for (short i = 0; i < konst::sqr_sz; i++)
    {
        diff_counter += (board_1[i] == board_2[i]) ? 0 : 1;
    }
    return diff_counter;
}