#include "../exceptions/Exceptions.hpp"
#include "Options.hpp"
#include "boost/program_options.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace po = boost::program_options;

Size<int> getAreaSize(const po::variables_map &vm)
{
	int width = vm["width"].as<int>();
	int height = vm["height"].as<int>();

	if (width > 50 || width < 10)
		throw Exception::ParsingOptions("Area's witdh must be between 10 and 50", EXIT_FAILURE);

	if (height > 30 || height < 10)
		throw Exception::ParsingOptions("Area's height must be between 10 and 30", EXIT_FAILURE);

	return { width, height };
}

std::string getGui(const po::variables_map &vm)
{
	std::string gui = vm["gui"].as<std::string>();
	if (gui != "Gl" && gui != "Retro")
		throw Exception::ParsingOptions("Invalid gui option", EXIT_FAILURE);
	return gui;
}

std::chrono::milliseconds getSpeed(const po::variables_map &vm)
{
	std::unordered_map<std::string, int> map = { { "slow", 300 }, { "normal", 200 }, { "fast", 100 } };

	std::string speed = vm["speed"].as<std::string>();
	if (speed != "slow" && speed != "normal" && speed != "fast")
		throw Exception::ParsingOptions("Invalid speed option", EXIT_FAILURE);
	return std::chrono::milliseconds(map[speed]);
}

Options parseCommandLine(int argc, const char **argv)
{
	po::options_description desc("Allowed options");
	desc.add_options()                                                                                       //
		("help,h", "produce help message")                                                                   //
		("width,W", po::value<int>()->required(), "set the area's width (required)")                         //
		("height,H", po::value<int>()->required(), "set the area's height (required)")                       //
		("gui", po::value<std::string>()->default_value("Gl"), "use the gui \"Retro\", \"Gl\" or \"third\"") //
		("no-wall", "do not set wall")                                                                       //
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

	return { getAreaSize(vm), getGui(vm), static_cast<bool>(vm.count("no-wall")), getSpeed(vm) };
}
