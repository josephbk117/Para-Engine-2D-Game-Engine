#version 140
in vec2 textureUV;
out vec4 color;
uniform sampler2D textureOne;
void main()
{
	color = texture(textureOne,textureUV);
	float xVal = textureUV.x - 0.5;
	float  yVal = textureUV.y -0.5;
	if(sqrt(xVal*xVal + yVal*yVal)>0.4)
		color = 1.0 - color;
}