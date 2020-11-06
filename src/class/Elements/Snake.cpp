#include "Snake.hpp"

#include "GameData.hpp"

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
	this->_id = snake._id;
	this->_grow = snake._grow;
	this->_direction = snake._direction;
	this->_grow = snake._grow;
	this->_positions = snake._positions;
	return *this;
}

Direction Snake::getDirection() const
{
	return this->_direction;
}

void Snake::move(GameData &gData, const Position &newHead)
{
	if (gData.area.isDanger(newHead))
		throw Exception::GameOver();

	if (this->_grow == 0)
	{
		gData.area[this->_positions.back()].reset();
		this->_positions.pop_back();
	}

	if (this->_grow > 0)
		this->_grow--;

	if (gData.area.isFood(newHead))
	{
		gData.foods.removeFood(newHead, gData.area);
		std::function<void()> fn = std::bind(&Foods::addRandomFood, &gData.foods, std::ref(gData.area));
		gData.cron.addEvent(fn, 0);
		this->_grow++;
		gData.score.increment();
	}

	this->_positions.push_front(newHead);
	gData.area[newHead].id = this->_id;
	gData.area[newHead].type = ElementType::SnakeT;
}

void Snake::moveTop(GameData &gData, bool forward)
{
	if (!forward && (this->_direction == Direction::Top || this->_direction == Direction::Bottom))
	{
		this->moveForward(gData);
		return;
	}

	Position newHead = this->_positions.front();
	newHead.y--;
	this->move(gData, newHead);
	this->_direction = Direction::Top;
}

void Snake::moveRight(GameData &gData, bool forward)
{
	if (!forward && (this->_direction == Direction::Left || this->_direction == Direction::Right))
	{
		this->moveForward(gData);
		return;
	}

	Position newHead = this->_positions.front();
	newHead.x++;
	this->move(gData, newHead);
	this->_direction = Direction::Right;
}

void Snake::moveBottom(GameData &gData, bool forward)
{
	if (!forward && (this->_direction == Direction::Top || this->_direction == Direction::Bottom))
	{
		this->moveForward(gData);
		return;
	}

	Position newHead = this->_positions.front();
	newHead.y++;
	this->move(gData, newHead);
	this->_direction = Direction::Bottom;
}

void Snake::moveLeft(GameData &gData, bool forward)
{
	if (!forward && (this->_direction == Direction::Left || this->_direction == Direction::Right))
	{
		this->moveForward(gData);
		return;
	}

	Position newHead = this->_positions.front();
	newHead.x--;
	this->move(gData, newHead);
	this->_direction = Direction::Left;
}

void Snake::moveForward(GameData &gData)
{
	std::unordered_map<Direction, void (Snake::*)(GameData &, bool)> fMap = { { Direction::Top, &Snake::moveTop },
		                                                                      { Direction::Right, &Snake::moveRight },
		                                                                      { Direction::Bottom, &Snake::moveBottom },
		                                                                      { Direction::Left, &Snake::moveLeft } };
	(this->*fMap[this->_direction])(gData, true);
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
