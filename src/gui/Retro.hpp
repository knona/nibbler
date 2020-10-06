#ifndef RETRO_HPP
#define RETRO_HPP

#include "ncursesw/ncurses.h"
#include "GUI.hpp"
#include "Game.hpp"
#include "Input.hpp"

#include <clocale>

class Retro : public GUI
{
private:
	WINDOW *_win;
	Retro(const Retro &) = delete;
	Retro &operator=(const Retro &) = delete;

public:
	Retro();
	~Retro();

	void init(Game &game);
	void close();
	Input getInput();
	void render(Game &game);
};

#endif // !RETRO_HPP
