#include "Size.hpp"

Size::Size() : width(0), height(0) {}

Size::Size(int width, int height) : width(width), height(height) {}

Size::Size(const Size &size)
{
	*this = size;
}

Size::~Size(){};

Size &Size::operator=(const Size &b)
{
	this->width = b.width;
	this->height = b.height;
	return *this;
}
std::ostream &operator<<(std::ostream &os, const Size &size)
{
	os << "width: " << size.width << ", height: " << size.height;
	return os;
}
