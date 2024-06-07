#include "ffpch.h"
#include "Renderer.h"

namespace FireFly
{

	RendererCommandQueue Renderer::s_CommandQueue;


	void Renderer::Init()
	{
		RendererAPI::Init();
	}

	void Renderer::Clear()
	{
		RendererAPI::Clear();
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		RendererAPI::SetClearColor(r, g, b, a);
	}

	void Renderer::DrawIndexed(unsigned int count, bool depthTest)
	{
		RendererAPI::DrawIndexed(count, depthTest);
	}

	void Renderer::SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		RendererAPI::SetViewPort(x, y, width, height);
	}

	void Renderer::Execute()
	{
		s_CommandQueue.Execute();
	}

}