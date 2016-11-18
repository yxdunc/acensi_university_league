#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool    escape_is_around(std::vector< std::string > input)
{
    if(input[1][1] == 'e') return (true);
    else if(input[2][2] == 'e') return (true);
    else if(input[2][0] == 'e') return (true);
    else return (false);
}

int main()
{
    std::vector< std::string >  input;
    char                word[4];
    char                tile;

    while (std::cin>>word) input.push_back(word);
    
    if (escape_is_around(input))
        tile = 'e';
    else
        tile = '-';
    
    if(input[1][1] == tile) // UP
    {
        std::cout << "UP" << std::endl;
    }
    else if(input[2][2] == tile) // RIGHT
    {
        std::cout << "RIGHT" << std::endl;
    }
    else if(input[2][0] == tile) // LEFT
    {
        std::cout << "LEFT" << std::endl;
    }
    else // DOWN
    {
        std::cout << "DOWN" << std::endl;
    }
    
    // debug
    std::cerr << input[0] << std::endl
              << input[1] << std::endl
              << input[2] << std::endl
              << input[3] << std::endl;
    //!debug
    
    return (0);
}
