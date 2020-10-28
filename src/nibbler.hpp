#ifndef NIBBLER_HPP
#define NIBBLER_HPP

#include "Area.hpp"
#include "Cell.hpp"
#include "Debug.hpp"
#include "Direction.hpp"
#include "Element.hpp"
#include "ElementType.hpp"
#include "Food.hpp"
#include "Foods.hpp"
#include "GUI.hpp"
#include "Game.hpp"
#include "Gl.hpp"
#include "Input.hpp"
#include "Options.hpp"
#include "Position.hpp"
#include "Retro.hpp"
#include "Size.tpp"
#include "Snake.hpp"
#include "Wall.hpp"
#include "Walls.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>

Options parseCommandLine(int argc, const char **argv);
void    loop(Game &game, GUI &gui);

#endif // !NIBBLER_HPP
