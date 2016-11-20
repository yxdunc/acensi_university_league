#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <random>
#include <map>

using namespace std;

bool    escape_is_around(std::vector< std::string > input)
{
    if(input[1][1] == 'e') return (true);
    else if(input[2][2] == 'e') return (true);
    else if(input[2][0] == 'e') return (true);
    else return (false);
}

bool al()
{
    std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(0,1);
    int dice_roll = distribution(generator);
    
    return ((dice_roll == 1) ? true : false);
}

bool    read_bo(std::string str)
{
    bool res = false;
    string line;
    ifstream myfile ("example.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cerr << str << "::" << line << '\n';
            if(!line.compare(str))
                res = true;
        }
        myfile.close();
    }
           
    else cerr << "Unable to open file";
    return (res);
}

bool    write_bo(std::string str)
{
    ofstream myfile ("example.txt", fstream::app);
    if (myfile.is_open())
    {
        myfile << str << "\n";
        myfile.close();
        return (true);
    }
    else cerr << "Unable to open file";
    return(false);
}

int main()
{
    std::vector< std::string >  input;
    std::string         line;
    char                word[4];
    char                tile;

    while (std::cin>>word) input.push_back(word);
    
    if (escape_is_around(input))
    {
        tile = 'e';
        std::remove("example.txt");
    }
    else
    {
        tile = '-';
        //TODO add check of corner
    }
    
    if(!input[1].compare("---") && !input[2].compare("---") && !input[3].compare("--#")) // SPECIAL CASE
    {
        if(read_bo("SP"))
            std::cout << "UP" << std::endl;
        else
        {
            write_bo("SP");
            std::cout << "RIGHT" << std::endl;
        }
    }
    else if(!input[1].compare("###") && !input[2].compare("#--") && !input[3].compare("#--")) // SPECIAL CASE
    {
        if(!read_bo("INIT"))
            std::cout << "DOWN" << std::endl;
        else
            std::cout << "RIGHT" << std::endl;
    }
    else if(!input[1].compare("#--") && !input[2].compare("#--") && !input[3].compare("###")) // SPECIAL CASE
    {
        if(!read_bo("INIT"))
            std::cout << "RIGHT" << std::endl;
        else
            std::cout << "UP" << std::endl;
    }
    else if(input[1][1] == tile) // UP
    {
        std::cout << "UP" << std::endl;
    }
    else if(input[2][0] == tile) // LEFT
    {
        std::cout << "LEFT" << std::endl;
    }
    else if(input[2][2] == tile) // RIGHT
    {
        std::cout << "RIGHT" << std::endl;
    }
    else // DOWN
    {
        std::cout << "DOWN" << std::endl;
    }
    write_bo("INIT");
    return (0);
}
