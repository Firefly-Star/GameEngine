#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Tangent;
layout(location = 3) in vec3 a_Binormal;
layout(location = 4) in vec2 a_Texcoord;

out vec2 v_Texcoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_PVmatrix;

uniform mat4 u_Modelmatrix;
uniform mat3 u_Normalmatrix;
		
void main()
{
	gl_Position = u_PVmatrix * u_Modelmatrix * vec4(a_Position, 1.0);
	v_Texcoord = a_Texcoord;
	v_Normal = u_Normalmatrix * a_Normal;
	v_FragPos = vec3(u_Modelmatrix * vec4(a_Position, 1.0));
}


#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_Texcoord;
in vec3 v_Normal;
in vec3 v_FragPos;

struct Material
{
	sampler2D texture_Diffuse;
	sampler2D texture_Specular;
	vec4 color;
	float shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Light u_Light;
uniform vec3 u_ViewPos;

uniform Material u_Material;
		
void main()
{
	vec4 texcolor = texture(u_Material.texture_Diffuse, v_Texcoord) * u_Material.color;
	vec3 lightDir = normalize(u_Light.position - v_FragPos);
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	vec3 norm = normalize(v_Normal);
	color = vec4(
	u_Light.ambient * texcolor.xyz + 
	u_Light.diffuse * texcolor.xyz * max( dot(norm, lightDir), 0.0 ) +
	u_Light.specular * u_Material.specular * pow(max(dot(norm, halfwayDir), 0.0), u_Material.shininess)
	, texcolor.w);
	color = clamp(color, 0.0, 1.0);
}