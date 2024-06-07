#pragma once

#include "Core/Renderer/RendererAPI.h"

namespace FireFly
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColorImpl(float r, float g, float b, float a) override;
		virtual void ClearImpl() override;
		virtual void InitImpl() override;
		virtual void SetViewPortImpl(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;

		virtual void DrawIndexedImpl(unsigned int count, bool isEnableDepthTest) override;
	};

}