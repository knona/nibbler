#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "Position.hpp"

#include <list>

class Element
{
	private:
	static int _idCounter;

	protected:
	int                 _id;
	std::list<Position> _positions;

	public:
	Element();
	Element(const std::list<Position> &positions);
	Element(const Element &);
	virtual ~Element();
	Element &operator=(const Element &);

	virtual std::list<Position> &      getPositions();
	virtual const std::list<Position> &getPositions() const;
	virtual int                        getId() const;
	virtual int                        setId();
	virtual int &                      getIdCounter() const;
};

#endif // !ELEMENT_HPP
