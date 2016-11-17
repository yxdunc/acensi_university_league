#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
using namespace std;

int     score(char pos)
{
	//the score of each types of neighbour
    if(pos == 'h')
        return(200);
    else if(pos == 'm')
        return(18);
    else if(pos == 'd')
        return(11);
    else if(pos == '-')
        return(19);
    else
        return(0);
}

int     compute_prob(std::string input, int x, int y)
{
    int prob;
    
	//init
    prob = 0;

	//compute according to neighbour
    prob += (x != 0) ? score(input[(x - 1) * 10 + y + 2]) : 19;
    prob += (x != 9) ? score(input[(x + 1) * 10 + y + 2]) : 19;
    prob += (y != 0) ? score(input[x * 10 + (y - 1) + 2]) : 19;
    prob += (y != 9) ? score(input[x * 10 + (y + 1) + 2]) : 19;
    
	//compute according to neighbour neighbour
    prob += (x > 1) ? score(input[(x - 2) * 10 + y + 2]) / 10 : 1;
    prob += (x < 8) ? score(input[(x + 2) * 10 + y + 2]) / 10 : 1;
    prob += (y > 1) ? score(input[x * 10 + (y - 2) + 2]) / 10 : 1;
    prob += (y < 8) ? score(input[x * 10 + (y + 2) + 2]) / 10 : 1;
    return (prob);
}

int main() {
    int pos_prob;
    int max_prob;
    int final_x;
    int final_y;
    int first;
    
    std::string     temp;
    std::string     input;
    
    std::random_device r; 
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(0,9);
    int dice_roll = distribution(generator);
    
    max_prob = 0;
    first = 1;
    
    while (std::cin >> temp) input += temp;
    if (input == "INIT")
    {
		//positioning boats
        std::cout   << "0 9" << std::endl <<
        "9 "  <<  dice_roll  << std::endl <<
        "6 4:7 4"            << std::endl <<
        "0 2:0 3"            << std::endl <<
        "7 7:7 9"            << std::endl <<
        "1 8:4 8"            << std::endl <<
        "4 1:8 1"            << std::endl;
    }
    else
    {
		//browse the grid to find the hit with the highest prob
        for(int x = 0; x < 10; x++)
        {
            for(int y = 0; y < 10; y++)
            {
                if(input[x * 10 + y + 2] == '-')
                {
                    if(first)
                    {
                        final_x = x;
                        final_y = y;
                        first = !first;
                    }
                    pos_prob = compute_prob(input, x, y);
                    if(pos_prob > max_prob)
                    {
                        max_prob = pos_prob;
                        final_x = x;
                        final_y = y;
                    }
                        
                }
            }
        }
        std::cout << final_x << " " << final_y << std::endl;
    }
    return 0;
}
