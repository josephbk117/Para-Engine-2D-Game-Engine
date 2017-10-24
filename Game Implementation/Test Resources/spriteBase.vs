#version 140
in vec2 vertexPosition;
in vec2 texCoords;
out vec2 textureUV;
uniform mat4 model;
uniform mat4 projection;
void main()
{
	gl_Position.xy =  (projection * model * vec4(vertexPosition,0,1)).xy;
	gl_Position.z = 0;
	gl_Position.w = 1.0;
	textureUV= texCoords;
}