#ifndef GUI_HPP
#define GUI_HPP

#include "Game.hpp"
#include "Input.hpp"

#include <memory>

class GUI
{
public:
	virtual void init(Game &game) = 0;
	virtual void close() = 0;
	virtual Input getInput() = 0;
	virtual void render(Game &game) = 0;
	virtual ~GUI(){};
	template <typename T>
	static std::unique_ptr<GUI> createGui();
};

template <typename T>
std::unique_ptr<GUI> GUI::createGui()
{
	return std::make_unique<T>();
}

#endif // !GUI_HPP
