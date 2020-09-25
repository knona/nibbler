#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <list>

#include "Position.hpp"

class Element
{
protected:
	std::list<Position> _positions;

public:
	Element();
	Element(const std::list<Position> &positions);
	Element(const Element &);
	virtual ~Element();
	Element &operator=(const Element &);
	std::list<Position> &getPositions(void);
	const std::list<Position> &getPositions(void) const;
};

#endif // !ELEMENT_HPP
