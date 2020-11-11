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
	ALLEGRO_FONT *       _font;
	ALLEGRO_EVENT_QUEUE *_queue;
	Size<float>          _screen;
	float                _cellSize;
	bool                 _primitivesAddonInitialized;
	bool                 _fontAddonInitialized;
	bool                 _ttfAddonInitialized;

	GuiAllegro(const GuiAllegro &) = delete;
	GuiAllegro &operator=(const GuiAllegro &) = delete;

	void createWindow(const Size<int> &areaSize);
	void renderText(int score, bool pause);

	public:
	GuiAllegro();
	~GuiAllegro();

	void  init(GameData &gData);
	void  close();
	Input getInput();
	void  render(GameData &gData);
};

extern "C"
{
	GUI *createGui();
	void deleteGui(GUI *gui);
}

#endif // !GUI_ALLEGRO_HPP
