#type vertex
#version 430 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec3 a_Binormal;
layout(location = 4) in vec2 a_TexCoords;

out Vertex_Output
{
	vec3 WorldPosition;
	vec3 Normal;
	vec2 TexCoord;
	mat3 NormalMat;
} vs_Output;

uniform mat4 u_PVmatrix;
uniform mat4 u_Modelmatrix;

void main()
{
	gl_Position = u_PVmatrix * u_Modelmatrix * a_Position;
	vs_Output.WorldPosition = u_Modelmatrix * a_Position;
	vs_Output.Normal = a_Normal;
	vs_Output.TexCoord = a_TexCoords;
	vs_Output.NormalMat = mat3(u_ModelMatrix) * mat3(a_Tangent, a_Binormal, a_Normal);
}