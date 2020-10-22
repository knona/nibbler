#include "Gl.hpp"

Gl::Gl(): _window(nullptr)
{}

Gl::~Gl()
{
	_window = nullptr;
	this->close();
}

void Gl::init(Game &game)
{
	if (!glfwInit())
		throw std::runtime_error("Failed to initliaze GLFW");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	_window = glfwCreateWindow(1280, 720, "NIBBLER", NULL, NULL);
	if (!_window)
		throw std::runtime_error("Failed to create GLFW window");

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw std::runtime_error("Failed to initialize GLAD");

	glViewport(0, 0, 1280, 720);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Gl::close()
{
	glfwTerminate();
}

Input Gl::getInput()
{
	if (glfwWindowShouldClose(_window))
		return Input::EXIT;
	return Input::NONE;
}

void Gl::render(Game &game)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(_window);
}

void Gl::errorCb(int err, const char *description)
{
	std::string error = "Code ";
	error += std::to_string(err);
	error += " , ";
	error += description;
	throw std::runtime_error(error);
}

void keyEventHandler(GLFWwindow *window, int key, int scancode, int action, int mods)
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
