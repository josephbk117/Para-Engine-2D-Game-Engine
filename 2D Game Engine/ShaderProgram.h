#pragma once
#include <string>
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	void compileShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	void linkShaders();
	void addAttribute(const std::string& attributeName);
	void use();
	void unuse();
	int getUniformLocation(const std::string& uniformName)const;
private:
	unsigned int programID, vertexShaderID, fragmentShaderID;
	void compileShader(const std::string& filePath, unsigned int ID);
	int attributeCount;
};

