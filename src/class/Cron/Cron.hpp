#ifndef CRON_HPP
#define CRON_HPP

#include "Area.hpp"
#include "Foods.hpp"
#include "Snake.hpp"
#include "Walls.hpp"

#include <functional>
#include <list>
#include <map>

class Cron
{
	private:
	std::map<int, std::list<std::function<void()>>> _cronTable;

	public:
	Cron();
	Cron(const Cron &);
	~Cron();
	Cron &operator=(const Cron &);

	void addEvent(const std::function<void()> &fn, int relativeCycle);
	void checkEvents();
};

#endif // !CRON_HPP
