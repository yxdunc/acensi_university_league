#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
using namespace std;

#define FIGX 15
#define FIGY 15

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

coord      find_first(std::vector< std::string > board, char c)
{
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[0].size(); y++)
        {
            if(board[x][y] == c)
                return(coord(x, y));
        }
    }
    std::cerr << "__not_found__" << std::endl;
	return(coord(-1, -1));
}


int      count(std::vector< std::string > board, char c)
{
    int    res;

    res = 0;
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[0].size(); y++)
        {
            if(board[x][y] == c)
                res++;
        }
    }
	return(res);
}

int     nb_neighbour(std::vector< std::string > board, coord pos, char c)
{
    int    res;
    std::vector< coord >    n_pos;
    
    n_pos.push_back(coord(pos.x, pos.y + 1));
    n_pos.push_back(coord(pos.x, pos.y - 1));
    
    n_pos.push_back(coord(pos.x + 1, pos.y));
    n_pos.push_back(coord(pos.x + 1, pos.y + 1));
    n_pos.push_back(coord(pos.x + 1, pos.y - 1));
    
    n_pos.push_back(coord(pos.x - 1, pos.y));
    n_pos.push_back(coord(pos.x - 1, pos.y + 1));
    n_pos.push_back(coord(pos.x - 1, pos.y - 1));
    
    res = 0;
    for (int i = 0; i < n_pos.size(); i++)
    {
        if(n_pos[i].x >= 0 && n_pos[i].y >= 0 && n_pos[i].x < 29 && n_pos[i].y < 29\
           && board[n_pos[i].x][n_pos[i].y] == c)
            res++;
    }
    
    return (res);
}

bool    has_neighbour(std::vector< std::string > board, coord pos)
{
    std::vector< coord >    n_pos;
    
    n_pos.push_back(coord(pos.x, pos.y + 1));
    n_pos.push_back(coord(pos.x, pos.y - 1));
    
    n_pos.push_back(coord(pos.x + 1, pos.y));
    n_pos.push_back(coord(pos.x + 1, pos.y + 1));
    n_pos.push_back(coord(pos.x + 1, pos.y - 1));
    
    n_pos.push_back(coord(pos.x - 1, pos.y));
    n_pos.push_back(coord(pos.x - 1, pos.y + 1));
    n_pos.push_back(coord(pos.x - 1, pos.y - 1));
    
    //
    n_pos.push_back(coord(pos.x + 2, pos.y));
    n_pos.push_back(coord(pos.x - 2, pos.y));
    n_pos.push_back(coord(pos.x, pos.y + 2));
    n_pos.push_back(coord(pos.x, pos.y - 2));
    
    n_pos.push_back(coord(pos.x + 2, pos.y + 1));
    n_pos.push_back(coord(pos.x + 2, pos.y - 1));
    
    n_pos.push_back(coord(pos.x - 2, pos.y + 1));
    n_pos.push_back(coord(pos.x - 2, pos.y - 1));
    
    n_pos.push_back(coord(pos.x + 1, pos.y + 2));
    n_pos.push_back(coord(pos.x - 1, pos.y + 2));
    
    n_pos.push_back(coord(pos.x + 1, pos.y - 2));
    n_pos.push_back(coord(pos.x - 1, pos.y - 2));
    //
    
    for (int i = 0; i < n_pos.size(); i++)
    {
        if(n_pos[i].x >= 0 && n_pos[i].y >= 0 && n_pos[i].x < 29 && n_pos[i].y < 29\
           && board[n_pos[i].x][n_pos[i].y] != '-')
            return(true);
    }
    
    return (false);
}


std::vector< coord >    neighbour_cells(std::vector< std::string > board)
{
    std::vector<coord>  res;
    for (int x = 0; x < board.size(); x++)
    {
        for (int y = 0; y < board[0].size(); y++)
        {
            if(board[x][y] == '-' && has_neighbour(board, coord(x, y)))
                res.push_back(coord(x, y));
        }
    }
    return(res);
}

void    sig_empty(const std::vector<std::string> board, std::vector<std::string> &new_board, coord pos, char player)
{
    int  us;
    int  them;
    char them_c;
    
    them_c = (player == 'w') ? 'b' : 'w';
    us = nb_neighbour(board, pos, player);
    them = nb_neighbour(board, pos, them_c);
    if (us + them == 3)
        new_board[pos.x][pos.y] = (us < them) ? them_c : player;
}

void    sig_filled(const std::vector<std::string> board, std::vector<std::string> &new_board, coord pos)
{
    unsigned int    neighbours;
    
    neighbours = nb_neighbour(board, pos, 'w') + nb_neighbour(board, pos, 'b');
    if (neighbours != 3 && neighbours != 2)
        new_board[pos.x][pos.y] = '-';
}

