#ifndef FOODS_HPP
#define FOODS_HPP

#include <unordered_map>
#include <memory>
#include <exception>

#include "Area.hpp"
#include "Position.hpp"
#include "ElementType.hpp"
#include "Food.hpp"

class Foods : public std::unordered_map<int, Food>
{
private:
	static int _id;

public:
	void addRandomFood(Area &area);
	void removeFood(int id, Area &area);
	void removeFood(const Position &pos, Area &area);
};

#endif // !FOODS_HPP
