#include "Snake.hpp"

Snake::Snake() : _direction(Direction::Right), _grow(false) {}

Snake::Snake(const Snake &snake)
{
	*this = snake;
}

Snake::~Snake() {}

Snake &Snake::operator=(const Snake &snake)
{
	this->_direction = snake._direction;
	this->_grow = snake._grow;
	return *this;
}

void Snake::moveFromInput(Area &area, const Position &newHead, Foods &foods)
{
	if (area.isDanger(newHead))
		throw Exception::GameOver();

	Position tail = this->_positions.back();
	this->_positions.pop_back();
	this->_lastTail = tail;

	this->_positions.push_front(newHead);
	if (area.isFood(newHead))
	{
		foods.removeFood(newHead, area);
		this->_grow = true;
	}
	area[newHead].id = this->_id;
	area[newHead].type = ElementType::SnakeT;
	area[tail].reset();
}

void Snake::moveFromTopInput(Area &area, Foods &foods)
{
	if (this->_direction == Direction::Top || this->_direction == Direction::Bottom)
		return;

	Position newHead = this->_positions.front();
	newHead.y--;
	this->moveFromInput(area, newHead, foods);
}

void Snake::moveFromRightInput(Area &area, Foods &foods)
{
	if (this->_direction == Direction::Left || this->_direction == Direction::Right)
		return;

	Position newHead = this->_positions.front();
	newHead.x++;
	this->moveFromInput(area, newHead, foods);
}

void Snake::moveFromBottomnput(Area &area, Foods &foods)
{
	if (this->_direction == Direction::Top || this->_direction == Direction::Bottom)
		return;

	Position newHead = this->_positions.front();
	newHead.y++;
	this->moveFromInput(area, newHead, foods);
}

void Snake::moveFromLeftInput(Area &area, Foods &foods)
{
	if (this->_direction == Direction::Left || this->_direction == Direction::Right)
		return;

	Position newHead = this->_positions.front();
	newHead.x--;
	this->moveFromInput(area, newHead, foods);
}

void Snake::grow(Area &area)
{
	if (!this->_grow)
		return;
	area[this->_lastTail].id = this->_id;
	area[this->_lastTail].type = ElementType::SnakeT;
	this->_positions.push_back(this->_lastTail);
}
