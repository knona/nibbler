#include "GuiSfml.hpp"

GuiSfml::GuiSfml(): _screen(1280, 720)
{}

GuiSfml::~GuiSfml()
{
	this->close();
}

void GuiSfml::init(GameData &gData)
{
	sf::err().rdbuf(nullptr);

	Size<int> areaSize = gData.area.getSize();

	_cellSize = std::min(_screen.width / areaSize.width, _screen.height / areaSize.height);
	if (_cellSize > 40)
		_cellSize = 40;
	_screen.width = areaSize.width * _cellSize;
	_screen.height = areaSize.height * _cellSize;

	_window.create(sf::VideoMode(_screen.width, _screen.height + 40), "NIBBLER",
	               sf::Style::Titlebar | sf::Style::Close);

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2i  windowPos;
	windowPos.x = static_cast<int>(desktop.width / 2.0 - _window.getSize().x / 2.0);
	windowPos.y = static_cast<int>(desktop.height / 2.0 - _window.getSize().y / 2.0);
	_window.setPosition(windowPos);

	_window.setKeyRepeatEnabled(false);
	_window.pollEvent(_event);
}

void GuiSfml::close()
{}

Input GuiSfml::getInput()
{
	const std::unordered_map<sf::Keyboard::Key, Input> map = {
		{ sf::Keyboard::Escape, Input::EXIT },                                    // EXIT
		{ sf::Keyboard::P, Input::PAUSE },                                        // PAUSE
		{ sf::Keyboard::Num1, Input::LIB1 },                                      // LIB1
		{ sf::Keyboard::Num2, Input::LIB2 },                                      // LIB2
		{ sf::Keyboard::Num3, Input::LIB3 },                                      // LIB3
		{ sf::Keyboard::Up, Input::UP },       { sf::Keyboard::W, Input::UP },    // UP
		{ sf::Keyboard::Right, Input::RIGHT }, { sf::Keyboard::D, Input::RIGHT }, // RIGHT
		{ sf::Keyboard::Down, Input::DOWN },   { sf::Keyboard::S, Input::DOWN },  // DOWN
		{ sf::Keyboard::Left, Input::LEFT },   { sf::Keyboard::A, Input::LEFT },  // LEFT
	};

	if (!_window.isOpen() || _event.type == sf::Event::Closed)
		return Input::EXIT;

	while (_window.pollEvent(_event))
	{
		if (_event.type == sf::Event::KeyPressed)
			for (const auto &[key, input]: map)
				if (_event.key.code == key)
					return input;
	}

	return Input::NONE;
}

void GuiSfml::renderText(GameData &gData)
{
	sf::RectangleShape rectangle(sf::Vector2f(_screen.width, 40));
	rectangle.setFillColor(sf::Color(86, 101, 115));
	rectangle.setPosition(0, 0);
	_window.draw(rectangle);

	sf::Font font;
	if (!font.loadFromFile("assets/font/ModernSans-Light.otf"))
		throw std::runtime_error("Cannot open the font");

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(26);
	scoreText.setFillColor(sf::Color::White);
	std::string scoreStr = "Score : " + std::to_string(gData.score.getScore());
	scoreText.setString(scoreStr);
	scoreText.setPosition(_screen.width / 2.0f - scoreText.getLocalBounds().width / 2.0f, 5);
	_window.draw(scoreText);

	if (gData.pause)
	{
		sf::Text pauseText;
		pauseText.setFont(font);
		pauseText.setCharacterSize(28);
		pauseText.setFillColor(sf::Color::White);
		pauseText.setString("||");
		pauseText.setStyle(sf::Text::Bold);
		pauseText.setPosition(_screen.width - pauseText.getLocalBounds().width - 15, 0);
		_window.draw(pauseText);
	}
}

void GuiSfml::render(GameData &gData)
{
	sf::Color bgColor(247, 249, 249);
	_window.clear(bgColor);

	sf::RectangleShape square(sf::Vector2f(_cellSize, _cellSize));
	for (int y = 0; y < gData.area.height(); y++)
	{
		for (int x = 0; x < gData.area.width(); x++)
		{
			Position pos(x, y);

			square.setPosition(_cellSize * x, _cellSize * y + 40);

			sf::Color color;
			if (gData.area.isWall(pos))
				color = sf::Color(211, 84, 0);
			else if (gData.area.isFood(pos))
				color = sf::Color(93, 173, 226);
			else if (gData.area.isSnake(pos))
				color = gData.snake.isHead(pos) ? sf::Color(244, 208, 63) : sf::Color(88, 214, 141);
			else
				continue;

			square.setFillColor(color);
			_window.draw(square);
		}
	}

	this->renderText(gData);

	_window.display();
}

GUI *createGui()
{
	return new GuiSfml;
}

void deleteGui(GUI *gui)
{
	delete gui;
}
