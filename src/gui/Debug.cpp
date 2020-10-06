#include "Debug.hpp"

Debug::Debug() {}

Debug::~Debug()
{
	this->close();
}

void Debug::init(Game &game)
{
	(void)game;
}

void Debug::close() {}

char Debug::getchar()
{
	char c;
	struct termios old_tio, new_tio;
	tcgetattr(STDIN_FILENO, &old_tio);
	new_tio = old_tio;
	new_tio.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
	c = ::getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
	return c;
}

Input Debug::getInput()
{
	char c = this->getchar();

	switch (c)
	{
	case 'w':
		return Input::UP;
	case 'd':
		return Input::RIGHT;
	case 's':
		return Input::DOWN;
	case 'a':
		return Input::LEFT;
	case 'q':
		return Input::EXIT;
	default:
		return Input::NONE;
	}
}

void Debug::render(Game &game)
{
	game.area.print(std::cout, &game.snake);
}
