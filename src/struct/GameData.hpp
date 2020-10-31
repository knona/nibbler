#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include "Area.hpp"
#include "Cron.hpp"
#include "Foods.hpp"
#include "Snake.hpp"
#include "Walls.hpp"

struct GameData
{
	int   score;
	Area  area;
	Foods foods;
	Walls walls;
	Snake snake;
	Cron  cron;
};

#endif // !GAME_DATA_HPP
