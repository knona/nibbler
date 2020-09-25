#include "Cell.hpp"

Cell::Cell() : id(-1),
			   type(static_cast<unsigned char>(ElementType::FreeT)) {}

Cell::Cell(int id, unsigned char type) : id(id), type(type) {}

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
