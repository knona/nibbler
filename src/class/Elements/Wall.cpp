#include "Wall.hpp"

Wall::Wall() {}

Wall::Wall(const Element &element) : Element(element) {}

int &Wall::getIdCounter() const
{
	return Wall::_idCounter;
}

int Wall::_idCounter = 0;

bool checkSides(Area &area, const Element &element)
{
	for (const Position &pos : element.getPositions())
	{
		bool res = true;
		for (int i = -1; i <= 1; i++)
			for (int j = -1; j <= 1; j++)
				if (j != pos.x || i != pos.y)
					res = res && !area.isDanger({pos.x + j, pos.y + i});
		if (!res)
			return false;
	}
	return true;
}

std::vector<Element> removeAdjacentElements(const std::vector<Element> &elements, Area &area)
{
	std::vector<Element> res;

	for (const Element &element : elements)
		if (checkSides(area, element))
			res.push_back(element);
	return res;
}

Wall Wall::getRandomWall(Area &area, int size)
{
	std::vector<Element> elements = removeAdjacentElements(area.getFreeElements(size), area);
	int nbElements = elements.size();

	if (nbElements == 0)
		throw Exception::NoSpace();

	return elements[std::rand() % nbElements];
}
