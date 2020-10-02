#ifndef GROW_ARGS_HPP
#define GROW_ARGS_HPP

#include "Snake.hpp"
#include "Area.hpp"

class Snake;

struct GrowArgs
{
	Snake *snake;
	Area *area;
	Position oldTail;
};

#endif // !GROW_ARGS_HPP
