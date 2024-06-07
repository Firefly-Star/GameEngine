#include "ffpch.h"
#include "RendererCommandQueue.h"

#if 1
namespace FireFly
{
	RendererCommandQueue::RendererCommandQueue()
		:m_CommandCount(0)
	{
		m_OriginCommandBuffer = new byte[FF_COMMAND_BUFFER_SIZE];
		auto padding = (size_t)m_OriginCommandBuffer % 8;

		m_CommandBuffer = m_OriginCommandBuffer;
		if (padding != 0) // alignment of 8
		{
			m_CommandBuffer = m_OriginCommandBuffer + 8 - padding;
		}
		m_CommandBufferWorkPtr = m_CommandBuffer;
		memset(m_CommandBuffer, 0, FF_COMMAND_BUFFER_SIZE);
	}

	RendererCommandQueue::~RendererCommandQueue()
	{
		delete[] m_OriginCommandBuffer;
		m_OriginCommandBuffer = nullptr;
		m_CommandBuffer = nullptr;
		m_CommandBufferWorkPtr = nullptr;
	}

	void* RendererCommandQueue::Allocate(RenderCommandFn fn, unsigned int size, unsigned int alignment)
	{
		// TODO: alignment
		*(RenderCommandFn*)m_CommandBufferWorkPtr = fn;
		m_CommandBufferWorkPtr += sizeof(RenderCommandFn);

		*(unsigned int*)m_CommandBufferWorkPtr = size;
		m_CommandBufferWorkPtr += sizeof(unsigned int);

		// alignment
		*(unsigned int*)m_CommandBufferWorkPtr = alignment;
		m_CommandBufferWorkPtr += sizeof(unsigned int);

		// alignment when memcpy
		{
			auto padding = (size_t)m_CommandBufferWorkPtr % alignment;
			if (padding != 0)
			{
				m_CommandBufferWorkPtr += alignment - padding;
			}
		}

		void* memory = m_CommandBufferWorkPtr;
		m_CommandBufferWorkPtr += size;

		// alignment for the next command
		{
			auto padding = (size_t)m_CommandBufferWorkPtr % 8;
			if (padding != 0)
			{
				m_CommandBufferWorkPtr += 8 - padding;
			}
		}

		m_CommandCount++;
		return memory;
	}

	void RendererCommandQueue::Execute()
	{
		//FF_CORE_TRACE("Renderer Command Queue: {0}commands, {1}bytes", m_CommandCount, m_CommandBufferWorkPtr - m_CommandBuffer);
		byte* workPtr = m_CommandBuffer;

		for (unsigned int i = 1; i <= m_CommandCount; i++)
		{
			// function
			RenderCommandFn func = *(RenderCommandFn*)workPtr;
			workPtr += sizeof(RenderCommandFn);
			// size
			unsigned int size = *(unsigned int*)workPtr;
			workPtr += sizeof(unsigned int);
			FF_CORE_TRACE("Executing the command at index {}, size:{}, sizePtr:{}", i, *(unsigned int*)workPtr, (size_t)workPtr);
			//alignment
			unsigned int alignment = *(unsigned int*)workPtr;
			workPtr += sizeof(unsigned int);

			// alignment when memcpy
			{
				auto padding = (size_t)workPtr % alignment;
				if (padding != 0)
				{
					workPtr += alignment - padding;
				}
			}
			// params
			func(workPtr);
			workPtr += size;

			// alignment for the next command
			{
				auto padding = (size_t)workPtr % 8;
				if (padding != 0)
				{
					workPtr += 8 - padding;
				}
			}
		}

		m_CommandBufferWorkPtr = m_CommandBuffer;
		m_CommandCount = 0;
	}

}
#endif