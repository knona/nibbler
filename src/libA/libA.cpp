#include "libA.hpp"

namespace libA
{
	void init()
	{
		setlocale(LC_ALL, "");
		initscr();
		curs_set(0);
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
		clear();
		Area &area = game.area;
		for (int y = 0; y < area.getSize().height; y++)
		{
			for (int x = 0; x < area.getSize().width; x++)
			{
				Position pos = {x, y};
				std::string color;

				if (area.isWall(pos))
					color = "🟥";
				else if (area.isFood(pos))
					color = "🟦";
				else if (area.isSnake(pos))
					color = "🟨";
				else
					color = "⬜";
				mvprintw(y, x, color.c_str());
			}
		}
		refresh();
	}
} // namespace libA
