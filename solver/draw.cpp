#include <iostream>

/*
reference board:
00 01 02 | 27 28 29 | 54 55 56
03 04 05 | 30 31 32 | 57 58 59
06 07 08 | 33 34 35 | 60 61 62
---------x----------x---------
09 10 11 | 36 37 38 | 63 64 65
12 13 14 | 39 40 41 | 66 67 68
15 16 17 | 42 43 44 | 69 70 71
---------x----------x---------
18 19 20 | 45 46 47 | 72 73 74
21 22 23 | 48 49 50 | 75 76 77
24 25 26 | 51 52 53 | 78 79 80
*/

/*
draw data represented in candidate register
*/
void draw_candidates(unsigned short candidat)
{
    if (candidat & 0x100)
    {
        std::cout << '9' << ' ';
    }
    if (candidat & 0x80)
    {
        std::cout << '8' << ' ';
    }
    if (candidat & 0x40)
    {
        std::cout << '7' << ' ';
    }
    if (candidat & 0x20)
    {
        std::cout << '6' << ' ';
    }
    if (candidat & 0x10)
    {
        std::cout << '5' << ' ';
    }
    if (candidat & 0x8)
    {
        std::cout << '4' << ' ';
    }
    if (candidat & 0x4)
    {
        std::cout << '3' << ' ';
    }
    if (candidat & 0x2)
    {
        std::cout << '2' << ' ';
    }
    if (candidat & 0x1)
    {
        std::cout << '1' << ' ';
    }
}
/*
draw board as it should appear
sort of evil (c'est tres literal)
*/
void draw_board(unsigned short* b)
{
    std::cout << b[0]  << ' ' << b[1]  << ' ' << b[2]  << " | ";
    std::cout << b[27] << ' ' << b[28] << ' ' << b[29] << " | ";
    std::cout << b[54] << ' ' << b[55] << ' ' << b[56] << '\n';
    std::cout << b[3]  << ' ' << b[4]  << ' ' << b[5]  << " | ";
    std::cout << b[30] << ' ' << b[31] << ' ' << b[32] << " | ";
    std::cout << b[57] << ' ' << b[58] << ' ' << b[59] << '\n';
    std::cout << b[6]  << ' ' << b[7]  << ' ' << b[8]  << " | ";
    std::cout << b[33] << ' ' << b[34] << ' ' << b[35] << " | ";
    std::cout << b[60] << ' ' << b[61] << ' ' << b[62] << '\n';
    std::cout << "------x-------x------\n";
    std::cout << b[9]  << ' ' << b[10] << ' ' << b[11] << " | ";
    std::cout << b[36] << ' ' << b[37] << ' ' << b[38] << " | ";
    std::cout << b[63] << ' ' << b[64] << ' ' << b[65] << '\n';
    std::cout << b[12] << ' ' << b[13] << ' ' << b[14] << " | ";
    std::cout << b[39] << ' ' << b[40] << ' ' << b[41] << " | ";
    std::cout << b[66] << ' ' << b[67] << ' ' << b[68] << '\n';
    std::cout << b[15] << ' ' << b[16] << ' ' << b[17] << " | ";
    std::cout << b[42] << ' ' << b[43] << ' ' << b[44] << " | ";
    std::cout << b[69] << ' ' << b[70] << ' ' << b[71] << '\n';
    std::cout << "------x-------x------\n";
    std::cout << b[18] << ' ' << b[19] << ' ' << b[20] << " | ";
    std::cout << b[45] << ' ' << b[46] << ' ' << b[47] << " | ";
    std::cout << b[72] << ' ' << b[73] << ' ' << b[74] << '\n';
    std::cout << b[21] << ' ' << b[22] << ' ' << b[23] << " | ";
    std::cout << b[48] << ' ' << b[49] << ' ' << b[50] << " | ";
    std::cout << b[75] << ' ' << b[76] << ' ' << b[77] << '\n';
    std::cout << b[24] << ' ' << b[25] << ' ' << b[26] << " | ";
    std::cout << b[51] << ' ' << b[52] << ' ' << b[53] << " | ";
    std::cout << b[78] << ' ' << b[79] << ' ' << b[80] << '\n';
}