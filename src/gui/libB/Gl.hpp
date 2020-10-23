#ifndef GL_HPP
#define GL_HPP

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "GUI.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "Program.hpp"
#include "glad/glad.h"

#include <clocale>
#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

class Gl: public GUI
{
	private:
	GLFWwindow *_window;
	GLuint      _EBO;
	GLuint      _VAO;
	GLuint      _VBO;
	Program     _program;

	Gl(const Gl &) = delete;
	Gl &        operator=(const Gl &) = delete;
	static void errorCb(int error, const char *description);

	public:
	Gl();
	~Gl();

	void  init(Game &game);
	void  close();
	Input getInput();
	void  render(Game &game);
};

#endif // !GL_HPP
