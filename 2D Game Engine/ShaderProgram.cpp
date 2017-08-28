#include "ShaderProgram.h"



ShaderProgram::ShaderProgram()
{
	programID = 0;
	vertexShaderID = 0;
	fragmentShaderID = 0;
}


ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::compileShader(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
{
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0)
		std::cout << "ERROR : Vertex shader creation";
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (vertexShaderID == 0)
		std::cout << "ERROR : Fragment shader creation";

	std::ifstream vertexFile(vertexShaderPath);
	if (vertexFile.fail())
	{
		perror(vertexShaderPath.c_str());
		std::cout << "ERROR : Vertex file couldnt be loaded";
	}
	std::string fileContents = "";
	std::string line;
	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}
	vertexFile.close();
	const char* charPointer = fileContents.c_str();
	glShaderSource(vertexShaderID, 1, &charPointer, nullptr);
	glCompileShader(vertexShaderID);

	GLint success = 0;
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
}

void ShaderProgram::linkShaders()
{
}
