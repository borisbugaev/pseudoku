#include "sudokonst.h"
#include <array>
#include <vector>
//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

/*
functions to be used in sudoku evaluation
TODO: square set eval, set striking
*/

const unsigned char my_square(unsigned char locale);
void draw_candidates(short candidat);
std::array<short, konst::sqr_sz> set_can(
    std::array<short, konst::sqr_sz> board);
void draw_board(std::array<short, konst::sqr_sz> b);
const short grp(
    const short row_id,
    const short index);
const short equiv(short c);
bool blank_check(
    std::array<short, konst::sqr_sz> board);
bool high_bit_count(
    short bit_map,
    short quant);
short high_bit_count(
    short bit_map);
short get_1st_mapped_short(
    short bit_map);
std::vector<std::vector<short>> ranges_vec_create(
    char type);
std::vector<short> range_vec_create(
    short type_id,
    char type);
std::vector<short> range_vec_create(
    short start,
    short end,
    short step);
std::vector<short> range_over(
    short bits);
short get_candidate_set(
    std::array<short, konst::sqr_sz> board,
    std::vector<short> range_set);

const short UNDEF
    {-1};
const std::array<short, 0x2> UNDEF_TPL
    {UNDEF, UNDEF};

/*
returns index of first square where there is ==1 candidate
if none, returns -1
*/
short find_solo(
    std::array<short, konst::sqr_sz> board)
{
    for (short i = 0; i < konst::sqr_sz; ++i)
    {
        if ((board[i] & (board[i] - 1)) == 0
            && board[i] > 0)
        {
            return i;
        }
    }
    return UNDEF;
}

short set_xor_search(
    std::array<short, konst::sqr_sz> board,
    std::vector<short> scope)
{
    short add_only_set
        {0x0},
    my_set
        {0x0};
    for (short index : scope)
    {
        const short can_at_index
            {static_cast<short>
                (board[index] >= 0
                    ? board[index] : 0)
            };
        add_only_set |= my_set & can_at_index;
        my_set ^= can_at_index;
    }
    const short my_xor
        {static_cast<short>
            (my_set & ~add_only_set)
        };
    return my_xor;
}

std::array<short, 0x2> generic_find(
    std::array<short, konst::sqr_sz> board,
    char type)
{
    short set
        {0x0},
    sub_range_index
        {0x0};
    std::vector<std::vector<short>> my_range
        {ranges_vec_create(type)};
    for (std::vector<short> sub_range : my_range)
    {
        set = set_xor_search(board, sub_range);
        if (set)
        {
            return {get_1st_mapped_short(set), sub_range_index};
        }
        set = 0x0;
        sub_range_index++;
    }
    return UNDEF_TPL;
}

std::array<short, konst::sqr_sz> cull_square_by_col(
    std::array<short, konst::sqr_sz> board,
    short square_number,
    short value_to_cull,
    short subscript_to_preserve)
{
    const short start_offset
        {static_cast<short>
            ((subscript_to_preserve == sqr_sub_id::col_1)
            ? 1 : 0)
        };
    const short end_offset
        {static_cast<short>
            ((subscript_to_preserve == sqr_sub_id::col_3)
            ? 1 : 0)
        };
    const short sqr_num
        {static_cast<short>
            (square_number * konst::sz)
        };
    const short start
        {static_cast<short>
            (sqr_num + start_offset)
        };
    const short end
        {static_cast<short>
            (sqr_num + konst::sz - end_offset)
        };
    for (short i = start; i < end; ++i)
    {
        if (i % konst::rt_sz == subscript_to_preserve)
        {
            continue;
        }
        if (board[i] > 0 && board[i] & value_to_cull)
        {
            board[i] &= ~value_to_cull;
        }
    }
    return board;
}

