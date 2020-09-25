#include "Food.hpp"

Food::Food() {}

Food::Food(const Element &element)
{
	this->_positions = element.getPositions();
}
