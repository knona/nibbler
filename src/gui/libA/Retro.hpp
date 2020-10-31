#ifndef RETRO_HPP
#define RETRO_HPP

#include "GUI.hpp"
#include "GameData.hpp"
#include "Input.hpp"
#include "ncursesw/ncurses.h"

#include <clocale>

class Retro: public GUI
{
	private:
	WINDOW *_win;
	Retro(const Retro &) = delete;
	Retro &operator=(const Retro &) = delete;

	public:
	Retro();
	~Retro();

	void  init(GameData &gData);
	void  close();
	Input getInput();
	void  render(GameData &gData);
};

#endif // !RETRO_HPP
