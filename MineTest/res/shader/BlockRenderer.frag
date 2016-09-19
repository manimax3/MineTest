#version 450 core

in vec2 TexCoords;
flat in int ID;

uniform sampler2DArray textures;

out vec4 color;

void main()
{
	color = vec4(texture(textures, vec3(TexCoords, ID)));
	//color = vec4(1,1,1,1);
}