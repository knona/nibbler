#ifndef GUI_SFML_HPP
#define GUI_SFML_HPP

#include "GUI.hpp"
#include "GameData.hpp"
#include "Input.hpp"
#include "Position.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GuiSfml: public GUI
{
	private:
	sf::RenderWindow _window;
	sf::Event        _event;
	Size<float>      _screen;
	float            _cellSize;

	GuiSfml(const GuiSfml &) = delete;
	GuiSfml &operator=(const GuiSfml &) = delete;

	void displayScore(GameData &gData);

	public:
	GuiSfml();
	~GuiSfml();

	void  init(GameData &gData);
	void  close();
	Input getInput();
	void  render(GameData &gData);
};

#endif // !GUI_SFML_HPP
