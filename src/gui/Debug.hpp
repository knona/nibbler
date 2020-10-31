#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "GUI.hpp"
#include "GameData.hpp"
#include "Input.hpp"
#include "ncursesw/ncurses.h"

#include <termios.h>
#include <unistd.h>

class Debug: public GUI
{
	private:
	char getchar();
	Debug(const Debug &) = delete;
	Debug &operator=(const Debug &) = delete;

	public:
	Debug();
	~Debug();

	void  init(GameData &game);
	void  close();
	Input getInput();
	void  render(GameData &game);
};

#endif // !DEBUG_HPP
