#include "ffpch.h"

#include "FrameBuffer.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace FireFly
{
	//----------------FrameBuffer---------------
	Ref<FrameBuffer> FrameBuffer::Create(unsigned int width, unsigned int height, FrameBufferFormat format, bool isEnableStencil)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLFrameBuffer>(width, height, format, isEnableStencil);
		}
		//FrameBufferPool::GetGlobal()->Add(std::make_shared<FrameBuffer>(result));
		return nullptr;
	}

	//----------------FrameBufferPool-----------------

	Ref<FrameBufferPool> FrameBufferPool::s_Instance = std::make_shared<FrameBufferPool>();

	FrameBufferPool::FrameBufferPool(unsigned int maxFBs)
	{
	}

	std::weak_ptr<FrameBuffer> FrameBufferPool::AllocateBuffer()
	{
		return std::weak_ptr<FrameBuffer>();
	}

	void FrameBufferPool::Add(Ref<FrameBuffer> frameBuffer)
	{
		m_Pool.push_back(frameBuffer);
	}

}