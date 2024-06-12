#include "ffpch.h"

#include "FrameBuffer.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace FireFly
{
	//----------------FrameBuffer---------------
	FrameBuffer* FrameBuffer::Create(unsigned int width, unsigned int height, FrameBufferFormat format)
	{
		FrameBuffer* result = nullptr;
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::OpenGL: result = new OpenGLFrameBuffer(width, height, format);
		}
		//FrameBufferPool::GetGlobal()->Add(std::make_shared<FrameBuffer>(result));
		return result;
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