std::vector<std::string>    simulate_step(std::vector<std::string> board, char player)
{
    coord   pos;
    std::vector<std::string>     new_board;
    
    new_board = board;
    for (pos.x = 0; pos.x < board.size(); pos.x++)
    {
        for (pos.y = 0; pos.y < board[0].size(); pos.y++)
        {
            if(board[pos.x][pos.y] == '-')
                sig_empty(board, new_board, pos, player);
            else if(board[pos.x][pos.y] == 'w' || board[pos.x][pos.y] == 'b')
                sig_filled(board, new_board, pos);
        }
    }
    return (new_board);
}

int     simulate_game(std::vector<std::string> board, char player, int depth)
{
    int     score;
    int     good;
    int     bad;
    
    score = 0;
    for(int i = 0; i < depth; i++)
    {
        board = simulate_step(board, player);
        bad = count(board, (player == 'w') ? 'b' : 'w');
        good = count(board, player);
        if(bad == 0 && good != 0)
        {
            score += (200 * (depth - i)); // try a return here ?
            break ;
        }
        else if(bad != 0 && good == 0)
        {
            score -= (200 * (depth - i));
            break ;
        }
    }
    
    score += count(board, player) - count(board, (player == 'w') ? 'b' : 'w');
    
    return (score);
}

int     comp_depth(int nb_move)
{
    return(1000 / nb_move); //950
}

void    t_simulate_game()
{
    
}

bool    t_best_move(std::vector<std::string> board, std::vector<coord> moves, char player)
{
    std::vector<std::string> board_test;
    std::vector< std::pair< int, coord > > to_max  
    int     max;
    int     temp;
    int     depth;
    coord   max_coord;
    
    max = -10;
    max_coord.x = moves[0].x;
    max_coord.y = moves[0].y;
    
    depth = comp_depth(moves.size());//adjust depth depending on moves.size()
//    std::cerr << "depth: " << depth << "size: " << moves.size() << std::endl;
    
    // x - x / nbt * nbt (offset: x/nbt*nbt) remaining calculations
    
    for (int i = 0; i < moves.size() && i < 500; i++) //190
    {
        board_test = board;
        board_test[moves[i].x][moves[i].y] = player;
        temp = simulate_game(board_test, player, depth); //5
        if(temp > max)
        {
            max = temp;
            max_coord = moves[i];
        }
    }
    std::cout << max_coord.x << " " << max_coord.y << std::endl;
//    std::cerr << "score: " << max << std::endl;
    
    return (true);
}


bool    best_move(std::vector<std::string> board, std::vector<coord> moves, char player)
{
    std::vector<string> board_test;
    int     max;
    int     temp;
    int     depth;
    coord   max_coord;
    
    max = -10;
    max_coord.x = moves[0].x;
    max_coord.y = moves[0].y;
    
    depth = comp_depth(moves.size());//adjust depth depending on moves.size()
//    std::cerr << "depth: " << depth << "size: " << moves.size() << std::endl;
    
    for (int i = 0; i < moves.size() && i < 500; i++) //190
    {
        board_test = board;
        board_test[moves[i].x][moves[i].y] = player;
        temp = simulate_game(board_test, player, depth); //5
        if(temp > max)
        {
            max = temp;
            max_coord = moves[i];
        }
    }
    std::cout << max_coord.x << " " << max_coord.y << std::endl;
//    std::cerr << "score: " << max << std::endl;
    
    return (true);
}

bool    bench(std::vector<std::string> board, std::vector<coord> moves, char player, int lim, int depth)
{
    std::vector<string> board_test;
    int     max;
    int     temp;
    coord   max_coord;
    
    max = -10;
    max_coord.x = moves[0].x;
    max_coord.y = moves[0].y;
    
    for (int i = 0; i < lim; i++)
    {
        board_test = board;
        board_test[moves[0].x][moves[0].y] = player;
        temp = simulate_game(board_test, player, depth);
        if(temp > max)
        {
            max = temp;
            max_coord = moves[i];
        }
    }
    std::cout << max_coord.x << " " << max_coord.y << std::endl;
    return (true);
}

void nextMove(char player, vector <string> board)
{
//    coord    available;
    
//    available = find_first(board, '-');
    
    if(find_first(board, 'w').x == -1 && find_first(board, 'b').x == -1)
    {
        std::cout << 14 << " " <<  14 << std::endl;
        return ;
    }
    
    if(best_move(board, neighbour_cells(board), player)) return ;
    //if(bench(board, neighbour_cells(board), player, 555, 2)) return ;
    
    return ;
}

int main(void)
{
    char player;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    vector <string> board;

    cin >> player;

    for(int i=0; i<29; i++) {
        string s; cin >> s;
        board.push_back(s);
    }

    nextMove(player,board);
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cerr << "Time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
    std::cerr << "Time = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() <<std::endl;
    return 0;
}
