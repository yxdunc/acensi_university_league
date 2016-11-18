#include <iostream>
#include <vector>
using namespace std;


class coord
{
    public:
        coord() {};
        coord(int x, int y) : x(x), y(y) {};
        int x;
        int y;
};

std::vector< coord >   find(std::vector< std::string > board, char c)
{
    std::vector< coord >    res;

    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[0].size(); y++)
        {
            if(board[x][y] == c)
                res.push_back(coord(x, y));
        }
    }
	return(res);
}

bool    is_available(std::vector< std::string > board, coord pos)
{
    return (board[pos.x][pos.y] == '-') ? true : false;
}

std::vector< coord > neighbour_available(std::vector< std::string > board, coord pos)
{
    std::vector< coord >    res;
    std::vector< coord >    n_pos;
    
    n_pos.push_back(coord(pos.x, pos.y + 1));
    n_pos.push_back(coord(pos.x, pos.y - 1));
    
    n_pos.push_back(coord(pos.x + 1, pos.y));
    n_pos.push_back(coord(pos.x + 1, pos.y + 1));
    n_pos.push_back(coord(pos.x + 1, pos.y - 1));
    
    n_pos.push_back(coord(pos.x - 1, pos.y));
    n_pos.push_back(coord(pos.x - 1, pos.y + 1));
    n_pos.push_back(coord(pos.x - 1, pos.y - 1));
    
    for (int i = 0; i < n_pos.size(); i++)
    {
        if(n_pos[i].x >= 0 && n_pos[i].y >= 0 && n_pos[i].x < 29 && n_pos[i].y < 29\
           && board[n_pos[i].x][n_pos[i].y] == '-')
            res.push_back(n_pos[i]);
    }
    
    return (res);
}

void nextMove(char player, vector <string> board)
{
    std::vector< coord >    us;
    std::vector< coord >    them;
    std::vector< coord >    available;
    std::vector< coord >    free_nb;

    us = find(board, player);
    them = find(board, (player == 'w') ? 'b' : 'w');
    available = find(board, '-');

    std::cerr << " 1 " << std::endl;
    if (them.size() == 0)
    {
        std::cerr << " 2 " << std::endl;
        std::cout << 15 << " " <<  15 << std::endl;
        return ;
    }
    for (int i = 0; i < them.size(); i++)
    {
        free_nb = neighbour_available(board, them[i]);
        if (free_nb.size() > 4)
        {
            std::cerr << " 3 " << std::endl;
            std::cout << free_nb[0].x << " " <<  free_nb[0].y << std::endl;
            return ;
        }
        std::cerr << " 3.1 " << std::endl;
    }
    std::cerr << " 4 " << std::endl;
    std::cout << available[0].x << " " <<  available[0].y << std::endl;
}

int main(void)
{
    char player;
    vector <string> board;

    cin >> player;

    for(int i=0; i<29; i++) {
        string s; cin >> s;
        board.push_back(s);
    }

    nextMove(player,board);

    return 0;
}
