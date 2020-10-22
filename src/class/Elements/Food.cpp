#include "Food.hpp"

Food::Food()
{}

Food::Food(const Element &element): Element(element)
{}

int &Food::getIdCounter() const
{
	return Food::_idCounter;
}

int Food::_idCounter = 0;

Food Food::getRandomFood(Area &area)
{
	Position pos = area.getRandomFreePosition();
	Element  element({ pos });

	return element;
}
