#include "Sprite.h"
#include <GL\glew.h>
#include <iostream>

Sprite::Sprite()
{
	vboID = 0;
}

Sprite::~Sprite()
{
	if (vboID != 0)
		glDeleteBuffers(1, &vboID);
}

void Sprite::init(const float& width, const float& height)
{
	this->width = width;
	this->height = height;
	if (vboID == 0)
		glGenBuffers(1, &vboID);
	setUpSpriteDimensions(width, height);
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 1);
}

void Sprite::setTextureID(const unsigned int& textureID)
{
	this->textureID = textureID;
}

unsigned int Sprite::getTextureID() const
{
	return textureID;
}

glm::vec2 Sprite::getDimensions() const
{
	return glm::vec2(width, height);
}

void Sprite::setDimension(glm::vec2 newDimension)
{
	setUpSpriteDimensions(newDimension.x, newDimension.y);
}

void Sprite::setUpSpriteDimensions(float width, float height)
{
	float vertexData[24];

	vertexData[0] = width * 0.5f;
	vertexData[1] = height * 0.5f;

	vertexData[2] = 1.0f;
	vertexData[3] = 1.0f;

	vertexData[4] = -width * 0.5f;
	vertexData[5] = height * 0.5f;

	vertexData[6] = 0.0f;
	vertexData[7] = 1.0f;

	vertexData[8] = -width * 0.5f;
	vertexData[9] = -height * 0.5f;

	vertexData[10] = 0.0f;
	vertexData[11] = 0.0f;

	vertexData[12] = -width * 0.5f;
	vertexData[13] = -height * 0.5f;

	vertexData[14] = 0.0f;
	vertexData[15] = 0.0f;

	vertexData[16] = width * 0.5f;
	vertexData[17] = -height * 0.5f;

	vertexData[18] = 1.0f;
	vertexData[19] = 0;

	vertexData[20] = width * 0.5f;
	vertexData[21] = height * 0.5f;

	vertexData[22] = 1.0f;
	vertexData[23] = 1.0f;

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
