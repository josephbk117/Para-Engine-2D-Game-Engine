#version 140
in vec2 textureUV;
out vec4 color;
uniform sampler2D textureOne;
void main()
{
	color = texture(textureOne,textureUV);	
	float xVal =  gl_FragCoord.x/600.0;
	float yVal = gl_FragCoord.y/600.0;
	float dist = sqrt((xVal-0.5)*(xVal-0.5) + (yVal-0.5)*(yVal-0.5));	
	if(dist > 0.35)
	color = vec4(1.0 - texture(textureOne,textureUV).xyz,1.0);
	if(color .a < 0.1) discard;
}