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
    std::array<short, konst::sqr_sz> b)
{
    for (short i = 0; i < konst::sqr_sz; i++)
    {
        if (b[i] <= 0)
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
    std::array<short, konst::sqr_sz> b)
{
    for (short i = 0; i < konst::sqr_sz; i++)
    {
        if ((b[i] & (b[i] - 1)) == 0 && b[i] > 0)
        {
            return i;
        }
    }
    return -1;
}

short set_xor_search(
    std::array<short, konst::sqr_sz> b,
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
        const short cn_at_j{static_cast<short>(b[j] >= 0 ? b[j] : 0)};
        add_only_set |= my_set & cn_at_j;
        my_set ^= cn_at_j;
    }
    return my_set & ~add_only_set; //n-input 'true' xor
}

std::array<short, 0x2> sqr_find(
    std::array<short, konst::sqr_sz> c)
{
    short sqr_set{0x0};
    for (short i = 0; i < konst::sqr_sz; i += konst::sz)
    {
        sqr_set = set_xor_search(c, i, 's');
        if (sqr_set != 0)
        {
            return {get_1st_mapped_short(sqr_set), i};
        }
        sqr_set = 0x0;
    }
    return {0x5, 0x5};
}

std::array<short, 0x2> row_find(
    std::array<short, konst::sqr_sz> c)
{
    short row_set{0x0};
    for (short i = 0; i < konst::th_sz; i += konst::rt_sz)
    {
        row_set = set_xor_search(c, i, 'r');
        if (row_set != 0)
        {
            return {get_1st_mapped_short(row_set), i};
        }
        row_set = 0x0;
    }
    return {0x5, 0x5};
}

std::array<short, 0x2> col_find(
    std::array<short, konst::sqr_sz> c)
{
    short col_set{0x0}, j{};
    for (short i = 0; i < konst::sz; i++)
    {
        j = grp(0, i);
        col_set = set_xor_search(c, j, 'c');
        if (col_set != 0)
        {
            return {get_1st_mapped_short(col_set), j};
        }
        col_set = 0x0;
    }
    return {0x5, 0x5};
}

