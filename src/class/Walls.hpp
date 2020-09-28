#ifndef WALLS_HPP
#define WALLS_HPP

#include <unordered_map>
#include <memory>
#include <exception>

#include "Area.hpp"
#include "Position.hpp"
#include "ElementType.hpp"
#include "Wall.hpp"

class Walls : public std::unordered_map<int, Wall>
{
private:
	static int _id;

public:
	void addRandomWall(Area &area);
	void removeWall(int id, Area &area);
};

#endif // !WALLS_HPP
