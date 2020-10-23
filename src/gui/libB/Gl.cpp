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
	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		throw std::runtime_error("Failed to initialize GLAD");

	glViewport(0, 0, 1280, 720);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	_program.setId();
	_program.addShader({ GL_VERTEX_SHADER, "src/gui/libB/shaders/vertex/shader.vert" });
	_program.addShader({ GL_FRAGMENT_SHADER, "src/gui/libB/shaders/fragment/shader.frag" });
	_program.link();

	float vertices[] = {
		// positions  // colors
		00.0f, 30.0f, 1.0f, 0.0f, 0.0f, // top left
		00.0f, 00.0f, 1.0f, 0.0f, 0.0f, // bottom left
		30.0f, 30.0f, 1.0f, 0.0f, 0.0f, // top right
		30.0f, 00.0f, 1.0f, 0.0f, 0.0f  // bottom right
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	_program.use();
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
	std::unordered_map<int, Input> map = {
		{ GLFW_KEY_ESCAPE, Input::EXIT },                               // EXIT
		{ GLFW_KEY_UP, Input::UP },       { GLFW_KEY_W, Input::UP },    // UP
		{ GLFW_KEY_RIGHT, Input::RIGHT }, { GLFW_KEY_D, Input::RIGHT }, // RIGHT
		{ GLFW_KEY_DOWN, Input::DOWN },   { GLFW_KEY_S, Input::DOWN },  // DOWN
		{ GLFW_KEY_LEFT, Input::LEFT },   { GLFW_KEY_A, Input::LEFT },  // LEFT
	};

	if (glfwWindowShouldClose(_window))
		return Input::EXIT;

	for (std::pair<const int, Input> &pair: map)
		if (glfwGetKey(_window, pair.first) == GLFW_PRESS)
			return pair.second;

	return Input::NONE;
}

void Gl::render(Game &game)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(_VAO);

	glm::mat4 model = glm::mat4(1.0f);

	glm::mat4 view = glm::mat4(1.0f);
	// view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	// _program.uniformSet("view", view);

	glm::mat4 projection;
	projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.0f, 10.0f);

	glm::mat4 transform = projection * view * model;
	_program.uniformSet("transform", transform);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glfwSwapBuffers(_window);
	glfwWaitEventsTimeout(0);
}

void Gl::errorCb(int err, const char *description)
{
	std::string error = "Code ";
	error += std::to_string(err);
	error += " , ";
	error += description;
	throw std::runtime_error(error);
}
