#include "Position.hpp"

Position::Position() : x(0), y(0) {}

Position::Position(int x, int y) : x(x), y(y) {}

Position::Position(const Position &pos)
{
	*this = pos;
}

Position::~Position(){};

Position &Position::operator=(const Position &b)
{
	this->x = b.x;
	this->y = b.y;
	return *this;
}

bool Position::operator==(const Position &b) const
{
	return this->x == b.x && this->y == b.y;
}

bool Position::operator!=(const Position &b) const
{
	return this->x != b.x || this->y != b.y;
}

bool Position::operator<(const Position &b) const
{
	return this->y < b.y || (this->y == b.y && this->x < b.x);
}

bool Position::operator>(const Position &b) const
{
	return this->y > b.y || (this->y == b.y && this->x > b.x);
}

bool Position::operator<=(const Position &b) const
{
	return *this < b || *this == b;
}

bool Position::operator>=(const Position &b) const
{
	return *this > b || *this == b;
}

Position Position::getRandomPosition(int xMax, int yMax)
{
	return {rand() % xMax, rand() % yMax};
}

void Position::print(const Size &size)
{
	this->print(size.width, size.height);
}

void Position::print(int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
			std::cout << (Position(x, y) == *this ? "🟥" : "⬜");
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Position &pos)
{
	os << "x: " << pos.x << ", y: " << pos.y;
	return os;
}
