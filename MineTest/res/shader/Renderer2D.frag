#version 450 core

in vec2 texcoord;
in vec3 color;
flat in int tid;

out vec4 frag_color;

uniform sampler2D textures[30];

void main()
{
	//  * vec4(color, 1.0)
	frag_color = texture(textures[tid], vec2(texcoord));
}