#ifndef AREA_HPP
#define AREA_HPP

#include <memory>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#include "Size.hpp"
#include "Position.hpp"
#include "Element.hpp"
#include "ElementType.hpp"
#include "Cell.hpp"
#include "Exceptions.hpp"

class Area
{
private:
	Size _size;
	std::unique_ptr<Cell[]> _data;
	Area();
	Area(const Area &);
	Area &operator=(const Area &);

public:
	Area(int width, int height);
	Area(const Size &size);
	~Area();

	Cell &operator[](size_t);
	Cell &operator[](const Position &pos);
	const Cell &operator[](size_t) const;
	const Cell &operator[](const Position &pos) const;
	Size getSize() const;
	bool isOverArea(const Position &) const;
	bool isFree(const Position &) const;
	bool isFood(const Position &) const;
	bool isSnake(const Position &) const;
	bool isWall(const Position &) const;
	bool isDanger(const Position &) const;
	std::vector<Position> getFreePositions() const;
	Position getRandomFreePosition() const;
	std::vector<Element> getFreeElements(int size) const;
	Element getRandomFreeElement(int size) const;
};

std::ostream &operator<<(std::ostream &os, const Area &);

#endif // !AREA_HPP
