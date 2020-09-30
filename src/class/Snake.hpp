#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Direction.hpp"
#include "Area.hpp"
#include "Element.hpp"
#include "Exceptions.hpp"
#include "Foods.hpp"

class Snake : public Element
{
private:
	Direction _direction;
	bool _grow;
	Position _lastTail;
	void move(Area &area, const Position &newHead, Foods &foods);

public:
	Snake();
	Snake(const Snake &);
	~Snake();
	Snake &operator=(const Snake &);

	void setSnakeOnArea(Area &area);

	void moveTop(Area &area, Foods &foods, bool forward = false);
	void moveRight(Area &area, Foods &foods, bool forward = false);
	void moveBottom(Area &area, Foods &foods, bool forward = false);
	void moveLeft(Area &area, Foods &foods, bool forward = false);
	void moveForward(Area &area, Foods &foods);

	bool isHead(const Position &pos) const;
	bool isTail(const Position &pos) const;

	void grow(Area &area);
};

#endif // !SNAKE_HPP
