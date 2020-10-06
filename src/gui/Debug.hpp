#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "ncursesw/ncurses.h"
#include "GUI.hpp"
#include "Game.hpp"
#include "Input.hpp"

#include <termios.h>
#include <unistd.h>

class Debug : public GUI
{
private:
	char getchar();
	Debug(const Debug &) = delete;
	Debug &operator=(const Debug &) = delete;

public:
	Debug();
	~Debug();

	void init(Game &game);
	void close();
	Input getInput();
	void render(Game &game);
};

#endif // !DEBUG_HPP
