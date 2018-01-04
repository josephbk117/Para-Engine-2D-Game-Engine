#version 140
in vec2 textureUV;
out vec4 color;
uniform sampler2D textureOne;
void main()
{
	color = texture(textureOne,textureUV);
}