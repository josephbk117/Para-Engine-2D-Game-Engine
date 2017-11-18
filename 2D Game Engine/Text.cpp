#include "Text.h"
Text::Text() {}
Text::~Text() {}

void Text::init(const std::string & fontPath,int x, int y)
{
	this->x = x;
	this->y = y;
	fread(ttf_buffer, 1, 1 << 20, fopen("Test Resources\\arial.ttf", "rb"));
	stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits!
																					 // can free ttf_buffer at this point
	glGenTextures(1, &ftex);
	glBindTexture(GL_TEXTURE_2D, ftex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	// can free temp_bitmap at this point
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Text::start()
{

}

void Text::update()
{
	my_stbtt_print(-250, 250, "Hello oio");
}
