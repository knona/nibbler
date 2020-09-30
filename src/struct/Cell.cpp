#include "Cell.hpp"

Cell::Cell() : id(-1), type(ElementType::FreeT) {}

Cell::Cell(int id, ElementType type) : id(id), type(type) {}

Cell::Cell(const Cell &cell)
{
	*this = cell;
}

Cell::~Cell() {}

Cell &Cell::operator=(const Cell &cell)
{
	this->id = cell.id;
	this->type = cell.type;
	return *this;
}

void Cell::reset()
{
	this->id = -1;
	this->type = ElementType::FreeT;
}
