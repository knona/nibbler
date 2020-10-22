#include "Element.hpp"

Element::Element()
{}

Element::Element(const std::list<Position> &positions)
{
	this->_positions = positions;
}

Element::Element(const Element &element)
{
	*this = element;
}

Element::~Element()
{}

Element &Element::operator=(const Element &element)
{
	this->_positions = element._positions;
	this->_id = element._id;
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

int Element::Element::getId() const
{
	return this->_id;
}

int Element::Element::setId()
{
	this->_id = this->getIdCounter()++;
	return this->_id;
}

int &Element::getIdCounter() const
{
	return Element::_idCounter;
}

int Element::_idCounter = 0;
