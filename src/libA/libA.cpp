#include "libA.hpp"

namespace libA
{
	WINDOW *win;

	void init(Game &game)
	{
		setlocale(LC_ALL, "");
		initscr();
		noecho();
		cbreak();
		curs_set(0);
		refresh();
		win = newwin(game.area.getSize().height + 2, game.area.getSize().width + 2, 1, 1);
	}

	void close()
	{
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
		box(win, 0, 0);
		Area &area = game.area;
		for (int y = 0; y < area.getSize().height; y++)
		{
			for (int x = 0; x < area.getSize().width; x++)
			{
				Position pos = {x, y};
				std::string color;

				if (area.isWall(pos))
					color = "w";
				else if (area.isFood(pos))
					color = "f";
				else if (area.isSnake(pos))
					color = "▪";
				if (!area.isFree(pos))
					mvwprintw(win, y + 1, x + 1, color.c_str());
			}
		}
		wrefresh(win);
	}
} // namespace libA
