#version 140
in vec2 textureUV;
out vec4 color;
uniform sampler2D textureOne;
uniform float brightness;
void main()
{
	color = texture(textureOne,textureUV);	
	color = brightness+ color;	
}