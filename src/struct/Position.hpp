#ifndef POSITION_HPP
#define POSITION_HPP

#include "Size.hpp"

#include <cstdlib>
#include <iostream>

struct Position
{
	int x;
	int y;

	Position();
	Position(int x, int y);
	Position(const Position &pos);
	Position &operator=(const Position &b);
	~Position();

	void            print(int width, int height);
	void            print(const Size &size);
	bool            operator==(const Position &b) const;
	bool            operator!=(const Position &b) const;
	bool            operator<(const Position &b) const;
	bool            operator>(const Position &b) const;
	bool            operator<=(const Position &b) const;
	bool            operator>=(const Position &b) const;
	static Position getRandomPosition(int xMax, int yMax);
};

std::ostream &operator<<(std::ostream &os, const Position &pos);

#endif // !POSITION_HPP
