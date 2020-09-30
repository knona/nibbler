#include "libA.hpp"
#include <sstream>

namespace libA
{
	WINDOW *win;

	void init(Game &game)
	{
		setlocale(LC_ALL, "");
		initscr();
		start_color();
		noecho();
		cbreak();
		curs_set(0);
		refresh();
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_CYAN, COLOR_BLACK);
		init_pair(3, COLOR_GREEN, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		init_pair(5, COLOR_WHITE, COLOR_BLACK);
		win = newwin(game.area.getSize().height + 2, game.area.getSize().width * 2 + 2, 1, 1);
	}

	void close()
	{
		delwin(win);
		endwin();
	}

	Input getInput()
	{
		int c = getch();

		switch (c)
		{
		case 119:
			return Input::UP;
		case 100:
			return Input::RIGHT;
		case 115:
			return Input::DOWN;
		case 97:
			return Input::LEFT;
		case 27:
			return Input::EXIT;
		default:
			return Input::NONE;
		}
	}

	void render(Game &game)
	{
		wclear(win);
		wattron(win, COLOR_PAIR(5));
		box(win, 0, 0);

		for (int y = 0; y < game.area.getSize().height; y++)
		{
			for (int x = 0; x < game.area.getSize().width; x++)
			{
				Position pos = {x, y};
				std::string color;

				if (game.area.isWall(pos))
					wattron(win, COLOR_PAIR(1));
				else if (game.area.isFood(pos))
					wattron(win, COLOR_PAIR(2));
				else if (game.area.isSnake(pos))
					game.snake.isHead({x, y}) ? wattron(win, COLOR_PAIR(4)) : wattron(win, COLOR_PAIR(3));

				if (!game.area.isFree(pos))
					mvwprintw(win, y + 1, x * 2 + 1, "◼");
			}
		}
		wrefresh(win);
	}
} // namespace libA
