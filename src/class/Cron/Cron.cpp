#include "Cron.hpp"

Cron::Cron()
{}

Cron::Cron(const Cron &cron)
{
	*this = cron;
}

Cron::~Cron()
{}

Cron &Cron::operator=(const Cron &cron)
{
	this->_cronTable = cron._cronTable;
	return *this;
}

void Cron::addEvent(const std::function<void()> &fn, int relativeCycle)
{
	this->_cronTable[relativeCycle].push_back(fn);
}

void Cron::checkEvents()
{
	std::map<int, std::list<std::function<void()>>>::iterator it = this->_cronTable.begin();
	while (it != this->_cronTable.end())
	{
		if (it->first == 0)
		{
			for (const std::function<void()> &fn: it->second)
				fn();
		}
		else
			this->_cronTable[it->first - 1] = it->second;
		it = this->_cronTable.erase(it);
	}
}
