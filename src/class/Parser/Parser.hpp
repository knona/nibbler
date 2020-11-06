#ifndef PARSER_HPP
#define PARSER_HPP

#include "Exceptions.hpp"
#include "Options.hpp"
#include "boost/program_options.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace po = boost::program_options;

class Parser
{
	private:
	static Size<int>   getAreaSize(const po::variables_map &vm);
	static std::string getGui(const po::variables_map &vm);
	static int         getSpeed(const po::variables_map &vm);
	static void        checkHelp(const po::variables_map &vm, const po::options_description &desc);

	public:
	static Options parseCommandLine(int argc, const char **argv);
	static int     parsingErrorHandler(const Exception::ParsingOptions &e);
};

#endif // !PARSER_HPP
