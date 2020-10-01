#include "Cron.hpp"

Cron::Cron() {}

Cron::Cron(const Cron &cron)
{
	*this = cron;
}

Cron::~Cron() {}

Cron &Cron::operator=(const Cron &cron)
{
	this->_cronTable = cron._cronTable;
	return *this;
}

void Cron::addEvent(CronData &cronData, int relativeCycle)
{
	this->_cronTable[relativeCycle - 1].push_back(cronData);
}

void Cron::checkEvents()
{
	std::map<int, std::list<CronData>>::iterator it = this->_cronTable.begin();
	while (it != this->_cronTable.end())
	{
		if (it->first == 0)
		{
			for (CronData &cronData : it->second)
				cronData.eventFunction(cronData.args);

			it = this->_cronTable.erase(it);
			std::cout << "1" << std::endl;
			std::cout << std::boolalpha << (it == this->_cronTable.end()) << std::endl;
			std::cout << "2" << std::endl;
		}
		else
		{
			this->_cronTable[it->first - 1] = it->second;
			it = this->_cronTable.erase(it);
		}
	}
}
