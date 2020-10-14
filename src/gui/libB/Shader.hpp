#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <exception>
#include <utility>
#include <memory>
#include <unordered_map>

#define BUFFER_SIZE 1000

class Shader
{
private:
	GLuint _id;
	GLenum _shaderType;
	std::vector<std::unique_ptr<char[]>> _shaderCode;
	std::string _shaderName;

	std::vector<std::unique_ptr<char[]>> readShaderCode(const char *) const;
	void checkShaderCompilationSuccess() const;

	Shader() = delete;
	Shader(const Shader &) = delete;
	Shader &operator=(const Shader &) = delete;

public:
	Shader(const GLenum shaderType, const char *shaderPath);
	Shader(Shader &&);
	virtual ~Shader();
	Shader &operator=(Shader &&);

	const GLuint &getId() const;
	void clear();
	void compile() const;
};

#endif // !SHADER_HPP
