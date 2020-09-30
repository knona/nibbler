#ifndef LIB_A_HPP
#define LIB_A_HPP

#include "ncurses.h"
#include "Game.hpp"

namespace libA
{
	void init();
	void close();
	void render(Game &game);
} // namespace libA

#endif // !LIB_A_HPP
