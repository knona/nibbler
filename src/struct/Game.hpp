#ifndef GAME_HPP
#define GAME_HPP

#include "Area.hpp"
#include "Foods.hpp"
#include "Walls.hpp"
#include "Snake.hpp"

struct Game
{
	Area area;
	Foods foods;
	Walls walls;
	Snake snake;
};

#endif // !GAME_HPP
