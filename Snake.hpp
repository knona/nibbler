#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Direction.hpp"

class Snake
{
private:
	Direction _currentDirection;

public:
	Snake();
	Snake(const Snake &);
	~Snake();
	Snake &operator=(const Snake &);

	void moveFromTopInput();
	void moveFromRightInput();
	void moveFromBottomnput();
	void moveFromLeftInput();
};

#endif // !SNAKE_HPP
