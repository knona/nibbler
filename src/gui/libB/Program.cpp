#include "Program.hpp"

Program::Program(): _id(0)
{}

Program::Program(Program &&program)
{
	*this = std::move(program);
}

Program &Program::operator=(Program &&program)
{
	if (this != &program)
	{
		this->_id = program._id;
		this->_shaders = std::move(program._shaders);
	}
	return *this;
}

Program::~Program()
{
	if (this->_id != 0)
		glDeleteProgram(this->_id);
}

void Program::use() const
{
	glUseProgram(this->_id);
}

void Program::attach() const
{
	for (const Shader &shader: this->_shaders)
		glAttachShader(this->_id, shader.getId());
}

void Program::link() const
{
	this->attach();
	glLinkProgram(this->_id);
	this->checkShaderLinkSuccess();
}

void Program::addShader(Shader &&shader)
{
	this->_shaders.push_back(std::move(shader));
}

GLuint Program::getId() const
{
	return this->_id;
}

void Program::setId()
{
	this->_id = glCreateProgram();
}

GLint Program::getUniformLocation(const std::string &uniformName) const
{
	GLint location = glGetUniformLocation(this->_id, uniformName.c_str());
	if (location == -1)
		throw std::runtime_error(std::string("Location ") + uniformName + " cannot be found");
	return location;
}

void Program::uniformSet(const std::string &uniformName, bool v0) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform1i(location, static_cast<int>(v0));
}

void Program::uniformSet(const std::string &uniformName, float v0) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform1f(location, v0);
}

void Program::uniformSet(const std::string &uniformName, float v0, float v1) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform2f(location, v0, v1);
}

void Program::uniformSet(const std::string &uniformName, float v0, float v1, float v2) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform3f(location, v0, v1, v2);
}

void Program::uniformSet(const std::string &uniformName, float v0, float v1, float v2, float v3) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform4f(location, v0, v1, v2, v3);
}

void Program::uniformSet(const std::string &uniformName, int v0) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform1i(location, v0);
}

void Program::uniformSet(const std::string &uniformName, int v0, int v1) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform2i(location, v0, v1);
}

void Program::uniformSet(const std::string &uniformName, int v0, int v1, int v2) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform3i(location, v0, v1, v2);
}

void Program::uniformSet(const std::string &uniformName, int v0, int v1, int v2, int v3) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform4i(location, v0, v1, v2, v3);
}

void Program::uniformSet(const std::string &uniformName, uint v0) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform1ui(location, v0);
}

void Program::uniformSet(const std::string &uniformName, uint v0, uint v1) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform2ui(location, v0, v1);
}

void Program::uniformSet(const std::string &uniformName, uint v0, uint v1, uint v2) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform3ui(location, v0, v1, v2);
}

void Program::uniformSet(const std::string &uniformName, uint v0, uint v1, uint v2, uint v3) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniform4ui(location, v0, v1, v2, v3);
}

void Program::uniformSet(const std::string &uniformName, int vecSize, int nbVec, const float *arr) const
{
	void (*fMap[4])(GLint, GLsizei, const GLfloat *value) = { glUniform1fv, glUniform2fv, glUniform3fv, glUniform4fv };

	if (vecSize < 1 || vecSize > 4)
		throw std::runtime_error("Invalid vector size");
	GLint location = this->getUniformLocation(uniformName);
	fMap[vecSize - 1](location, nbVec, arr);
}

void Program::uniformSet(const std::string &uniformName, int vecSize, int nbVec, const int *arr) const
{
	void (*fMap[4])(GLint, GLsizei, const GLint *value) = { glUniform1iv, glUniform2iv, glUniform3iv, glUniform4iv };

	if (vecSize < 1 || vecSize > 4)
		throw std::runtime_error("Invalid vector size");
	GLint location = this->getUniformLocation(uniformName);
	fMap[vecSize - 1](location, nbVec, arr);
}

void Program::uniformSet(const std::string &uniformName, int vecSize, int nbVec, const uint *arr) const
{
	void (*fMap[4])(GLint, GLsizei, const GLuint *value) = { glUniform1uiv, glUniform2uiv, glUniform3uiv,
		                                                     glUniform4uiv };

	if (vecSize < 1 || vecSize > 4)
		throw std::runtime_error("Invalid vector size");
	GLint location = this->getUniformLocation(uniformName);
	fMap[vecSize - 1](location, nbVec, arr);
}

void Program::uniformSet(const std::string &uniformName, const glm::mat2 &mat, bool transpose) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniformMatrix2fv(location, 1, transpose, glm::value_ptr(mat));
}

void Program::uniformSet(const std::string &uniformName, const glm::mat3 &mat, bool transpose) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniformMatrix3fv(location, 1, transpose, glm::value_ptr(mat));
}

void Program::uniformSet(const std::string &uniformName, const glm::mat4 &mat, bool transpose) const
{
	GLint location = this->getUniformLocation(uniformName);
	glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(mat));
}

void Program::uniformSet(const std::string &uniformName, int matSize, int nbMat, const float *arr, bool transpose) const
{
	void (*fMap[4])(GLint, GLsizei, GLboolean, const GLfloat *value) = { glUniformMatrix2fv, glUniformMatrix3fv,
		                                                                 glUniformMatrix4fv };

	if (matSize < 2 || matSize > 4)
		throw std::runtime_error("Invalid matrix size");
	GLint location = this->getUniformLocation(uniformName);
	fMap[matSize - 1](location, nbMat, transpose, arr);
}

void Program::checkShaderLinkSuccess() const
{
	int success;

	glGetProgramiv(this->_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		int length = 0;
		glGetProgramiv(this->_id, GL_INFO_LOG_LENGTH, &length);
		std::unique_ptr<char[]> infoLog = std::make_unique<char[]>(length);
		glGetProgramInfoLog(this->_id, length, NULL, infoLog.get());
		throw std::runtime_error(std::string("Shader: Link failed: ") + infoLog.get());
	}
}
