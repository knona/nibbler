#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Shader.hpp"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <string>
#include <utility>
#include <vector>

class Program
{
	private:
	GLuint              _id;
	std::vector<Shader> _shaders;

	void checkShaderLinkSuccess() const;
	Program(const Program &) = delete;
	Program &operator=(const Program &) = delete;
	GLint    getUniformLocation(const std::string &uniformName) const;

	public:
	Program();
	Program(GLuint id);
	Program(Program &&);
	Program &operator=(Program &&);
	~Program();

	void   attach() const;
	void   link() const;
	void   use() const;
	void   addShader(Shader &&shader);
	void   setId();
	GLuint getId() const;

	void uniformSet(const std::string &uniformName, bool v0) const;
	void uniformSet(const std::string &uniformName, float v0) const;
	void uniformSet(const std::string &uniformName, float v0, float v1) const;
	void uniformSet(const std::string &uniformName, float v0, float v1, float v2) const;
	void uniformSet(const std::string &uniformName, float v0, float v1, float v2, float v3) const;
	void uniformSet(const std::string &uniformName, int v0) const;
	void uniformSet(const std::string &uniformName, int v0, int v1) const;
	void uniformSet(const std::string &uniformName, int v0, int v1, int v2) const;
	void uniformSet(const std::string &uniformName, int v0, int v1, int v2, int v3) const;
	void uniformSet(const std::string &uniformName, uint v0) const;
	void uniformSet(const std::string &uniformName, uint v0, uint v1) const;
	void uniformSet(const std::string &uniformName, uint v0, uint v1, uint v2) const;
	void uniformSet(const std::string &uniformName, uint v0, uint v1, uint v2, uint v3) const;
	void uniformSet(const std::string &uniformName, const glm::mat2 &mat, bool transpose = false) const;
	void uniformSet(const std::string &uniformName, const glm::mat3 &mat, bool transpose = false) const;
	void uniformSet(const std::string &uniformName, const glm::mat4 &mat, bool transpose = false) const;

	void uniformSet(const std::string &uniformName, int vecSize, int nbVec, const float *arr) const;
	void uniformSet(const std::string &uniformName, int vecSize, int nbVec, const int *arr) const;
	void uniformSet(const std::string &uniformName, int vecSize, int nbVec, const uint *arr) const;
	void uniformSet(const std::string &uniformName, int matSize, int nbMat, const float *arr, bool transpose) const;
};

#endif // !PROGRAM_HPP
