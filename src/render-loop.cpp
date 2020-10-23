#include "nibbler.hpp"

void moveTop(Game &game)
{
	game.snake.moveTop(game.area, game.foods, game.cron);
}

void moveRight(Game &game)
{
	game.snake.moveRight(game.area, game.foods, game.cron);
}

void moveBottom(Game &game)
{
	game.snake.moveBottom(game.area, game.foods, game.cron);
}

void moveLeft(Game &game)
{
	game.snake.moveLeft(game.area, game.foods, game.cron);
}

void moveForward(Game &game)
{
	game.snake.moveForward(game.area, game.foods, game.cron);
}

void loop(Game &game, GUI &gui)
{
	std::unordered_map<Input, void (*)(Game & game)> fMap = {
		{ Input::UP, moveTop }, { Input::RIGHT, moveRight }, { Input::DOWN, moveBottom }, { Input::LEFT, moveLeft }
	};

	Input       input;
	std::string pause;

	gui.init(game);
	gui.render(game);
	while ((input = gui.getInput()) != Input::EXIT)
	{
		auto time1 = std::chrono::high_resolution_clock::now();
		if (fMap.count(input))
			fMap[input](game);
		else
			moveForward(game);
		game.cron.checkEvents();
		gui.render(game);
		auto time2 = std::chrono::high_resolution_clock::now();

		int64_t timeElapsed = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
		if (timeElapsed < 0)
			timeElapsed = 0;
		std::chrono::milliseconds max(200);
		std::this_thread::sleep_for(std::chrono::microseconds(max) - std::chrono::microseconds(timeElapsed));
	}
}
