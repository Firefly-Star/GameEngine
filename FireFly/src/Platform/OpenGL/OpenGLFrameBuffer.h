#pragma once

#include "Core/Renderer/FrameBuffer.h"

namespace FireFly
{
	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(unsigned int width, unsigned int height, FrameBufferFormat format, bool isEnableStencil);
		virtual ~OpenGLFrameBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void BindTexture(unsigned int slot = 0) const override;
		virtual void BindRenderBuffer() const override;

		inline virtual unsigned int GetRendererID() const override { return m_RendererID; }
		inline virtual unsigned int GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		inline virtual unsigned int GetDSAttachmentRendererID() const override { return m_DSAttachment; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Width, m_Height;
		FrameBufferFormat m_Format;
		bool m_IsEnableStencil;
		unsigned int m_ColorAttachment, m_DSAttachment;
	};
}