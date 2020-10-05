#include "nibbler.hpp"
#include <termios.h>
#include <unistd.h>

char getcharr()
{
	char c;
	struct termios old_tio, new_tio;
	tcgetattr(STDIN_FILENO, &old_tio);
	new_tio = old_tio;
	new_tio.c_lflag &= (~ICANON & ~ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
	return c;
}

void loopDebug(Game &game)
{
	char c;

	game.area.print(std::cout, &game.snake);
	while ((c = getcharr()) != 'q')
	{
		if (c == 'w')
			game.snake.moveTop(game.area, game.foods, game.cron);
		else if (c == 'd')
			game.snake.moveRight(game.area, game.foods, game.cron);
		else if (c == 's')
			game.snake.moveBottom(game.area, game.foods, game.cron);
		else if (c == 'a')
			game.snake.moveLeft(game.area, game.foods, game.cron);
		else
			game.snake.moveForward(game.area, game.foods, game.cron);
		game.cron.checkEvents();
		game.area.print(std::cout, &game.snake);
	}
}

void debug(Game &game)
{
	loopDebug(game);
}
