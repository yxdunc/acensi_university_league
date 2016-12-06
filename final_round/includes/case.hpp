#ifndef CASE_HPP
# define CASE_HPP

#include <iostream>
#include "colors.hpp"
#include "coord.hpp"


class Case
{
	public:

		Case( void );
		Case( std::string type_name );
		~Case( void );
		std::string	render( void ) const;
		void		set_state( std::string );
		void		set_type( std::string );

		std::string type;
		std::string state;
		int	player;
private:


};

#endif //!CASE_HPP

