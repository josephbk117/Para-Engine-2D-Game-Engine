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

void Text::printText(float x, float y)
{
	// assume orthographic projection with units = screen pixels, origin at top left
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ftex);
	glBegin(GL_QUADS);

	char* textCharValue = &text[0];
	while (*textCharValue) {
		if (*textCharValue >= 32 && *textCharValue < 128) {
			stbtt_aligned_quad q;
			stbtt_GetBakedQuad(cdata, 512, 512, *textCharValue - 32, &x, &y, &q, 1);//1=opengl & d3d10+,0=d3d9
			if (*textCharValue == 'g' || *textCharValue == 'j' || *textCharValue == 'p' || *textCharValue == 'q' || *textCharValue == 'y')
			{
				glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0 / 500, (q.y0 - 6.0f) / 500);
				glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1 / 500, (q.y0 - 6.0f) / 500);
				glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1 / 500, (q.y1 - 6.0f) / 500);
				glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0 / 500, (q.y1 - 6.0f) / 500);
			}
			else if (cdata[(int)*textCharValue - 32].yoff < -16)
			{
				glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0 / 500, (q.y0 + 4.0f) / 500);
				glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1 / 500, (q.y0 + 4.0f) / 500);
				glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1 / 500, (q.y1 + 4.0f) / 500);
				glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0 / 500, (q.y1 + 4.0f) / 500);
			}
			else
			{
				glTexCoord2f(q.s0, q.t1); glVertex2f(q.x0 / 500, q.y0 / 500);
				glTexCoord2f(q.s1, q.t1); glVertex2f(q.x1 / 500, q.y0 / 500);
				glTexCoord2f(q.s1, q.t0); glVertex2f(q.x1 / 500, q.y1 / 500);
				glTexCoord2f(q.s0, q.t0); glVertex2f(q.x0 / 500, q.y1 / 500);
			}
		}
		++textCharValue;
	}
	glEnd();
}
