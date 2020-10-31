#ifndef GL_HPP
#define GL_HPP

#include "GUI.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "glad/glad.h"

#include <SDL2/SDL.h>
#include <clocale>
#include <exception>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <optional>

class Gl: public GUI
{
	private:
	SDL_Window *_window;
	GLuint      _EBO;
	GLuint      _VAO;
	GLuint      _VBO;
	GLuint      _textures[9];
	Program     _program;
	Size<float> _screen;
	float       _cellSize;

	Gl(const Gl &) = delete;
	Gl &operator=(const Gl &) = delete;

	void setTexture(GLuint &texture, const char *path, bool flipY, bool rgba) const;
	void drawCell(const Position &pos, int textureIndex, std::optional<float> rotation = {}) const;

	public:
	Gl();
	~Gl();

	void  init(Game &game);
	void  close();
	Input getInput();
	void  render(Game &game);
};

#endif // !GL_HPP
