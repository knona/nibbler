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
	static int _id;
	Direction _direction;
	bool _grow;
	Position _lastTail;
	void moveFromInput(Area &area, const Position &newHead, Foods &foods);

public:
	Snake();
	Snake(const Snake &);
	~Snake();
	Snake &operator=(const Snake &);

	void moveFromTopInput(Area &area, Foods &foods);
	void moveFromRightInput(Area &area, Foods &foods);
	void moveFromBottomnput(Area &area, Foods &foods);
	void moveFromLeftInput(Area &area, Foods &foods);

	void grow(Area &area);
};

#endif // !SNAKE_HPP
