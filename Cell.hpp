#ifndef CELL_HPP
#define CELL_HPP

#include "ElementType.hpp"

struct Cell
{
	int id;
	ElementType type;

	Cell();
	Cell(int id, ElementType type);
	Cell(const Cell &cell);
	~Cell();
	Cell &operator=(const Cell &);

	void reset();
};

#endif // !CELL_HPP
