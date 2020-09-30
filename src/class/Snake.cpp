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

void Snake::move(Area &area, const Position &newHead, Foods &foods)
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

void Snake::moveTop(Area &area, Foods &foods, bool forward)
{
	if (!forward && (this->_direction == Direction::Top || this->_direction == Direction::Bottom))
	{
		if (this->_direction == Direction::Top) // to remove
			this->moveForward(area, foods);		// to remove
		return;
	}

	Position newHead = this->_positions.front();
	newHead.y--;
	this->move(area, newHead, foods);
	this->_direction = Direction::Top;
}

void Snake::moveRight(Area &area, Foods &foods, bool forward)
{
	if (!forward && (this->_direction == Direction::Left || this->_direction == Direction::Right))
	{
		if (this->_direction == Direction::Right) // to remove
			this->moveForward(area, foods);		  // to remove
		return;
	}

	Position newHead = this->_positions.front();
	newHead.x++;
	this->move(area, newHead, foods);
	this->_direction = Direction::Right;
}

void Snake::moveBottom(Area &area, Foods &foods, bool forward)
{
	if (!forward && (this->_direction == Direction::Top || this->_direction == Direction::Bottom))
	{
		if (this->_direction == Direction::Bottom) // to remove
			this->moveForward(area, foods);		   // to remove
		return;
	}

	Position newHead = this->_positions.front();
	newHead.y++;
	this->move(area, newHead, foods);
	this->_direction = Direction::Bottom;
}

void Snake::moveLeft(Area &area, Foods &foods, bool forward)
{
	if (!forward && (this->_direction == Direction::Left || this->_direction == Direction::Right))
	{
		if (this->_direction == Direction::Left) // to remove
			this->moveForward(area, foods);		 // to remove
		return;
	}

	Position newHead = this->_positions.front();
	newHead.x--;
	this->move(area, newHead, foods);
	this->_direction = Direction::Left;
}

void Snake::moveForward(Area &area, Foods &foods)
{
	if (this->_direction == Direction::Top)
		moveTop(area, foods, true);
	if (this->_direction == Direction::Right)
		moveRight(area, foods, true);
	if (this->_direction == Direction::Bottom)
		moveBottom(area, foods, true);
	if (this->_direction == Direction::Left)
		moveLeft(area, foods, true);
}

void Snake::grow(Area &area)
{
	if (!this->_grow)
		return;
	area[this->_lastTail].id = this->_id;
	area[this->_lastTail].type = ElementType::SnakeT;
	this->_positions.push_back(this->_lastTail);
	this->_grow = false;
}

void Snake::setSnakeOnArea(Area &area)
{
	Size areaSize = area.getSize();
	int y = areaSize.height / 2;
	int x = areaSize.width / 2 - 2;

	for (int i = 3; i >= 0; i--)
	{
		Position pos = {x + i, y};
		Cell &cell = area[pos];
		cell.id = this->_id;
		cell.type = ElementType::SnakeT;
		this->_positions.push_back(pos);
	}
}

bool Snake::isHead(const Position &pos) const
{
	return this->_positions.front() == pos;
}

bool Snake::isTail(const Position &pos) const
{
	return this->_positions.back() == pos;
}
