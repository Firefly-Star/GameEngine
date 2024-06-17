#include "ffpch.h"

#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace FireFly
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(unsigned int width, unsigned int height, FrameBufferFormat format, bool isEnableStencil)
		:m_Width(width), m_Height(height), m_Format(format), m_IsEnableStencil(isEnableStencil), 
		m_RendererID(0), m_ColorAttachment(0), m_DSAttachment(0)
	{
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		
		glGenTextures(1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		switch (format)
		{
		case FrameBufferFormat::RGBA8: 
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); 
			break;
		case FrameBufferFormat::RGBA16F: 
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_HALF_FLOAT, nullptr); 
			break;
		default: 
			FF_CORE_ASSERT(false, "Unknown texture format!");
			break;
		}
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		glGenRenderbuffers(1, &m_DSAttachment);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DSAttachment);
		if (isEnableStencil)
		{
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		}
		else
		{
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32F, width, height);
		}
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DSAttachment);

		FF_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Failed to initialize framebuffer!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::BindTexture(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
	}

	void OpenGLFrameBuffer::BindRenderBuffer() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_DSAttachment);
	}
}