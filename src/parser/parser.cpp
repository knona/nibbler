#include "boost/program_options.hpp"
#include "Options.hpp"
#include "../exceptions/Exceptions.hpp"

#include <iostream>
#include <string>
#include <sstream>

namespace po = boost::program_options;

Options parseCommandLine(int argc, const char **argv)
{
	Size areaSize;

	po::options_description desc("Allowed options");
	desc.add_options()																	//
		("help,h", "produce help message")												//
		("width,W", po::value<int>(&areaSize.width), "set the area's width (required)") //
		("height,H", po::value<int>(&areaSize.height), "set the area's height (required)");

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

	if (areaSize.height == 0 || areaSize.width == 0)
		throw Exception::ParsingOptions("You must set area's witdh and height", EXIT_FAILURE);

	if (areaSize.width > 200 || areaSize.width < 8)
		throw Exception::ParsingOptions("Area's witdh must be between 8 and 200", EXIT_FAILURE);

	if (areaSize.height > 200 || areaSize.height < 8)
		throw Exception::ParsingOptions("Area's height must be between 8 and 200", EXIT_FAILURE);

	return {.areaSize = areaSize};
}
