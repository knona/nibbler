#include "nibbler.hpp"

void startGame(const Options &options)
{
	libA();
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
