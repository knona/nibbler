#ifndef FOODS_HPP
#define FOODS_HPP

#include <unordered_map>
#include <memory>
#include <exception>

#include "Area.hpp"
#include "Position.hpp"
#include "ElementType.hpp"
#include "Food.hpp"
#include "AddRandomFoodArgs.hpp"

class Foods : public std::unordered_map<int, Food>
{
public:
	void addRandomFood(Area &area);
	void removeFood(int id, Area &area);
	void removeFood(const Position &pos, Area &area);

	static void addRandomFoodFromCron(const std::shared_ptr<void> &);
};

#endif // !FOODS_HPP
