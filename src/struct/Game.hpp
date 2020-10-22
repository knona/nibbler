#ifndef GAME_HPP
#define GAME_HPP

#include "Area.hpp"
#include "Cron.hpp"
#include "Foods.hpp"
#include "Snake.hpp"
#include "Walls.hpp"

struct Game
{
	public:
	Area  area;
	Foods foods;
	Walls walls;
	Snake snake;
	Cron  cron;
};

#endif // !GAME_HPP
