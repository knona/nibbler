#include "Wall.hpp"

Wall::Wall() {}

Wall::Wall(const Element &element) : Element(element) {}

int &Wall::getIdCounter() const
{
	return Wall::_idCounter;
}

int Wall::_idCounter = 0;
