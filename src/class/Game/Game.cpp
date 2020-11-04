#include "Game.hpp"

Game::Game(const Options &options): _options(std::move(options))
{}

Game::~Game()
{}

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

InputMap Game::_inputMap = //
	{ { Input::UP, [](GameData &gData) { gData.snake.moveTop(gData); } },
	  { Input::RIGHT, [](GameData &gData) { gData.snake.moveRight(gData); } },
	  { Input::DOWN, [](GameData &gData) { gData.snake.moveBottom(gData); } },
	  { Input::LEFT, [](GameData &gData) { gData.snake.moveLeft(gData); } } };

void Game::loop(GUI &gui)
{
	Input       input;
	std::string pause;

	gui.init(this->_gData);
	gui.render(this->_gData);
	std::this_thread::sleep_for(this->_options.cycleTime * 3);
	while ((input = gui.getInput()) != Input::EXIT)
	{
		auto time1 = std::chrono::high_resolution_clock::now();
		if (Game::_inputMap.count(input))
			Game::_inputMap[input](this->_gData);
		else
			this->_gData.snake.moveForward(this->_gData);
		this->_gData.cron.checkEvents();
		gui.render(this->_gData);
		auto time2 = std::chrono::high_resolution_clock::now();

		std::chrono::microseconds timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1);
		std::chrono::microseconds timeToSleep = std::chrono::microseconds(this->_options.cycleTime) - timeElapsed;
		if (timeToSleep.count() < 0)
			timeToSleep = std::chrono::microseconds(0);
		std::this_thread::sleep_for(timeToSleep);
	}
}

void Game::start()
{
	std::unordered_map<std::string, std::unique_ptr<GUI> (*)()> fMap = //
		{ { "Gl", GUI::createGui<Gl> }, { "Retro", GUI::createGui<Retro> }, { "Sfml", GUI::createGui<GuiSfml> } };

	this->_gData.score = { this->_options };
	this->_gData.area = { this->_options.areaSize };
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

	std::unique_ptr<GUI> gui = fMap[this->_options.gui]();
	try
	{
		this->loop(*gui);
	}
	catch (const Exception::GameOver &e)
	{
		std::cout << e.what() << std::endl;
		gui.release();
		this->_gData.score.displayScore();
	}
	catch (const Exception::Win &e)
	{
		std::cout << e.what() << std::endl;
		gui.release();
		this->_gData.score.displayScore();
	}
}
