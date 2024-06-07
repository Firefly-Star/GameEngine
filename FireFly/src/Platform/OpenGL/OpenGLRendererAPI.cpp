#include "ffpch.h"

#include "OpenGLRendererAPI.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace FireFly
{
	static void APIENTRY OpenGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		switch (severity)
		{
		case(GL_DEBUG_SEVERITY_LOW):
			FF_CORE_WARN("OpenGL Waring({0}): {1}", id, message);
			break;
		case(GL_DEBUG_SEVERITY_HIGH):
		case(GL_DEBUG_SEVERITY_MEDIUM):
			FF_CORE_ERROR("OpenGL Error(0): {1}", id, message);
			break;
		default:
			break;
		}
	}

	void OpenGLRendererAPI::SetClearColorImpl(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::ClearImpl()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::InitImpl()
	{
		glDebugMessageCallback(OpenGLDebugMessage, nullptr);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);

		unsigned int vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
	}

	void OpenGLRendererAPI::SetViewPortImpl(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::DrawIndexedImpl(unsigned int count, bool isEnableDepthTest)
	{
		if (isEnableDepthTest)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}