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

struct GameData;
class Cron;

class Snake: public Element
{
	private:
	Direction _direction;
	int       _grow;
	void      move(GameData &gData, const Position &newHead);

	public:
	Snake();
	Snake(const Snake &);
	~Snake();
	Snake &operator=(const Snake &);

	Direction getDirection() const;

	void setSnakeOnArea(Area &area);

	void moveTop(GameData &gData, bool forward = false);
	void moveRight(GameData &gData, bool forward = false);
	void moveBottom(GameData &gData, bool forward = false);
	void moveLeft(GameData &gData, bool forward = false);
	void moveForward(GameData &gData);

	bool isHead(const Position &pos) const;
	bool isTail(const Position &pos) const;
};

#endif // !SNAKE_HPP
