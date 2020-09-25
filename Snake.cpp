#include "Snake.hpp"

Snake::Snake() : _currentDirection(Direction::Right) {}

Snake::Snake(const Snake &snake)
{
	*this = snake;
}

Snake::~Snake() {}

Snake &Snake::operator=(const Snake &snake)
{
	this->_currentDirection = snake._currentDirection;
	return *this;
}
