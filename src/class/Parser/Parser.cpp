#include "Parser.hpp"

int Parser::parsingErrorHandler(const Exception::ParsingOptions &e)
{
	int exitStatus = e.getExitStatus();
	if (exitStatus == EXIT_FAILURE)
		std::cerr << "\033[0;31mError: \033[0m" << e.what() << std::endl;
	else
		std::cout << e.what() << std::endl;
	return exitStatus;
}

Size<int> Parser::getAreaSize(const po::variables_map &vm)
{
	int width = vm["width"].as<int>();
	int height = vm["height"].as<int>();

	if (width > 50 || width < 8)
		throw Exception::ParsingOptions("Area's witdh must be between 8 and 50", EXIT_FAILURE);

	if (height > 30 || height < 8)
		throw Exception::ParsingOptions("Area's height must be between 8 and 30", EXIT_FAILURE);

	return { width, height };
}

std::string Parser::getGui(const po::variables_map &vm)
{
	std::string gui = vm["gui"].as<std::string>();
	if (gui != "Sdl" && gui != "Allegro" && gui != "Sfml")
		throw Exception::ParsingOptions("Invalid gui option", EXIT_FAILURE);
	return gui;
}

int Parser::getSpeed(const po::variables_map &vm)
{
	std::unordered_map<std::string, int> map = { { "slow", 2 }, { "normal", 1 }, { "fast", 0 } };

	std::string speed = vm["speed"].as<std::string>();
	if (speed != "slow" && speed != "normal" && speed != "fast")
		throw Exception::ParsingOptions("Invalid speed option", EXIT_FAILURE);
	return map[speed];
}

Options Parser::parseCommandLine(int argc, const char **argv)
{
	po::options_description desc("Allowed options");
	desc.add_options()                                                                                          //
		("help,h", "produce help message")                                                                      //
		("width,W", po::value<int>()->required(), "set the area's width (required)")                            //
		("height,H", po::value<int>()->required(), "set the area's height (required)")                          //
		("gui", po::value<std::string>()->default_value("Sdl"), "use the gui \"Sdl\", \"Sfml\" or \"Allegro\"") //
		("no-wall", "do not set wall")                                                                          //
		("high-score", "check highscore for a specific area size")                                              //
		("speed", po::value<std::string>()->default_value("normal"),
	     "set snake's speed: \"slow\", \"normal\" or \"fast\"");

	po::variables_map vm;

	try
	{
		po::store(po::parse_command_line(argc, argv, desc), vm);
	}
	catch (const std::exception &e)
	{
		throw Exception::ParsingOptions(e.what(), EXIT_FAILURE);
	}

	po::notify(vm);

	if (vm.count("help"))
	{
		std::stringstream buffer;
		buffer << desc;
		throw Exception::ParsingOptions(buffer.str(), EXIT_SUCCESS);
	}

	return { Parser::getAreaSize(vm), Parser::getGui(vm), static_cast<bool>(vm.count("no-wall")),
		     static_cast<bool>(vm.count("high-score")), Parser::getSpeed(vm) };
}
