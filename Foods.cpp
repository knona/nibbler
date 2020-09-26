#include "Foods.hpp"

void Foods::addRandomFood(Area &area)
{
	Position pos = area.getRandomFreePosition();
	Element element({pos});
	Food food(element);

	int newId = food.setId();

	area[pos].id = newId;
	area[pos].type = ElementType::FoodT;

	(*this)[newId] = food;
}

void Foods::removeFood(const Position &pos, Area &area)
{
	this->removeFood(area[pos].id, area);
}

void Foods::removeFood(int id, Area &area)
{
	if (this->find(id) == this->end())
		throw std::out_of_range("Food id does not exist");

	Food &food = (*this)[id];

	for (const Position &pos : food.getPositions())
		area[pos].reset();

	this->erase(id);
}