std::array<short, konst::sqr_sz> cull_square_from_row(
    std::array<short, konst::sqr_sz> board,
    short square_number,
    short value_to_cull,
    short subscript_to_preserve)
{
    const short start_offset
        {static_cast<short>
            ((subscript_to_preserve == sqr_sub_id::row_a)
            ? konst::rt_sz : 0)
        };
    const short mid_offset
        {static_cast<short>
            ((subscript_to_preserve == sqr_sub_id::row_b)
            ? konst::rt_sz : 0)
        };
    const short end_offset
        {static_cast<short>
            ((subscript_to_preserve == sqr_sub_id::row_c)
            ? konst::rt_sz : 0)
        };
    const short sqr_num
        {static_cast<short>
            (square_number * konst::sz)
        };
    const short start
        {static_cast<short>
            (sqr_num + start_offset)
        };
    const short mid
        {static_cast<short>
            (sqr_num + mid_offset)
        };
    const short end
        {static_cast<short>
            (sqr_num + konst::sz - end_offset)
        };
    for (short i = start; i < end; ++i)
    {
        if (mid_offset
            && i == mid)
        {
            i += konst::rt_sz;
            continue;
        }
        if (board[i] > 0 && board[i] & value_to_cull)
        {
            board[i] &= ~value_to_cull;
        }
    }
    return board;
}

const short col_intersec(
    short subscript)
{
    short intersec
        {0x0};
    const short start
        {grp(0, subscript)};
    for (short i = start; i < start + konst::th_sz; i += konst::rt_sz)
    {
        intersec |= 1 << my_square(i);
    }
    return intersec;
}

const short row_intersec(
    short subscript)
{
    short intersec
        {0x0};
    for (short i = 0; i < konst::sz; ++i)
    {
        const short my_loc
            {grp(subscript, i)};
        intersec |= 1 << my_square(my_loc);
    }
    return intersec;
}

short square_subset_get(
    std::array<short, konst::sqr_sz> board,
    short square_number,
    short subset_id)
{
    short square_set
        {0x0};
    const short squid
        {static_cast<short>
            (square_number * konst::sz)
        };
    if (subset_id < sqr_sub_id::row_a)
    {
        for (short i = squid + subset_id; i < konst::sz + squid + subset_id; i += konst::rt_sz)
        {
            square_set |= (board[i] > 0) ? board[i] : 0;
        }
    }
    else
    {
        const short a_subset_id
            {static_cast<short>
                ((subset_id - konst::rt_sz) * konst::rt_sz)
            };
        for (short i = squid + a_subset_id; i < squid + a_subset_id + konst::rt_sz; ++i)
        {
            square_set |= (board[i] > 0) ? board[i] : 0;
        }
    }
    return square_set;
}

std::array<short, konst::sqr_sz> prune_squares_by_cols(
    std::array<short, konst::sqr_sz> board)
{
    std::array<short, konst::rt_sz> sq_col{};
    for (short col = 0; col < konst::sz; ++col)
    {
        const short my_col_start
            {grp(0, col)};
        const short intersects_squares
            {col_intersec(col)};
        short temp_intersec
            {intersects_squares};
        const short hbc
            {high_bit_count(intersects_squares)};
        if (hbc != konst::rt_sz)
        {
            break;
        }
    }
    return board;
}

// if all instances of a candidate in a row are within a single square, remove that candidate
// from indices in the square which are not in the row
std::array<short, konst::sqr_sz> prune_squares_by_rows(
    std::array<short, konst::sqr_sz> board)
{
    std::array<short, konst::rt_sz> sq_rw{}, int_sq{};
    for (short i = 0; i < konst::th_sz; i+=konst::rt_sz)
    {
        const short intersects_squares
            {row_intersec(i)};
        short temp_isec
            {intersects_squares};
        const short hbc
            {high_bit_count(intersects_squares)};
        if (hbc != konst::rt_sz)
        {
            break;
        }
        const short subrow
            {static_cast<short>
                ((i % konst::sz) / konst::rt_sz + sqr_sub_id::row_a)
            };
        short superset
            {0x0},
        xorset
            {0x0};
        for (short j = 0; j < konst::rt_sz; ++j)
        {
            int_sq[j] = equiv(get_1st_mapped_short(temp_isec)) - 1;
            sq_rw[j] = square_subset_get(board, int_sq[j], subrow);
            temp_isec &= ~get_1st_mapped_short(temp_isec);
        }
        for (short j = 0; j < konst::rt_sz; ++j)
        {
            superset |= xorset & sq_rw[j];
            xorset ^= sq_rw[j];
        }
        xorset &= ~superset;
        if (xorset == 0)
        {
            continue;
        }
        const short xs
            {high_bit_count(xorset)};
        short temp_xset
            {xorset};
        short x_sqr_id
            {0x0};
        for (short xj = 0; xj < xs; ++xj)
        {
            short xset_next
                {get_1st_mapped_short(temp_xset)};
            for (short j = 0; j < konst::rt_sz; ++j)
            {
                x_sqr_id |= (xset_next & sq_rw[j]) ? (1 << j) : 0;
            }
            temp_xset &= ~xset_next;
        }
        const short x_hbc
            {high_bit_count(x_sqr_id)};
        temp_xset = xorset;
        for (short j = 0; j < x_hbc; ++j)
        {
            short square_to_cull = equiv(get_1st_mapped_short(x_sqr_id)) - 1;
            short square_number
                {int_sq[square_to_cull]};
            short value
                {get_1st_mapped_short(temp_xset)};
            board = cull_square_from_row(board, square_number, value,subrow);
            temp_xset &= ~value;
            x_sqr_id &= ~get_1st_mapped_short(x_sqr_id);
        }
    }
    return board;
}

