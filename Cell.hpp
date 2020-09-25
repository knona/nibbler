#ifndef CELL_HPP
#define CELL_HPP

#include "ElementType.hpp"

struct Cell
{
	int id;
	unsigned char type;

	Cell();
	Cell(int id, unsigned char type);
	Cell(const Cell &cell);
	~Cell();
	Cell &operator=(const Cell &);
};

#endif // !CELL_HPP
