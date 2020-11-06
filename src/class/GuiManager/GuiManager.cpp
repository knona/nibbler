#include "GuiManager.hpp"

GuiManager::GuiManager(): _handle(nullptr), _createGui(nullptr), _deleteGui(nullptr), _gui(nullptr)
{}

GuiManager::GuiManager(const std::string &lib):
	_handle(nullptr), _createGui(nullptr), _deleteGui(nullptr), _gui(nullptr)
{
	this->openLib(lib);
}

GuiManager::~GuiManager()
{
	this->closeLib();
}

void GuiManager::closeLib()
{
	if (this->_gui)
	{
		this->_deleteGui(this->_gui);
		this->_gui = nullptr;
	}
	if (this->_handle)
	{
		dlclose(this->_handle);
		this->_handle = nullptr;
	}
	this->_createGui = nullptr;
	this->_deleteGui = nullptr;
}

bool GuiManager::openLib(const std::string &lib)
{
	if (lib == _currentLib)
		return false;
	this->closeLib();
	this->_handle = dlopen(lib.c_str(), RTLD_LAZY | RTLD_GLOBAL);
	if (!this->_handle)
	{
		std::string error = "Cannot open lib " + lib;
		throw std::runtime_error(error.c_str());
	}
	this->_createGui = reinterpret_cast<GUI *(*)()>(dlsym(this->_handle, "createGui"));
	if (!this->_createGui)
	{
		std::string error = "Cannot get createGui function from " + lib;
		throw std::runtime_error(error.c_str());
	}
	this->_deleteGui = reinterpret_cast<void (*)(GUI *)>(dlsym(this->_handle, "deleteGui"));
	if (!this->_deleteGui)
	{
		std::string error = "Cannot get deleteGui function from " + lib;
		throw std::runtime_error(error.c_str());
	}
	this->_currentLib = lib;
	this->_gui = this->_createGui();
	return true;
}

GUI *&GuiManager::getGui()
{
	return this->_gui;
}
