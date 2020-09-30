#include "libA.hpp"

namespace libA
{
	void init()
	{
		initscr();
	}

	void close()
	{
		endwin();
	}

	void render(Game &game)
	{
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
				mvprintw(x, y, color.c_str());
			}
		}
		refresh();
	}
} // namespace libA
