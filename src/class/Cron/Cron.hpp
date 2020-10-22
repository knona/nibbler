#ifndef CRON_HPP
#define CRON_HPP

#include "Area.hpp"
#include "CronData.hpp"
#include "Foods.hpp"
#include "Snake.hpp"
#include "Walls.hpp"

#include <list>
#include <map>

class Cron
{
	private:
	std::map<int, std::list<CronData>> _cronTable;

	public:
	Cron();
	Cron(const Cron &);
	~Cron();
	Cron &operator=(const Cron &);

	void addEvent(CronData cronData, int relativeCycle);
	void checkEvents();
};

#endif // !CRON_HPP
