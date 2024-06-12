#include "ffpch.h"

#include "OpenGLFrameBuffer.h"

namespace FireFly
{
	OpenGLFrameBuffer::OpenGLFrameBuffer(unsigned int width, unsigned int height, FrameBufferFormat format)
		:m_Width(width), m_Height(height), m_Format(format), m_RendererID(0)
	{

	}
	void OpenGLFrameBuffer::Bind() const
	{
	}
	void OpenGLFrameBuffer::UnBind() const
	{
	}
	void OpenGLFrameBuffer::Resize(unsigned int width, unsigned int height)
	{
	}
	void OpenGLFrameBuffer::BindTexture(unsigned int slot) const
	{
	}

}