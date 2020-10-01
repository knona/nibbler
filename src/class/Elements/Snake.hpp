#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "Direction.hpp"
#include "Area.hpp"
#include "Element.hpp"
#include "Exceptions.hpp"
#include "Foods.hpp"
#include "Cron.hpp"
#include "SnakeGrowData.hpp"

#include <memory>
#include <unordered_map>

class Cron;

class Snake : public Element
{
private:
	Direction _direction;
	void move(Area &area, const Position &newHead, Foods &foods, Cron &cron);
	static void grow(const std::shared_ptr<void> &);

public:
	Snake();
	Snake(const Snake &);
	~Snake();
	Snake &operator=(const Snake &);

	void setSnakeOnArea(Area &area);

	void moveTop(Area &area, Foods &foods, Cron &cron, bool forward = false);
	void moveRight(Area &area, Foods &foods, Cron &cron, bool forward = false);
	void moveBottom(Area &area, Foods &foods, Cron &cron, bool forward = false);
	void moveLeft(Area &area, Foods &foods, Cron &cron, bool forward = false);
	void moveForward(Area &area, Foods &foods, Cron &cron);

	bool isHead(const Position &pos) const;
	bool isTail(const Position &pos) const;
};

#endif // !SNAKE_HPP
