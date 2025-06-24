#include <string>
#include <iostream>

// massively unsafe cmd-line utility
int main (int argc, char** argv)
{
    if (argv[1])
    {
        const short input_arg{static_cast<short>(std::stoi(argv[1]))};
        for (int i = 0; i < 9; i++)
        {
            if (0x1 & input_arg >> i)
            {
                std::cout << i + 1 << ' ';
            }
        }
        std::cout << std::endl;
    }
    return 0;
}