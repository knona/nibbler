#ifndef WALL_HPP
#define WALL_HPP

#include "Element.hpp"

class Wall : public Element
{
private:
public:
	Wall();
	Wall(const Element &element);
};

#endif // !WALL_HPP
