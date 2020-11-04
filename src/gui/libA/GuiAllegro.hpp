#ifndef GUI_ALLEGRO_HPP
#define GUI_ALLEGRO_HPP

#include "GUI.hpp"
#include "GameData.hpp"
#include "Input.hpp"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

class GuiAllegro: public GUI
{
	private:
	ALLEGRO_DISPLAY *    _disp;
	Size<float>          _screen;
	float                _cellSize;
	ALLEGRO_FONT *       _font;
	ALLEGRO_EVENT_QUEUE *_queue;

	GuiAllegro(const GuiAllegro &) = delete;
	GuiAllegro &operator=(const GuiAllegro &) = delete;

	public:
	GuiAllegro();
	~GuiAllegro();

	void  init(GameData &gData);
	void  close();
	Input getInput();
	void  render(GameData &gData);
};

#endif // !GUI_ALLEGRO_HPP
