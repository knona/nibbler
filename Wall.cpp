#include "Wall.hpp"

Wall::Wall() {}

Wall::Wall(const Element &element)
{
	this->_positions = element.getPositions();
}
