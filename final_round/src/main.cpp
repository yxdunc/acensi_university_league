#include<iostream>
#include"board.hpp"

int		nb_player(std::string input);
int		throw_dice( void );

int		main(int argc, char *argv[])
{
	std::string	move;
	int		win = 0;
	int		qt_player;
	int		dice1;
	int		dice2;

	if(argc == 1 || argc < 2)
		return 1;
	qt_player = nb_player(argv[1]);
	if(!qt_player)
		return 1;

	Board	board(qt_player);

	board.draw_grid();

	dice1 = throw_dice();
	dice2 = throw_dice();
	board.draw_dice(dice1);
	board.draw_dice(dice2);
	while( !win )
	{
		win = board.update(dice1, dice2);
		board.draw_grid();
		dice1 = throw_dice();
		dice2 = throw_dice();
		board.draw_dice(dice1);
		board.draw_dice(dice2);
	}

	std::cout << "Player" << win << " win the quantum board" << std::endl;



    return 0;
}

int		nb_player(std::string input)
{
	int 	res;
	try
	{
		res = std::stoi(input);
	}
	catch (int e)
	{
		std::cerr << "not a number: " << e << std::endl;
		return (0);
	}
	if(res < 2 || res > 4)
		return (0);
	return (res);
}

int		throw_dice( void )
{
	std::random_device r;
    std::default_random_engine generator(r());
    std::uniform_int_distribution<int> distribution(1, 6);
    return (distribution(generator));
}

