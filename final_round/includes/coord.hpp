#ifndef COORD_HPP
# define COORD_HPP
class Coord
{
    public:
        Coord() {};
        Coord(int x, int y) : x(x), y(y) {};
        unsigned int x;
        unsigned int y;

		std::string serialize() { return (std::to_string(this->x) + " " + std::to_string(this->y)); };
};
#endif // !COORD_HPP
