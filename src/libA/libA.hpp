#ifndef LIB_A_HPP
#define LIB_A_HPP

#include "ncursesw/ncurses.h"
#include "Game.hpp"
#include <clocale>

namespace libA
{
	void init();
	void close();
	void render(Game &game);
} // namespace libA

#endif // !LIB_A_HPP
