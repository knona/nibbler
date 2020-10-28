#include "Gl.hpp"

Gl::Gl(): _window(nullptr), _EBO(0), _VAO(0), _VBO(0), _screen(1280, 720)
{}

Gl::~Gl()
{
	this->close();
}

void Gl::init(Game &game)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		throw std::runtime_error("Failed to initliaze SDL");

	SDL_GL_LoadLibrary(NULL);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	Size<int> areaSize = game.area.getSize();

	_cellSize = std::min(_screen.width / areaSize.width, _screen.height / areaSize.height);
	if (_cellSize > 40)
		_cellSize = 40;
	_screen.width = areaSize.width * _cellSize;
	_screen.height = areaSize.height * _cellSize;

	_window = SDL_CreateWindow("NIBBLER", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen.width, _screen.height,
	                           SDL_WINDOW_OPENGL);
	if (!_window)
		throw std::runtime_error("Failed to create SDL window");

	SDL_SetWindowResizable(_window, SDL_FALSE);

	SDL_GL_CreateContext(_window);

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		throw std::runtime_error("Failed to initialize GLAD");

	glViewport(0, 0, _screen.width, _screen.height);
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

	glm::mat4 projection =
		glm::ortho(0.0f, static_cast<float>(_screen.width), 0.0f, static_cast<float>(_screen.height), -1.0f, 1.0f);
	_program.uniformSet("projection", projection);
}

void Gl::close()
{
	if (_window)
	{
		SDL_DestroyWindow(_window);
		_window = nullptr;
	}
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
	SDL_Quit();
}

Input Gl::getInput()
{
	SDL_Event event;

	const std::unordered_map<int, Input> map = {
		{ SDL_SCANCODE_ESCAPE, Input::EXIT },                                   // EXIT
		{ SDL_SCANCODE_UP, Input::UP },       { SDL_SCANCODE_W, Input::UP },    // UP
		{ SDL_SCANCODE_RIGHT, Input::RIGHT }, { SDL_SCANCODE_D, Input::RIGHT }, // RIGHT
		{ SDL_SCANCODE_DOWN, Input::DOWN },   { SDL_SCANCODE_S, Input::DOWN },  // DOWN
		{ SDL_SCANCODE_LEFT, Input::LEFT },   { SDL_SCANCODE_A, Input::LEFT },  // LEFT
	};

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return Input::EXIT;
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			for (const std::pair<const int, Input> &pair: map)
				if (event.key.keysym.scancode == pair.first)
					return pair.second;
		}
	}

	return Input::NONE;
}

void Gl::render(Game &game)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(_VAO);

	float xStart = 0;
	float yStart = _screen.height;

	for (int i = 0; i < game.area.getSize().height; i++)
	{
		for (int j = 0; j < game.area.getSize().width; j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(xStart + _cellSize * j, yStart - _cellSize * (i + 1), 0.0f));
			model = glm::scale(model, glm::vec3(_cellSize, _cellSize, 0.0f));
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

	SDL_GL_SwapWindow(_window);
}
