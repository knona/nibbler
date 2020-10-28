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

const char *Exception::Classic::what() const throw()
{
	return "You got an error ><";
}

Exception::Detail::Detail(const std::string &detail)
{
	std::stringstream buffer;
	buffer << "My awesome error: " << detail;
	Exception::error = buffer.str();
}

const char *Exception::Detail::what() const throw()
{
	return Exception::error.c_str();
}

std::string Exception::error;
