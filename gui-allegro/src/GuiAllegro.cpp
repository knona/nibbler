#include "GuiAllegro.hpp"

GuiAllegro::GuiAllegro(): _screen(1280, 720)
{}

GuiAllegro::~GuiAllegro()
{
	this->close();
}

void GuiAllegro::init(GameData &gData)
{
	al_init();
	al_install_keyboard();

	Size<int> areaSize = gData.area.getSize();

	_cellSize = std::min(_screen.width / areaSize.width, _screen.height / areaSize.height);
	if (_cellSize > 40)
		_cellSize = 40;
	_screen.width = areaSize.width * _cellSize;
	_screen.height = areaSize.height * _cellSize;
	_disp = al_create_display(_screen.width, _screen.height + 40);

	ALLEGRO_MONITOR_INFO info;
	al_get_monitor_info(0, &info);
	int winX = static_cast<int>(info.x2 / 2.0 - _screen.width / 2.0);
	int winY = static_cast<int>(info.y2 / 2.0 - (_screen.height + 40) / 2.0);
	al_set_window_position(_disp, winX, winY);

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	_font = al_load_font("assets/font/Retro Gaming.ttf", 26, 0);

	_queue = al_create_event_queue();
	al_register_event_source(_queue, al_get_keyboard_event_source());
	al_register_event_source(_queue, al_get_display_event_source(_disp));
}

void GuiAllegro::close()
{
	al_destroy_font(_font);
	al_destroy_display(_disp);
	al_destroy_event_queue(_queue);
	al_shutdown_font_addon();
	al_shutdown_primitives_addon();
}

Input GuiAllegro::getInput()
{
	const std::unordered_map<int, Input> map = {
		{ ALLEGRO_KEY_ESCAPE, Input::EXIT },                                  // EXIT
		{ ALLEGRO_KEY_UP, Input::UP },       { ALLEGRO_KEY_W, Input::UP },    // UP
		{ ALLEGRO_KEY_RIGHT, Input::RIGHT }, { ALLEGRO_KEY_D, Input::RIGHT }, // RIGHT
		{ ALLEGRO_KEY_DOWN, Input::DOWN },   { ALLEGRO_KEY_S, Input::DOWN },  // DOWN
		{ ALLEGRO_KEY_LEFT, Input::LEFT },   { ALLEGRO_KEY_A, Input::LEFT },  // LEFT
	};

	ALLEGRO_EVENT event;

	while (al_get_next_event(_queue, &event))
	{
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			return Input::EXIT;
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
			for (const auto &[key, input]: map)
				if (event.keyboard.keycode == key)
					return input;
	}

	return Input::NONE;
}

void GuiAllegro::render(GameData &gData)
{
	al_clear_to_color(al_map_rgb(241, 240, 238));

	const std::string scoreStr = "Score : " + std::to_string(gData.score.getScore());
	al_draw_filled_rectangle(0, 0, _screen.width, 40, al_map_rgb(161, 55, 49));
	int textWidth = al_get_text_width(_font, scoreStr.c_str());
	al_draw_text(_font, al_map_rgb(255, 255, 255), _screen.width / 2.0f - textWidth / 2.0f, 5, 0, scoreStr.c_str());

	for (int y = 0; y < gData.area.height(); y++)
	{
		for (int x = 0; x < gData.area.width(); x++)
		{
			Position pos(x, y);

			ALLEGRO_COLOR color;
			if (gData.area.isWall(pos))
				color = al_map_rgb(126, 99, 82);
			else if (gData.area.isFood(pos))
				color = al_map_rgb(237, 85, 76);
			else if (gData.area.isSnake(pos))
				color = gData.snake.isHead(pos) ? al_map_rgb(65, 47, 47) : al_map_rgb(241, 194, 132);
			else
				continue;
			al_draw_filled_rectangle(x * _cellSize, y * _cellSize + 40, (x + 1) * _cellSize, (y + 1) * _cellSize + 40,
			                         color);
		}
	}
	al_flip_display();
}

GUI *createGui()
{
	return new GuiAllegro;
}

void deleteGui(GUI *gui)
{
	delete gui;
}
