#include <FireFly.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

struct Material
{
	int texture;
	glm::vec4 color;
	glm::vec3 specular;
	float shininess;
};

struct Light
{
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class EditLayer : public FireFly::Layer
{
public:
	EditLayer()
		:Layer(){}
	virtual void OnAttach() override
	{
		m_Shader = FireFly::Shader::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly-main/Sandbox/assets/Shaders/BasicShader.glsl");
		m_Shader->Bind();
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0,

			4, 5, 6,
			6, 7, 4,

			8, 9, 10,
			10, 11, 8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20
		};
		m_IB = FireFly::IndexBuffer::Create(indices, sizeof(indices));
		float vertices[] = {
			-5.0f, -5.0f, -5.0f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
			 5.0f, -5.0f, -5.0f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
			 5.0f,  5.0f, -5.0f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
			-5.0f,  5.0f, -5.0f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,

			-5.0f, -5.0f, -5.0f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
			-5.0f, -5.0f,  5.0f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-5.0f,  5.0f,  5.0f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
			-5.0f,  5.0f, -5.0f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

			-5.0f, -5.0f,  5.0f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
			 5.0f, -5.0f,  5.0f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
			 5.0f,  5.0f,  5.0f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
			-5.0f,  5.0f,  5.0f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,

			 5.0f, -5.0f, -5.0f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
			 5.0f, -5.0f,  5.0f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
			 5.0f,  5.0f,  5.0f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
			 5.0f,  5.0f, -5.0f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

			-5.0f, -5.0f,  5.0f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
			-5.0f, -5.0f, -5.0f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
			 5.0f, -5.0f, -5.0f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
			 5.0f, -5.0f,  5.0f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,

			-5.0f,  5.0f,  5.0f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
			-5.0f,  5.0f, -5.0f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
			 5.0f,  5.0f, -5.0f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
			 5.0f,  5.0f,  5.0f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f
		};
		m_VB = FireFly::VertexBuffer::Create(vertices, sizeof(vertices));
		m_IB->Bind();
		m_VB->Bind();
		m_Texture = FireFly::Texture2D::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly-main/Sandbox/assets/Texture/Robin.jpg");
		m_PureWhiteTexture = FireFly::Texture2D::Create();
		unsigned char PWT[] = { 255, 255, 255 };
		m_PureWhiteTexture->SetTexture(PWT, 1, 1);
		m_PureWhiteTexture->Bind();
		m_Texture->Bind(1);
		m_Layout = FireFly::BufferLayout::Create();
		m_Layout->Push({ "Position", FireFly::LayoutElementType::Float3 });
		m_Layout->Push({ "TexCoord", FireFly::LayoutElementType::Float2 });
		m_Layout->Push({ "Normal", FireFly::LayoutElementType::Float3 });
		m_Layout->UploadLayout();
		m_Comtroller.SetIsEnableVRotation(true);
		m_Comtroller.SetRotationSpeed(30.0f);
		m_Comtroller.SetPanSpeed(2.0f);
		m_Material.texture = 1;
		m_Material.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_Material.specular = { 0.9f, 0.9f, 0.9f };
		m_Material.shininess = 128.0f;
	}

	virtual void OnUpdate(FireFly::Ref<FireFly::Input> input) override
	{
		float time = FireFly::TimeStep::GetTime();
		//m_Light.position = { sin(time / 2) * 5, 0.0f,cos(time / 2) * 5 - 20.0f };
		m_Light.position = { -5, 0.0f, -5.0f };
		m_Light.ambient = { 0.2f, 0.2f, 0.2f };
		m_Light.diffuse = { 0.2f, abs(sin(time)), 0.8f };
		m_Light.specular = { 0.9f, 0.9f, 0.9f };
		
		glm::mat4 modelMatrix =
			glm::translate(glm::mat4(1.0f), {0.0f, 0.0f, -20.0f}) * 
			//glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), {1.0f, 1.0f, 1.0f}) *
			glm::scale(glm::mat4(1.0f), {0.3f, 0.3f, 0.3f});
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
		m_Comtroller.OnUpdate(input);

		m_Shader->UploadUniform(m_Light.position.x, m_Light.position.y, m_Light.position.z, "u_Light.position");
		m_Shader->UploadUniform(m_Light.ambient.x, m_Light.ambient.y, m_Light.ambient.z, "u_Light.ambient");
		m_Shader->UploadUniform(m_Light.diffuse.x, m_Light.diffuse.y, m_Light.diffuse.z, "u_Light.diffuse");
		m_Shader->UploadUniform(m_Light.specular.x, m_Light.specular.y, m_Light.specular.z, "u_Light.specular");
		m_Shader->UploadUniform(m_Comtroller.GetCamera().GetPVmatrix(), "u_PVmatrix");
		m_Shader->UploadUniform(m_Comtroller.GetCamera().GetPosition().x, m_Comtroller.GetCamera().GetPosition().y, m_Comtroller.GetCamera().GetPosition().z, "u_ViewPos");

		m_Shader->UploadUniform(modelMatrix, "u_Modelmatrix");
		m_Shader->UploadUniform(normalMatrix, "u_Normalmatrix");
		m_Shader->UploadUniform(m_Material.color.x, m_Material.color.y, m_Material.color.z, m_Material.color.w, "u_Material.color");
		m_Shader->UploadUniform(m_Material.texture, "u_Material.texture");
		m_Shader->UploadUniform(m_Material.specular.x, m_Material.specular.y, m_Material.specular.z, "u_Material.specular");
		m_Shader->UploadUniform(m_Material.shininess, "u_Material.shininess");

		FireFly::Renderer::DrawIndexed(m_IB->GetCount(), true);
	}

	bool OnEvent(FireFly::Event& e) override
	{
		m_Comtroller.OnEvent(e);
		return false;
	}
private:
	FireFly::Ref<FireFly::VertexBuffer> m_VB;
	FireFly::Ref<FireFly::IndexBuffer> m_IB;
	FireFly::Ref<FireFly::Shader> m_Shader;
	FireFly::Ref<FireFly::Texture> m_Texture;
	FireFly::Ref<FireFly::Texture> m_PureWhiteTexture;
	FireFly::Ref<FireFly::BufferLayout> m_Layout;
	FireFly::PerspectiveCameraController m_Comtroller;
	Material m_Material;
	Light m_Light;
};

FireFly::Ref<FireFly::Application> FireFly::CreateApplication()
{
	FireFly::Ref<Application> app = std::make_shared<FireFly::Application>();
	
	app->PushLayer(std::make_shared<EditLayer>());

	return app;
}
