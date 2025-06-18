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

void draw_candidates(unsigned short candidat);
std::array<unsigned short, konst::bs> init_can(
    std::array<unsigned short, konst::bs> board);
void draw_board(std::array<unsigned short, konst::bs> b);


/*
corrects for rows
*/
const short grp(
    const short row_id,
    const short index)
{
    short id{row_id};
    id += index % 0x3;
    id += (index >= 0x3) ? konst::sb : 0;
    id += (index >= 0x6) ? konst::sb : 0;
    return id;
}

/*
returns actual value represented in candidates when ==1
*/
constexpr short equiv(unsigned short c)
{
    return ((0x100 & c)/0x100) * 9
    + ((0x80 & c)/0x80) * 8
    + ((0x40 & c)/0x40) * 7
    + ((0x20 & c)/0x20) * 6
    + ((0x10 & c)/0x10) * 5
    + ((0x08 & c)/0x08) * 4
    + ((0x04 & c)/0x04) * 3
    + ((0x02 & c)/0x02) * 2
    + (0x01 & c);
}

bool blank_check(
    std::array<unsigned short, konst::bs> b)
{
    for (short i = 0; i < konst::bs; i++)
    {
        if (b[i] == 0)
        {
            return true;
        }
    }
    return false;
}

short high_bit_count(
    unsigned short bit_map)
{
    short counter{0x0};
    for (short i = 0x0; i < 0x10; i++)
    {
        counter += 0x1 & (bit_map >> i);
    }
    return counter;
}

