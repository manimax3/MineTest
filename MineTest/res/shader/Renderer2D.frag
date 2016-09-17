#version 450 core

in vec2 texcoord;
in vec3 color;
flat in int tid;

out vec4 frag_color;

uniform sampler2D textures;
uniform float isText;

void main()
{
	vec4 texcolor = texture(textures, texcoord);
	if(isText == 1)
	{
		if(texcolor.r < 0.1)
			discard;
		else
			frag_color = vec4(color, 1.0);
	}
	else
		frag_color =  vec4(color + texcolor.rgb, 1.0);
}