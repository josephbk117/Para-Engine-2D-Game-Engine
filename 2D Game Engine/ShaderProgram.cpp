#include "ShaderProgram.h"
#include <vector>


ShaderProgram::ShaderProgram()
{
	programID = 0;
	vertexShaderID = 0;
	fragmentShaderID = 0;
	attributeCount = 0;
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::compileShaders(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0)
		std::cout << "ERROR : Vertex shader creation";
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (vertexShaderID == 0)
		std::cout << "ERROR : Fragment shader creation";
	compileShader(vertexShaderPath, vertexShaderID);
	compileShader(fragmentShaderPath, fragmentShaderID);
}

void ShaderProgram::linkShaders()
{
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);
	//Add error checking
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, (int *)&isLinked);
		std::vector<char> infoLog(maxLength);
		std::cout << &(infoLog[0]);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);
		glDeleteProgram(programID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	else
	{
		std::cout << "\nLinked successfully";
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void ShaderProgram::addAttribute(const std::string & attributeName)
{
	glBindAttribLocation(programID, attributeCount++, attributeName.c_str());
}

void ShaderProgram::use()
{
	glUseProgram(programID);
	for (int i = 0; i < attributeCount; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void ShaderProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < attributeCount; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void ShaderProgram::compileShader(const std::string & filePath, GLuint ID)
{
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail())
	{
		perror(filePath.c_str());
		std::cout << "ERROR : file : " << filePath << " couldnt be loaded";
	}
	std::string fileContents = "";
	std::string line;
	while (std::getline(shaderFile, line))
	{
		fileContents += line + "\n";
	}
	shaderFile.close();
	const char* charPointer = fileContents.c_str();
	glShaderSource(ID, 1, &charPointer, nullptr);
	glCompileShader(ID);

	GLint success = 0;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(ID, maxLength, &maxLength, &errorLog[0]);

		std::cout << filePath << " failed to compile";
		std::cout << &(errorLog[0]);

		glDeleteShader(ID);
		return;
	}
	else
	{
		std::cout << "Compiled Correctly : " << filePath;
	}
}
