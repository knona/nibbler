#include "nibbler.hpp"

void moveTop(Game &game)
{
	game.snake.moveTop(game.area, game.foods, game.cron);
}

void moveRight(Game &game)
{
	game.snake.moveRight(game.area, game.foods, game.cron);
}

void moveBottom(Game &game)
{
	game.snake.moveBottom(game.area, game.foods, game.cron);
}

void moveLeft(Game &game)
{
	game.snake.moveLeft(game.area, game.foods, game.cron);
}

void moveForward(Game &game)
{
	game.snake.moveForward(game.area, game.foods, game.cron);
}

void loop(Game &game, GUI &gui)
{
	std::unordered_map<Input, void (*)(Game & game)> fMap =
		{{Input::UP, moveTop},
		 {Input::RIGHT, moveRight},
		 {Input::DOWN, moveBottom},
		 {Input::LEFT, moveLeft}};

	Input input;

	gui.init(game);
	gui.render(game);
	while ((input = gui.getInput()) != Input::EXIT)
	{
		if (fMap.count(input))
			fMap[input](game);
		else
			moveForward(game);
		game.cron.checkEvents();
		gui.render(game);
	}
}

void addWalls(Game &game)
{
	game.walls.addRandomWall(game.area);
	game.walls.addRandomWall(game.area);
	game.walls.addRandomWall(game.area);
}

void startGame(const Options &options)
{
	Game game = {.area = {options.areaSize}};

	game.snake.setId();
	game.snake.setSnakeOnArea(game.area);

	game.foods.addRandomFood(game.area);

	addWalls(game);

	std::unique_ptr<GUI> gui = GUI::createGui<Retro>();
	loop(game, *gui);
}

int parsingErrorHandler(const Exception::ParsingOptions &e)
{
	int exitStatus = e.getExitStatus();
	if (exitStatus == EXIT_FAILURE)
		std::cerr << "\033[0;31mError: \033[0m" << e.what() << std::endl;
	else
		std::cout << e.what() << std::endl;
	return exitStatus;
}

int main(int argc, const char *argv[])
{
	Options options;

	srand(time(NULL));
	try
	{
		options = parseCommandLine(argc, argv);
	}
	catch (const Exception::ParsingOptions &e)
	{
		return parsingErrorHandler(e);
	}
	catch (const std::exception &e)
	{
		std::cerr << "\033[0;31mError: \033[0m" << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		startGame(options);
	}
	catch (const std::exception &e)
	{
		std::cerr << "\033[0;31mError: \033[0m" << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
