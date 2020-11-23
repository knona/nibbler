#ifndef GAME_HPP
#define GAME_HPP

#include "GUI.hpp"
#include "GameData.hpp"
#include "GuiManager.hpp"
#include "Input.hpp"
#include "Options.hpp"
#include "Parser.hpp"
#include "Size.tpp"

#include <dlfcn.h>
#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>

typedef std::unordered_map<Input, void (*)(GameData &gData)> InputMap;
typedef std::chrono::milliseconds                            millisec;
typedef std::chrono::microseconds                            microsec;
typedef std::chrono::_V2::system_clock::time_point           timePoint;
class Game
{
	private:
	Options         _options;
	GameData        _gData;
	static InputMap _inputMap;

	Game() = delete;
	Game(const Game &) = delete;
	Game &operator=(const Game &) = delete;

	void        loop();
	void        addWalls(GameData &gData);
	void        sleep(timePoint time1, timePoint time2) const;
	bool        isLibInput(const Input &input) const;
	std::string getLibPath(const Input &input) const;
	std::string getLibPath(const std::string &libName) const;

	public:
	Game(const Options &options);
	void start();
	~Game();
};

#endif // !GAME_HPP
