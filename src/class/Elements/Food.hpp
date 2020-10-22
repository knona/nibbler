#ifndef FOOD_HPP
#define FOOD_HPP

#include "Area.hpp"
#include "Element.hpp"

class Food: public Element
{
	private:
	static int _idCounter;

	public:
	Food();
	Food(const Element &element);

	int &       getIdCounter() const;
	static Food getRandomFood(Area &area);
};

#endif // !FOOD_HPP
