
#include <math.h>

namespace implicit_konstants
{
    const long long root_n{};
    const long long size_n{root_n * root_n};
    const long long size_b{size_n * size_n};
}

using namespace implicit_konstants;

struct sq_sub_row
{

};

struct sq_sub_column
{

};

struct sub_square
{
    long long zero_index{};
    sq_sub_row* subrow[root_n];
    sq_sub_column* subcol[root_n];
};

struct board
{

};