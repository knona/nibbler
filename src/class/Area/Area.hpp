#ifndef AREA_HPP
#define AREA_HPP

#include "Cell.hpp"
#include "Element.hpp"
#include "ElementType.hpp"
#include "Exceptions.hpp"
#include "Position.hpp"
#include "Size.tpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

class Snake;

class Area
{
	private:
	Size<int>               _size;
	std::unique_ptr<Cell[]> _data;
	Area(const Area &);
	Area &operator=(const Area &);

	public:
	Area();
	Area(int width, int height);
	Area(const Size<int> &size);
	Area(Area &&);
	Area &operator=(Area &&);
	~Area();

	Cell &                operator[](size_t);
	Cell &                operator[](const Position &pos);
	const Cell &          operator[](size_t) const;
	const Cell &          operator[](const Position &pos) const;
	Size<int>             getSize() const;
	bool                  isOverArea(const Position &) const;
	bool                  isFree(const Position &) const;
	bool                  isFood(const Position &) const;
	bool                  isSnake(const Position &) const;
	bool                  isWall(const Position &) const;
	bool                  isDanger(const Position &) const;
	std::vector<Position> getFreePositions() const;
	Position              getRandomFreePosition() const;
	std::vector<Element>  getFreeElements(int size) const;
	Element               getRandomFreeElement(int size) const;
	void                  print(std::ostream &os, const Snake *snake = nullptr) const;
	int                   height() const;
	int                   width() const;
};

std::ostream &operator<<(std::ostream &os, const Area &);

#endif // !AREA_HPP
