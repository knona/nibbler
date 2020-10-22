#include "Retro.hpp"

Retro::Retro(): _win(nullptr)
{}

Retro::~Retro()
{
	this->close();
}

void Retro::init(Game &game)
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
	int width = game.area.getSize().width;
	int height = game.area.getSize().height;
	_win = newwin(height + 2, width * 2 + 2, 1, 1);
	keypad(_win, true);
}

void Retro::close()
{
	if (_win)
	{
		delwin(_win);
		_win = nullptr;
	}
	endwin();
}

Input Retro::getInput()
{
	// wtimeout(win, 200);
	int c = wgetch(_win);

	switch (c)
	{
	case KEY_UP:
	case 'w': return Input::UP;
	case KEY_RIGHT:
	case 'd': return Input::RIGHT;
	case KEY_DOWN:
	case 's': return Input::DOWN;
	case KEY_LEFT:
	case 'a': return Input::LEFT;
	case 27: // ESC
		return Input::EXIT;
	default: return Input::NONE;
	}
}

void Retro::render(Game &game)
{
	wclear(_win);
	wattron(_win, COLOR_PAIR(5));
	box(_win, 0, 0);

	for (int y = 0; y < game.area.getSize().height; y++)
	{
		for (int x = 0; x < game.area.getSize().width; x++)
		{
			Position    pos = { x, y };
			std::string color;

			if (game.area.isWall(pos))
				wattron(_win, COLOR_PAIR(1));
			else if (game.area.isFood(pos))
				wattron(_win, COLOR_PAIR(2));
			else if (game.area.isSnake(pos))
				game.snake.isHead({ x, y }) ? wattron(_win, COLOR_PAIR(4)) : wattron(_win, COLOR_PAIR(3));

			if (!game.area.isFree(pos))
				mvwprintw(_win, y + 1, x * 2 + 1, "◼");
		}
	}
	wrefresh(_win);
}
