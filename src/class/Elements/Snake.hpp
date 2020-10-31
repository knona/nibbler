#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Area.hpp"
#include "Cron.hpp"
#include "Direction.hpp"
#include "Element.hpp"
#include "Exceptions.hpp"
#include "Foods.hpp"

#include <memory>
#include <unordered_map>

struct Game;
class Cron;

class Snake: public Element
{
	private:
	Direction _direction;
	int       _grow;
	void      move(Game &game, const Position &newHead);

	public:
	Snake();
	Snake(const Snake &);
	~Snake();
	Snake &operator=(const Snake &);

	Direction getDirection() const;

	void setSnakeOnArea(Area &area);

	void moveTop(Game &game, bool forward = false);
	void moveRight(Game &game, bool forward = false);
	void moveBottom(Game &game, bool forward = false);
	void moveLeft(Game &game, bool forward = false);
	void moveForward(Game &game);

	bool isHead(const Position &pos) const;
	bool isTail(const Position &pos) const;
};

#endif // !SNAKE_HPP
