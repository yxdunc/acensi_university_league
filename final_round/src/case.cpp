#include <iostream>
#include "Case.hpp"

Case::Case( void )
{

	return ;
}

Case::Case( std::string type_name ) : type(type_name)
{

	return ;
}

Case::~Case( void )
{

	return ;
}

void		Case::set_type(std::string new_type)
{
	this->type = new_type;
}

std::string	Case::render( void ) const
{
	if (!this->type.size())
		return (FRED("ERROR"));
	else if (this->type == "Q")
		return (FYEL("Q"));
	else if (this->type == "T")
		return (FMAG("T"));
	else if (this->type == "#")
		return (FGRN("#"));
	else if (this->type == "A")
		return (FBLU("A"));
	else if (this->type == "V")
		return (FCYN("V"));
	else
		return ("-");
}

void	Case::set_state( std::string new_state )
{
	this->state = new_state;
}
