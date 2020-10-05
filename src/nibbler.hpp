#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "Area.hpp"
#include "Cell.hpp"
#include "Direction.hpp"
#include "Element.hpp"
#include "ElementType.hpp"
#include "Food.hpp"
#include "Foods.hpp"
#include "Position.hpp"
#include "Size.hpp"
#include "Snake.hpp"
#include "Wall.hpp"
#include "Walls.hpp"
#include "Options.hpp"
#include "Game.hpp"
#include "libA.hpp"
#include "Input.hpp"

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_map>

Options parseCommandLine(int argc, const char **argv);
void debug(Game &game);

#endif // !NIBBLER_HPP
