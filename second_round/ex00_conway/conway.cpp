#include <iostream>
#include <vector>
#include <map>
using namespace std;


class coord
{
    public:
        coord() {};
        coord(int x, int y) : x(x), y(y) {};
        int x;
        int y;

		std::string serialize() { return (std::to_string(this->x) + " " + std::to_string(this->y)); };
};

std::vector<coord>  append(std::vector<coord> a, std::vector<coord> b)
{
    a.insert( a.end(), b.begin(), b.end() );
    return (a);
}
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

std::vector< coord > is_neighbour(std::vector< std::string > board, coord pos, char c)
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
           && board[n_pos[i].x][n_pos[i].y] == c)
            res.push_back(n_pos[i]);
    }
    
    return (res);
}

std::vector< coord > neighbour_available(std::vector< std::string > board, coord pos)
{
    return (is_neighbour(board, pos, '-'));
}
std::vector< coord > neighbour_unavailable(std::vector< std::string > board, coord pos)
{
    return (append(is_neighbour(board, pos, 'b'), is_neighbour(board, pos, 'w')));
}

std::vector< coord >    check_exploder(std::vector<std::string> board, char player)
{
    std::vector< coord >    res;
    bool                    complet;
    
    complet = true;
    /* tiger */
/*    res.push_back(coord(15, 15));
    res.push_back(coord(15, 16));
    res.push_back(coord(13, 16));
    res.push_back(coord(14, 18));
    res.push_back(coord(15, 19));
    res.push_back(coord(15, 20));
    res.push_back(coord(15, 21));
*/    /**/
    /* heart patern */
    res.push_back(coord(15, 15));
    res.push_back(coord(15, 17));
    res.push_back(coord(16, 15));
    res.push_back(coord(16, 16));
    res.push_back(coord(16, 17));
    res.push_back(coord(17, 16));
    
    for (int i = 0; i < res.size(); i++)
    {
        if(is_neighbour(board, res[i], (player == 'w') ? 'b' : 'w').size() > 0)
            return (std::vector< coord >());
        if(board[res[i].x][res[i].y] == '-')
            complet = false;
    }
    if (complet)
        return (std::vector< coord >());
    return (res);
}

bool    print_first_av(std::vector<std::string> board, std::vector< coord > explo)
{
    if(explo.size() == 0)
        return (false);
    for (int i = 0; i < explo.size(); i++)
    {    
        if (is_available(board, explo[i]))
        {
            std::cout << explo[i].x << " " <<  explo[i].y << std::endl;
            return (true);
        }
    }
    return (false);
}
void    incr_score_neighbour(std::vector< coord > free_nb, std::map< std::string, int > &result, int inc)
{
    for(int i = 0; i < free_nb.size(); i++)
    {
        result[free_nb[i].serialize()] = result[free_nb[i].serialize()] + inc;
    }
}


void    suicide_penalty(std::vector<std::string> board, std::vector< coord > free_nb, std::map< std::string, int > &result, int inc)
{
    for(int i = 0; i < free_nb.size(); i++)
    {
        if(neighbour_unavailable(board, free_nb[i]).size() != 3 && neighbour_unavailable(board, free_nb[i]).size() != 2)
            result[free_nb[i].serialize()] = result[free_nb[i].serialize()] + inc;
    }
}

bool    print_deadly(std::vector< std::string > board, std::vector< coord > them, std::vector< coord > us)
{
    std::map< std::string, int >    result;
    std::pair< std::string, int >   max;
    std::vector<coord>              free_nb;
    std::vector<coord>              not_free_nb;

    max.second = -142;
    
    for (int i = 0; i < them.size(); i++)
    {
        free_nb = neighbour_available(board, them[i]);
        not_free_nb = neighbour_unavailable(board, them[i]);
        if (not_free_nb.size() < 4)
            incr_score_neighbour(free_nb, result, 100);
    }
    for (int i = 0; i < us.size(); i++)
    {
        free_nb = neighbour_available(board, us[i]);
        not_free_nb = neighbour_unavailable(board, us[i]);
        if (not_free_nb.size() < 4)
            incr_score_neighbour(free_nb, result, -1);
        suicide_penalty(board, free_nb, result, -10);
        
    }
    
    typedef std::map< std::string, int >::iterator it_type;
    for(it_type it = result.begin(); it != result.end(); it++)
    {
        std::cerr << "all.coord: " << it->first << std::endl;
        std::cerr << "all.score: " << it->second << std::endl;
        if (it->second > max.second)
		{
            max.first = it->first;
            max.second = it->second;
		}
    }
    
    if(max.second != -142)
    {
        std::cout << max.first << std::endl;
        std::cerr << "result of max: " << max.second << std::endl;
        return(1);
    }
    else
        return(0);
}

void nextMove(char player, vector <string> board)
{
    std::vector< coord >    us;
    std::vector< coord >    them;
    std::vector< coord >    available;
    std::vector< coord >    exploder;

    us = find(board, player);
    them = find(board, (player == 'w') ? 'b' : 'w');
    available = find(board, '-');
    exploder = check_exploder(board, player);

    std::cerr << "nb_them: " << them.size() << std::endl;
    if (them.size() == 0)
    {
        std::cout << 15 << " " <<  15 << std::endl;
        return ;
    }
    if (print_deadly(board, them, us)) return ;
    if (print_first_av(board, exploder)) return ;
    std::cout << available[available.size()/5].x << " " <<  available[available.size()/5].y << std::endl;
    
    return ;
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
