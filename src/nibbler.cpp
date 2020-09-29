#include "nibbler.hpp"
#include "glad/glad.h"
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
	Options options;

	try
	{
		options = parseCommandLine(argc, argv);
	}
	catch (const Exception::ParsingOptions &e)
	{
		int exitStatus = e.getExitStatus();
		if (exitStatus == EXIT_FAILURE)
			std::cerr << "\033[0;31mError: \033[0m" << e.what() << std::endl;
		else
			std::cout << e.what() << std::endl;
		return exitStatus;
	}

	std::cout << options.areaSize << std::endl;
	return EXIT_SUCCESS;
}
