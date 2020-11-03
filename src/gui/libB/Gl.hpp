#ifndef GL_HPP
#define GL_HPP

#include "GUI.hpp"
#include "GameData.hpp"
#include "Input.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "glad/glad.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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

	void RenderText(const std::string &Text, unsigned char r, unsigned char g, unsigned char b);

	void createWindow(GameData &gData);
	void createVAO();

	void setTexture(GLuint &texture, const char *path, bool flipY, bool rgba);
	void setTextures();
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

	void  init(GameData &gData);
	void  close();
	Input getInput();
	void  render(GameData &gData);
};

#endif // !GL_HPP
