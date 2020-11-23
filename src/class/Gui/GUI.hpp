#ifndef GUI_HPP
#define GUI_HPP

#include "GameData.hpp"
#include "Input.hpp"

#include <memory>

class GUI
{
	public:
	virtual void  init(GameData &gData) = 0;
	virtual void  close() = 0;
	virtual Input getInput() = 0;
	virtual void  render(GameData &gData) = 0;
	virtual ~GUI() {};
};

#endif // !GUI_HPP
