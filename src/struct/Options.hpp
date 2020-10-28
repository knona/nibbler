#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include "Size.tpp"

#include <chrono>

struct Options
{
	Size<int>                 areaSize;
	std::string               gui;
	bool                      noWall;
	std::chrono::milliseconds cycleTime;
};

#endif // !OPTIONS_HPP
