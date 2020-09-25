#include "Element.hpp"

Element::Element() {}

Element::Element(const std::list<Position> &positions)
{
	this->_positions = positions;
}

Element::Element(const Element &element)
{
	*this = element;
}

Element::~Element() {}

Element &Element::operator=(const Element &element)
{
	this->_positions = element._positions;
	return *this;
}

std::list<Position> &Element::getPositions(void)
{
	return this->_positions;
}

const std::list<Position> &Element::getPositions(void) const
{
	return this->_positions;
}
