#include "ffpch.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace FireFly
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	Scope<RendererAPI> RendererAPI::s_Instance = RendererAPI::Create();

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case (API::OpenGL): return std::make_unique<OpenGLRendererAPI>();
		}

		FF_CORE_ASSERT(false, "Unknown API!");
		return nullptr;
	}

	void RendererAPI::SwitchToOtherAPI(API api)
	{
		if (api == s_API)
		{
			FF_CORE_INFO("You have been using this graphic API!");
			return;
		}
		switch (api)
		{
		case (API::OpenGL):
			s_Instance.reset(new OpenGLRendererAPI());
			s_API = API::OpenGL;
		}

		FF_CORE_ASSERT(false, "Unknown API!");
	}

	void RendererAPI::SetClearColor(float r, float g, float b, float a)
	{
		s_Instance->SetClearColorImpl(r, g, b, a);
	}

	void RendererAPI::Clear()
	{
		s_Instance->ClearImpl();
	}

	void RendererAPI::Init()
	{
		s_Instance->InitImpl();
	}

	void RendererAPI::SetViewPort(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		s_Instance->SetViewPortImpl(x, y, width, height);
	}

	void RendererAPI::DrawIndexed(unsigned int count, bool isEnableDepthTest)
	{
		s_Instance->DrawIndexedImpl(count, isEnableDepthTest);
	}

}