#pragma once

#include "Core/Renderer/Texture.h"

namespace FireFly
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filepath);
		OpenGLTexture2D();
		~OpenGLTexture2D();
		inline virtual unsigned int GetWidth() const override { return m_Width; }
		inline virtual unsigned int GetHeight() const override { return m_Height; }
		virtual void Bind(unsigned int slot = 0) const override;
		virtual void SetTexture(unsigned char* data, unsigned int width, unsigned int height) override;
	private:
		unsigned int m_Width, m_Height;
		unsigned int m_RendererID;
	};

}