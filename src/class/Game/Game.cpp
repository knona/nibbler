#include "Game.hpp"

Game::Game(const Options &options): _options(std::move(options))
{}

Game::~Game()
{}

std::string Game::getLibPath(const Input &input) const
{
	std::unordered_map<Input, std::string> map = //
		{ { Input::LIB1, "./gui-sdl/libgui-sdl.so" },
		  { Input::LIB2, "./gui-allegro/libgui-allegro.so" },
		  { Input::LIB3, "./gui-sfml/libgui-sfml.so" } };

	return map[input];
}

std::string Game::getLibPath(const std::string &libName) const
{
	std::unordered_map<std::string, std::string> map = //
		{ { "Sdl", "./gui-sdl/libgui-sdl.so" },
		  { "Allegro", "./gui-allegro/libgui-allegro.so" },
		  { "Sfml", "./gui-sfml/libgui-sfml.so" } };

	return map[libName];
}

bool Game::isLibInput(const Input &input) const
{
	return input == Input::LIB1 || input == Input::LIB2 || input == Input::LIB3;
}

void Game::addWalls(GameData &gData)
{
	int surfaceArea = gData.area.width() * gData.area.height();
	int surfaceWalls = 0.03f * surfaceArea;

	while (surfaceWalls > 0)
	{
		int size = rand() % static_cast<int>(std::round(std::log(surfaceArea / 2))) + 2;
		gData.walls.addRandomWall(gData.area, size);
		surfaceWalls -= size;
	}
}

void Game::sleep(timePoint time1, timePoint time2) const
{
	int      time[3] = { 100, 200, 300 };
	millisec cycleTime = millisec(time[this->_options.speed]);

	microsec timeElapsed = std::chrono::duration_cast<microsec>(time2 - time1);
	microsec timeToSleep = microsec(cycleTime) - timeElapsed;
	if (timeToSleep.count() < 0)
		timeToSleep = microsec(0);
	std::this_thread::sleep_for(timeToSleep);
}

InputMap Game::_inputMap = //
	{ { Input::UP, [](GameData &gData) { gData.snake.moveTop(gData); } },
	  { Input::RIGHT, [](GameData &gData) { gData.snake.moveRight(gData); } },
	  { Input::DOWN, [](GameData &gData) { gData.snake.moveBottom(gData); } },
	  { Input::LEFT, [](GameData &gData) { gData.snake.moveLeft(gData); } } };

void Game::loop()
{
	Input      input = Input::NONE;
	GuiManager guiManager(this->getLibPath(this->_options.gui));
	GUI *&     gui = guiManager.getGui();

	gui->init(this->_gData);
	gui->render(this->_gData);
	while ((input = gui->getInput()) == Input::NONE)
		std::this_thread::sleep_for(millisec(100));
	while (input != Input::EXIT)
	{
		auto time1 = std::chrono::high_resolution_clock::now();
		if (input == Input::PAUSE)
			this->_gData.pause = !this->_gData.pause;
		else if (this->isLibInput(input) && guiManager.openLib(this->getLibPath(input)))
		{
			gui->init(this->_gData);
			gui->render(this->_gData);
		}
		else if (!this->_gData.pause)
		{
			if (Game::_inputMap.count(input))
				Game::_inputMap[input](this->_gData);
			else
				this->_gData.snake.moveForward(this->_gData);
			this->_gData.cron.checkEvents();
		}
		gui->render(this->_gData);
		auto time2 = std::chrono::high_resolution_clock::now();
		this->sleep(time1, time2);
		input = gui->getInput();
	}
}

void Game::start()
{
	this->_gData.score = { this->_options };
	this->_gData.area = { this->_options.areaSize };
	this->_gData.pause = false;
	if (this->_options.highScore)
	{
		this->_gData.score.displayHighScore();
		return;
	}

	this->_gData.snake.setId();
	this->_gData.snake.setSnakeOnArea(this->_gData.area);
	this->_gData.foods.addRandomFood(this->_gData.area);
	if (!this->_options.noWall)
		addWalls(this->_gData);

	try
	{
		this->loop();
	}
	catch (const Exception::GameOver &e)
	{
		std::cout << e.what() << std::endl;
		this->_gData.score.displayScore();
	}
	catch (const Exception::Win &e)
	{
		std::cout << e.what() << std::endl;
		this->_gData.score.displayScore();
	}
}
