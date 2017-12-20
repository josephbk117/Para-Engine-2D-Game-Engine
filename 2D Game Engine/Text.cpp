#include <iostream>
#include "Text.h"
Text::Text() {}
Text::~Text() {}

void Text::init(const std::string & fontFilePath)
{
	unsigned char* ttf_buffer = new unsigned char[600000];
	unsigned char temp_bitmap[512 * 512];
	fread(ttf_buffer, 1, 600000, fopen(fontFilePath.c_str(), "rb"));
	stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits!
																					 // can free ttf_buffer at this point
	delete[] ttf_buffer;
	glGenTextures(1, &ftex);
	glBindTexture(GL_TEXTURE_2D, ftex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Text::start()
{
	transform = attachedGameObject->getComponent<Transform>();
}

void Text::update()
{
	glm::vec2 position = transform->getPosition();
	printText(position.x, position.y);
}