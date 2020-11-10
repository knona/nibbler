#ifndef GUI_SDL_HPP
#define GUI_SDL_HPP

#include "GUI.hpp"
#include "GameData.hpp"
#include "Input.hpp"
#include "Program.hpp"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Texture.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <clocale>
#include <exception>
#include <functional>

namespace ph = std::placeholders;

class GuiSdl: public GUI
{
	private:
	SDL_Window *  _window;
	SDL_GLContext _context;
	GLuint        _VAO[3];
	GLuint        _VBO[3];
	GLuint        _EBO[3];
	GLuint        _textures[9];
	Program       _program;
	Program       _headerProgram;
	Size<float>   _screen;
	float         _cellSize;
	TTF_Font *    _font;

	GuiSdl(const GuiSdl &) = delete;
	GuiSdl &operator=(const GuiSdl &) = delete;

	void createWindow(GameData &gData);
	void createCellVAO();
	void createTextVAO(float width, float height);
	void createHeaderVAO();
	void createPrograms();

	void setTexture(GLuint &texture, const char *path, bool flipY, bool rgba);
	void setTextures();
	void getSnakeTexture(const Snake &snake, std::list<Position>::const_iterator it, Texture &outTexture,
	                     float &outRotation) const;

	void drawCell(const Position &pos, Texture texture, std::optional<float> rotation = {}) const;
	void drawText(const std::string &text, SDL_Color textColor, std::function<void(float, float)> setPosition);
	void setPositionScore(float textW, float);
	void setPositionPause(float textW, float textH);

	bool isTextureBody(const Position &prevPos, const Position &pos, const Position &nextPos) const;
	bool isTextureCornerBL(const Position &prevPos, const Position &pos, const Position &nextPos) const;
	bool isTextureCornerBR(const Position &prevPos, const Position &pos, const Position &nextPos) const;
	bool isTextureCornerTL(const Position &prevPos, const Position &pos, const Position &nextPos) const;
	bool isTextureCornerTR(const Position &prevPos, const Position &pos, const Position &nextPos) const;

	public:
	GuiSdl();
	~GuiSdl();

	void  init(GameData &gData);
	void  close();
	Input getInput();
	void  render(GameData &gData);
};

extern "C"
{
	GUI *createGui();
	void deleteGui(GUI *gui);
}

#endif // !GUI_SDL_HPP
