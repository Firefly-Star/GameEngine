#type vertex
#version 430 core
layout(location = 0) in vec3 a_Position;
layout(location = 4) in vec2 a_TexCoord;

uniform mat4 u_PVmatrix;
uniform mat4 u_Modelmatrix;

out vec2 v_TexCoord;

void main()
{
	gl_Position = u_PVmatrix * u_Modelmatrix * vec4(a_Position, 1.0);
	v_TexCoord = a_TexCoord;
}

#type fragment
#version 430 core

out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D texture_diffuse1;

void main()
{
	color = texture(texture_diffuse1, v_TexCoord);
}