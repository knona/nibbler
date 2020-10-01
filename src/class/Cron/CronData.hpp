#ifndef CRON_DATA_HPP
#define CRON_DATA_HPP

#include <memory>

struct CronData
{
	void (*eventFunction)(const std::shared_ptr<void> &);
	std::shared_ptr<void> args;
};

#endif // !CRON_DATA_HPP
