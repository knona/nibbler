#ifndef CRON_HPP
#define CRON_HPP

#include "Area.hpp"
#include "Foods.hpp"
#include "Walls.hpp"
#include "Snake.hpp"
#include "CronData.hpp"

#include <map>
#include <list>

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
