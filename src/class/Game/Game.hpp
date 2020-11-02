#ifndef GAME_HPP
#define GAME_HPP

#include "Debug.hpp"
#include "GUI.hpp"
#include "GameData.hpp"
#include "Gl.hpp"
#include "Input.hpp"
#include "Options.hpp"
#include "Parser.hpp"
#include "Retro.hpp"
#include "Size.tpp"

#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>

typedef std::unordered_map<Input, void (*)(GameData &gData)> InputMap;

class Game
{
	private:
	Options         _options;
	GameData        _gData;
	static InputMap _inputMap;

	Game() = delete;
	Game(const Game &) = delete;
	Game &operator=(const Game &) = delete;

	void loop(GUI &gui);
	void addWalls(GameData &gData);

	public:
	Game(const Options &options);
	void start();
	~Game();
};

#endif // !GAME_HPP