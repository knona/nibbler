#include "Walls.hpp"

void Walls::addRandomWall(Area &area)
{
	int size = std::rand() % 3 + 2;
	Element element = area.getRandomFreeElement(size);
	Wall wall(element);

	int newId = Walls::_id++;

	for (const Position &pos : element.getPositions())
	{
		area[pos].id = newId;
		area[pos].type = ElementType::WallT;
	}
	(*this)[newId] = wall;
}

void Walls::removeWall(int id, Area &area)
{
	if (this->find(id) == this->end())
		throw std::out_of_range("Wall id does not exist");

	Wall &wall = (*this)[id];

	for (const Position &pos : wall.getPositions())
		area[pos].reset();

	this->erase(id);
}

int Walls::_id = 0;
