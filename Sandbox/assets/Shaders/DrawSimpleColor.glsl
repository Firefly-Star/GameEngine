#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;

void main()
{
	gl_Position = a_Position;
}

#type fragment
#version 430 core

out vec4 color;

void main()
{
	color = vec4(0.2f, 0.3f, 0.6f, 1.0f);
}