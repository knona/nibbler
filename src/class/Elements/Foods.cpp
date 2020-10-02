#include "Foods.hpp"

void Foods::addRandomFoodFromCron(const std::shared_ptr<void> &args)
{
	AddRandomFoodArgs &data = *(std::static_pointer_cast<AddRandomFoodArgs>(args));
	(data.foods->Foods::addRandomFood)(*data.area);
}

void Foods::addRandomFood(Area &area)
{
	Food food;

	try
	{
		food = Food::getRandomFood(area);
	}
	catch (const Exception::NoSpace &e)
	{
		throw Exception::Win();
	}
	Position pos = food.getPositions().front();

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
