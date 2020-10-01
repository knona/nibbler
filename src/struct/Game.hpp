#ifndef GAME_HPP
#define GAME_HPP

#include "Area.hpp"
#include "Foods.hpp"
#include "Walls.hpp"
#include "Snake.hpp"
#include "Cron.hpp"

struct Game
{
public:
	Area area;
	Foods foods;
	Walls walls;
	Snake snake;
	Cron cron;
};

#endif // !GAME_HPP
