#include "sudokonst.h"
#include <array>
#include <vector>
//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

/*
corrects for rows
*/
const short grp(
    const short row_id,
    const short index)
{
    short id
        {row_id};
    id += index % 0x3;
    id += (index >= 0x3) ? konst::th_sz : 0;
    id += (index >= 0x6) ? konst::th_sz : 0;
    return id;
}

/*
returns actual value represented in candidates when ==1
*/
const short equiv(short c)
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
    for (short i = 0; i < konst::sqr_sz; ++i)
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
    short counter
        {0x0};
    for (short i = 0x0; i < 0x10; ++i)
    {
        counter += 0x1 & (bit_map >> i);
        if (counter > quant)
        {
            break;
        }
    }
    bool is_equal
        {counter == quant}; 
    return is_equal;
}

short high_bit_count(
    short bit_map)
{
    short counter
        {0x0};
    for (short i = 0x0; i < 0x10; ++i)
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

std::vector<short> range_over_row(
    short row_id)
{
    std::vector<short> range_vec
        {};
    row_id *= 3;
    for (short i = 0; i < konst::sz; ++i)
    {
        range_vec.push_back(grp(row_id, i));
    }
    return range_vec;
}

std::vector<std::vector<short>> ranges_over_rows()
{
    std::vector<std::vector<short>> ranges_vec
        {};
    for (short i = 0; i < konst::sz; ++i)
    {
        ranges_vec.push_back(range_over_row(i));
    }
    return ranges_vec;
}

std::vector<short> range_vec_create(
    short start,
    short end,
    short step)
{
    std::vector<short> range_vec
        {};
    for (short i = start; i < end; i += step)
    {
        range_vec.push_back(i);
    }
    return range_vec;
}

std::vector<short> range_vec_create(
    short type_id,
    char type)
{
    std::vector<short> range_vec
        {};
    switch (type)
    {
        case 'r':
        {
            range_vec = range_over_row(type_id);
            break;
        }
        case 'c':
        {
            short start
                {grp(0, type_id)};
            short end
                {static_cast<short>
                    (start + konst::th_sz)
                },
            step
                {konst::rt_sz};
            range_vec = range_vec_create(start, end, step);
            break;
        }
        case 's':
        {
            short start
                {static_cast<short>
                    (type_id * konst::sz)
                };
            short end
                {static_cast<short>
                    (start + konst::sz)
                },
            step
                {1};
            range_vec = range_vec_create(start, end, step);
            break;
        }
    }
    return range_vec;
}

std::vector<std::vector<short>> ranges_over_squares()
{
    std::vector<std::vector<short>> ranges_vec
        {};
    for (short i = 0; i < konst::sqr_sz; i += konst::sz)
    {
        short start
            {i},
        end
            {static_cast<short>
                (i + konst::sz)
            },
        step
            {1};
        ranges_vec.push_back(range_vec_create(start, end, step));
    }
    return ranges_vec;
}

std::vector<std::vector<short>> ranges_over_columns()
{
    std::vector<std::vector<short>> ranges_vec
        {};
    std::vector<short> row_0_indices
        {range_over_row(0)};
    for (short index : row_0_indices)
    {
        short start
            {index},
        end
            {static_cast<short>
                (index + konst::th_sz)
            },
        step
            {konst::rt_sz};
        ranges_vec.push_back(range_vec_create(start, end, step));
    }
    return ranges_vec;
}

std::vector<std::vector<short>> ranges_vec_create(
    char type)
{
    std::vector<std::vector<short>> ranges_vec
        {};
    switch (type)
    {
        case 'r':
        {
            ranges_vec = ranges_over_rows();
            break;
        }
        case 'c':
        {
            ranges_vec = ranges_over_columns();
            break;
        }
        case 's':
        {
            ranges_vec = ranges_over_squares();
            break;
        }
    }
    return ranges_vec;
}