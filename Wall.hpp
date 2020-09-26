#ifndef WALL_HPP
#define WALL_HPP

#include "Element.hpp"

class Wall : public Element
{
private:
	static int _idCounter;

public:
	Wall();
	Wall(const Element &element);

	int &getIdCounter() const;
};

#endif // !WALL_HPP
