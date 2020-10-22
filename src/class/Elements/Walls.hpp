#ifndef WALLS_HPP
#define WALLS_HPP

#include "Area.hpp"
#include "ElementType.hpp"
#include "Position.hpp"
#include "Wall.hpp"

#include <exception>
#include <memory>
#include <unordered_map>

class Walls: public std::unordered_map<int, Wall>
{
	private:
	static int _id;

	public:
	void addRandomWall(Area &area);
	void removeWall(int id, Area &area);
};

#endif // !WALLS_HPP
