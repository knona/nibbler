#include "Exceptions.hpp"

const char *Exception::GameOver::what() const throw()
{
	return "\033[0;31mGAME OVER\033[0m";
}

const char *Exception::Win::what() const throw()
{
	return "\033[0;32mWIN\033[0m";
}

Exception::ParsingOptions::ParsingOptions(const std::string &detail, int exitStatus)
{
	this->_exitStatus = exitStatus;
	std::stringstream buffer;
	buffer << detail;
	Exception::error = buffer.str();
}

const char *Exception::ParsingOptions::what() const throw()
{
	return Exception::error.c_str();
}

int Exception::ParsingOptions::getExitStatus() const
{
	return this->_exitStatus;
}

const char *Exception::NoSpace::what() const throw()
{
	return "No space";
}

std::string Exception::error;
