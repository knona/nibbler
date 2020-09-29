#ifndef SIZE_HPP
#define SIZE_HPP

#include <iostream>

struct Size
{
	int width;
	int height;

	Size();
	Size(int width, int height);
	Size(const Size &size);
	~Size();
	Size &operator=(const Size &b);
};

std::ostream &operator<<(std::ostream &os, const Size &size);
#endif // !SIZE_HPP
