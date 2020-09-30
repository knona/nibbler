#ifndef LIB_A_HPP
#define LIB_A_HPP

#include "ncursesw/ncurses.h"
#include "Game.hpp"
#include "Input.hpp"

#include <clocale>

namespace libA
{
	void init();
	void close();
	Input getInput();
	void render(Game &game);
} // namespace libA

#endif // !LIB_A_HPP
