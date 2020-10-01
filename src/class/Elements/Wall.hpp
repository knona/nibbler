#ifndef WALL_HPP
#define WALL_HPP

#include "Element.hpp"
#include "Area.hpp"

class Wall : public Element
{
private:
	static int _idCounter;

public:
	Wall();
	Wall(const Element &element);

	int &getIdCounter() const;
	static Wall getRandomWall(Area &area, int size);
};

#endif // !WALL_HPP
