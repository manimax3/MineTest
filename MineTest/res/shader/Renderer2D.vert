#version 450 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 colorf;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in int id;

out vec2 texcoord;
out vec3 color;
out int tid;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(position, 0.0, 1.0);
	texcoord = texCoords;
	color = colorf;
	tid = id;
}