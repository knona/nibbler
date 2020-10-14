#include "Gl.hpp"

Gl::Gl() : _win(nullptr) {}

Gl::~Gl()
{
	_win = nullptr;
	this->close();
}

void Gl::init(Game &game)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
}

void Gl::close()
{
	glfwTerminate();
}

Input Gl::getInput()
{
	if (glfwWindowShouldClose(_win))
		return Input::EXIT;
	return Input::NONE;
}

void Gl::render(Game &game)
{
	(void)game;
}

void Gl::errorCb(int err, const char *description)
{
	std::string error = "Code ";
	error += std::to_string(err);
	error += " , ";
	error += description;
	throw std::runtime_error(error);
}

void Gl::keyEventHandler(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	// if (action == GLFW_PRESS)
	// {
	// 	switch (key)
	// 	{
	// 	case GLFW_KEY_UP:
	// 	case GLFW_KEY_W:
	// 		Gl::_lastInput = Input::UP;
	// 		break;
	// 	case GLFW_KEY_RIGHT:
	// 	case GLFW_KEY_D:
	// 		Gl::_lastInput = Input::RIGHT;
	// 		break;
	// 	case GLFW_KEY_DOWN:
	// 	case GLFW_KEY_S:
	// 		Gl::_lastInput = Input::DOWN;
	// 		break;
	// 	case GLFW_KEY_LEFT:
	// 	case GLFW_KEY_A:
	// 		Gl::_lastInput = Input::LEFT;
	// 		break;
	// 	case GLFW_KEY_ESCAPE:
	// 		Gl::_lastInput = Input::EXIT;
	// 		break;
	// 	default:
	// 		Gl::_lastInput = Input::NONE;
	// 		break;
	// 	}
	// }
}
