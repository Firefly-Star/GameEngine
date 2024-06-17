#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 430 core

out vec4 color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	color =  vec4(vec3(1.0 - texture(u_Texture, v_TexCoord)), 1.0);
}