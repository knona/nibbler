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
	void drawCell(const Position &pos, Texture texture, std::optional<float> rotation = {}) const;
	void getSnakeTexture(const Snake &snake, std::list<Position>::const_iterator it, Texture &outTexture,
	                     float &outRotation) const;

	bool isTextureBody(const Position &prevPos, const Position &pos, const Position &nextPos) const;
	bool isTextureCornerBL(const Position &prevPos, const Position &pos, const Position &nextPos) const;
	bool isTextureCornerBR(const Position &prevPos, const Position &pos, const Position &nextPos) const;
	bool isTextureCornerTL(const Position &prevPos, const Position &pos, const Position &nextPos) const;
	bool isTextureCornerTR(const Position &prevPos, const Position &pos, const Position &nextPos) const;

	public:
	Gl();
	~Gl();

	void  init(Game &game);
	void  close();
	Input getInput();
	void  render(Game &game);
};

#endif // !GL_HPP
