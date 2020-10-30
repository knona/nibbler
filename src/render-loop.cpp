#include "nibbler.hpp"

std::unordered_map<Input, void (*)(Game &game)> getInputMap()
{
	std::unordered_map<Input, void (*)(Game & game)> inputMap = {
		{ Input::UP, [](Game &game) { game.snake.moveTop(game.area, game.foods, game.cron); } },
		{ Input::RIGHT, [](Game &game) { game.snake.moveRight(game.area, game.foods, game.cron); } },
		{ Input::DOWN, [](Game &game) { game.snake.moveBottom(game.area, game.foods, game.cron); } },
		{ Input::LEFT, [](Game &game) { game.snake.moveLeft(game.area, game.foods, game.cron); } }
	};
	return inputMap;
}

void loop(Game &game, GUI &gui, const Options &options)
{
	std::unordered_map<Input, void (*)(Game & game)> inputMap = getInputMap();
	Input                                            input;
	std::string                                      pause;

	gui.init(game);
	gui.render(game);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	while ((input = gui.getInput()) != Input::EXIT)
	{
		auto time1 = std::chrono::high_resolution_clock::now();
		if (inputMap.count(input))
			inputMap[input](game);
		else
			game.snake.moveForward(game.area, game.foods, game.cron);
		game.cron.checkEvents();
		gui.render(game);
		auto time2 = std::chrono::high_resolution_clock::now();

		std::chrono::microseconds timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1);
		std::chrono::microseconds timeToSleep = std::chrono::microseconds(options.cycleTime) - timeElapsed;
		if (timeToSleep.count() < 0)
			timeToSleep = std::chrono::microseconds(0);
		std::this_thread::sleep_for(timeToSleep);
	}
}
