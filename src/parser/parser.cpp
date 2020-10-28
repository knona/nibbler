#include "../exceptions/Exceptions.hpp"
#include "Options.hpp"
#include "boost/program_options.hpp"

#include <iostream>
#include <sstream>
#include <string>

namespace po = boost::program_options;

Options parseCommandLine(int argc, const char **argv)
{
	Size<int> areaSize;

	po::options_description desc("Allowed options");
	desc.add_options()                                                                                          //
		("help,h", "produce help message")                                                                      //
		("width,W", po::value<int>(&areaSize.width), "set the area's width (required)")                         //
		("height,H", po::value<int>(&areaSize.height), "set the area's height (required)")                      //
		("gui,G", po::value<std::string>()->default_value("Gl"), "use the gui \"Retro\", \"Gl\" or \"third\""); //

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

	std::string gui = vm["gui"].as<std::string>();

	if (gui != "Gl" && gui != "Retro")
		throw Exception::ParsingOptions("Invalid gui option", EXIT_FAILURE);

	if (vm.count("help"))
	{
		std::stringstream buffer;
		buffer << desc;
		throw Exception::ParsingOptions(buffer.str(), EXIT_SUCCESS);
	}

	if (areaSize.height == 0 || areaSize.width == 0)
		throw Exception::ParsingOptions("You must set area's witdh and height", EXIT_FAILURE);

	if (areaSize.width > 50 || areaSize.width < 10)
		throw Exception::ParsingOptions("Area's witdh must be between 10 and 50", EXIT_FAILURE);

	if (areaSize.height > 30 || areaSize.height < 10)
		throw Exception::ParsingOptions("Area's height must be between 10 and 30", EXIT_FAILURE);

	return { .areaSize = areaSize, .gui = std::move(gui) };
}