short get_candidate_pair(
    std::array<short, konst::sqr_sz> board,
    std::vector<short> range)
{
    short candidate_pair
        {0x0};
    for (short index : range)
    {
        if (board[index] <= 0)
        {
            continue;
        }
        else if (high_bit_count(board[index], 2))
        {
            for (short index_2 : range)
            {
                if (index == index_2)
                {
                    continue;
                }
                else
                {
                    candidate_pair = board[index] == board[index_2]
                        ? board[index] : candidate_pair;
                }
            }
        }
    }
    return candidate_pair;
}

std::array<short, konst::sqr_sz> prune_extraneous(
    std::array<short, konst::sqr_sz> board,
    std::vector<short> range,
    short candidate_pair)
{
    for (short index : range)
    {
        if (board[index] <= 0)
        {
            continue;
        }
        else if (board[index] != candidate_pair
            && high_bit_count(board[index]) > 1)
        {
            board[index] &= ~candidate_pair;
        }
    }
    return board;
}

std::array<short, konst::sqr_sz> generic_prune(
    std::array<short, konst::sqr_sz> board,
    char type)
{
    short candidate_pair
        {0x0};
    std::vector<std::vector<short>> ranges
        {ranges_vec_create(type)};
    for (std::vector<short> range : ranges)
    {
        candidate_pair = get_candidate_pair(board, range);
        if (high_bit_count(candidate_pair, 2))
        {
            board = prune_extraneous(board, range, candidate_pair);
        }
        candidate_pair = 0x0;
    } 
    return board;
}

std::array<short, konst::sqr_sz> prune(
    std::array<short, konst::sqr_sz> board)
{
    for (char type : konst::types)
    {
        board = generic_prune(board, type);
    }
    return board;
}

std::array<short, konst::sqr_sz> try_solo_find(
    std::array<short, konst::sqr_sz> board)
{
    short index = find_solo(board);
    while (index != UNDEF)
    {
        short value = equiv(board[index]);
        board[index] = -value;
        board = set_can(board);
        index = (value == 0) ? UNDEF : find_solo(board);
    }
    return board;
}

std::array<short, konst::sqr_sz> try_generic_find(
    std::array<short, konst::sqr_sz> board,
    char type)
{
    if (!blank_check(board))
    {
        return board;
    }
    std::array<short, 0x2> value = generic_find(board, type);
    if (value[0] == UNDEF)
    {
        return board;
    }
    std::vector<short> my_range
        {range_vec_create(value[1], type)};
    for (short position : my_range)
    {
        if (value[0] & board[position] && board[position] > 0)
        {
            board[position] = -equiv(value[0]);
            board = set_can(board);
            break;
        }
    }
    return board;
}

short diff_magn(
    std::array<short, konst::sqr_sz> board_1,
    std::array<short, konst::sqr_sz> board_2)
{
    short diff_counter
        {0};
    for (short i = 0; i < konst::sqr_sz; ++i)
    {
        diff_counter += (board_1[i] == board_2[i]) ? 0 : 1;
    }
    return diff_counter;
}

std::array<short, konst::sqr_sz> diff_at(
    std::array<short, konst::sqr_sz> board_1,
    std::array<short, konst::sqr_sz> board_2)
{
    for (short i = 0; i < konst::sqr_sz; ++i)
    {
        board_1[i] = board_1[i] == board_2[i] ? 0 : 1;
    }
    return board_1;
}