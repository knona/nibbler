#include "nibbler.hpp"
#include "GLFW/glfw3.h"

void displayError(int errorCode, const char *error)
{
	std::cout << "Error code: " << errorCode << std::endl;
	std::cout << error << std::endl;
}

int testOpengl()
{
	glfwSetErrorCallback(displayError);

	GLFWwindow *window;

	/* Initialize the library */
	if (!glfwInit())
	{
		std::cerr << "Init failed" << std::endl;
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cerr << "Window creation failed" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

int main(int argc, const char *argv[])
{
	Options options = parseCommandLine(argc, argv);

	return testOpengl();
	// std::cout << "width: " << options.areaSize.width << ", height: " << options.areaSize.height << std::endl;
	// return 0;
}
