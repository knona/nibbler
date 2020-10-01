#ifndef SNAKE_GROW_DATA_HPP
#define SNAKE_GROW_DATA_HPP

#include "Snake.hpp"
#include "Area.hpp"

class Snake;

struct SnakeGrowData
{
	Snake *snake;
	Area *area;
	Position oldTail;
};

#endif // !SNAKE_GROW_DATA_HPP
