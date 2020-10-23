#include "Gl.hpp"

Gl::Gl(): _window(nullptr), _EBO(0), _VAO(0), _VBO(0)
{}

Gl::~Gl()
{
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

	// glfwSetInputMode(_window, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GLFW_FALSE);
	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw std::runtime_error("Failed to initialize GLAD");

	glViewport(0, 0, 1280, 720);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	_program.setId();
	_program.addShader({ GL_VERTEX_SHADER, "src/gui/libB/shaders/vertex/shader.vert" });
	_program.addShader({ GL_FRAGMENT_SHADER, "src/gui/libB/shaders/fragment/shader.frag" });
	_program.link();

	float square[] = {
		00.0f, 01.0f, // top left
		00.0f, 00.0f, // bottom left
		01.0f, 01.0f, // top right
		01.0f, 00.0f, // bottom right
	};

	uint indices[] = {
		0, 1, 2, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<void *>(0));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	_program.use();

	glm::mat4 view = glm::mat4(1.0f);
	_program.uniformSet("view", view);

	glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
	_program.uniformSet("projection", projection);
}

void Gl::close()
{
	_window = nullptr;
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
	glfwTerminate();
}

Input Gl::getInput()
{
	const std::unordered_map<int, Input> map = {
		{ GLFW_KEY_ESCAPE, Input::EXIT },                               // EXIT
		{ GLFW_KEY_UP, Input::UP },       { GLFW_KEY_W, Input::UP },    // UP
		{ GLFW_KEY_RIGHT, Input::RIGHT }, { GLFW_KEY_D, Input::RIGHT }, // RIGHT
		{ GLFW_KEY_DOWN, Input::DOWN },   { GLFW_KEY_S, Input::DOWN },  // DOWN
		{ GLFW_KEY_LEFT, Input::LEFT },   { GLFW_KEY_A, Input::LEFT },  // LEFT
	};

	if (glfwWindowShouldClose(_window))
		return Input::EXIT;

	for (const std::pair<const int, Input> &pair: map)
		if (glfwGetKey(_window, pair.first) == GLFW_PRESS)
			return pair.second;

	return Input::NONE;
}

void Gl::render(Game &game)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(_VAO);

	float cellSize = 30.0f;
	float xStart = 50.0f;
	float yStart = 720.0f - 50.0f;

	for (int i = 0; i < game.area.getSize().height; i++)
	{
		for (int j = 0; j < game.area.getSize().width; j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(xStart + cellSize * j, yStart - cellSize * i, 0.0f));
			model = glm::scale(model, glm::vec3(cellSize, cellSize, 0.0f));
			_program.uniformSet("model", model);

			Position  pos(j, i);
			glm::vec3 color(1.0f, 1.0f, 1.0f);

			if (game.area.isWall(pos))
				color = glm::vec3(0.46f, 0.33f, 0.0f);
			else if (game.area.isFood(pos))
				color = glm::vec3(0.61f, 0.62f, 1.0f);
			else if (game.area.isSnake(pos))
				color = game.snake.isHead(pos) ? glm::vec3(0.83f, 1.0f, 0.0f) : glm::vec3(0.06f, 1.0f, 0.16f);

			_program.uniformSet("color", color.x, color.y, color.z);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
	glBindVertexArray(0);

	// glfwWaitEventsTimeout(0);
	glfwPollEvents();
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
