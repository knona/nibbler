#include "nibbler.hpp"

void displayScore(GameData &game)
{
	std::cout << "Score: " << game.score << std::endl;
}

void addWalls(GameData &game)
{
	int surfaceArea = game.area.width() * game.area.height();
	int surfaceWalls = 0.03f * surfaceArea;

	while (surfaceWalls > 0)
	{
		int size = rand() % static_cast<int>(std::round(std::log(surfaceArea / 2))) + 2;
		game.walls.addRandomWall(game.area, size);
		surfaceWalls -= size;
	}
}

void startGame(const Options &options)
{
	std::unordered_map<std::string, std::unique_ptr<GUI> (*)()> fMap = //
		{ { "Gl", GUI::createGui<Gl> }, { "Retro", GUI::createGui<Retro> }, { "Debug", GUI::createGui<Debug> } };

	GameData game = { .score = 0, .area = { options.areaSize } };

	game.snake.setId();
	game.snake.setSnakeOnArea(game.area);

	game.foods.addRandomFood(game.area);

	if (!options.noWall)
		addWalls(game);

	std::unique_ptr<GUI> gui = fMap[options.gui]();

	try
	{
		loop(game, *gui, options);
	}
	catch (const Exception::GameOver &e)
	{
		std::cout << e.what() << std::endl;
		displayScore(game);
	}
	catch (const Exception::Win &e)
	{
		std::cout << e.what() << std::endl;
		displayScore(game);
	}
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
