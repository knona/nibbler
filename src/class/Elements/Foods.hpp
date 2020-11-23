#ifndef FOODS_HPP
#define FOODS_HPP

#include "Area.hpp"
#include "ElementType.hpp"
#include "Food.hpp"
#include "Position.hpp"

#include <exception>
#include <functional>
#include <memory>
#include <unordered_map>

class Foods: public std::unordered_map<int, Food>
{
	public:
	void addRandomFood(Area &area);
	void removeFood(int id, Area &area);
	void removeFood(const Position &pos, Area &area);
};

#endif // !FOODS_HPP