short get_1st_mapped_short(
    unsigned short bit_map)
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
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    for (short i = 0; i < konst::bs; i++)
    {
        if ((c[i] & (c[i] - 1)) == 0 && b[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

unsigned short set_xor_search(
    std::array<unsigned short, konst::bs> c,
    short start,
    char type)
{
    short add_only_set{0x0}, my_set{0x0};
    const short i_col{0x3}, i_els{0x1}, f_row{0x0};
    short by{(type == 'c') ? i_col : i_els};
    short from{(type == 'r') ? f_row : start};
    short buf{(type == 'c') ? konst::sb : konst::sz};
    for (short i = from; i < (from + buf); i+=by)
    {
        const short j{(type == 'r') ? grp(start, i) : i};
        add_only_set |= my_set & c[j];
        my_set ^= c[j];
    }
    return my_set & ~add_only_set; //n-input 'true' xor
}

std::array<short, 0x2> sqr_find(
    std::array<unsigned short, konst::bs> c)
{
    short sqr_set{0x0};
    for (short i = 0; i < konst::bs; i+=9)
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
    std::array<unsigned short, konst::bs> c)
{
    short row_set{0x0};
    for (short i = 0; i < konst::sb; i+=3)
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
    std::array<unsigned short, konst::bs> c)
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

std::array<unsigned short, konst::bs> sqr_prune(
    std::array<unsigned short, konst::bs> c)
{
    short candidate_pair{0x0};
    for (short i = 0; i < konst::bs; i += konst::sz)
    {
        for (short j = 0; j < konst::sz; j++)
        {
            if (c[i+j] == 0)
            {
                continue;
            }
            else if (high_bit_count(c[i+j]) == 2)
            {
                for (short k = j + 1; k < konst::sz - j; k++)
                {
                    candidate_pair = c[i+j] == c[i+k] ? c[i+j] : candidate_pair;
                }
            }
        }
        for (short j = 0; j < konst::sz; j++)
        {
            if (j == 0 && high_bit_count(candidate_pair) != 2)
            {
                break;
            }
            if (c[i+j] != candidate_pair && high_bit_count(c[i+j]) > 1)
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
            #ifdef DEBUG_is
            else{
            std::cout << "sqr_____" << algae::to[i+j] << "_is ";
            draw_candidates(c[i+j]);
            }
            #endif
        }
        candidate_pair = 0x0;
        // if 2 squares each have 2 candidates
        // and those 2 candidates are the same
        // then remove those candidates from all other candidate sets
    }
    return c;
}

std::array<unsigned short, konst::bs> row_prune(
    std::array<unsigned short, konst::bs> c)
{
    short candidate_pair{0x0};
    for (short i = 0; i < konst::sb; i+=3)
    {
       for (short j = 0; j < konst::sz; j++)
       {
            //i = (i<0) ? 0 : i;
            const short r_1{grp(i, j)};
            if (c[r_1] == 0)
            {
                continue;
            }
            else if (high_bit_count(c[r_1]) == 2)
            {
                for (short k = j + 1; k < konst::sz - j; k++)
                {
                    const short r_2{grp(i, k)};
                    candidate_pair = c[r_1] == c[r_2] ? c[r_1] : candidate_pair;
                }
            }
            #ifdef DEBUG_REV
            std::cout << "at " << algae::to[r_1] << ' ';
            draw_candidates(c[r_1]);
            #endif
       }
       for (short j = 0; j < konst::sz; j++)
       {
            if (j == 0 && high_bit_count(candidate_pair) != 2)
            {
                break;
            }
            const short r{grp(i, j)};
            if (c[r] != candidate_pair && high_bit_count(c[r]) > 1)
            {
                #ifdef DEBUG
                std::cout << "row_set " << algae::to[r] << " from ";
                draw_candidates(c[r]);
                #endif
                c[r] &= ~candidate_pair;
                #ifdef DEBUG_REV
                std::cout << "pair__is ";
                draw_candidates(candidate_pair);
                #endif
                #ifdef DEBUG
                std::cout << "\t   to   ";
                draw_candidates(c[r]);
                #endif
            }
            #ifdef DEBUG_is
            else{
            std::cout << "row_____" << algae::to[r] << "_is ";
            draw_candidates(c[r]);
            }
            #endif
       }
       candidate_pair = 0x0;
    }
    return c;
}

std::array<unsigned short, konst::bs> col_prune(
    std::array<unsigned short, konst::bs> c)
{
    short candidate_pair{0x0};
    for (short i = 0; i < konst::sz; i++)
    {
        const short r{grp(0, i)};
        for (short j = r; j < r + konst::sb; j+=3)
        {
            if (c[j] == 0x0)
            {
                continue;
            }
            else if (high_bit_count(c[j]) == 2)
            {
                for (short k = (j + 3); k < r + konst::sb; k+=3)
                {
                    candidate_pair = c[j] == c[k] ? c[j] : candidate_pair;
                }
            }
        }
        for (short j = r; j < r + konst::sb; j+=3)
        {
            if (j == r && high_bit_count(candidate_pair) != 2)
            {
                break;
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
            #ifdef DEBUG_is
            else{
            std::cout << "col_____" << algae::to[j] << "_is ";
            draw_candidates(c[j]);
            }
            #endif
        }
        candidate_pair = 0x0;
    }
    return c;
}

std::array<unsigned short, konst::bs> prune(
    std::array<unsigned short, konst::bs> c)
{
    c = sqr_prune(c);
    c = row_prune(c);
    c = col_prune(c);
    return c;
}

std::array<unsigned short, konst::bs> try_solo_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    short index = find_solo(b, c);
    while (index != (-1))
    {
        short value = equiv(c[index]);
        b[index] = value;
        #ifdef DEBUG
        bool FAILURE{(b[index] == sref[index]) ? false : true};
        if (FAILURE)
        {
            std::cout << "ERR\n";
        }
        std::cout << "sol_i_" << b[index] << "_at_" << algae::to[index] << '\n';
        #endif
        c = init_can(b);
        index = (value == 0) ? (-1) : find_solo(b, c);
    }

    return b;
}

std::array<unsigned short, konst::bs> try_row_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    if (!blank_check(b))
    {
        return b;
    }
    std::array<short, 0x2> value = row_find(c);
    while (value[0] != 0x5)
    {
        for (short i = 0; i < konst::sz; i++)
        {
            if ((value[0] & c[grp(value[1], i)]) != 0)
            {
                b[grp(value[1], i)] = equiv(value[0]);
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
        c = init_can(b);
        value = row_find(c);
    }
    return b;
}

std::array<unsigned short, konst::bs> try_col_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    if (!blank_check(b))
    {
        return b;
    }
    std::array<short, 0x2> value = col_find(c);
    while (value[0] != 0x5)
    {
        for (short i = value[1]; i < (value[1] + konst::sb); i+=3)
        {
            if ((value[0] & c[i]) != 0)
            {
                b[i] = equiv(value[0]);
                #ifdef DEBUG
                bool FAILURE{(b[i] == sref[i]) ? false : true};
                if (FAILURE)
                {
                    std::cout << "ERR\n";
                }
                std::cout << "col_i_" << b[i] << "_at_" << algae::to[i] << '\n';
                #endif
            }
        c = init_can(b);
        }
        value = col_find(c);
    }
    return b;
}

std::array<unsigned short, konst::bs> try_sqr_find(
    std::array<unsigned short, konst::bs> b,
    std::array<unsigned short, konst::bs> c)
{
    if (!blank_check(b))
    {
        return b;
    }
    std::array<short, 0x2> value = sqr_find(c);
    while (value[0] != 0x5)
    {
        for (short i = value[1]; i < (value[1] + konst::sz); i++)
        {
            if ((value[0] & c[i]) != 0)
            {
                b[i] = equiv(value[0]);
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
        c = init_can(b);
        value = sqr_find(c);
    }
    return b;
}

short diff_magn(
    std::array<unsigned short, konst::bs> b_1,
    std::array<unsigned short, konst::bs> b_2)
{
    short diff_counter{0};
    for (short i = 0; i < konst::bs; i++)
    {
        diff_counter += (b_1[i] == b_2[i]) ? 0 : 1;
    }
    return diff_counter;
}