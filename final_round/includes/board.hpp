#ifndef BOARD_HPP
# define BOARD_HPP

#include <iostream>
#include <vector>
#include <random>
#include "colors.hpp"
#include "case.hpp"
#include "coord.hpp"

typedef std::vector<std::vector <Case> > Matrix;
typedef unsigned int Uint;

class Board
{
	public:

		Board( char nb_players );
		Board( Board const & src );
		~Board( void );

		Matrix			get_m( void ) const;
		void			draw_grid( void ) const;
		void			draw_dice(int dice) const;
		std::string		random_type( void ) const;
		int 			check_winner() const;

		int				update(int dice1, int dice2);
		bool			activate();
		void			move_to_next(std::string move);

		std::vector< Coord >	players;

		Board &	operator=( Board const & rhs );

	private:
		void			init_board(Uint height, Uint width);
		void			init_pos( void );

		std::vector <std::string>	type_list;
		std::string					dice_color;
		Matrix						m;
		std::vector<int>			score;
		std::vector<std::string>	player_state;
		int 						current_player;


};

#endif //!BOARD_HPP

