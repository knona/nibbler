#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <sstream>
#include <string>

class Exception
{
	public:
	static std::string error;

	class GameOver: public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class Win: public std::exception
	{
		public:
		virtual const char *what() const throw();
	};

	class ParsingOptions: public std::exception
	{
		private:
		int _exitStatus;
		ParsingOptions();

		public:
		ParsingOptions(const std::string &detail, int exitStatus);
		virtual const char *what() const throw();
		int                 getExitStatus() const;
	};

	class NoSpace: public std::exception
	{
		public:
		virtual const char *what() const throw();
	};
};

#endif // !EXCEPTIONS_HPP
