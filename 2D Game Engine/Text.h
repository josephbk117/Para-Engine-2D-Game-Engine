#pragma once
#include "GuiComponent.h"
#include "stb_truetype.h"
#include "GL\glew.h"

class Text : public GuiComponent
{
public:
	Text();
	~Text();
	std::string text = "";
	float x, y;
	void init(const std::string& fontFilePath, int x, int y);
	virtual void start();
	virtual void update();
private:
	GLuint ftex;
	stbtt_bakedchar cdata[96];
	void my_stbtt_print(float x, float y)
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
};

