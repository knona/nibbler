#ifndef SIZE_HPP
#define SIZE_HPP

#include <iostream>

template<typename T>
struct Size
{
	T width;
	T height;

	Size();
	Size(T width, T height);
	Size(const Size<T> &size);
	~Size();
	Size<T> &operator=(const Size<T> &b);
};

template<typename T>
Size<T>::Size(): width(0), height(0)
{}

template<typename T>
Size<T>::Size(T width, T height): width(width), height(height)
{}

template<typename T>
Size<T>::Size(const Size<T> &size)
{
	*this = size;
}

template<typename T>
Size<T>::~Size() {};

template<typename T>
Size<T> &Size<T>::operator=(const Size<T> &b)
{
	this->width = b.width;
	this->height = b.height;
	return *this;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Size<T> &size)
{
	os << "width: " << size.width << ", height: " << size.height;
	return os;
}

#endif // !SIZE_HPP
