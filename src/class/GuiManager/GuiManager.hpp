#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include "GUI.hpp"

#include <dlfcn.h>

class GuiManager
{
	private:
	void *_handle;
	GUI *(*_createGui)();
	void (*_deleteGui)(GUI *);
	GUI *       _gui;
	std::string _currentLib;

	GuiManager(const GuiManager &) = delete;
	GuiManager &operator=(const GuiManager &) = delete;

	public:
	GuiManager();
	GuiManager(const std::string &lib);
	~GuiManager();

	bool  openLib(const std::string &lib);
	void  closeLib();
	GUI *&getGui();
};

#endif // !GUI_MANAGER_HPP
