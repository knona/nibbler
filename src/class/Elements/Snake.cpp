#include "Snake.hpp"

Snake::Snake(): _direction(Direction::Right), _grow(0)
{}

Snake::Snake(const Snake &snake)
{
	*this = snake;
}

Snake::~Snake()
{}

Snake &Snake::operator=(const Snake &snake)
{
	this->_direction = snake._direction;
	this->_grow = snake._grow;
	return *this;
}

void Snake::move(Area &area, const Position &newHead, Foods &foods, Cron &cron)
{
	if (area.isDanger(newHead))
		throw Exception::GameOver();

	if (this->_grow == 0)
	{
		area[this->_positions.back()].reset();
		this->_positions.pop_back();
	}

	if (area.isFood(newHead))
	{
		foods.removeFood(newHead, area);
		std::function<void()> fn = std::bind(Foods::addRandomFood, &foods, area);
		cron.addEvent(fn, 0);
		this->_grow++;
	}
	else if (this->_grow > 0)
		this->_grow--;

	this->_positions.push_front(newHead);
	area[newHead].id = this->_id;
	area[newHead].type = ElementType::SnakeT;
}

void Snake::moveTop(Area &area, Foods &foods, Cron &cron, bool forward)
{
	if (!forward && (this->_direction == Direction::Top || this->_direction == Direction::Bottom))
	{
		this->moveForward(area, foods, cron);
		return;
	}

	Position newHead = this->_positions.front();
	newHead.y--;
	this->move(area, newHead, foods, cron);
	this->_direction = Direction::Top;
}

void Snake::moveRight(Area &area, Foods &foods, Cron &cron, bool forward)
{
	if (!forward && (this->_direction == Direction::Left || this->_direction == Direction::Right))
	{
		this->moveForward(area, foods, cron);
		return;
	}

	Position newHead = this->_positions.front();
	newHead.x++;
	this->move(area, newHead, foods, cron);
	this->_direction = Direction::Right;
}

void Snake::moveBottom(Area &area, Foods &foods, Cron &cron, bool forward)
{
	if (!forward && (this->_direction == Direction::Top || this->_direction == Direction::Bottom))
	{
		this->moveForward(area, foods, cron);
		return;
	}

	Position newHead = this->_positions.front();
	newHead.y++;
	this->move(area, newHead, foods, cron);
	this->_direction = Direction::Bottom;
}

void Snake::moveLeft(Area &area, Foods &foods, Cron &cron, bool forward)
{
	if (!forward && (this->_direction == Direction::Left || this->_direction == Direction::Right))
	{
		this->moveForward(area, foods, cron);
		return;
	}

	Position newHead = this->_positions.front();
	newHead.x--;
	this->move(area, newHead, foods, cron);
	this->_direction = Direction::Left;
}

void Snake::moveForward(Area &area, Foods &foods, Cron &cron)
{
	std::unordered_map<Direction, void (Snake::*)(Area &, Foods &, Cron &, bool)> fMap = {
		{ Direction::Top, &Snake::moveTop },
		{ Direction::Right, &Snake::moveRight },
		{ Direction::Bottom, &Snake::moveBottom },
		{ Direction::Left, &Snake::moveLeft }
	};
	(this->*fMap[this->_direction])(area, foods, cron, true);
}

void Snake::setSnakeOnArea(Area &area)
{
	Size<int> areaSize = area.getSize();
	int       y = areaSize.height / 2;
	int       x = areaSize.width / 2 - 2;

	for (int i = 3; i >= 0; i--)
	{
		Position pos = { x + i, y };
		Cell &   cell = area[pos];
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
