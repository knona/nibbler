#include "Wall.hpp"

Wall::Wall()
{}

Wall::Wall(const Element &element): Element(element)
{}

int &Wall::getIdCounter() const
{
	return Wall::_idCounter;
}

int Wall::_idCounter = 0;

bool checkSidesHorizontalElement(Area &area, const Position &pos, const Position &back, const Position &front)
{
	bool res = true;
	res = res && !area.isDanger({ pos.x, pos.y + 1 }) && !area.isDanger({ pos.x, pos.y - 1 });
	if (Position(pos.x, pos.y) == front)
	{
		res = res &&                                      //
		      !area.isDanger({ pos.x - 1, pos.y }) &&     //
		      !area.isDanger({ pos.x - 1, pos.y + 1 }) && //
		      !area.isDanger({ pos.x - 1, pos.y - 1 });
	}
	if (Position(pos.x, pos.y) == back)
	{
		res = res &&                                      //
		      !area.isDanger({ pos.x + 1, pos.y }) &&     //
		      !area.isDanger({ pos.x + 1, pos.y + 1 }) && //
		      !area.isDanger({ pos.x + 1, pos.y - 1 });
	}
	return res;
}

bool checkSidesVerticalElement(Area &area, const Position &pos, const Position &back, const Position &front)
{
	bool res = true;
	res = res && !area.isDanger({ pos.x + 1, pos.y }) && !area.isDanger({ pos.x - 1, pos.y });
	if (Position(pos.x, pos.y) == front)
	{
		res = res &&                                      //
		      !area.isDanger({ pos.x, pos.y - 1 }) &&     //
		      !area.isDanger({ pos.x + 1, pos.y - 1 }) && //
		      !area.isDanger({ pos.x - 1, pos.y - 1 });
	}
	if (Position(pos.x, pos.y) == back)
	{
		res = res &&                                      //
		      !area.isDanger({ pos.x, pos.y + 1 }) &&     //
		      !area.isDanger({ pos.x + 1, pos.y + 1 }) && //
		      !area.isDanger({ pos.x - 1, pos.y + 1 });
	}
	return res;
}

bool checkSides(Area &area, const Element &element)
{
	std::list<Position> positions = element.getPositions();
	Position            back = positions.back();
	Position            front = positions.front();
	bool                isHorizontal = back.y == front.y;

	for (const Position &pos: element.getPositions())
	{
		bool res = isHorizontal ? checkSidesHorizontalElement(area, pos, back, front) :
                                  checkSidesVerticalElement(area, pos, back, front);
		if (!res)
			return false;
	}

	return true;
}

std::vector<Element> removeAdjacentElements(const std::vector<Element> &elements, Area &area)
{
	std::vector<Element> res;

	for (const Element &element: elements)
		if (checkSides(area, element))
			res.push_back(element);
	return res;
}

Wall Wall::getRandomWall(Area &area, int size)
{
	std::vector<Element> elements = removeAdjacentElements(area.getFreeElements(size), area);
	int                  nbElements = elements.size();

	if (nbElements == 0)
		throw Exception::NoSpace();

	return elements[std::rand() % nbElements];
}
