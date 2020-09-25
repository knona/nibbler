#include "Position.hpp"

Position::Position()
{
	this->x = 0;
	this->y = 0;
}

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

std::ostream &operator<<(std::ostream &os, const Position &pos)
{
	os << "x: " << pos.x << ", y: " << pos.y;
	return os;
}
