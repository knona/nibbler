#include "Exceptions.hpp"

const char *Exception::GameOver::what() const throw()
{
	return "GAME OVER";
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
