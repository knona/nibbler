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
	GLuint      _EBO[3];
	GLuint      _VAO[3];
	GLuint      _VBO[3];
	GLuint      _textures[9];
	Program     _program;
	Program     _headerProgram;
	Size<float> _screen;
	float       _cellSize;
	TTF_Font *  _font;

	Gl(const Gl &) = delete;
	Gl &operator=(const Gl &) = delete;

	void createWindow(GameData &gData);
	void createCellVAO();
	void createTextVAO(float width, float height);
	void createHeaderVAO();

	void setTexture(GLuint &texture, const char *path, bool flipY, bool rgba);
	void setTextures();
	void getSnakeTexture(const Snake &snake, std::list<Position>::const_iterator it, Texture &outTexture,
	                     float &outRotation) const;

	void drawCell(const Position &pos, Texture texture, std::optional<float> rotation = {}) const;
	void drawText(int score);

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
