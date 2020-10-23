#include "Debug.hpp"

Debug::Debug()
{}

Debug::~Debug()
{
	this->close();
}

void Debug::init(Game &game)
{
	(void)game;
}

void Debug::close()
{}

char Debug::getchar()
{
	char           c;
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
	const std::unordered_map<int, Input> map = {
		{ 'q', Input::EXIT },  // EXIT
		{ 'w', Input::UP },    // UP
		{ 'd', Input::RIGHT }, // RIGHT
		{ 's', Input::DOWN },  // DOWN
		{ 'a', Input::LEFT },  // LEFT
	};

	char c = this->getchar();

	for (const std::pair<const int, Input> &pair: map)
		if (c == pair.first)
			return pair.second;

	return Input::NONE;
}

void Debug::render(Game &game)
{
	game.area.print(std::cout, &game.snake);
}
