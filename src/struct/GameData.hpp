#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include "Area.hpp"
#include "Cron.hpp"
#include "Foods.hpp"
#include "Score.hpp"
#include "Snake.hpp"
#include "Walls.hpp"

struct GameData
{
	Score score;
	Area  area;
	Foods foods;
	Walls walls;
	Snake snake;
	Cron  cron;
	bool  pause;
};

#endif // !GAME_DATA_HPP
