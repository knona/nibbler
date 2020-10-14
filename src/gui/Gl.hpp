#ifndef GL_HPP
#define GL_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GUI.hpp"
#include "Game.hpp"
#include "Input.hpp"

#include <exception>
#include <clocale>

class Gl : public GUI
{
private:
	GLFWwindow *_win;

	Gl(const Gl &) = delete;
	Gl &operator=(const Gl &) = delete;
	static void errorCb(int error, const char *description);
	static void keyEventHandler(GLFWwindow *window, int key, int scancode, int action, int mods);

public:
	Gl();
	~Gl();

	void init(Game &game);
	void close();
	Input getInput();
	void render(Game &game);
};

#endif // !GL_HPP
