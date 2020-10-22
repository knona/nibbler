#ifndef FOODS_HPP
#define FOODS_HPP

#include "AddRandomFoodArgs.hpp"
#include "Area.hpp"
#include "ElementType.hpp"
#include "Food.hpp"
#include "Position.hpp"

#include <exception>
#include <memory>
#include <unordered_map>

class Foods: public std::unordered_map<int, Food>
{
	public:
	void addRandomFood(Area &area);
	void removeFood(int id, Area &area);
	void removeFood(const Position &pos, Area &area);

	static void addRandomFoodFromCron(const std::shared_ptr<void> &);
};

#endif // !FOODS_HPP
