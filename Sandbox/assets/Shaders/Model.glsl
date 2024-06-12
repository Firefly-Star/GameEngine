#type vertex
#version 330 core
layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec3 a_Tangent;
layout (location = 3) in vec3 a_Binormal;
layout (location = 4) in vec2 a_TexCoords;

out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Modelmatrix;
uniform mat4 u_PVmatrix;
uniform mat3 u_NormalMat;

void main() 
{
    v_TexCoords = a_TexCoords;
    gl_Position = u_PVmatrix * u_Modelmatrix * vec4(a_Pos, 1.0);
    v_Normal = u_NormalMat * a_Normal;
    v_FragPos = vec3(u_Modelmatrix * vec4(a_Pos, 1.0));
}

#type fragment
#version 330 core
out vec4 FragColor;

struct Light
{
    vec3 Pos;
    
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

in vec2 v_TexCoords;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform Light u_Light;
uniform vec3 u_ViewPos;

void main() 
{
    vec4 OriginColor = texture(texture_specular1, v_TexCoords);

    vec3 Normal = normalize(v_Normal);
    vec3 LightDir = normalize(u_Light.Pos - v_FragPos);
    vec3 HalfWayDir = normalize((u_Light.Pos - v_FragPos) + (u_ViewPos - v_FragPos));

    vec3 AmbientColor = u_Light.Ambient * OriginColor.xyz;

    vec3 DiffuseColor = max(dot(Normal, LightDir), 0.0) * u_Light.Diffuse * OriginColor.xyz;

    vec3 SpecularColor = pow(max(dot(HalfWayDir, Normal), 0.0), 128) * u_Light.Specular * texture(texture_diffuse1, v_TexCoords).xyz;


    FragColor = vec4(AmbientColor + DiffuseColor + SpecularColor, 1.0);
    FragColor = clamp(FragColor, 0.0, 1.0);
    //FragColor = texture(texture_diffuse1, v_TexCoords);
    //FragColor = texture(texture_specular1, v_TexCoords);
}