std::array<short, konst::sqr_sz> sqr_prune(
    std::array<short, konst::sqr_sz> c)
{
    short candidate_pair{0x0};
    for (short i = 0; i < konst::sqr_sz; i += konst::sz)
    {
        for (short j = 0; j < konst::sz; j++)
        {
            if (c[i+j] <= 0)
            {
                continue;
            }
            else if (high_bit_count(c[i+j], 2))
            {
                for (short k = j + 1; k < konst::sz - j; k++)
                {
                    candidate_pair = c[i+j] == c[i+k] ? c[i+j] : candidate_pair;
                }
            }
        }
        if (high_bit_count(candidate_pair, 2))
        {
            for (short j = 0; j < konst::sz; j++)
            {
                if (c[i+j] <= 0)
                {
                    continue;
                }
                else if (c[i+j] != candidate_pair && high_bit_count(c[i+j]) > 1)
                {
                    #ifdef DEBUG
                    std::cout << "sqr_set " << algae::to[i+j] << " from ";
                    draw_candidates(c[i+j]);
                    #endif
                    c[i+j] &= ~candidate_pair;
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
    return c;
}

std::array<short, konst::sqr_sz> row_prune(
    std::array<short, konst::sqr_sz> c)
{
    short candidate_pair{0x0};
    for (short i = 0; i < konst::th_sz; i += konst::rt_sz)
    {
       for (short j = 0; j < konst::sz; j++)
       {
            //i = (i<0) ? 0 : i;
            const short r_1{grp(i, j)};
            if (c[r_1] <= 0)
            {
                continue;
            }
            else if (high_bit_count(c[r_1], 2))
            {
                for (short k = j + 1; k < konst::sz - j; k++)
                {
                    const short r_2{grp(i, k)};
                    candidate_pair = c[r_1] == c[r_2] ? c[r_1] : candidate_pair;
                }
            }
       }
        if (high_bit_count(candidate_pair, 2))
        {
            for (short j = 0; j < konst::sz; j++)
            {
                const short r{grp(i, j)};
                if (c[r] <= 0)
                {
                    continue;
                }
                else if (c[r] != candidate_pair && high_bit_count(c[r]) > 1)
                {
                    #ifdef DEBUG
                    std::cout << "row_set " << algae::to[r] << " from ";
                    draw_candidates(c[r]);
                    #endif
                    c[r] &= ~candidate_pair;
                    #ifdef DEBUG
                    std::cout << "\t   to   ";
                    draw_candidates(c[r]);
                    #endif
                }
            }
        }
       candidate_pair = 0x0;
    }
    return c;
}

std::array<short, konst::sqr_sz> col_prune(
    std::array<short, konst::sqr_sz> c)
{
    short candidate_pair{0x0};
    for (short i = 0; i < konst::sz; i++)
    {
        const short r{grp(0, i)};
        for (short j = r; j < r + konst::th_sz; j += konst::rt_sz)
        {
            if (c[j] <= 0)
            {
                continue;
            }
            else if (high_bit_count(c[j], 2))
            {
                for (short k = (j + 3); k < r + konst::th_sz; k += konst::rt_sz)
                {
                    candidate_pair = c[j] == c[k] ? c[j] : candidate_pair;
                }
            }
        }
        if (high_bit_count(candidate_pair, 2))
        {
            for (short j = r; j < r + konst::th_sz; j += konst::rt_sz)
            {
                if (c[j] <= 0)
                {
                    continue;
                }
                else if (c[j] != candidate_pair && high_bit_count(c[j]) > 1)
                {
                    #ifdef DEBUG
                    std::cout << "col_set " << algae::to[j] << " from ";
                    draw_candidates(c[j]);
                    #endif
                    c[j] &= ~candidate_pair;
                    #ifdef DEBUG
                    std::cout <<"\t   to   ";
                    draw_candidates(c[j]);
                    #endif
                }
            }
        }
        candidate_pair = 0x0;
    }
    return c;
}

std::array<short, konst::sqr_sz> prune(
    std::array<short, konst::sqr_sz> c)
{
    c = sqr_prune(c);
    c = row_prune(c);
    c = col_prune(c);
    return c;
}

std::array<short, konst::sqr_sz> try_solo_find(
    std::array<short, konst::sqr_sz> b)
{
    short index = find_solo(b);
    while (index != (-1))
    {
        short value = equiv(b[index]);
        b[index] = -value;
        #ifdef DEBUG
        bool FAILURE{(b[index] == sref[index]) ? false : true};
        if (FAILURE)
        {
            std::cout << "ERR\n";
        }
        std::cout << "sol_i_" << b[index] << "_at_" << algae::to[index] << '\n';
        #endif
        b = set_can(b);
        index = (value == 0) ? (-1) : find_solo(b);
    }
    return b;
}

std::array<short, konst::sqr_sz> try_row_find(
    std::array<short, konst::sqr_sz> b)
{
    if (!blank_check(b))
    {
        return b;
    }
    std::array<short, 0x2> value = row_find(b);
    while (value[0] != 0x5)
    {
        for (short i = 0; i < konst::sz; i++)
        {
            const short position{grp(value[1], i)};
            if ((value[0] & b[position]) != 0 && b[position] > 0)
            {
                b[position] = -equiv(value[0]);
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
        b = set_can(b);
        value = row_find(b);
    }
    return b;
}

std::array<short, konst::sqr_sz> try_col_find(
    std::array<short, konst::sqr_sz> b)
{
    if (!blank_check(b))
    {
        return b;
    }
    std::array<short, 0x2> value = col_find(b);
    while (value[0] != 0x5)
    {
        for (short i = value[1]; i < (value[1] + konst::th_sz); i += konst::rt_sz)
        {
            if ((value[0] & b[i]) != 0 && b[i] > 0)
            {
                b[i] = -equiv(value[0]);
                #ifdef DEBUG
                bool FAILURE{(b[i] == sref[i]) ? false : true};
                if (FAILURE)
                {
                    std::cout << "ERR\n";
                }
                std::cout << "col_i_" << b[i] << "_at_" << algae::to[i] << '\n';
                #endif
            }
        b = set_can(b);
        }
        value = col_find(b);
    }
    return b;
}

std::array<short, konst::sqr_sz> try_sqr_find(
    std::array<short, konst::sqr_sz> b)
{
    if (!blank_check(b))
    {
        return b;
    }
    std::array<short, 0x2> value = sqr_find(b);
    while (value[0] != 0x5)
    {
        for (short i = value[1]; i < (value[1] + konst::sz); i++)
        {
            if ((value[0] & b[i]) != 0 && b[i] > 0)
            {
                b[i] = -equiv(value[0]);
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
        b = set_can(b);
        value = sqr_find(b);
    }
    return b;
}

short diff_magn(
    std::array<short, konst::sqr_sz> b_1,
    std::array<short, konst::sqr_sz> b_2)
{
    short diff_counter{0};
    for (short i = 0; i < konst::sqr_sz; i++)
    {
        diff_counter += (b_1[i] == b_2[i]) ? 0 : 1;
    }
    return diff_counter;
}