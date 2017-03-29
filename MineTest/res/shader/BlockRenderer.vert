#version 450 core

layout (location = 0) in vec3 block_vertex;
layout (location = 1) in vec2 block_texture_coord;

layout (location = 2) in int id;
layout (location = 3) in vec3 position;

out vec2 TexCoords;
out int ID;

uniform mat4 vp;
uniform vec2 chunk_position;

void main()
{
	gl_Position = vp * vec4(block_vertex + position + vec3(chunk_position.x, 0, chunk_position.y), 1.0);
	TexCoords = block_texture_coord;
	ID = id;
}
