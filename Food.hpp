#ifndef FOOD_HPP
#define FOOD_HPP

#include "Element.hpp"

class Food : public Element
{
private:
	static int _idCounter;

public:
	Food();
	Food(const Element &element);

	int &getIdCounter() const;
};

#endif // !FOOD_HPP
