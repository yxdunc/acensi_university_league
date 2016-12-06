#include <iostream>
#include "board.hpp"


Board::Board( char nb_players )
{
	this->type_list.push_back("Q");
	this->type_list.push_back("T");
	this->type_list.push_back("V");
	this->type_list.push_back("#");
	this->type_list.push_back("A");
	init_board(20, 20);
	this->players.resize(nb_players);
	this->player_state.resize(nb_players);
	this->score.resize(nb_players);
	current_player = 0;
	init_pos();
	return ;
}

Board::Board( Board const & src )
{
	(void) src;
	return ;
}

Matrix	Board::get_m( void ) const
{
	return(this->m);
}

std::string		Board::random_type() const
{
	std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(0, this->type_list.size() - 1);
    int dice_roll = distribution(generator);
    return (this->type_list[dice_roll]);
}

void	Board::init_board(Uint height, Uint width)
{
	this->m.resize(height);
	for(Uint x = 0; x < height; x++)
	{
		this->m[x].resize(width);
		for(Uint y = 0; y < width; y++)
		{
			this->m[x][y].set_type(random_type());
		}
	}
}

void	Board::init_pos( void )
{
	for(Uint i = 0; i < this->players.size(); i++)
	{
		this->players[i] = Coord(0,0);
	}
}

void	Board::draw_grid( void ) const
{
	for(Uint x = 0; x < this->m.size(); x++)
	{
		for(Uint y = 0; y < this->m[0].size(); y++)
		{
			if(this->m[x][y].state ==  "player")
				std::cout << this->m[x][y].player;
			else if(this->m[x][y].state == "trail")
				std::cout << " ";
			else
				std::cout << this->m[x][y].render();
		}
		std::cout << std::endl;
	}
}

int 	Board::check_winner() const
{
	for(Uint i = 0; i < this->players.size(); i++)
	{
		if (this->score[i] > 10)
			return(i);
	}
	return (0);
}

bool	is_move(std::string input)
{
	if(input == "a" || input == "s" || input == "d" || input == "w")
		return true;
	return false;
}

bool	Board::activate()
{	
	Coord p = players[current_player];

	if(m[p.x][p.y].type == "A" && dice_color != "BLUE")
		dice_color = "BLUE";
	else if (m[p.x][p.y].type == "A" && dice_color == "BLUE")
		dice_color = "GREEN";
//	else if (m[p.x][p.y].type == "A" && dice_color == "BLUE")
//
	else if (m[p.x][p.y].type == "T")
		player_state[current_player] = "T";
	else if (player_state[current_player] == "T")
		m[p.x][p.y].state = "trail";
	return true;
}

void	Board::move_to_next(std::string move)
{
	(void)move;
	m[players[current_player].x][players[current_player].y].state = "";
	if(move == "a" && players[current_player].y != 0)
	{
		players[current_player].y--;
	}
	else if(move == "d" && players[current_player].y != m[0].size())
		players[current_player].y++;
	else if(move == "w" && players[current_player].x != 0)
		players[current_player].x--;
	else if(move == "s" && players[current_player].x != m[0].size())
		players[current_player].x++;

	m[players[current_player].x][players[current_player].y].state = "player";
	m[players[current_player].x][players[current_player].y].player = current_player;
}

int		Board::update(int dice1, int dice2)
{
	std::string player_state = "D";
	std::string	input;

	for(int i = 0; i < dice1 + dice2; i++)
	{
		getline(std::cin, input);
		if(!activate())
			return (0);
		if(input.size() != 1){}
		else if(is_move(input))
		{
			move_to_next(input);
		}
		else if(input == "x"){}

	}
	this->current_player = (this->current_player + 1) % this->players.size();
	return (check_winner());
}

void	Board::draw_dice(int dice) const
{
	static std::vector <std::string>	dice_face;

	dice_face.resize(7);
	dice_face[1] = "###\n#O#\n###\n";
	dice_face[2] = "O##\n###\n##O\n";
	dice_face[3] = "O##\n#O#\n##O\n";
	dice_face[4] = "O#O\n###\nO#O\n";
	dice_face[5] = "O#O\n#O#\nO#O\n";
	dice_face[6] = "O#O\nO#O\nO#O\n";
	if(this->dice_color == "BLUE")
		std::cout << KBLU << dice_face[dice] << RST << std::endl;
	else if (this->dice_color == "GREEN")
		std::cout << KGRN << dice_face[dice] << RST << std::endl;
	else if (this->dice_color == "RED")
		std::cout << KGRN << dice_face[dice] << RST << std::endl;
	else
		std::cout << dice_face[dice] << std::endl;
}


Board::~Board( void )
{

	return ;
}

Board &	Board::operator=( Board const & rhs )
{
	(void) rhs;
	return *this; // allow a = b = c
}
