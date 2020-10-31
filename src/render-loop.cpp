#include "nibbler.hpp"

std::unordered_map<Input, void (*)(GameData &gData)> getInputMap()
{
	std::unordered_map<Input, void (*)(GameData & gData)> inputMap = {
		{ Input::UP, [](GameData &gData) { gData.snake.moveTop(gData); } },
		{ Input::RIGHT, [](GameData &gData) { gData.snake.moveRight(gData); } },
		{ Input::DOWN, [](GameData &gData) { gData.snake.moveBottom(gData); } },
		{ Input::LEFT, [](GameData &gData) { gData.snake.moveLeft(gData); } }
	};
	return inputMap;
}

void loop(GameData &gData, GUI &gui, const Options &options)
{
	std::unordered_map<Input, void (*)(GameData & gData)> inputMap = getInputMap();
	Input                                                 input;
	std::string                                           pause;

	gui.init(gData);
	gui.render(gData);
	std::this_thread::sleep_for(options.cycleTime * 2);
	while ((input = gui.getInput()) != Input::EXIT)
	{
		auto time1 = std::chrono::high_resolution_clock::now();
		if (inputMap.count(input))
			inputMap[input](gData);
		else
			gData.snake.moveForward(gData);
		gData.cron.checkEvents();
		gui.render(gData);
		auto time2 = std::chrono::high_resolution_clock::now();

		std::chrono::microseconds timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1);
		std::chrono::microseconds timeToSleep = std::chrono::microseconds(options.cycleTime) - timeElapsed;
		if (timeToSleep.count() < 0)
			timeToSleep = std::chrono::microseconds(0);
		std::this_thread::sleep_for(timeToSleep);
	}
}
