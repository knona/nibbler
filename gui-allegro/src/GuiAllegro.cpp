#include "GuiAllegro.hpp"

GuiAllegro::GuiAllegro():
	_disp(nullptr), _font(nullptr), _queue(nullptr), _screen(1280, 720), _primitivesAddonInitialized(false),
	_fontAddonInitialized(false), _ttfAddonInitialized(false)
{}

GuiAllegro::~GuiAllegro()
{
	this->close();
}

void GuiAllegro::createWindow(const Size<int> &areaSize)
{
	_cellSize = std::min(_screen.width / areaSize.width, _screen.height / areaSize.height);
	if (_cellSize > 40)
		_cellSize = 40;
	_screen.width = areaSize.width * _cellSize;
	_screen.height = areaSize.height * _cellSize;
	_disp = al_create_display(_screen.width, _screen.height + 40);
	if (!_disp)
		throw std::runtime_error("Cannot create allegro display");
	al_set_window_title(_disp, "NIBBLER");

	ALLEGRO_MONITOR_INFO info;
	al_get_monitor_info(0, &info);
	int winX = static_cast<int>(info.x2 / 2.0 - _screen.width / 2.0);
	int winY = static_cast<int>(info.y2 / 2.0 - (_screen.height + 40) / 2.0);
	al_set_window_position(_disp, winX, winY);
}

void GuiAllegro::init(GameData &gData)
{
	if (!al_init())
		throw std::runtime_error("Cannot initialize allegro");

	if (!al_install_keyboard())
		throw std::runtime_error("Cannot install keyboard allegro");

	this->createWindow(gData.area.getSize());

	if (!(_primitivesAddonInitialized = al_init_primitives_addon()))
		throw std::runtime_error("Cannot initialize primitives allegro addon");
	if (!(_fontAddonInitialized = al_init_font_addon()))
		throw std::runtime_error("Cannot initialize font allegro addon");
	if (!(_ttfAddonInitialized = al_init_ttf_addon()))
		throw std::runtime_error("Cannot initialize ttf allegro addon");

	if (!(_font = al_load_font("assets/font/Retro Gaming.ttf", 24, 0)))
		throw std::runtime_error("Cannot load assets/font/Retro Gaming.ttf font allegro");

	_queue = al_create_event_queue();
	al_register_event_source(_queue, al_get_keyboard_event_source());
	al_register_event_source(_queue, al_get_display_event_source(_disp));
}

void GuiAllegro::close()
{
	if (_font)
	{
		al_destroy_font(_font);
		_font = nullptr;
	}
	if (_disp)
	{
		al_destroy_display(_disp);
		_disp = nullptr;
	}
	if (_queue)
	{
		al_destroy_event_queue(_queue);
		_queue = nullptr;
	}
	if (_ttfAddonInitialized)
		al_shutdown_ttf_addon();
	if (_fontAddonInitialized)
		al_shutdown_font_addon();
	if (_primitivesAddonInitialized)
		al_shutdown_primitives_addon();
}

Input GuiAllegro::getInput()
{
	const std::unordered_map<int, Input> map = {
		{ ALLEGRO_KEY_ESCAPE, Input::EXIT },                                  // EXIT
		{ ALLEGRO_KEY_P, Input::PAUSE },                                      // PAUSE
		{ ALLEGRO_KEY_1, Input::LIB1 },                                       // LIB1
		{ ALLEGRO_KEY_2, Input::LIB2 },                                       // LIB2
		{ ALLEGRO_KEY_3, Input::LIB3 },                                       // LIB3
		{ ALLEGRO_KEY_ESCAPE, Input::EXIT },                                  // EXIT
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

void GuiAllegro::renderText(int score, bool pause)
{
	al_draw_filled_rectangle(0, 0, _screen.width, 40, al_map_rgb(161, 55, 49));
	{
		const std::string text = "Score : " + std::to_string(score);
		int               textWidth = al_get_text_width(_font, text.c_str());
		al_draw_text(_font, al_map_rgb(255, 255, 255), _screen.width / 2.0f - textWidth / 2.0f, 5, 0, text.c_str());
	}
	if (pause)
	{
		const char *text = "||";
		int         textWidth = al_get_text_width(_font, text);
		al_draw_text(_font, al_map_rgb(255, 255, 255), _screen.width - textWidth - 15, 5, 0, text);
	}
}

void GuiAllegro::render(GameData &gData)
{
	al_clear_to_color(al_map_rgb(241, 240, 238));

	renderText(gData.score.getScore(), gData.pause);

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
