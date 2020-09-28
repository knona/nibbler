#ifndef MAIN_HPP
#define MAIN_HPP

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

#include <iostream>
#include <string>

Options parseCommandLine(int argc, const char **argv);

#endif // !MAIN_HPP
