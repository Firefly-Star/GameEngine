#include "ffpch.h"
#include "EntryPoint.h"

#include "Application.h"

#if 0
int main(int argc, char** argv)
{
	FireFly::Log::Init();
	DEBUG_ONLY(FF_CORE_DEBUG("Configuration: Debug"););
	auto app = FireFly::CreateApplication();
	app->Run();
}
#endif

//----------------------------------
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Core/Renderer/Shader.h"
#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Texture.h"
#include "Core/Renderer/FrameBuffer.h"
int main(int argc, char** argv)
{
	using namespace FireFly;
	Log::Init();
	if (!glfwInit())
	{
		FF_CORE_ASSERT(false, "GLFW init failed");
	}
	GLFWwindow* window = glfwCreateWindow(1000, 800, "FireFly", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		FF_CORE_ASSERT(false, "Glad init failed");
	}

	Renderer::Init();
	Ref<Shader> m_Shader = Shader::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Shaders/DrawTexture.glsl");
	Ref<Shader> m_ExShader = Shader::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Shaders/FrameBufferTest.glsl");
	m_Shader->Bind();
	float vertices[] =
	{
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
	};
	Ref<VertexBuffer> m_VBO = VertexBuffer::Create(vertices, sizeof(vertices));
	unsigned int indices[] =
	{
		0, 1, 2, 
		2, 3, 0
	};
	Ref<IndexBuffer> m_IBO = IndexBuffer::Create(indices, sizeof(indices));

	m_VBO->Bind();
	m_IBO->Bind();

	Ref<BufferLayout> m_Layout = BufferLayout::Create();
	m_Layout->Push({ "Position", LayoutElementType::Float3 });
	m_Layout->Push({ "TexCoord", LayoutElementType::Float2 });
	m_Layout->UploadLayout();

	Ref<Texture> m_Texture = Texture2D::Create("C:/Users/Summer/Desktop/Game_Engine/FireFly/Sandbox/assets/Texture/Robin.jpg");
#if 1
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	unsigned int txbuffer;
	glGenTextures(1, &txbuffer);
	glBindTexture(GL_TEXTURE_2D, txbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1000, 800, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTextureParameteri(txbuffer, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(txbuffer, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, txbuffer, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1000, 800);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	FF_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer init failed!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
#if 0
	Ref<FrameBuffer> fb = FrameBuffer::Create(1000, 800, FrameBufferFormat::RGBA8, true);
	unsigned int fbo = fb->GetRendererID();
	unsigned int txbuffer = fb->GetColorAttachmentRendererID();
	unsigned int rbo = fb->GetDSAttachmentRendererID();
#endif
	FF_CORE_TRACE("fbo: {}, tx: {}, rb:{}", fbo, txbuffer, rbo);
	while (!glfwWindowShouldClose(window))
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		m_Shader->Bind();
		m_IBO->Bind();
		m_VBO->Bind();
		m_Texture->Bind(2);
		m_Shader->UploadUniform(2, "u_Texture");
		Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		Renderer::DrawIndexed(m_IBO->GetCount());
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		m_ExShader->Bind();
		m_IBO->Bind();
		m_VBO->Bind();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, txbuffer);
		m_ExShader->UploadUniform(0, "u_Texture");
		Renderer::DrawIndexed(m_IBO->GetCount(), false);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}