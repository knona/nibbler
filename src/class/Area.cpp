#include "Area.hpp"

std::unique_ptr<Cell[]> alloc(const Size &size)
{
	return std::make_unique<Cell[]>(size.width * size.height);
}

Area::Area() {}

Area::Area(int width, int height) : _size({width, height}), _data(alloc(_size)) {}

Area::Area(const Size &size) : _size(size), _data(alloc(_size)) {}

Area::~Area() {}

Cell &Area::operator[](const Position &pos)
{
	return (*this)[pos.y * this->_size.width + pos.x];
}

Cell &Area::operator[](size_t index)
{
	return _data[index];
}

const Cell &Area::operator[](const Position &pos) const
{
	return (*this)[pos.y * this->_size.width + pos.x];
}

const Cell &Area::operator[](size_t index) const
{
	return _data[index];
}

Size Area::getSize(void) const
{
	return this->_size;
}

bool Area::isOverArea(const Position &pos) const
{
	return pos.x >= this->_size.width || pos.y >= this->_size.height || pos.x < 0 || pos.y < 0;
}

std::vector<Position> Area::getFreePositions() const
{
	std::vector<Position> freePositions;

	for (int y = 0; y < this->_size.height; y++)
		for (int x = 0; x < this->_size.width; x++)
			if (this->isFree({x, y}))
				freePositions.push_back({x, y});
	return freePositions;
}

bool Area::isFree(const Position &pos) const
{
	if (this->isOverArea(pos))
		return false;
	return (*this)[pos].type == static_cast<unsigned char>(ElementType::FreeT);
}

bool Area::isFood(const Position &pos) const
{
	if (this->isOverArea(pos))
		return false;
	return (*this)[pos].type == static_cast<unsigned char>(ElementType::FoodT);
}

bool Area::isSnake(const Position &pos) const
{
	if (this->isOverArea(pos))
		return false;
	return (*this)[pos].type == static_cast<unsigned char>(ElementType::SnakeT);
}

bool Area::isWall(const Position &pos) const
{
	if (this->isOverArea(pos))
		return false;
	return (*this)[pos].type == static_cast<unsigned char>(ElementType::WallT);
}

bool Area::isDanger(const Position &pos) const
{
	if (this->isOverArea(pos))
		return true;
	return this->isWall(pos) || this->isSnake(pos);
}

Position Area::getRandomFreePosition() const
{
	std::vector<Position> freePositions = this->getFreePositions();
	size_t size = freePositions.size();

	if (size == 0)
		throw Exception::NoSpace();
	return freePositions[std::rand() % size];
}

std::list<Position> allFreeColumn(const Area *area, int x, int y, int size)
{
	std::list<Position> positions;
	bool allFree = true;

	for (int j = y; j < y + size; j++)
		allFree = allFree && area->isFree({x, j});

	if (allFree)
		for (int j = y; j < y + size; j++)
			positions.push_back({x, j});
	return positions;
}

std::list<Position> allFreeLine(const Area *area, int x, int y, int size)
{
	std::list<Position> positions;
	bool allFree = true;

	for (int i = x; i < x + size; i++)
		allFree = allFree && area->isFree({i, y});

	if (allFree)
		for (int i = x; i < x + size; i++)
			positions.push_back({i, y});
	return positions;
}

std::vector<Element> Area::getFreeElements(int size) const
{
	std::vector<Element> elements;
	std::list<Position> tmp;

	for (int y = 0; y < this->_size.height; y++)
	{
		for (int x = 0; x < this->_size.width; x++)
		{
			if (x + size - 1 < this->_size.width)
			{
				tmp = allFreeLine(this, x, y, size);
				if (!tmp.empty())
					elements.push_back(tmp);
			}
			if (y + size - 1 < this->_size.height)
			{
				tmp = allFreeColumn(this, x, y, size);
				if (!tmp.empty())
					elements.push_back(tmp);
			}
		}
	}
	return elements;
}

Element Area::getRandomFreeElement(int size) const
{
	std::vector<Element> elements = this->getFreeElements(size);
	int nbElements = elements.size();

	if (nbElements == 0)
		throw Exception::NoSpace();
	return elements[std::rand() % nbElements];
}

std::ostream &operator<<(std::ostream &os, const Area &area)
{
	for (int y = 0; y < area.getSize().height; y++)
	{
		if (y != 0)
			os << std::endl;
		for (int x = 0; x < area.getSize().width; x++)
		{
			Position pos = {x, y};
			std::string color;

			if (area.isWall(pos))
				color = "\033[0;31m";
			else if (area.isFood(pos))
				color = "\033[0;36m";
			else if (area.isSnake(pos))
				color = "\033[1;33m";
			else
				color = "\033[0m";
			if (x != 0)
				os << " ";
			os << color << "*";
		}
	}
	os << "\033[0m";
	return os;
}
