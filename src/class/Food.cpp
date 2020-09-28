#include "Food.hpp"

Food::Food() {}

Food::Food(const Element &element) : Element(element) {}

int &Food::getIdCounter() const
{
	return Food::_idCounter;
}

int Food::_idCounter = 0;
