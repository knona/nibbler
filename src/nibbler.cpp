#include "nibbler.hpp"

void loopDebug(Game &game)
{
	std::string line;

	game.area.print(std::cout, &game.snake);
	std::cout << std::endl;
	while (std::getline(std::cin, line) && line != "q")
	{
		if (line == "w")
			game.snake.moveTop(game.area, game.foods, game.cron);
		else if (line == "d")
			game.snake.moveRight(game.area, game.foods, game.cron);
		else if (line == "s")
			game.snake.moveBottom(game.area, game.foods, game.cron);
		else if (line == "a")
			game.snake.moveLeft(game.area, game.foods, game.cron);
		else
			game.snake.moveForward(game.area, game.foods, game.cron);
		std::cout << "BEFORE EVENTS --" << std::endl;
		game.area.print(std::cout, &game.snake);
		std::cout << std::endl
				  << "----------------" << std::endl;
		game.cron.checkEvents();
		game.area.print(std::cout, &game.snake);
		std::cout << std::endl;
	}
}

void loop(Game &game)
{
	Input input;

	libA::render(game);
	while ((input = libA::getInput()) != Input::EXIT)
	{
		if (input == Input::UP)
			game.snake.moveTop(game.area, game.foods, game.cron);
		else if (input == Input::RIGHT)
			game.snake.moveRight(game.area, game.foods, game.cron);
		else if (input == Input::DOWN)
			game.snake.moveBottom(game.area, game.foods, game.cron);
		else if (input == Input::LEFT)
			game.snake.moveLeft(game.area, game.foods, game.cron);
		else
			game.snake.moveForward(game.area, game.foods, game.cron);
		game.cron.checkEvents();
		libA::render(game);
	}
}

void startGame(const Options &options)
{
	Game game = {.area = {options.areaSize}};

	game.snake.setId();
	game.snake.setSnakeOnArea(game.area);

	game.foods.addRandomFood(game.area);

	// game.walls.addRandomWall(game.area);
	// game.walls.addRandomWall(game.area);
	// game.walls.addRandomWall(game.area);

	// libA::init(game);
	try
	{
		loopDebug(game);
	}
	catch (const std::exception &e)
	{
		// libA::close();
		throw;
	}
	// libA::close();
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
