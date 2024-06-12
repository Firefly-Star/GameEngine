#pragma once

#include "Core/Renderer/FrameBuffer.h"

namespace FireFly
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(unsigned int width, unsigned int height, FrameBufferFormat format);
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void Resize(unsigned int width, unsigned int height) override;
		virtual void BindTexture(unsigned int slot = 0) const override;

		inline virtual unsigned int GetRendererID() const override { return m_RendererID; }
		inline virtual unsigned int GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		inline virtual unsigned int GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Width, m_Height;
		FrameBufferFormat m_Format;

		unsigned int m_ColorAttachment, m_DepthAttachment;
	};
}