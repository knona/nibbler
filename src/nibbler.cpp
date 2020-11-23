#include "Game.hpp"
#include "Options.hpp"

#include <cstdlib>
#include <ctime>
#include <exception>

int main(int argc, const char *argv[])
{
	Options options;

	srand(time(NULL));
	try
	{
		options = Parser::parseCommandLine(argc, argv);
	}
	catch (const Exception::ParsingOptions &e)
	{
		return Parser::parsingErrorHandler(e);
	}
	catch (const std::exception &e)
	{
		std::cerr << "\033[0;31mError: \033[0m" << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "\033[0;31mAn error has occured\033[0m" << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		Game game(options);
		game.start();
	}
	catch (const std::exception &e)
	{
		std::cerr << "\033[0;31mError: \033[0m" << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "\033[0;31mAn error has occured\033[0m" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
