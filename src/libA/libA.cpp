#include "libA.hpp"
#include <sstream>
#include <fstream>
#include <iostream>

namespace libA
{
	WINDOW *win;

	void init(Game &game)
	{
		setlocale(LC_ALL, "");
		initscr();
		start_color();
		noecho();
		raw();
		curs_set(0);
		refresh();
		init_pair(1, COLOR_RED, COLOR_BLACK);
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(3, COLOR_GREEN, COLOR_BLACK);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		init_pair(5, COLOR_WHITE, COLOR_BLACK);
		win = newwin(game.area.getSize().height + 2, game.area.getSize().width * 2 + 2, 1, 1);
		keypad(win, true);
	}

	void close()
	{
		delwin(win);
		endwin();
	}

	Input getInput()
	{
		// wtimeout(win, 500);
		int c = wgetch(win);

		// std::ofstream file("log.txt", std::ios_base::app);
		// file << c << std::endl;
		// file.close();
		switch (c)
		{
		case 259:
		case 119:
			return Input::UP;
		case 261:
		case 100:
			return Input::RIGHT;
		case 258:
		case 115:
			return Input::DOWN;
		case 260:
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
