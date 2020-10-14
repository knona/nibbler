#include "Shader.hpp"

// Shader::Shader() {}

Shader::Shader(const GLenum shaderType, const char *shaderPath)
{
	std::unordered_map<GLenum, const char *> map = {{GL_VERTEX_SHADER, "Vertex"}, {GL_FRAGMENT_SHADER, "Fragment"}};

	this->_id = glCreateShader(shaderType);
	this->_shaderType = shaderType;
	this->_shaderName = map[shaderType];
	this->_shaderCode = readShaderCode(shaderPath);
	this->compile();
}

Shader::Shader(Shader &&shader)
{
	*this = std::move(shader);
}

Shader::~Shader()
{
	this->clear();
}

Shader &Shader::operator=(Shader &&shader)
{
	if (&shader != this)
	{
		this->_id = shader._id;
		this->_shaderCode = std::move(shader._shaderCode);
		this->_shaderName = std::move(shader._shaderName);
		this->_shaderType = shader._shaderType;
		shader._id = 0;
	}
	return *this;
}

void Shader::clear()
{
	if (this->_id != 0)
	{
		glDeleteShader(this->_id);
		this->_id = 0;
	}
}

const GLuint &Shader::getId() const
{
	return this->_id;
}

std::vector<std::unique_ptr<char[]>> Shader::readShaderCode(const char *path) const
{
	std::ifstream file(path);
	std::vector<std::unique_ptr<char[]>> shaderCode;

	if (!file)
		throw std::runtime_error(std::string("Cannot open file: ") + path);
	shaderCode.push_back(std::make_unique<char[]>(BUFFER_SIZE));
	while (file.read(shaderCode.back().get(), BUFFER_SIZE - 1))
	{
		shaderCode.back()[file.gcount()] = '\0';
		shaderCode.push_back(std::make_unique<char[]>(BUFFER_SIZE));
	}
	shaderCode.back()[file.gcount()] = '\0';
	return shaderCode;
}

void Shader::compile() const
{
	std::vector<const char *> data(this->_shaderCode.size());
	for (size_t i = 0; i < this->_shaderCode.size(); i++)
		data[i] = this->_shaderCode[i].get();

	glShaderSource(this->_id, this->_shaderCode.size(), data.data(), NULL);
	glCompileShader(this->_id);
	checkShaderCompilationSuccess();
}

void Shader::checkShaderCompilationSuccess() const
{
	int success;

	glGetShaderiv(this->_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		int length;
		glGetShaderiv(this->_id, GL_INFO_LOG_LENGTH, &length);
		std::unique_ptr<char[]> infoLog = std::make_unique<char[]>(length);
		glGetShaderInfoLog(this->_id, length, NULL, infoLog.get());
		throw std::runtime_error(this->_shaderName + " Shader: Compilation failed: " + infoLog.get());
	}
}
