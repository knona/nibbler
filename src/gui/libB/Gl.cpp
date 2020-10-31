#include "Gl.hpp"

#include "stb_image.h"

void Gl::setTexture(GLuint &texture, const char *path, bool flipY, bool rgba) const
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nbChannels;
	if (flipY)
		stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path, &width, &height, &nbChannels, 0);
	if (!data)
		throw std::runtime_error(std::string("Failed to load texture ") + path);

	int colorBit = rgba ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, colorBit, width, height, 0, colorBit, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
}

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
	glClearColor(0.95, 0.91, 0.89f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_program.setId();
	_program.addShader({ GL_VERTEX_SHADER, "src/gui/libB/shaders/vertex/shader.vert" });
	_program.addShader({ GL_FRAGMENT_SHADER, "src/gui/libB/shaders/fragment/shader.frag" });
	_program.link();

	float square[] = {
		00.0f, 01.0f, 00.0f, 01.0f, // top left
		00.0f, 00.0f, 00.0f, 00.0f, // bottom left
		01.0f, 01.0f, 01.0f, 01.0f, // top right
		01.0f, 00.0f, 01.0f, 00.0f, // bottom right
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

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	this->setTexture(_textures[Texture::HEAD], "src/gui/libB/assets/snake/head.png", true, true);
	this->setTexture(_textures[Texture::BODY], "src/gui/libB/assets/snake/body.png", true, true);
	this->setTexture(_textures[Texture::TAIL], "src/gui/libB/assets/snake/tail.png", true, true);
	this->setTexture(_textures[Texture::CORNER_BL], "src/gui/libB/assets/snake/corner-bl.png", true, true);
	this->setTexture(_textures[Texture::CORNER_BR], "src/gui/libB/assets/snake/corner-br.png", true, true);
	this->setTexture(_textures[Texture::CORNER_TL], "src/gui/libB/assets/snake/corner-tl.png", true, true);
	this->setTexture(_textures[Texture::CORNER_TR], "src/gui/libB/assets/snake/corner-tr.png", true, true);
	this->setTexture(_textures[Texture::FOOD], "src/gui/libB/assets/food.png", true, true);
	this->setTexture(_textures[Texture::WALL], "src/gui/libB/assets/wall.png", false, false);

	_program.use();

	glm::mat4 view = glm::mat4(1.0f);
	_program.uniformSet("view", view);

	glm::mat4 projection = glm::ortho(0.0f, _screen.width, 0.0f, _screen.height, -1.0f, 1.0f);
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

void Gl::drawCell(const Position &pos, Texture texture, std::optional<float> rotation) const
{
	float xStart = 0;
	float yStart = _screen.height;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(xStart + _cellSize * pos.x, yStart - _cellSize * (pos.y + 1), 0.0f));
	model = glm::scale(model, glm::vec3(_cellSize, _cellSize, 0.0f));
	if (rotation)
	{
		model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
		model = glm::rotate(model, rotation.value(), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f, -0.5f, 0.0f));
	}
	_program.uniformSet("model", model);

	glBindTexture(GL_TEXTURE_2D, _textures[texture]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool Gl::isTextureBody(const Position &prevPos, const Position &pos, const Position &nextPos) const
{
	return (prevPos.x + 1 == pos.x && pos.x + 1 == nextPos.x) || (prevPos.x - 1 == pos.x && pos.x - 1 == nextPos.x) ||
	       (prevPos.y + 1 == pos.y && pos.y + 1 == nextPos.y) || (prevPos.y - 1 == pos.y && pos.y - 1 == nextPos.y);
}

bool Gl::isTextureCornerBL(const Position &prevPos, const Position &pos, const Position &nextPos) const
{
	return (prevPos.x + 1 == pos.x && pos.y + 1 == nextPos.y) || (prevPos.y - 1 == pos.y && pos.x - 1 == nextPos.x);
}

bool Gl::isTextureCornerBR(const Position &prevPos, const Position &pos, const Position &nextPos) const
{
	return (prevPos.x - 1 == pos.x && pos.y + 1 == nextPos.y) || (prevPos.y - 1 == pos.y && pos.x + 1 == nextPos.x);
}

bool Gl::isTextureCornerTL(const Position &prevPos, const Position &pos, const Position &nextPos) const
{
	return (prevPos.x + 1 == pos.x && pos.y - 1 == nextPos.y) || (prevPos.y + 1 == pos.y && pos.x - 1 == nextPos.x);
}

bool Gl::isTextureCornerTR(const Position &prevPos, const Position &pos, const Position &nextPos) const
{
	return (prevPos.x - 1 == pos.x && pos.y - 1 == nextPos.y) || (prevPos.y + 1 == pos.y && pos.x + 1 == nextPos.x);
}

void Gl::getSnakeTexture(const Snake &snake, std::list<Position>::const_iterator it, Texture &outTexture,
                         float &outRotation) const
{
	Position pos = *it;

	if (snake.isHead(pos))
	{
		outTexture = Texture::HEAD;
		Direction direction = snake.getDirection();
		if (direction == Direction::Top)
			outRotation = glm::pi<float>();
		if (direction == Direction::Right)
			outRotation = glm::half_pi<float>();
		if (direction == Direction::Left)
			outRotation = glm::three_over_two_pi<float>();
	}
	else
	{
		Position prevPos = *std::prev(it);
		if (snake.isTail(pos))
		{
			outTexture = Texture::TAIL;
			if (prevPos.x + 1 == pos.x)
				outRotation = glm::half_pi<float>();
			if (prevPos.x - 1 == pos.x)
				outRotation = glm::three_over_two_pi<float>();
			if (prevPos.y - 1 == pos.y)
				outRotation = glm::pi<float>();
		}
		else
		{
			Position nextPos = *std::next(it);

			if ((prevPos.x + 1 == pos.x && pos.x + 1 == nextPos.x) ||
			    (prevPos.x - 1 == pos.x && pos.x - 1 == nextPos.x))
				outRotation = glm::half_pi<float>();

			if (this->isTextureCornerBL(prevPos, pos, nextPos))
				outTexture = Texture::CORNER_BL;
			else if (this->isTextureCornerBR(prevPos, pos, nextPos))
				outTexture = Texture::CORNER_BR;
			else if (this->isTextureCornerTL(prevPos, pos, nextPos))
				outTexture = Texture::CORNER_TL;
			else if (this->isTextureCornerTR(prevPos, pos, nextPos))
				outTexture = Texture::CORNER_TR;
		}
	}
}

void Gl::render(Game &game)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(_VAO);
	glActiveTexture(GL_TEXTURE0);

	for (std::pair<const int, Food> &pair: game.foods)
		for (const Position &pos: pair.second.getPositions())
			drawCell(pos, Texture::FOOD);

	for (std::pair<const int, Wall> &pair: game.walls)
		for (const Position &pos: pair.second.getPositions())
			drawCell(pos, Texture::WALL);

	const std::list<Position> &positions = game.snake.getPositions();
	for (std::list<Position>::const_iterator it = positions.cbegin(); it != positions.cend(); it++)
	{
		float   rotation = glm::two_pi<float>();
		Texture texture = Texture::BODY;

		getSnakeTexture(game.snake, it, texture, rotation);
		drawCell(*it, texture, rotation);
	}

	glBindVertexArray(0);
	SDL_GL_SwapWindow(_window);
}
