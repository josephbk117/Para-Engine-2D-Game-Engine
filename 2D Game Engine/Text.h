#pragma once
#include "Component.h"
#include "stb_truetype.h"
#include "Transform.h"
#include "GL\glew.h"

class Text : public Component
{
public:
	Text();
	~Text();
	std::string text = "";
	void init(const std::string& fontFilePath);
	virtual void start();
	virtual void update();
private:
	GLuint ftex;
	stbtt_bakedchar cdata[96];
	Transform* transform;
	void printText(float x, float y);
};

