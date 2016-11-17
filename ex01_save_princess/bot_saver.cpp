#include <iostream>
#include <vector>

void displayPathtoPrincess(int n, std::vector < std::string > grid)
{
    unsigned int princesse_x;
    unsigned int princesse_y;
    unsigned int bot_x;
    unsigned int bot_y;
    std::string  upside_move;
    std::string  side_move;
    
    for (unsigned int x = 0; x < n; x++)
    {
        for(unsigned int y = 0; y < n; y++)
        {
            if(grid[x][y] == 'p')
            {
                princesse_x = x;
                princesse_y = y;
            }
            else if (grid[x][y] == 'm')
            {
                bot_x = x;
                bot_y = y;
            }           
        }
    }
    if (princesse_x < bot_x)
    {
        upside_move = "UP";
        bot_x = bot_x - princesse_x;
    }
    else
    {
        upside_move = "DOWN";
        bot_x = princesse_x - bot_x;
    }

    if (princesse_y < bot_y)
    {
        side_move = "LEFT";
        bot_y = bot_y - princesse_y;
    }
    else
    {
        side_move = "RIGHT";
        bot_y = princesse_y - bot_y;
    }

    for (unsigned int i = 0; i < bot_x; i++)
        std::cout << upside_move << std::endl; 
    
    for (unsigned int z = 0; z < bot_y; z++)
        std::cout << side_move << std::endl; 
}
int main(void) {

    int m;
    std::vector < std::string > grid;

    std::cin >> m;

    for(int i=0; i<m; i++) {
        std::string s;
		std::cin >> s;
        grid.push_back(s);
    }

    displayPathtoPrincess(m,grid);

    return 0;
}
